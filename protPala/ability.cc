#include "ability.hh"

Ability::Ability(std::string inName, MagicSchool inSchool) : name_(inName), school_(inSchool), averageDps_(0), damage_(0), castTime_(0), cooldown_(0), proccChance_(0), dot_(false), uptime_(0){
}

Ability::Ability(const Ability& in): name_(in.get_name()), school_(in.get_school()), averageDps_(in.get_average_dps()), damage_(get_damage()), castTime_(in.get_cast_time()), cooldown_(in.get_cd()), proccChance_(in.get_procc_chance()), dot_(in.is_dot()), uptime_(in.get_uptime()){

}

void Ability::operator=(Ability in) {
  name_ = in.get_name();
  school_ = in.get_school();
  averageDps_ = in.get_average_dps();
  damage_ = in.get_damage();
  castTime_ = in.get_cast_time();
  cooldown_ = in.get_cd();
  dot_ = in.is_dot();
  uptime_ = in.get_uptime();
  proccChance_ = in.get_procc_chance();
  primDebuff_ = in.get_prim_debuff();
  secDebuff_ = in.get_sec_debuff();
}

void Ability::set_debuff(PrimaryStats prim) {
  SecondaryStats temp;
  set_debuff(prim, temp);
}

void Ability::set_debuff(PrimaryStats prim, SecondaryStats sec) {
  primDebuff_.set_stats(prim);
  secDebuff_.set_stats(sec);
}
