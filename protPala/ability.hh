#ifndef _ABILITY_HH_
#define _ABILITY_HH_

#include "stats.hh"
// #include "enums.hh"
#include <string>

class Ability {
public:
  Ability(std::string, MagicSchool);
  Ability(const Ability &);
  ~Ability() = default;

  void set_dps(double in) { averageDps_ = in; }
  void set_casttime(double in) { castTime_ = in; }
  void set_dot(bool in) { dot_ = in; }
  void set_uptime(unsigned int in) { uptime_ = in; }
  void set_procc_chance(double in){proccChance_=in;}
  void set_debuff(PrimaryStats, SecondaryStats);
  void set_debuff(PrimaryStats);
  void set_cooldown(double in) { cooldown_ = in; }
  void set_damage(double in) { damage_ = in; }
  std::string get_name() const { return name_; }
  MagicSchool get_school() const { return school_; }
  double get_average_dps() const { return averageDps_; }
  double get_damage() const { return damage_; }
  double get_cast_time() const { return castTime_; }
  double get_cd() const { return cooldown_; }
  bool is_dot() const { return dot_; }
  unsigned int get_uptime() const { return uptime_; }
  double get_procc_chance() const { return proccChance_; }
  PrimaryStats get_prim_debuff() const { return primDebuff_; }
  SecondaryStats get_sec_debuff() const { return secDebuff_; }
  void operator=(Ability);

private:
  std::string name_;
  MagicSchool school_;
  double averageDps_;
  double damage_;
  double castTime_;
  double cooldown_;
  double proccChance_;
  bool dot_;
  unsigned int uptime_;
  PrimaryStats primDebuff_;
  SecondaryStats secDebuff_;
};

#endif
