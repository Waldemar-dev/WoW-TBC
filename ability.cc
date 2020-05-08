#include "ability.hh"

Ability::Ability(string name_, string school_) {
  name = name_;
  school = school_;
}

void Ability::operator=(Ability in) {
  name = in.get_name();
  school = in.get_school();
  average_dps = in.get_average_dps();
  damage = in.get_damage();
  cast_time = in.get_cast_time();
  cooldown = in.get_cd();
  dot = in.is_dot();
  uptime = in.get_uptime();
  procc_chance = in.get_procc_chance();
  prim_debuff = in.get_prim_debuff();
  sec_debuff = in.get_sec_debuff();
}

void Ability::set_debuff(PrimaryStats prim) {
  SecondaryStats temp;
  set_debuff(prim, temp);
}

void Ability::set_debuff(PrimaryStats prim, SecondaryStats sec) {
  prim_debuff = prim;
  sec_debuff = sec;
}
