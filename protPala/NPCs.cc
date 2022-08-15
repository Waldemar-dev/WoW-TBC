#include "NPCs.hh"

using namespace std;

WorstCaseSzenario::WorstCaseSzenario(): nHits_(0), dmgPerHit_(0), sunderArmor_(false), sunderArmorDebuff_(0), multiplier_(1), physicalAbilityDmg_(0){
}

void WorstCaseSzenario::set_magic_dmg(MagicSchool inSchool, double inDmg)
{
  magicSchool_.push_back(inSchool);
  magicDmg_.push_back(inDmg);
}

void WorstCaseSzenario::operator=(WorstCaseSzenario in)
{
  nHits_ = in.get_n_hits();
  dmgPerHit_ = in.get_white_dmg();
  magicSchool_ = in.get_magic_school();
  magicDmg_ = in.get_magic_dmg();
}

double WorstCaseSzenario::get_max_damage(Character *in)
{
  double result = 0;
  double armor_red = in->get_armor_reduction(sunderArmorDebuff_ * 5);
  if (in->get_crush() <= 0.0)
  {
    result += max(get_white_dmg() * (1 - armor_red) - in->get_block_value(), 0.0) * get_n_hits();
    result += max(0.0, get_yellow_dmg() * (1 - armor_red) - in->get_block_value());
  }
  else
  {
    result += get_white_dmg() * (1 - armor_red) * get_n_hits() * 1.5;
    result += get_yellow_dmg() * (1 - armor_red) * 1.5;
  }
  for (uint i = 0; i < magicDmg_.size(); i++)
  {
    result += magicDmg_[i] * (1 - in->average_resistance(magicSchool_[i]));
  }
  return result;
}

Boss::Boss(std::string inName, double inMinDamage, double inMaxDamage): name_(inName), minWhiteDmg_(inMinDamage), maxWhiteDmg_(inMaxDamage), lvl_(73), effectiveSwingTimer_(0), raidDps_(0), blockChance_(0), parryChance_(0.14){
}

void Boss::operator=(Boss inBoss)
{
  for (uint i = PrimaryAttributes::FirstPrimary; i != PrimaryAttributes::LastPrimary; i++)
  {
    set_prim_stat((PrimaryAttributes)i, inBoss.get_prim_stat((PrimaryAttributes)i));
  }
  for (uint i = SecondaryAttributes::FirstSecondary; i != SecondaryAttributes::LastSecondary; i++)
  {
    set_sec_stat((SecondaryAttributes)i, inBoss.get_sec_stat((SecondaryAttributes)i));
  }
  abilities_ = inBoss.get_abilities();
  worstCase_ = (*inBoss.get_worst_case_szenario());
  set_lvl(inBoss.get_lvl());
  set_name(inBoss.get_name());
}

double Boss::getDamageReductionFromArmor(unsigned int inPlayerLevel, unsigned int inArmorPen)
{
  double tempArmor = get_prim_stat(PrimaryAttributes::Armor) - inArmorPen;
  double result = tempArmor / (tempArmor + 467.5 * inPlayerLevel - 22167.5);
  result = min(0.75, result);
  return result;
}

Attumen::Attumen(): Boss("Attumen the Huntsman", 3864, 4649)
{
  set_prim_stat(PrimaryAttributes::Armor, 7684);
  set_prim_stat(PrimaryAttributes::Health, 379400);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 2.0);
  set_prim_stat(PrimaryAttributes::WeaponDamage, (get_max_white_hit() + get_min_white_hit()) / 2.0);
  Ability shadow_cleave("Shadow Cleave", MagicSchool::Shadow);
  shadow_cleave.set_damage(4000);
  shadow_cleave.set_cooldown(6);
  add_ability(shadow_cleave);
  WorstCaseSzenario temp;
  temp.set_dmg_per_hit(4649);
  temp.set_n_hits(2);
  temp.set_magic_dmg(MagicSchool::Shadow, 4000);
  add_worst_case_scenario(temp);
}

