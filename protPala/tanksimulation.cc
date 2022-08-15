#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TMath.h"
#include <climits>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

double effective_block_chance_increase(unsigned int points, double avoidance, double base_block_chance) {
  double x1 = 40 - base_block_chance;
  double x2 = 100 - base_block_chance;
  double y1 = base_block_chance / 100.0 + 0.206309 - x1 * 0.00185542;
  double y2 = base_block_chance / 100.0;
  if (avoidance < x1) {
    return 0.206309 - avoidance * 0.00185542;
  } else if (avoidance >= x1 && avoidance < x2) {
    double c = 0.645623 * base_block_chance / 100.0 + 0.348888;
    double b = 0.00365483 * base_block_chance / 100.0 - 0.00675105;
    double a = -6.66862 * TMath::Power(10, -6) * base_block_chance / 100.0 + 3.2928 * TMath::Power(10, -5);
    double result = a * avoidance * avoidance + b * avoidance + c - base_block_chance / 100.0;
    return result;
  }
  return 0;
}

class Boss {
public:
  Boss() = default;
  ~Boss() = default;
  double get_attack_speed() { return attack_speed; }
  double get_attack_damage() { return attack_damage; }
  unsigned int get_level() { return level; }

private:
  double attack_speed = 2.0;
  double attack_damage = 1000;
  unsigned int level = 73;
};

class SimpleCharacter {
public:
  SimpleCharacter() = default;
  ~SimpleCharacter() = default;
  void set_dodge(double in) { dodge_chance = in; }
  void set_block_chance(double in) { block_chance = in; }
  void set_block_value(double in) { block_value = in; }
  void set_hp(double in) { hp = in; }
  void get_damage(double);
  void heal(double);
  void blocked();
  void reset_hp() { hp = max_hp; }
  void reset();
  void reset_buff();
  double get_hp() { return hp; }
  double get_max_hp() { return max_hp; }
  double get_dodge() { return dodge_chance; }
  double get_parry() { return parry_chance; }
  double get_missed() { return miss_chance; }
  double get_armor_reduction() { return armor_reduction; }
  double get_block_chance();
  double get_block_value() { return block_value; }
  double get_hps() { return hps; }
  unsigned int get_blocked_attacks() { return blocked_attacks; }
  unsigned int get_charges() { return block_charges; }
  unsigned int get_level() { return level; }
  bool was_procc_activated();
  bool is_procc_active() { return procc_active; }

private:
  double dodge_chance = 0.0;
  double parry_chance = 0.0;
  double miss_chance = 0.0;
  double armor_reduction = 0.5;
  double block_chance = 0.5;
  double block_value = 10;
  double max_hp = 10000;
  double hp = max_hp;
  double hps = 5;
  unsigned int block_charges = 0;
  unsigned int blocked_attacks = 0;
  unsigned int level = 70;
  bool procc_active = false;
  bool procc_activated = false;
};

void SimpleCharacter::reset_buff() {
  if (procc_active) {
    procc_active = false;
    procc_activated = false;
    block_charges = 0;
    block_chance -= 0.3;
  }
}

bool SimpleCharacter::was_procc_activated() {
  bool result = false;
  if (procc_activated) {
    result = true;
    procc_activated = false;
  }
  return result;
}

void SimpleCharacter::get_damage(double in) {
  hp -= in;
  if (hp < 0) {
    hp = 0;
  }
  double rnd_number = ((double)rand()) / ((double)RAND_MAX);
  if (rnd_number <= 0.1) {
    if (!procc_active) {
      block_chance += 0.3;
    }
    block_charges = 5;
    procc_active = true;
    procc_activated = true;
  }
}

void SimpleCharacter::heal(double in) {
  if (hp < max_hp) {
    hp += in;
    if (hp > max_hp) {
      reset_hp();
    }
  }
}

double SimpleCharacter::get_block_chance() {
  double result = block_chance;
  if (block_charges > 0) {
    result = block_chance + 0.3;
  }
  if (result > 1) {
    result = 1;
  }
  return result;
}

void SimpleCharacter::blocked() {
  if (block_charges > 0) {
    block_charges--;
    if (block_charges == 0) {
      block_chance -= 0.3;
      procc_active = false;
    }
  }
  blocked_attacks++;
}

void SimpleCharacter::reset() {
  hp = max_hp;
  block_charges = 0;
  blocked_attacks = 0;
  if (procc_active) {
    procc_activated = false;
    procc_active = false;
    block_chance -= 0.3;
  }
}

