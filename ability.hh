#ifndef _ABILITY_HH_
#define _ABILITY_HH_

#include "stats.hh"
#include <string>

using namespace std;

class Ability {
public:
  Ability(string, string);
  ~Ability() = default;

  void set_dps(double in) { average_dps = in; }
  void set_casttime(double in) { cast_time = in; }
  void set_dot(bool in) { dot = in; }
  void set_uptime(unsigned int in) { uptime = in; }
  void set_procc_chance(double in);
  void set_debuff(PrimaryStats, SecondaryStats);
  void set_debuff(PrimaryStats);
  void set_cooldown(double in) { cooldown = in; }
  void set_damage(double in) { damage = in; }
  string get_name() { return name; }
  string get_school() { return school; }
  double get_average_dps() { return average_dps; }
  double get_damage() { return damage; }
  double get_cast_time() { return cast_time; }
  double get_cd() { return cooldown; }
  bool is_dot() { return dot; }
  unsigned int get_uptime() { return uptime; }
  double get_procc_chance() { return procc_chance; }
  PrimaryStats get_prim_debuff() { return prim_debuff; }
  SecondaryStats get_sec_debuff() { return sec_debuff; }
  void operator=(Ability);

private:
  string name;
  string school;
  double average_dps;
  double damage;
  double cast_time;
  double cooldown;
  bool dot;
  unsigned int uptime;
  double procc_chance;
  PrimaryStats prim_debuff;
  SecondaryStats sec_debuff;
};

#endif