Midnight::Midnight(): Boss("Midnight", 4713, 5945)
{
  set_prim_stat(PrimaryAttributes::Armor, -7684);
  set_prim_stat(PrimaryAttributes::Health, 379400);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 2.0);
  set_prim_stat(PrimaryAttributes::WeaponDamage, (get_max_white_hit() + get_min_white_hit()) / 2.0);
}

PrinceMalchezaar::PrinceMalchezaar() : Boss("Prince Malchezaar", 9909, 14064)
{
  set_prim_stat(PrimaryAttributes::Health, 1138200);
  // set_max_white_dmg(); // 9385
  // set_min_white_dmg();  // 6638
  set_prim_stat(PrimaryAttributes::WeaponDamage, (get_max_white_hit() + get_min_white_hit()) / 2.0);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 2.0);
  set_prim_stat(PrimaryAttributes::Armor, 7684);
  Ability amplify_damage("Amplify Damage", MagicSchool::Shadow);
  Ability enfeeble("Enfeeble", MagicSchool::Physical);     // not on tank, 30sec cd
  Ability shadow_nova("Shadow Nova", MagicSchool::Shadow); // all phases
  shadow_nova.set_dps(3000.0 / 3.0);
  shadow_nova.set_casttime(3.0);
  add_ability(shadow_nova);
  Ability shadow_word_pain("Shadow Word: Pain", MagicSchool::Shadow); // phases 1 (on mt) and 3 (random)
  double average_dps_swp = (1313.0 + 1687.0) / 2.0;                   // 1500
  shadow_word_pain.set_dps(average_dps_swp / 3.0 * 18.0);
  shadow_word_pain.set_dot(true);
  shadow_word_pain.set_uptime(18);
  add_ability(shadow_word_pain);
  Ability sunder_armor("Sunder Armor", MagicSchool::Physical); // phase 2
  PrimaryStats sunder_armor_temp;
  sunder_armor_temp.set_stat(PrimaryAttributes::Armor, 1000);
  sunder_armor.set_debuff(sunder_armor_temp);
  add_ability(sunder_armor);
  Ability thrash("Thrash", MagicSchool::Physical); // phase 2
  thrash.set_procc_chance(0.35); //undefined reference. why?
  add_ability(thrash);
  // get_worst_case_szenario()->set_dmg_per_hit(set_prim_stat(PrimaryAttributes::WeaponDamage,));
  // get_worst_case_szenario()->set_n_hits(3);//thrash in phase 2
  // get_worst_case_szenario()->set_magic_dmg(MagicSchool::Fire, 600);//all phases
  // get_worst_case_szenario()->set_magic_dmg(MagicSchool::Shadow, 3000);//all phases
  
  WorstCaseSzenario phase1, phase2, phase3;
  unsigned int n_hits = (unsigned int)(2.5 / get_eff_swing_timer()) + 1;
  double infernal_tick = 600; //(875.0+1125.0)/2.0;//600
  phase1.set_magic_dmg(MagicSchool::Fire, infernal_tick);
  phase1.set_magic_dmg(MagicSchool::Shadow, 1687.0 + 3000);
  phase1.set_dmg_per_hit(get_max_white_hit());
  phase1.set_n_hits(n_hits);
  add_worst_case_scenario(phase1);
  add_phase_threshold(0.6);

  phase2.set_magic_dmg(MagicSchool::Fire, infernal_tick);
  phase2.set_magic_dmg(MagicSchool::Shadow, 3000);
  phase2.set_sunder_armor(1000);
  phase2.set_dmg_per_hit(get_max_white_hit());
  phase2.set_n_hits(2 + n_hits);
  add_worst_case_scenario(phase2);
  add_phase_threshold(0.3);

  phase3.set_magic_dmg(MagicSchool::Fire, infernal_tick);
  phase3.set_magic_dmg(MagicSchool::Shadow, 1687.0 + 3000);
  phase3.set_dmg_per_hit(get_max_white_hit());
  phase3.set_n_hits(n_hits);
  phase3.set_amplify_damage(2.0);
  phase3.set_phys_ability_damage(2000);
  add_worst_case_scenario(phase3);

  double average_warlock_t4_kara_dps = 1303.68;
  double average_hunter_t4_kara_dps = 1294.04;
  double average_mage_t4_kara_dps = 1220.78;
  double average_shaman_t4_kara_dps = 1201.24;
  double average_priest_t4_kara_dps = 951.43;
  double average_rogue_t4_kara_dps = 877;
  std::vector<double> average_t4_kara_dps_vec = {average_warlock_t4_kara_dps, average_hunter_t4_kara_dps, average_mage_t4_kara_dps, average_shaman_t4_kara_dps, average_priest_t4_kara_dps, average_rogue_t4_kara_dps};
  set_average_dps_vec(average_t4_kara_dps_vec);
}

