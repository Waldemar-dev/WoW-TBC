#ifndef NPCS_HH_
#define NPCS_HH_

#include "ability.hh"
#include "stats.hh"
#include <vector>

using namespace std;

class WorstCaseSzenario {
public:
  WorstCaseSzenario() = default;
  ~WorstCaseSzenario() = default;

  void set_n_hits(unsigned int in) { n_hits = in; }
  void set_dmg_per_hit(double in) { dmg_per_hit = in; }
  void set_magic_dmg(string, double);
  unsigned int get_n_hits() { return n_hits; }
  double get_white_dmg() { return dmg_per_hit; }
  double get_magic_dmg() { return magic_dmg; }
  string get_magic_school() { return magic_school; }
  void operator=(WorstCaseSzenario);

private:
  unsigned int n_hits = 0;
  double dmg_per_hit = 0;
  string magic_school = "";
  double magic_dmg = 0;
};

class Boss {
public:
  Boss() = default;
  ~Boss() = default;

  void set_name(string in) { name = in; }
  string get_name() { return name; }
  void set_prim_stats(PrimaryStats in) { primary_stats = in; }
  void set_sec_stats(SecondaryStats in) { secondary_stats = in; }
  void add_ability(Ability in) { abilities.push_back(in); }
  void set_lvl(unsigned int in) { lvl = in; }
  unsigned int get_lvl() { return lvl; }
  double get_attack_speed() { return primary_stats.attack_speed; }
  double get_attack_damage() { return primary_stats.weapondamage; }
  double get_health() { return primary_stats.health; }
  PrimaryStats get_primary_stats() { return primary_stats; }
  SecondaryStats get_secondary_stats() { return secondary_stats; }
  vector<Ability> get_abilities() { return abilities; }
  double get_max_white_hit() { return max_white_dmg; }
  WorstCaseSzenario *get_worst_case_szenario() { return &worst_case; }
  void operator=(Boss);

private:
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
  vector<Ability> abilities;
  string name;
  double max_white_dmg;
  unsigned int lvl;
  WorstCaseSzenario worst_case;
};

class Attumen : public Boss {
public:
  Attumen();

private:
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
};

class Midnight : public Boss {
public:
  Midnight();

private:
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
};

class PrinceMalchezaar : public Boss {
public:
  PrinceMalchezaar();

private:
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
};

#endif
