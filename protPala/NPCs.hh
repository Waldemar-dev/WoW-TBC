#ifndef NPCS_HH_
#define NPCS_HH_

class Character;
#include "ability.hh"
#include "stats.hh"
#include "Character.hh"
#include "equipment.hh"
#include <vector>
#include <map>
#include <unordered_map>

class WorstCaseSzenario
{
public:
  WorstCaseSzenario();
  ~WorstCaseSzenario() = default;

  void set_n_hits(double in) { nHits_ = in; }
  void set_dmg_per_hit(double in) { dmgPerHit_ = in; }
  void set_magic_dmg(MagicSchool, double);
  unsigned int get_n_hits() { return nHits_; }
  double get_max_damage(Character *);
  double get_white_dmg() { return dmgPerHit_; }
  double get_yellow_dmg() { return physicalAbilityDmg_; }
  std::vector<double> get_magic_dmg() { return magicDmg_; }
  std::vector<MagicSchool> get_magic_school() { return magicSchool_; }
  void set_sunder_armor(unsigned int in)
  {
    sunderArmorDebuff_ = in;
    sunderArmor_ = true;
  }
  void set_amplify_damage(double in) { multiplier_ = in; }
  void set_phys_ability_damage(double in) { physicalAbilityDmg_ = in; }
  void operator=(WorstCaseSzenario);

private:
  double nHits_;
  double dmgPerHit_;
  std::vector<MagicSchool> magicSchool_;
  std::vector<double> magicDmg_;
  bool sunderArmor_;
  unsigned int sunderArmorDebuff_;
  double multiplier_;
  double physicalAbilityDmg_;
};

class Boss
{
public:
  Boss(std::string, double, double);
  ~Boss() = default;

  void set_name(std::string in) { name_ = in; }
  std::string get_name() { return name_; }
  void set_effective_swing_timer(double in) { effectiveSwingTimer_ = in; }
  void set_prim_stats(PrimaryStats in) { primaryStats_ = in; }
  void set_sec_stats(SecondaryStats in) { secondaryStats_ = in; }
  void set_prim_stat(PrimaryAttributes inIndex, double inValue) { primaryStats_.set_stat(inIndex, inValue); }
  void set_sec_stat(SecondaryAttributes inIndex, double inValue) { secondaryStats_.set_stat(inIndex, inValue); }
  void set_max_white_dmg(double in) { maxWhiteDmg_ = in; }
  void set_min_white_dmg(double in) { minWhiteDmg_ = in; }
  void add_ability(Ability in) { abilities_.push_back(in); }
  void set_lvl(unsigned int in) { lvl_ = in; }
  void add_worst_case_scenario(WorstCaseSzenario in) { worstCase_.push_back(in); }
  void set_raid_dps(double in) { raidDps_ = in; }
  void add_phase_threshold(double in) { phaseThresholds_.push_back(in); }
  unsigned int get_lvl() { return lvl_; }
  double get_attack_speed() { return get_prim_stat(PrimaryAttributes::AttackSpeed); }
  double get_attack_damage() { return get_prim_stat(PrimaryAttributes::WeaponDamage); }
  double get_health() { return get_prim_stat(PrimaryAttributes::Health); }
  double get_block_chance(){return blockChance_;}
  double get_parry_chance(){return parryChance_;} // assumption
  double get_max_white_hit() { return maxWhiteDmg_; }
  double get_min_white_hit() { return minWhiteDmg_; }
  double getDamageReductionFromArmor(unsigned int player_level, unsigned int armor_pen = 0);
  double get_eff_swing_timer() { return effectiveSwingTimer_; }
  double get_raid_dps() { return raidDps_; }
  double get_prim_stat(PrimaryAttributes inIndex) { return primaryStats_.get_stat(inIndex); }
  double get_sec_stat(SecondaryAttributes inIndex) { return secondaryStats_.get_stat(inIndex); }
  virtual double get_total_damage_dealt(Character *) { return 0; }
  std::vector<double> get_phase_thresholds() { return phaseThresholds_; }
  std::unordered_map<MagicSchool, double, std::hash<int>> get_magic_dps()
  {
    std::unordered_map<MagicSchool, double, std::hash<int>> result;
    return result;
  }
  std::vector<WorstCaseSzenario> *get_worst_case_szenario() { return &worstCase_; }
  PrimaryStats get_primary_stats() { return primaryStats_; }
  SecondaryStats get_secondary_stats() { return secondaryStats_; }
  std::vector<Ability> get_abilities() { return abilities_; }
  void set_average_dps_vec(std::vector<double> in) { averageDpsVec_ = in; }
  std::vector<double> get_average_dps_vec() { return averageDpsVec_; }
  void operator=(Boss);

private:
  PrimaryStats primaryStats_;
  SecondaryStats secondaryStats_;
  std::vector<Ability> abilities_;
  std::string name_;
  double minWhiteDmg_, maxWhiteDmg_;
  unsigned int lvl_;
  std::vector<WorstCaseSzenario> worstCase_;
  double effectiveSwingTimer_;
  double raidDps_;
  std::vector<double> phaseThresholds_;
  std::vector<double> averageDpsVec_;
  double blockChance_;
  double parryChance_;
};

class Attumen : public Boss
{
public:
  Attumen();
  ~Attumen() = default;

  std::unordered_map<MagicSchool, double, std::hash<int>> get_magic_dps();
  double get_total_damage_dealt() { return -1; } // to do
};

class Midnight : public Boss
{
public:
  Midnight();
  ~Midnight() = default;

  std::unordered_map<MagicSchool, double, std::hash<int>> get_magic_dps();
  double get_total_damage_dealt() { return -1; } // to do
  // private:
  //   PrimaryStats primary_stats;
  //   SecondaryStats secondary_stats;
};

class PrinceMalchezaar : public Boss
{
public:
  PrinceMalchezaar();
  ~PrinceMalchezaar() = default;

  std::unordered_map<MagicSchool, double, std::hash<int>> get_magic_dps();
  double get_total_damage_dealt(Character *);
  bool useless_gear(Gear*, Character*);

private:
  unsigned int sunderArmorDebuff_ = 0;
  double get_phase_1_damage(Character*);
  double get_phase_2_damage(Character*);
  double get_phase_3_damage(Character*);
};

class Hydros : public Boss
{
public:
  Hydros();
  ~Hydros() = default;

  std::unordered_map<MagicSchool, double, std::hash<int>> get_magic_dps();
  double get_total_damage_dealt() { return -1; } // to do
  // private:
  //   PrimaryStats primary_stats;
  //   SecondaryStats secondary_stats;
};

#endif