double PrinceMalchezaar::get_phase_1_damage(Character *playerChar)
{
  double attack_damage = get_attack_damage() * (1 - playerChar->get_armor_reduction());
  double sanctuary_bonus = 0;
  for (uint i = 0; i < playerChar->get_buffs().size(); i++)
  {
    if (playerChar->get_buffs()[i].get_name() == "Blessing of Sanctuary")
    {
      sanctuary_bonus = 80;
      break;
    }
  }
  double average_damage = (attack_damage - sanctuary_bonus) * (1 - playerChar->get_critted_chance() - playerChar->get_crush() - playerChar->get_block() / 100.0 - playerChar->get_avoidance() / 100.0);
  double average_crush_damage = (attack_damage * 1.5 - sanctuary_bonus) * playerChar->get_crush();
  double average_crit_damage = (attack_damage * 2 - sanctuary_bonus) * playerChar->get_critted_chance();
  double average_blocked_damage = playerChar->get_block() / 100.0 * (std::max(get_max_white_hit() * (1 - playerChar->get_armor_reduction()) - sanctuary_bonus - playerChar->get_block_value(), 0.0) + std::max(0.0, get_min_white_hit() * (1 - playerChar->get_armor_reduction()) - sanctuary_bonus - playerChar->get_block_value())) / 2.0;
  double result = (average_damage + average_crit_damage + average_crush_damage + average_blocked_damage) / get_attack_speed() * playerChar->get_time_of_encounter() * (1 - get_phase_thresholds()[0]);
  if (result < 0 || std::isnan(result))
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << attack_damage << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << average_damage << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << average_crush_damage << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << average_crit_damage << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << average_blocked_damage << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << get_attack_speed() << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << playerChar->get_time_of_encounter() << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << (1 - get_phase_thresholds()[0]) << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << " " << result << std::endl;
  }
  return result;
}

double PrinceMalchezaar::get_phase_2_damage(Character *playerChar)
{
  double sanctuary_bonus = 0;
  for (uint i = 0; i < playerChar->get_buffs().size(); i++)
  {
    if (playerChar->get_buffs()[i].get_name() == "Blessing of Sanctuary")
    {
      sanctuary_bonus = 80;
      break;
    }
  }
  double attack_damage = get_attack_damage() * (1 - playerChar->get_armor_reduction(sunderArmorDebuff_ * 5));
  double average_damage = (attack_damage - sanctuary_bonus) * (1 - playerChar->get_critted_chance() - playerChar->get_crush(true) - playerChar->get_block(true) / 100.0 - playerChar->get_avoidance(true) / 100.0);
  double average_crush_damage = attack_damage * 1.5 * playerChar->get_crush(true) - sanctuary_bonus;
  double average_crit_damage = attack_damage * 2 * playerChar->get_critted_chance() - sanctuary_bonus;
  double average_blocked_damage = playerChar->get_block(true) / 100.0 * (std::max(get_max_white_hit() * (1 - playerChar->get_armor_reduction(sunderArmorDebuff_ * 5)) - sanctuary_bonus - playerChar->get_block_value(), 0.0) + std::max(0.0, get_min_white_hit() * (1 - playerChar->get_armor_reduction(sunderArmorDebuff_ * 5)) - sanctuary_bonus - playerChar->get_block_value())) / 2.0;
  double result = (average_damage + average_crit_damage + average_crush_damage + average_blocked_damage) / get_attack_speed() * playerChar->get_time_of_encounter() * (get_phase_thresholds()[0] - get_phase_thresholds()[1]);
  return result;
}

