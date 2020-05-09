#include "NPCs.hh"

using namespace std;

void WorstCaseSzenario::set_magic_dmg(string school_, double dmg_) {
  magic_school = school_;
  magic_dmg = dmg_;
}

void WorstCaseSzenario::operator=(WorstCaseSzenario in) {
  n_hits = in.get_n_hits();
  dmg_per_hit = in.get_white_dmg();
  magic_school = in.get_magic_school();
  magic_dmg = in.get_magic_dmg();
}

void Boss::operator=(Boss boss_) {
  primary_stats = boss_.get_primary_stats();
  secondary_stats = boss_.get_secondary_stats();
  abilities = boss_.get_abilities();
  worst_case = (*boss_.get_worst_case_szenario());
  set_lvl(boss_.get_lvl());
  set_name(boss_.get_name());
}

Attumen::Attumen() {
  set_name("Attumen the Huntsman");
  primary_stats.armor = 7684;
  primary_stats.health = 379400;
  primary_stats.attack_speed = 2.0;
  primary_stats.weapondamage = (4649.0 + 3864.0) / 2.0;
  set_prim_stats(primary_stats);
  Ability shadow_cleave("Shadow Cleave", "Shadow");
  shadow_cleave.set_damage(4000);
  shadow_cleave.set_cooldown(6);
  add_ability(shadow_cleave);
  get_worst_case_szenario()->set_dmg_per_hit(4649);
  get_worst_case_szenario()->set_n_hits(2);
  get_worst_case_szenario()->set_magic_dmg("Shadow", 4000);
}

Midnight::Midnight() {
  set_name("Midnight");
  primary_stats.armor = -7684;
  primary_stats.health = 379400;
  primary_stats.attack_speed = 2.0;
  primary_stats.weapondamage = (5945.0 + 4713.0) / 2.0;
  set_prim_stats(primary_stats);
}

PrinceMalchezaar::PrinceMalchezaar() {
  set_name("Prince Malchezaar");
  primary_stats.health = 1138200;
  primary_stats.weapondamage = (9288.0 + 7364.0) / 2.0;
  primary_stats.attack_speed = 2.0;
  primary_stats.armor = 7684;
  set_prim_stats(primary_stats);
  Ability amplify_damage("Amplify Damage", "Shadow");
  Ability enfeeble("Enfeeble", "Physical");
  Ability shadow_nova("Shadow Nova", "Shadow");
  shadow_nova.set_dps(3000.0 / 3.0);
  shadow_nova.set_casttime(3.0);
  add_ability(shadow_nova);
  Ability shadow_word_pain("Shadow Word: Pain", "Shadow");
  double average_dps_swp = (1313.0 + 1687.0) / 2.0;
  shadow_word_pain.set_dps(average_dps_swp / 3.0 * 18.0);
  shadow_word_pain.set_dot(true);
  shadow_word_pain.set_uptime(18);
  add_ability(shadow_word_pain);
  Ability sunder_armor("Sunder Armor", "Physical");
  PrimaryStats sunder_armor_temp;
  sunder_armor_temp.armor = 1000;
  sunder_armor.set_debuff(sunder_armor_temp);
  add_ability(sunder_armor);
  Ability thrash("Thrash", "Physical");
  // thrash.set_procc_chance(0.35); undefined reference. why?
  add_ability(thrash);
  get_worst_case_szenario()->set_dmg_per_hit(9288);
  get_worst_case_szenario()->set_n_hits(3);
  get_worst_case_szenario()->set_magic_dmg("Fire", 600);
}

Hydros::Hydros() {
  set_name("Hydros the Unstable");
  primary_stats.health = 1540000;
  primary_stats.attack_speed = 2.0;
  set_prim_stats(primary_stats);
  Ability frost_based_autoattack("Frost Based Autoattack", "Frost");
  frost_based_autoattack.set_damage(5500);
  frost_based_autoattack.set_casttime(2.0);
  frost_based_autoattack.set_dps(5500.0 / 2.0);
  add_ability(frost_based_autoattack);
  Ability mark_of_hydros("Mark of Hydros", "Frost"); //+10%,25%,50%,100%,250%,500% frost damage, stacks
  Ability water_tomb("Water Tomb", "Frost");         // 4 sec stun
  water_tomb.set_damage(4500);
  water_tomb.set_dot(true);
  water_tomb.set_uptime(5);
  water_tomb.set_cooldown(7);
  double most_damage = (5500.0 / 2.0 + 4500.0 / 5.0) * 4.0 * 2.0;
  get_worst_case_szenario()->set_magic_dmg("Frost", most_damage);
}
