#ifndef _CHARACTER_HH_
#define _CHARACTER_HH_

#include "NPCs.hh"
#include "buffs.hh"
#include "equipment.hh"
#include "stats.hh"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Character {
public:
  Character(string, string);
  ~Character() = default;

  void set_encounter(Boss, unsigned int);
  void set_boss(Boss in) { boss = in; }
  void set_n_ally_dd(unsigned int in) { n_dd = in; }
  void get_raid_buffed();
  void print_buffs();
  double get_time_of_encounter() { return time_needed; }
  double get_eff_hp(double time_in_seconds_ = 0.0);
  double get_avoidance();
  double get_crush();
  void set_talent(string, unsigned int);
  double get_dodge_chance();
  double get_dodge_chance_with_dr();
  unsigned int get_armor();
  double get_armor_reduction();
  double get_parry();
  double get_missed();
  double get_block();
  void equip(Gear);
  double red_chance_to_get_crit();
  double get_tps();
  void compute_stats();
  void print_gear();
  double get_spell_hit_chance();
  double get_effective_redoubt_chance();
  double check_block_chance(double);
  double get_spell_crit_chance();
  double get_hp();
  double get_mp();
  unsigned int get_defense();
  unsigned int get_block_value();
  void print_base_stats();
  vector<Elixir> get_elixirs() { return elixirs; }
  void add_elixir(Elixir);
  void print_elixirs();
  void find_best_gems(Gear *, vector<Socket> *); // to do
  double get_hps();                              // to do
  void reset_boni();
  double average_resistance(string);
  bool survives_worst_case_szenario();
  Boss get_encounter() { return boss; }
  unsigned int get_n_dds() { return n_dd; }
  void add_buff(Buff);
  void operator=(Character);
  map<string, unsigned int> talents;
  string class_, race_;
  PrimaryStats base_stats;
  PrimaryStats primary_stats;
  PrimaryStats bonus_prim_stats;
  SecondaryStats secondary_stats;
  SecondaryStats bonus_sec_stats;
  unsigned int defense, expertise, level;
  double dodge, parry, block_chance, crit, spell_crit, hit, spell_hit;
  double r_expertise, r_hit, r_spell_hit, r_crit, r_haste, r_armor_pen, r_def, r_def_avoidance, r_dodge, r_parry, r_block, r_resilience, c_d, c_p, c_m, k, my_r_dodge;
  double f_expertise, f_hit, f_spell_hit, f_crit, f_haste, f_armor_pen, f_def, f_def_avoidance, f_dodge, f_parry, f_block, f_resilience, h, my_h;
  map<string, Gear> gear;
  unsigned int number_of_rings = 0;
  unsigned int number_of_trinkets = 0;

private:
  vector<Elixir> elixirs;
  vector<Buff> buffs;
  Boss boss;
  unsigned int n_dd; // DDs in group/raid
  double time_needed;
  bool kings = false;
  bool sanctuary = false;
};

#endif