double PrinceMalchezaar::get_phase_3_damage(Character *playerChar)
{
  double attack_damage = get_attack_damage() * (1 - playerChar->get_armor_reduction());
  double sanctuary_bonus = 0;
  for (uint i = 0; i < playerChar->get_buffs().size(); i++)
  {
    if (playerChar->get_buffs()[i].get_name() == "Blessing of Sanctuary")
    {
      sanctuary_bonus = 80;
      break;
    }
  }
  double average_damage = (attack_damage - sanctuary_bonus) * (1 - playerChar->get_critted_chance() - playerChar->get_crush() - playerChar->get_block() / 100.0 - playerChar->get_avoidance() / 100.0);
  double average_crush_damage = attack_damage * 1.5 * playerChar->get_crush() - sanctuary_bonus;
  double average_crit_damage = attack_damage * 2 * playerChar->get_critted_chance() - sanctuary_bonus;
  double average_blocked_damage = playerChar->get_block() / 100.0 * (std::max(get_max_white_hit() * (1 - playerChar->get_armor_reduction()) - sanctuary_bonus - playerChar->get_block_value(), 0.0) + std::max(0.0, get_min_white_hit() * (1 - playerChar->get_armor_reduction()) - sanctuary_bonus - playerChar->get_block_value())) / 2.0;
  double result = (average_damage + average_crit_damage + average_crush_damage + average_blocked_damage) / get_attack_speed() * playerChar->get_time_of_encounter() * (get_phase_thresholds()[1]);
  return result;
}