int main() {
  TFile *my_file = new TFile("tanksimulation_data.root", "RECREATE");
  Boss some_boss;
  SimpleCharacter some_character;

  TGraphErrors *hp_simulated = new TGraphErrors();
  hp_simulated->SetTitle("Damage dealt;avoidance/%;damage output");
  TGraph *hp_calc = new TGraph();
  hp_calc->SetTitle("Effective HP predicted by model;avoidance/%;HP");
  TGraphErrors *hp_diff = new TGraphErrors();
  hp_diff->SetTitle("relative difference between effective HP and boss damage;avoidance/%;(data-model)/data");
  double red_chi_sq_hp_diff = 0;
  double chi_sq_temp = 0;
  TGraphErrors *block_procc_graph = new TGraphErrors();
  block_procc_graph->SetTitle("Mean block chance;avoidance/%;block chance");
  TGraph *timeout_graph = new TGraph();
  timeout_graph->SetTitle("Number of times N 'Redoubt' timed out;avoidance/%;N");
  TGraph *relative_timeout_graph = new TGraph();
  relative_timeout_graph->SetTitle("relative timeout graph;avoidance/%;timeouts/activations");
  TGraph *block_model = new TGraph();
  block_model->SetTitle("Prediction of the model;avoidance/%;effective block chance");
  TGraphErrors *block_model_difference = new TGraphErrors();
  block_model_difference->SetTitle("Realtive difference between data and model;avoidance/%;(data-model)/data");
  srand(time(NULL));
  double eff_hp;
  unsigned int counter2 = 0;
  double time_of_encounter = 60 * 60.0;
  for (uint j = 0; j < 95; j += 2) {
    some_character.set_dodge(((double)j) / 100.0);
    if (some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() >= 1) {
      continue;
    }
    if (some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() + some_character.get_block_chance() > 1) {
      some_character.set_block_chance(1 - some_character.get_dodge() - some_character.get_parry() - some_character.get_missed());
    }
    TH1D *hist_damage_dealt = new TH1D("damage dealt", "damage enemy dealt;Damage output", 100, 0, 0);
    TH1D *hist_hp_calc = new TH1D("calculated hp", "calculated effective health;eff HP", 100, 0, 0);
    TH1D *hist_hp_diff = new TH1D("diff", "difference of damage dealt and calculated eff. hp; difference", 100, 0, 0);
    TH1D *hist_blocked = new TH1D("blocked", "blocked attacks;blocked/total attacks", 100, 0, 0);
    unsigned int timeout = 0;
    unsigned int activations = 0;
    double time_since_procc = 0.0;

    for (uint i = 0; i < 20000; i++) {
      some_character.reset_hp();
      vector<double> combat_log;
      unsigned int damage_output = 0;
      while (some_character.get_hp() > 0) {
        if (some_character.is_procc_active()) {
          time_since_procc += some_boss.get_attack_speed();
          if (time_since_procc >= 10.0) {
            some_character.reset_buff();
            time_since_procc = 0.0;
            timeout++;
          }
        }
        some_character.heal(some_boss.get_attack_speed() * some_character.get_hps());
        double rnd_number = ((double)rand()) / ((double)RAND_MAX);
        if (rnd_number <= some_character.get_dodge() + some_character.get_parry() + some_character.get_missed()) {
          // combat_log.push_back(0);
        } else if (rnd_number > some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() &&
                   rnd_number <= some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() + some_character.get_block_chance()) {
          // combat_log.push_back(some_boss.get_attack_damage() * some_character.get_armor_reduction() - some_character.get_block_value());
          some_character.get_damage(some_boss.get_attack_damage() * some_character.get_armor_reduction() - some_character.get_block_value());
          some_character.blocked();
        } else if (rnd_number > some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() + some_character.get_block_chance() &&
                   rnd_number <= some_character.get_dodge() + some_character.get_parry() + some_character.get_missed() + some_character.get_block_chance() +
                                     0.02 * (some_boss.get_level() - some_character.get_level()) - 0.15) {
          some_character.get_damage(some_boss.get_attack_damage() * some_character.get_armor_reduction() * 1.5);
        } else {
          // combat_log.push_back(some_boss.get_attack_damage() * some_character.get_armor_reduction());
          some_character.get_damage(some_boss.get_attack_damage() * some_character.get_armor_reduction());
        }
        damage_output += some_boss.get_attack_damage();
        if (some_character.was_procc_activated()) {
          time_since_procc = 0.0;
          activations++;
        }
        if (damage_output / some_boss.get_attack_damage() > time_of_encounter / some_boss.get_attack_speed() || damage_output > 0.8 * UINT_MAX) {
          break;
        }
        /*if (combat_log.size() > time_of_encounter / some_boss.get_attack_speed()) {
          break;
        }*/
      }
      double attacks_done = damage_output / (double)some_boss.get_attack_damage();
      hist_blocked->Fill(some_character.get_blocked_attacks() / attacks_done);
      some_character.reset();
      hist_damage_dealt->Fill(attacks_done * some_boss.get_attack_damage());
      eff_hp = (some_character.get_max_hp() +
                (some_character.get_block_chance() + effective_block_chance_increase(5, j, some_character.get_block_chance() * 100.0)) * some_character.get_block_value() * attacks_done +
                some_character.get_hps() * attacks_done * some_boss.get_attack_speed()) /
               (1 - some_character.get_armor_reduction()) / (1 - some_character.get_dodge() - some_character.get_parry() - some_character.get_missed());
      hist_hp_calc->Fill(eff_hp);
      hist_hp_diff->Fill(attacks_done * some_boss.get_attack_damage() - eff_hp);
      chi_sq_temp += pow(attacks_done * some_boss.get_attack_damage() - eff_hp, 2);
      cout << "data=" << attacks_done * some_boss.get_attack_damage() << endl;
      cout << "model=" << eff_hp << endl;
      cout << "difference=" << attacks_done * some_boss.get_attack_damage() - eff_hp << endl;
    }
    some_character.reset();
    cout << "nominator=" << chi_sq_temp << endl;
    cout << "std dev=" << hist_damage_dealt->GetStdDev() << endl;
    chi_sq_temp /= pow(hist_damage_dealt->GetStdDev(), 2);
    red_chi_sq_hp_diff += chi_sq_temp;
    chi_sq_temp = 0.0;
    cout << "block chance=" << some_character.get_block_chance() << endl;

    block_procc_graph->SetPoint(counter2, j, hist_blocked->GetMean());
    block_procc_graph->SetPointError(counter2, 0, hist_blocked->GetMean(11));
    timeout_graph->SetPoint(counter2, j, timeout);
    relative_timeout_graph->SetPoint(counter2, j, timeout / (double)activations);
    block_model->SetPoint(counter2, j, effective_block_chance_increase(5, j, some_character.get_block_chance() * 100.0) + some_character.get_block_chance());
    block_model_difference->SetPoint(
        counter2, j, (hist_blocked->GetMean() - effective_block_chance_increase(5, j, some_character.get_block_chance() * 100.0) - some_character.get_block_chance()) / hist_blocked->GetMean());
    block_model_difference->SetPointError(counter2, 0,
                                          (effective_block_chance_increase(5, j, some_character.get_block_chance() * 100.0) + some_character.get_block_chance()) * hist_blocked->GetMean(11) /
                                              pow(hist_blocked->GetMean(), 2));
    hist_hp_calc->Write();
    hist_hp_diff->Write("hp difference");
    hist_blocked->Write("blocked attacks");
    hist_damage_dealt->Write("damage dealt");
    // TF1 *poisson_fit = new TF1("poisson_fit", "TMath::Poisson(x+[2],[0])*[1]", 0, 0);
    // poisson_fit->SetParameters(1, 120000, 200);
    // hist_damage_dealt->Fit("poisson_fit");
    hp_simulated->SetPoint(counter2, j, hist_damage_dealt->GetMean());
    hp_simulated->SetPointError(counter2, 0, hist_damage_dealt->GetMean(11));
    hp_calc->SetPoint(counter2, j, hist_hp_calc->GetMean());
    hp_diff->SetPoint(counter2, j, (hist_damage_dealt->GetMean() - hist_hp_calc->GetMean()) / hist_damage_dealt->GetMean());
    hp_diff->SetPointError(counter2, 0, (hist_damage_dealt->GetMean(11) / pow(hist_damage_dealt->GetMean(), 2)) * hist_hp_calc->GetMean());
    counter2++;
    // abort();
  }
  hp_simulated->Write("simulated hp graph");
  hp_calc->SetLineColor(kRed);
  hp_calc->Write("calculated hp graph");
  hp_diff->Write("hp model difference");
  block_procc_graph->Write("block chance vs avoidance");
  timeout_graph->Write("timeouts");
  relative_timeout_graph->Write("relative timeouts");
  block_model->SetLineColor(kRed);
  block_model->Write("Block Model");
  block_model_difference->Write("block model difference");
  red_chi_sq_hp_diff /= (counter2 - 1);
  cout << "red_chi_sq_hp_diff=" << red_chi_sq_hp_diff << endl;
  my_file->Close();
  return 0;
}