double PrinceMalchezaar::get_total_damage_dealt(Character *playerChar)
{
  // phase 1
  double result1 = get_phase_1_damage(playerChar);
  if (result1 < 0 || isnan(result1))
  {
    std::cout << __LINE__ << " : result1=" << result1 << std::endl;
  }
  // phase 3
  double result3 = get_phase_3_damage(playerChar);
  if (result3 < 0 || isnan(result3))
  {
    std::cout << __LINE__ << " : result3=" << result3 << std::endl;
  }
  // phase 2
  double result2 = get_phase_2_damage(playerChar);
  if (result2 < 0 || isnan(result2))
  {
    std::cout << __LINE__ << " : result2=" << result2 << std::endl;
  }
  double result = result1 + result2 + result3;
  if (result < 0 || isnan(result))
  {
    std::cout << __LINE__ << " : result=" << result << std::endl;
  }
  std::unordered_map<MagicSchool, double, std::hash<int>> temp_map = get_magic_dps();
  for (std::unordered_map<MagicSchool, double, std::hash<int>>::iterator it = temp_map.begin(); it != temp_map.end(); it++)
  {
    result += it->second * (1 - playerChar->average_resistance(it->first)) * playerChar->get_time_of_encounter();
  }
  if (result < 0 || isnan(result))
  {
    std::cout << __LINE__ << " : result=" << result << std::endl;
  }
  if (playerChar->gear[Slot::Trinket1].get_uptime() > 0 || playerChar->gear[Slot::Trinket2].get_uptime() > 0)
  {
    if (!playerChar->how_use_trinkets()) // serial
    {
      double temp_result = 0;
      double no_cd_factor = 1;
      if (playerChar->gear[Slot::Trinket1].get_uptime() > 0)
      {
        playerChar->gear[Slot::Trinket1].activate();
        playerChar->gear[Slot::Trinket2].deactivate();
        playerChar->compute_stats();
        temp_result = get_phase_1_damage(playerChar) + get_phase_2_damage(playerChar) + get_phase_3_damage(playerChar);
        for (std::unordered_map<MagicSchool, double, std::hash<int>>::iterator it = temp_map.begin(); it != temp_map.end(); it++)
        {
          temp_result += it->second * (1 - playerChar->average_resistance(it->first)) * playerChar->get_time_of_encounter();
        }
        temp_result *= playerChar->gear[Slot::Trinket1].get_uptime() / playerChar->gear[Slot::Trinket1].get_cooldown();
        no_cd_factor -= playerChar->gear[Slot::Trinket1].get_uptime() / playerChar->gear[Slot::Trinket1].get_cooldown();
      }
      if (playerChar->gear[Slot::Trinket2].get_uptime() > 0)
      {
        playerChar->gear[Slot::Trinket2].activate();
        playerChar->gear[Slot::Trinket1].deactivate();
        playerChar->compute_stats();
        for (std::unordered_map<MagicSchool, double, std::hash<int>>::iterator it = temp_map.begin(); it != temp_map.end(); it++)
        {
          temp_result += (it->second * (1 - playerChar->average_resistance(it->first)) * playerChar->get_time_of_encounter()) * playerChar->gear[Slot::Trinket2].get_uptime() / playerChar->gear[Slot::Trinket2].get_cooldown();
        }
        temp_result += (get_phase_1_damage(playerChar) + get_phase_2_damage(playerChar) + get_phase_3_damage(playerChar)) * playerChar->gear[Slot::Trinket2].get_uptime() / playerChar->gear[Slot::Trinket2].get_cooldown();
        no_cd_factor -= playerChar->gear[Slot::Trinket2].get_uptime() / playerChar->gear[Slot::Trinket2].get_cooldown();
      }
      result *= no_cd_factor;
      result += temp_result;
    }
    else // parallel
    {
      double no_cd_factor = 1 - std::max(playerChar->gear[Slot::Trinket1].get_uptime(), playerChar->gear[Slot::Trinket2].get_uptime()) / std::max(playerChar->gear[Slot::Trinket1].get_cooldown(), playerChar->gear[Slot::Trinket2].get_cooldown());
      result *= no_cd_factor;
      playerChar->gear[Slot::Trinket1].activate();
      playerChar->gear[Slot::Trinket2].activate();
      playerChar->compute_stats();
      result += (get_phase_1_damage(playerChar) + get_phase_2_damage(playerChar) + get_phase_3_damage(playerChar)) * std::min(playerChar->gear[Slot::Trinket1].get_uptime(), playerChar->gear[Slot::Trinket2].get_uptime()) / std::max(playerChar->gear[Slot::Trinket1].get_cooldown(), playerChar->gear[Slot::Trinket2].get_cooldown());
      double temp_result = std::abs(playerChar->gear[Slot::Trinket1].get_uptime() - playerChar->gear[Slot::Trinket2].get_uptime()) / std::max(playerChar->gear[Slot::Trinket1].get_cooldown(), playerChar->gear[Slot::Trinket2].get_cooldown());
      playerChar->gear[Slot::Trinket1].deactivate();
      playerChar->gear[Slot::Trinket2].deactivate();
      double temp_result2 = 0;
      if (playerChar->gear[Slot::Trinket1].get_uptime() > playerChar->gear[Slot::Trinket2].get_uptime())
      {
        playerChar->gear[Slot::Trinket1].activate();
        playerChar->gear[Slot::Trinket2].deactivate();
        playerChar->compute_stats();
        for (std::unordered_map<MagicSchool, double, std::hash<int>>::iterator it = temp_map.begin(); it != temp_map.end(); it++)
        {
          temp_result2 += it->second * (1 - playerChar->average_resistance(it->first)) * playerChar->get_time_of_encounter();
        }
        temp_result *= (get_phase_1_damage(playerChar) + get_phase_2_damage(playerChar) + get_phase_3_damage(playerChar) + temp_result2);
      }
      else if (playerChar->gear[Slot::Trinket1].get_uptime() < playerChar->gear[Slot::Trinket2].get_uptime())
      {
        playerChar->gear[Slot::Trinket1].deactivate();
        playerChar->gear[Slot::Trinket2].activate();
        playerChar->compute_stats();
        for (std::unordered_map<MagicSchool, double, std::hash<int>>::iterator it = temp_map.begin(); it != temp_map.end(); it++)
        {
          temp_result2 += it->second * (1 - playerChar->average_resistance(it->first)) * playerChar->get_time_of_encounter();
        }
        temp_result *= (get_phase_1_damage(playerChar) + get_phase_2_damage(playerChar) + get_phase_3_damage(playerChar) + temp_result2);
      }
      result += temp_result;
      if (result < 0 || isnan(result))
      {
        std::cout << "no_cd_factor=" << no_cd_factor << std::endl;
        std::cout << "temp_result=" << temp_result << std::endl;
        std::cout << "temp_result2=" << temp_result2 << std::endl;
        std::cout << "result=" << result << std::endl;
        playerChar->print_all_stats();
        playerChar->print_gear();
        abort();
      }
    }
  }
  playerChar->gear[Slot::Trinket1].deactivate();
  playerChar->gear[Slot::Trinket2].deactivate();
  playerChar->compute_stats();
  return result;
}

std::unordered_map<MagicSchool, double, std::hash<int>> PrinceMalchezaar::get_magic_dps()
{
  std::unordered_map<MagicSchool, double, std::hash<int>> result;
  double phase_1_duration = (1.0 - get_phase_thresholds()[0]) * get_prim_stat(PrimaryAttributes::Health) / get_raid_dps();
  double swp_average_dps = (1313.0 + 1687.0) / 2.0 / 3.0 * (uint)(phase_1_duration / 18.0 + 1) * 18.0 / (get_prim_stat(PrimaryAttributes::Health) / get_raid_dps());
  result.insert(pair<MagicSchool, double>(MagicSchool::Shadow, swp_average_dps + 3000.0 / 30.0));
  double infernal_duration = 180.0;
  double infernal_average_damage = 600 * infernal_duration / (get_prim_stat(PrimaryAttributes::Health) / get_raid_dps());
  result.insert(pair<MagicSchool, double>(MagicSchool::Fire, infernal_average_damage));
  return result;
}

Hydros::Hydros():Boss("Hydros the Unstable",0,0)
{
  set_prim_stat(PrimaryAttributes::Health, 1540000);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 2.0);
  Ability frost_based_autoattack("Frost Based Autoattack", MagicSchool::Frost);
  frost_based_autoattack.set_damage(5500);
  frost_based_autoattack.set_casttime(2.0);
  frost_based_autoattack.set_dps(5500.0 / 2.0);
  add_ability(frost_based_autoattack);
  Ability mark_of_hydros("Mark of Hydros", MagicSchool::Frost); //+10%,25%,50%,100%,250%,500% frost damage, stacks
  Ability water_tomb("Water Tomb", MagicSchool::Frost);         // 4 sec stun
  water_tomb.set_damage(4500);
  water_tomb.set_dot(true);
  water_tomb.set_uptime(5);
  water_tomb.set_cooldown(7);
  double most_damage = (5500.0 / 2.0 + 4500.0 / 5.0) * 4.0 * 2.0;
  WorstCaseSzenario temp;
  temp.set_magic_dmg(MagicSchool::Frost, most_damage);
  add_worst_case_scenario(temp);
}

bool PrinceMalchezaar::useless_gear(Gear *in, Character *playerChar)
{
  bool useless_resi = (in->get_prim_stat(PrimaryAttributes::FireResistance) == 0 && in->get_prim_stat(PrimaryAttributes::ShadowResistance) == 0) && (in->get_prim_stat(PrimaryAttributes::FrostResistance) > 0 || in->get_prim_stat(PrimaryAttributes::ArcaneResistance) > 0 || in->get_prim_stat(PrimaryAttributes::NatureResistance) > 0);
  if (useless_resi)
  {
    return true;
  }
  return false;
}