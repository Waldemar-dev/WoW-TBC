#include "Character.hh"

unsigned long int binomialCoefficients(int n, int r, int k = -1)
{
  if (k < 0)
    k = r = std::min(r, n - r);
  return k == 0 ? 1 : binomialCoefficients(n, r, k - 1) * (n - r + k) / k;
}

unsigned long int multinomialCoefficients(unsigned int n, std::vector<unsigned int> *k)
{
  long int result = 1;
  for (uint i = 0; i < k->size(); i++)
  {
    long int sum = 0;
    for (uint j = 0; j <= i; j++)
    {
      sum += k->at(j);
    }
    result *= binomialCoefficients(sum, k->at(i));
  }
  return result;
}

// std::function<double(const double *)> fit_min_lacerate_output(std::function<double(const double *)> fit_min_lacerate)
// {
//   std::function<double(const double *)> out = [fit_min_lacerate](const double *args) -> double
//   { return fit_min_lacerate(args); };
//   return out;
// }

// std::function<double(const double *)> fit_min_lacerate(Character *playerChar)
// {
//   std::function<double(const double *)> out = [playerChar](const double *args)
//       -> double
//   {
//     uint min_lacerate = (uint) round(args[0]);
//     double mse=0;
//     if (playerChar->get_class()!=CharacterClass::Druid){return mse;}
//     double p5=0;
//     double n5=0;
//     uint i=0;
//     while (i*playerChar->get_global_cd()<15){
//       double sum=0;
//       double n5_sum=0;
//       for (uint j=0;j<=i;j++){
//         for (uint k=0;k<=i-j;k++){
//           uint l=i-j-k;
//           std::vector<uint> k_vec={5,j,k,l};
//           double temp2=multinomialCoefficients(5+i,&k_vec)*pow(playerChar->get_hit_chance(),5)*pow(playerChar->get_miss_chance(),j)*pow(playerChar->get_dodged_chance(),k)*pow(playerChar->get_parried_chance(),l);
//           p5+=(temp2);
//           n5+=(temp2*(i+5));
//         }
//       }
//       i++;
//     }
//     n5/=p5;
//     uint k=0;
//     double temp=0;
//     while (k<=min_lacerate){
//       temp+=(binomialCoefficients(min_lacerate,k)*pow(playerChar->get_hit_chance(),min_lacerate-k)*pow(1-playerChar->get_hit_chance(),k)*(min_lacerate-k+k*n5));
//       k++;
//     }
//     mse=pow(temp-min_lacerate,2);
//     return mse;
//   };
//   return out;
// }

double Character::calc_average_raid_dps(double tps)
{
  double average_raid_damage = std::min(tps * 1.29 / 0.6, 1622.70); // Arcane Mage
  average_raid_damage += 1421.36;                                   // Beast Master Hunter
  average_raid_damage += std::min(tps * 1.29 / 0.9, 1406.76);       // Destruction Warlock
  average_raid_damage += std::min(tps * 1.29, 1344.17);             // Survival Hunter
  average_raid_damage += std::min(tps * 1.09 / 0.9, 1339.79);       // Furry Warrior
  average_raid_damage += std::min(tps * 1.29 / 0.9, 1326.57);       // Demonology Warlock
  average_raid_damage += std::min(tps * 1.29 / 0.9, 1315.77);       // Fire Mage
  average_raid_damage += std::min(tps * 1.29, 1264.9);              // Elemental Shaman
  average_raid_damage += std::min(tps * 1.29 / 0.9, 1236.78);       // Affliction Warlock
  average_raid_damage += std::min(tps * 1.09, 1208.35);             // Arms Warrior
  average_raid_damage += std::min(tps * 1.29 / 0.75, 1176.78);      // Shadow Priest
  average_raid_damage += std::min(tps * 1.09, 1165.2);              // Enhancement Shaman
  average_raid_damage += std::min(tps * 1.09 / 0.7, 1158.12);       // Retribution Paladin
  average_raid_damage += std::min(tps * 1.09, 1139.37);             // Combat Rogue
  average_raid_damage += std::min(tps * 1.29, 1089.56);             // Balance Druid
  average_raid_damage += std::min(tps * 1.29, 1087.78);             // Marksmanship Hunter
  average_raid_damage += std::min(tps * 1.29 / 0.9, 1077.7);        // Frost Mage
  average_raid_damage /= 17.0;
  return average_raid_damage;
}

double Character::calc_average_raid_damage(double total_threat, double time_estimation)
{
  // double average_raid_damage = std::min(total_threat * 1.29 / 0.6, 1622.70 * time_estimation); // Arcane Mage
  // average_raid_damage += 1421.36 * time_estimation;                                            // Beast Master Hunter
  // average_raid_damage += std::min(total_threat * 1.29 / 0.9, 1406.76 * time_estimation);       // Destruction Warlock
  // average_raid_damage += std::min(total_threat * 1.29, 1344.17 * time_estimation);             // Survival Hunter
  // average_raid_damage += std::min(total_threat * 1.09 / 0.9, 1339.79 * time_estimation);       // Furry Warrior
  // average_raid_damage += std::min(total_threat * 1.29 / 0.9, 1326.57 * time_estimation);       // Demonology Warlock
  // average_raid_damage += std::min(total_threat * 1.29 / 0.9, 1315.77 * time_estimation);       // Fire Mage
  // average_raid_damage += std::min(total_threat * 1.29, 1264.9 * time_estimation);              // Elemental Shaman
  // average_raid_damage += std::min(total_threat * 1.29 / 0.9, 1236.78 * time_estimation);       // Affliction Warlock
  // average_raid_damage += std::min(total_threat * 1.09, 1208.35 * time_estimation);             // Arms Warrior
  // average_raid_damage += std::min(total_threat * 1.29 / 0.75, 1176.78 * time_estimation);      // Shadow Priest
  // average_raid_damage += std::min(total_threat * 1.09, 1165.2 * time_estimation);              // Enhancement Shaman
  // average_raid_damage += std::min(total_threat * 1.09 / 0.7, 1158.12 * time_estimation);       // Retribution Paladin
  // average_raid_damage += std::min(total_threat * 1.09, 1139.37 * time_estimation);             // Combat Rogue
  // average_raid_damage += std::min(total_threat * 1.29, 1089.56 * time_estimation);             // Balance Druid
  // average_raid_damage += std::min(total_threat * 1.29, 1087.78 * time_estimation);             // Marksmanship Hunter
  // average_raid_damage += std::min(total_threat * 1.29 / 0.9, 1077.7 * time_estimation);        // Frost Mage
  // average_raid_damage /= 17.0;
  return calc_average_raid_dps(total_threat/time_estimation)*time_estimation;
}

double Character::calc_bear_dps(double n_auto, double n_maul, double n_filler, double n_lacerate)
{
  double result = 0;
  double time_estimation = (n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  std::map<std::string, unsigned int>::iterator it = talents.find("Predatory Instincts");
  double crit_bonus = 0;
  if (it != talents.end())
  {
    crit_bonus = it->second * 0.02;
  }
  double auto_damage = get_white_damage() * (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double glancing_damage = get_glancing_blow_damage() * (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double average_auto_damage = auto_damage * (get_hit_chance(false) + crit_bonus * get_melee_crit_chance() + get_glancing_blow_chance() * glancing_damage);

  double maul_damage = get_white_damage() + 176;
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    maul_damage += 50;
  }
  maul_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));

  double mangle_damage = get_white_damage() * 1.15 + 207; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of the Wild")
  {
    mangle_damage += 52;
  }
  mangle_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));

  double lacerate_direct_dmg = 31 + 0.01 * get_attackpower();
  double lacerate_dot_dmg = 155 + get_attackpower() / 20; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of Ursoc")
  {
    lacerate_direct_dmg += 8;
    lacerate_dot_dmg += 8;
  }
  double filler_damage = lacerate_direct_dmg;
  if (!isLacerateFiller_)
  {
    double swipe_damage = get_attackpower() * 0.171 + 84;
    if (gear[Slot::Idol].get_name() == "Idol of Brutality")
    {
      swipe_damage += 10;
    }
    swipe_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
    filler_damage = swipe_damage;
  }
  result = n_auto * average_auto_damage + (n_maul * maul_damage + n_filler * filler_damage + n_lacerate * lacerate_direct_dmg + n_mangle * mangle_damage) * (get_hit_chance(true) * (1 - get_melee_crit_chance()) + crit_bonus * get_melee_crit_chance() * get_hit_chance(true));
  result /= time_estimation;
  if (gear[Slot::Trinket1].get_name() == "Darkmoon Card: Vengeance" || gear[Slot::Trinket2].get_name() == "Darkmoon Card: Vengeance")
  {
    double temp_sp = 0.001 * get_tot_sec_stat(SecondaryAttributes::SpellPower) + 0.0025 * get_tot_sec_stat(SecondaryAttributes::HolySpellPower);
    double vengenace_damage = (95.0 + 115.0) / 2.0;
    vengenace_damage += temp_sp;
    result += 0.1 * (1 - get_avoidance() / 100.0) * vengenace_damage / get_encounter()->get_attack_speed() * ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 2);
  }
  return result;
}

double Character::calc_bear_tps(double in_n_auto, double in_n_maul, double in_n_filler, double in_n_min_lacerate)
{
  double result = 0;
  double time_estimation = (in_n_auto + in_n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  uint n_mangle = (uint)time_estimation / 6.0;
  double white_bonus_threat = 0;
  double white_threat_multiplier = 1.3 * 1.15;
  std::map<std::string, unsigned int>::iterator it = talents.find("Predatory Instincts");
  double crit_bonus = 0;
  if (it != talents.end())
  {
    crit_bonus = it->second * 0.02;
  }
  double auto_damage = get_white_damage() * (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double glancing_damage = get_glancing_blow_damage() * (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  // double average_auto_damage = auto_damage * (get_hit_chance() + crit_bonus * get_melee_crit_chance() + get_glancing_blow_chance() * glancing_damage);
  double threat_auto = (auto_damage + white_bonus_threat) * white_threat_multiplier;
  double threat_auto_crit = (auto_damage * crit_bonus + white_bonus_threat) * white_threat_multiplier;
  double threat_auto_glancing = (glancing_damage + white_bonus_threat) * white_threat_multiplier;
  double maul_damage = get_white_damage() + 176;
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    maul_damage += 50;
  }
  maul_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double threat_maul = (maul_damage + maulBonusThreat_) * maulThreatMultiplier_;
  double threat_maul_crit = (maul_damage * crit_bonus + maulBonusThreat_) * maulThreatMultiplier_;
  double swipe_damage = get_attackpower() * 0.171 + 84;
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    swipe_damage += 10;
  }
  swipe_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double threat_swipe = (swipe_damage + swipeBonusThreat_) * swipeThreatMultiplier_;
  double threat_swipe_crit = (swipe_damage * crit_bonus + swipeBonusThreat_) * swipeThreatMultiplier_;
  double mangle_damage = get_white_damage() * 1.15 + 207; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of the Wild")
  {
    mangle_damage += 52;
  }
  mangle_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double threat_mangle = (mangle_damage + mangleBonusThreat_) * mangleThreatMultiplier_;
  double threat_mangle_crit = (mangle_damage * crit_bonus + mangleBonusThreat_) * mangleThreatMultiplier_;
  double lacerate_direct_dmg = 31 + 0.01 * get_attackpower();
  double lacerate_dot_dmg = 155 + get_attackpower() / 20; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of Ursoc")
  {
    lacerate_direct_dmg += 8;
    lacerate_dot_dmg += 8;
  }
  double threat_lacerate_direct = (lacerate_direct_dmg + lacerateDirectBonusThreat_) * lacerateDirectThreatMultiplier_;
  double threat_lacerate_direct_crit = (lacerate_direct_dmg * crit_bonus + lacerateDirectBonusThreat_) * lacerateDirectThreatMultiplier_;
  double tps_lacerate_dot = lacerate_dot_dmg * 7 / 24.0 / 15.0 * 1.3; // incl mangle buff
  double threat_filler = 0;
  double threat_filler_crit = 0;
  if ((threat_lacerate_direct * get_hit_chance(true) * (1 - get_melee_crit_chance()) + threat_lacerate_direct_crit * get_hit_chance(true) * get_melee_crit_chance()) >= (threat_swipe * get_hit_chance(true) * (1 - get_melee_crit_chance()) + threat_swipe_crit * get_hit_chance(true) * get_melee_crit_chance()))
  {
    isLacerateFiller_ = true;
    threat_filler = threat_lacerate_direct;
    threat_filler_crit = threat_lacerate_direct_crit;
  }
  else
  {
    isLacerateFiller_ = false;
    threat_filler = threat_swipe;
    threat_filler_crit = threat_swipe_crit;
  }
  double average_auto_tps = in_n_auto * (get_hit_chance(false) * threat_auto + get_melee_crit_chance() * threat_auto_crit + get_glancing_blow_chance() * threat_auto_glancing) / time_estimation;
  double average_yellow_tps = get_hit_chance(true) * (1 - get_melee_crit_chance()) * (threat_maul * in_n_maul + threat_filler * in_n_filler + threat_mangle * n_mangle + threat_lacerate_direct * in_n_min_lacerate) + (get_hit_chance(true) * get_melee_crit_chance()) * (threat_maul_crit * in_n_maul + threat_filler_crit * in_n_filler + threat_mangle_crit * n_mangle + threat_lacerate_direct_crit * in_n_min_lacerate);
  average_yellow_tps /= time_estimation;
  result = average_auto_tps + average_yellow_tps + tps_lacerate_dot;
  if (gear[Slot::Trinket1].get_name() == "Darkmoon Card: Vengeance" || gear[Slot::Trinket2].get_name() == "Darkmoon Card: Vengeance")
  {
    double temp_sp = 0.001 * get_tot_sec_stat(SecondaryAttributes::SpellPower) + 0.0025 * get_tot_sec_stat(SecondaryAttributes::HolySpellPower);
    double vengenace_damage = (95.0 + 115.0) / 2.0;
    vengenace_damage += temp_sp;
    result += 1.3 * 0.1 * (1 - get_avoidance() / 100.0) * vengenace_damage / get_encounter()->get_attack_speed() * ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 2);
  }
  // threat enchantment
  if (gear[Slot::Hands].get_enchantment().get_name() == "Threat")
  {
    result *= 1.02;
  }
  return result;
}

std::function<double(const double *)> fit_tps_output(std::function<double(const double *)> fit_tps)
{
  std::function<double(const double *)> out = [fit_tps](const double *args) -> double
  { return fit_tps(args); };
  return out;
}

std::function<double(const double *)> fit_tps(Character *playerChar, double n_min_lacerate)
{
  std::function<double(const double *)> out = [playerChar, n_min_lacerate](const double *args)
      -> double
  {
    abort();
    uint n_auto = (uint)args[0];
    uint n_maul = (uint)args[1];
    uint n_filler = (uint)args[2];
    double time_estimation = (n_auto + n_maul) * playerChar->get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
    uint n_lacerate = (time_estimation - n_min_lacerate * playerChar->get_global_cd()) / 15.0 + n_min_lacerate;
    uint n_mangle = (uint)time_estimation / 6.0;
    if ((time_estimation <= 0) || (n_lacerate / time_estimation < 1.0 / 15.0) || ((n_filler + n_lacerate + n_mangle) * playerChar->get_global_cd() > time_estimation))
    {
      return 0;
    }
    double total_threat = playerChar->calc_bear_tps(n_auto, n_maul, n_filler, n_lacerate) * time_estimation;
    uint r_maul = 15;
    uint r_swipe = 20;
    uint r_mangle = 20;
    uint r_lacerate = 15;

    std::map<std::string, unsigned int>::iterator it = playerChar->talents.find("Shredding Attacks");
    if (it != playerChar->talents.end())
    {
      r_lacerate -= it->second;
    }
    it = playerChar->talents.find("Ferocity");
    if (it != playerChar->talents.end())
    {
      r_maul -= it->second;
      r_swipe -= it->second;
      r_mangle -= it->second;
    }
    it = playerChar->talents.find("Primal Fury");
    uint primalFuryTalents = 0;
    if (it != playerChar->talents.end())
    {
      primalFuryTalents = it->second;
    }
    uint n_swipe = 0;
    if (!playerChar->use_lacerate_over_swipe())
    {
      n_swipe = n_filler;
    }
    else
    {
      n_lacerate += n_filler;
    }
    double rage_use_per_second = playerChar->get_passive_rage_generation() / playerChar->get_encounter()->get_attack_speed() + playerChar->get_active_rage_generation() * n_auto / time_estimation;
    double rage_use = (playerChar->get_hit_chance(true) * (1 - playerChar->get_melee_crit_chance()) + playerChar->get_miss_chance()) * (r_maul * n_maul + r_swipe * n_swipe + r_mangle * n_mangle + r_lacerate * n_lacerate) + (playerChar->get_hit_chance(true) * playerChar->get_melee_crit_chance()) * (r_maul * n_maul + r_swipe * n_swipe + r_mangle * n_mangle + r_lacerate * n_lacerate - primalFuryTalents / 2.0 * 5 * (n_maul + n_swipe + n_mangle + n_lacerate)) + (playerChar->get_dodged_chance() + playerChar->get_parried_chance()) * 0.25 * (r_maul * n_maul + r_swipe * n_swipe + r_mangle * n_mangle + r_lacerate * n_lacerate);
    rage_use_per_second -= rage_use / time_estimation;
    if (rage_use_per_second < 0)
    {
      return 0;
    }

    double bear_dps = playerChar->calc_bear_dps(n_auto, n_maul, n_filler, n_lacerate);
    double raid_damage = playerChar->calc_average_raid_damage(total_threat, time_estimation) * playerChar->get_n_dds() + bear_dps * time_estimation;
    return -raid_damage / time_estimation;
    // if ((bear_dps+average_raid_dps*playerChar->get_n_dds())*time_estimation<playerChar->get_encounter()->get_health()){return 0;}
    // tps=temp_tps_sum;
    // return playerChar->get_encounter()->get_health()-(bear_dps+average_raid_dps*playerChar->get_n_dds())*time_estimation;
  };
  return out;
}

double Character::simple_bear_tps()
{
  double result;
  double time_window = get_tot_prim_stat(PrimaryAttributes::AttackSpeed) * 15;
  double time_factor = (1 / get_global_cd() - 1 / 6.0 - 1 / 15.0);
  n_auto = 0;
  n_maul = time_window / (double)get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  n_filler = time_window * time_factor;
  n_min_lacerate = time_window / 15.0;
  double rage = time_window * get_passive_rage_generation() / get_encounter()->get_attack_speed();
  uint r_maul = 15;
  uint r_swipe = 20;
  uint r_mangle = 20;
  uint r_lacerate = 15;

  std::map<std::string, unsigned int>::iterator it = talents.find("Shredding Attacks");
  if (it != talents.end())
  {
    r_lacerate -= it->second;
  }
  it = talents.find("Ferocity");
  if (it != talents.end())
  {
    r_maul -= it->second;
    r_swipe -= it->second;
    r_mangle -= it->second;
  }
  uint primalFuryTalents = 0;
  it = talents.find("Primal Fury");
  if (it != talents.end())
  {
    primalFuryTalents = it->second;
  }
  double temp_factor = (get_hit_chance(true) * (1 - get_melee_crit_chance()) + get_miss_chance() + 0.25 * (get_dodge_chance() + get_parried_chance()));
  double yellow_crit_chance = get_hit_chance(true) * get_melee_crit_chance();
  double effective_r_maul = r_maul * temp_factor + (r_maul - 5 * primalFuryTalents / 2.0) * yellow_crit_chance;
  double effective_r_lacerate = r_lacerate * temp_factor + (r_lacerate - 5 * primalFuryTalents / 2.0) * yellow_crit_chance;
  double effective_r_mangle = r_mangle * temp_factor + (r_mangle - 5 * primalFuryTalents / 2.0) * yellow_crit_chance;
  double effective_r_swipe = r_swipe * temp_factor + (r_swipe - 5 * primalFuryTalents / 2.0) * yellow_crit_chance;
  rage -= (effective_r_mangle / 6.0 + effective_r_lacerate / 15.0 + effective_r_maul / get_tot_prim_stat(PrimaryAttributes::AttackSpeed)) * time_window;
  // if (rage < 0)
  // {
  //   std::cout << get_passive_rage_generation() / get_encounter()->get_attack_speed() << "-" << (effective_r_mangle / 6.0 + effective_r_lacerate / 15.0 + effective_r_maul / get_tot_prim_stat(PrimaryAttributes::AttackSpeed))<< std::endl;
  //   std::cout << "simple bear tps failed." << std::endl;
  //   abort();
  // }
  it = talents.find("Predatory Instincts");
  double crit_bonus = 0;
  if (it != talents.end())
  {
    crit_bonus = it->second * 0.02;
  }
  double swipe_damage = get_attackpower() * 0.171 + 84;
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    swipe_damage += 10;
  }
  swipe_damage *= (1 - get_encounter()->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double threat_swipe = (swipe_damage + swipeBonusThreat_) * swipeThreatMultiplier_;
  double threat_swipe_crit = (swipe_damage * crit_bonus + swipeBonusThreat_) * swipeThreatMultiplier_;
  double lacerate_direct_dmg = 31 + 0.01 * get_attackpower();
  double lacerate_dot_dmg = 155 + get_attackpower() / 20; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of Ursoc")
  {
    lacerate_direct_dmg += 8;
    lacerate_dot_dmg += 8;
  }
  double threat_lacerate_direct = (lacerate_direct_dmg + lacerateDirectBonusThreat_) * lacerateDirectThreatMultiplier_;
  double threat_lacerate_direct_crit = (lacerate_direct_dmg * crit_bonus + lacerateDirectBonusThreat_) * lacerateDirectThreatMultiplier_;
  double effective_r_filler = 0;
  if ((threat_lacerate_direct * get_hit_chance(true) * (1 - get_melee_crit_chance()) + threat_lacerate_direct_crit * get_hit_chance(true) * get_melee_crit_chance()) >= (threat_swipe * get_hit_chance(true) * (1 - get_melee_crit_chance()) + threat_swipe_crit * get_hit_chance(true) * get_melee_crit_chance()))
  {
    isLacerateFiller_ = true;
    effective_r_filler = effective_r_lacerate;
  }
  else
  {
    isLacerateFiller_ = false;
    effective_r_filler = effective_r_swipe;
  }
  rage -= effective_r_filler * time_factor * time_window;
  if (rage < 0)
  {
    n_auto = (-rage) / (get_active_rage_generation() + effective_r_maul);
    n_maul -= n_auto;
    if ((n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) != time_window && n_maul >= 0)
    {
      std::cout << "Simplification failed." << std::endl;
      std::cout << (n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) << "!=" << time_window << std::endl;
      abort();
    }
  }

  result = calc_bear_tps(n_auto, n_maul, n_filler, n_min_lacerate);
  return result;
}

void Character::add_elixir(Elixir in)
{
  bool add = true;
  for (uint i = 0; i < elixirs_.size(); i++)
  {
    if ((elixirs_[i].is_guardian_elixir() && in.is_guardian_elixir()) || (elixirs_[i].is_battle_elixir() && in.is_battle_elixir()))
    {
      add = false;
      break;
    }
  }
  if (add)
  {
    parryHaste_ = false;
    saveMetric_ = true;
    saveTps_ = true;
    saveHps_ = true;
    saveWorstCase_ = true;
    reset_boni();
    elixirs_.push_back(in);
    set_prim_stats(get_prim_stats() + in.get_prim_stats());
    set_sec_stats(get_sec_stats() + in.get_sec_stats());
    set_prim_stat(PrimaryAttributes::Armor, get_prim_stat(PrimaryAttributes::Armor) - in.get_prim_stat(PrimaryAttributes::Armor));
  }
}

double Character::check_block_chance(double in, bool dual_wield)
{
  if (get_avoidance(dual_wield) + in > 100)
  {
    double result = 100 - get_avoidance(dual_wield);
    if (result < 0)
    {
      return 0;
    }
    return result;
  }
  return in;
}

double Character::get_effective_redoubt_chance()
{
  bool skilled = false;
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "Redoubt")
    {
      if (it->second != 5)
      {
        std::cout << "Not yet understood." << std::endl;
        abort();
      }
      skilled = true;
    }
  }
  if (!skilled)
  {
    return 0;
  }
  double tot_block_chance = get_block();
  if (gear[Slot::Libram].get_name() == "Libram of Repentance")
  {
    tot_block_chance += (43 * myH_ / fBlock_);
  }
  tot_block_chance = check_block_chance(tot_block_chance);
  double x1 = 40 - tot_block_chance;
  double x2 = 100 - tot_block_chance;
  // double y1 = tot_block_chance / 100.0 + 0.206309 - x1 * 0.00185542;
  // double y2 = tot_block_chance / 100.0;
  double avoidance = get_dodge_chance() + get_parry() + get_missed();
  if (avoidance < x1)
  {
    return (0.206309 - avoidance * 0.00185542) * 100;
  }
  else if (avoidance >= x1 && avoidance < x2)
  {
    double c = 0.645623 * tot_block_chance / 100.0 + 0.348888;
    double b = 0.00365483 * tot_block_chance / 100.0 - 0.00675105;
    double a = -6.66862 * pow(10, -6) * tot_block_chance / 100.0 + 3.2928 * pow(10, -5);
    double result = a * avoidance * avoidance + b * avoidance + c - tot_block_chance / 100.0;
    return result * 100.0;
  }
  return 0;
}

void Character::operator=(Character b)
{
  talents = b.talents;
  set_base_prim_stats(b.get_base_prim_stats());
  set_base_sec_stats(b.get_base_sec_stats());
  set_prim_stats(b.get_prim_stats());
  set_sec_stats(b.get_sec_stats());
  set_bonus_prim_stats(b.get_bonus_prim_stats());
  set_bonus_sec_stats(b.get_bonus_sec_stats());
  defense_ = b.getBaseDefense();
  expertise_ = b.getBaseExpertise();
  dodge_ = b.getBaseDodge();
  parry_ = b.getBaseParry();
  blockChance_ = b.getBaseBlockChance();
  crit_ = b.getBaseCrit();
  spellCrit_ = b.getBaseSpellCrit();
  hit_ = b.getBaseHit();
  spellHit_ = b.getBaseSpellHit();
  h_ = b.getH();
  gear = b.gear;
  number_of_rings = b.number_of_rings;
  number_of_trinkets = b.number_of_trinkets;
  buffs_ = b.get_buffs();
  elixirs_ = b.get_elixirs();
  (*boss_) = (*b.get_encounter());
  nDDs_ = b.get_n_dds();
  timeNeeded_ = b.get_time_of_encounter();
  savedTps_ = b.get_tps();
  saveTps_ = false;
  savedMetric_ = b.metric();
  saveMetric_ = false;
  trinketsParallel_ = b.how_use_trinkets();
  buffFood_ = b.get_buff_food();
}

const double Character::myH_ = 0.6313425; // for lvl 70 only
const double Character::fExpertise_ = 2.5;
const double Character::fDef_ = 1.5;
const double Character::fDodge_ = 13.8;
const double Character::fParry_ = 13.8;
const double Character::fBlock_ = 5.0;
const double Character::fHit_ = 10.0;
const double Character::fSpellHit_ = 8.0;
const double Character::fCrit_ = 14.0;
const double Character::fHaste_ = 10.0;
const double Character::fResilience_ = 28.75;
const double Character::fArmorPen_ = 3.756097412;
const double Character::rExpertise_ = Character::myH_ / Character::fExpertise_;
const double Character::rHit_ = Character::myH_ / Character::fHit_;
const double Character::rSpellHit_ = Character::myH_ / Character::fSpellHit_;
const double Character::rCrit_ = Character::myH_ / Character::fCrit_;
const double Character::rHaste_ = Character::myH_ / Character::fHaste_;
const double Character::rArmorPen_ = Character::myH_ / Character::fArmorPen_;
const double Character::rDef_ = Character::myH_ / Character::fDef_;
const double Character::rDefAvoidance_ = 14.8125;
const double Character::rDodge_ = Character::myH_ / Character::fDodge_;
const double Character::myRDodge_ = 0.0528579;
const double Character::rParry_ = Character::myH_ / Character::fDodge_;
const double Character::rBlock_ = Character::myH_ / Character::fBlock_;
const double Character::rResilience_ = Character::myH_ / Character::fResilience_;
const double Character::cD_ = 0; // for wotlk
const double Character::cP_ = 0; // for wotlk
const double Character::cM_ = 0; // for wotlk
const double Character::k_ = 0;  // for wotlk
const double Character::lacerateDirectBonusThreat_ = 11941 / 27.0;
const double Character::lacerateDirectThreatMultiplier_ = 27 / 31.0;
const double Character::swipeBonusThreat_ = 0;
const double Character::swipeThreatMultiplier_ = 1.3 * 1.15;
const double Character::maulBonusThreat_ = 0;
const double Character::maulThreatMultiplier_ = 1.3 * 1.15;
const double Character::mangleBonusThreat_ = 0;
const double Character::mangleThreatMultiplier_ = 1.3 * 1.15;
const unsigned int Character::tpsFitAttempts_ = 5000;
unsigned int Character::nDDs_ = 5;
unsigned int Character::maxPhase_ = 5;
bool Character::kings_ = false;
bool Character::sanctuary_ = false;
bool Character::bearForm_ = false;
bool Character::catForm_ = false;

Character::Character(CharacterClass inClass, Race inRace, const unsigned int inLevel, Boss *const inBoss) : charClass_(inClass), charRace_(inRace), level_(inLevel), boss_(inBoss), h_(-3.0 / 82.0 * level_ + 131.0 / 41.0), defense_(5 * level_), expertise_(0), dodge_(0), parry_(5), blockChance_(5), crit_(0), spellCrit_(0), hit_(0), spellHit_(0), trinketsParallel_(false), timeNeeded_(0), seal_("None"), isLacerateFiller_(false), recursions_(1), parryHaste_(false), saveMetric_(true), saveTps_(true), saveHps_(true), saveWorstCase_(true), saveDps_(true), savedTps_(0), savedMetric_(0), savedDps_(0), savedWorstCase_(false), savedWorstCaseN_(0)
{
  if (get_class() == CharacterClass::Paladin && get_race() == Race::Human && level_ == 70)
  {
    set_base_prim_stat(PrimaryAttributes::Armor, 0);
    set_base_prim_stat(PrimaryAttributes::Strength, 126);
    set_base_prim_stat(PrimaryAttributes::Agility, 77);
    set_base_prim_stat(PrimaryAttributes::Stamina, 120);
    set_base_prim_stat(PrimaryAttributes::Intelligence, 83);
    set_base_prim_stat(PrimaryAttributes::Spirit, 98);
    set_base_prim_stat(PrimaryAttributes::Health, 3197);
    set_base_prim_stat(PrimaryAttributes::Mana, 2938);
    dodge_ += 0.65;
    spellCrit_ += 3.31;
    crit_ = 0.65;
    set_base_sec_stat(SecondaryAttributes::AttackPower, 214.0797);
  }
  else if (get_class() == CharacterClass::Druid && get_race() == Race::Tauren && level_ == 70)
  {
    set_base_prim_stat(PrimaryAttributes::Armor, 0);
    set_base_prim_stat(PrimaryAttributes::Strength, 81);
    set_base_prim_stat(PrimaryAttributes::Agility, 65);
    set_base_prim_stat(PrimaryAttributes::Stamina, 85);
    set_base_prim_stat(PrimaryAttributes::Intelligence, 115);
    set_base_prim_stat(PrimaryAttributes::Spirit, 135);
    set_base_prim_stat(PrimaryAttributes::Health, 4498 / 1.05 - 85 * 10);
    set_base_prim_stat(PrimaryAttributes::Mana, 3815);
    set_base_prim_stat(PrimaryAttributes::NatureResistance, 10);
    dodge_ += 2.62;
    spellCrit_ += 3.29;
    crit_ = 0.77;
    set_base_sec_stat(SecondaryAttributes::AttackPower, 0);
    MarkOfTheWild motw;
    add_buff(motw);
  }
  else
  {
    std::cout << "Not defined character combination." << std::endl;
    abort();
  }
}

Character::Character(const Character &in) : charClass_(in.get_class()), charRace_(in.get_race()), level_(in.getLevel()), boss_(in.get_encounter()), h_(-3.0 / 82.0 * level_ + 131.0 / 41.0), defense_(in.getBaseDefense()), expertise_(in.getBaseExpertise()), dodge_(in.getBaseDodge()), parry_(in.getBaseParry()), blockChance_(in.getBaseBlockChance()), crit_(in.getBaseCrit()), spellCrit_(in.getBaseSpellCrit()), hit_(in.getBaseHit()), spellHit_(in.getBaseSpellHit()), trinketsParallel_(in.how_use_trinkets()), timeNeeded_(in.get_time_of_encounter()), seal_(in.getSeal()), isLacerateFiller_(in.use_lacerate_over_swipe()), recursions_(in.getRecursions()), parryHaste_(in.calculatedParryHaste()), saveMetric_(in.saveMetric()), saveTps_(in.saveTps()), saveHps_(in.saveHps()), saveWorstCase_(in.saveWorstCase()), saveDps_(in.saveDps()), savedTps_(in.getSavedTps()), savedMetric_(in.getSavedMetric()), savedDps_(in.getSavedDps()), savedWorstCase_(in.savedWorstCase()), savedWorstCaseN_(in.getSavedWorstCaseN())
{
  talents = in.talents;
  set_base_prim_stats(in.get_base_prim_stats());
  set_base_sec_stats(in.get_base_sec_stats());
  set_prim_stats(in.get_prim_stats());
  set_sec_stats(in.get_sec_stats());
  set_bonus_prim_stats(in.get_bonus_prim_stats());
  set_bonus_sec_stats(in.get_bonus_sec_stats());
  h_ = in.getH();
  gear = in.gear;
  number_of_rings = in.number_of_rings;
  number_of_trinkets = in.number_of_trinkets;
  buffs_ = in.get_buffs();
  elixirs_ = in.get_elixirs();
  (*boss_) = (*in.get_encounter());
  nDDs_ = in.get_n_dds();
  timeNeeded_ = in.get_time_of_encounter();
  savedTps_ = in.getSavedTps();
  savedMetric_ = in.getSavedMetric();
  trinketsParallel_ = in.how_use_trinkets();
  buffFood_ = in.get_buff_food();
}

void Character::set_talent(std::string name_, unsigned int points)
{
  talents.insert(std::pair<std::string, unsigned int>(name_, points));
  if (name_ == "Deflection")
  {
    parry_ += (1.0 * points);
  }
  else if (name_ == "Improved Seal of the Crusader")
  {
    crit_ += (points * 1.0);
    spellCrit_ += (points * 1.0);
  }
  else if (name_ == "Conviction")
  {
    crit_ += (points * 1.0);
  }
  else if (name_ == "Vengeance")
  {
    crit_ += (1.0 * points * 3.0);
    spellCrit_ += (1.0 * points * 3.0);
  }
  else if (name_ == "Sanctified Seals")
  {
    crit_ += (1.0 * points);
    spellCrit_ += (1.0 * points);
  }
  else if (name_ == "Anticipation")
  {
    defense_ += (4 * points);
  }
  else if (name_ == "Combat Expertise")
  {
    expertise_ += (1 * points);
  }
  else if (name_ == "Holy Power")
  {
    spellCrit_ += (1.0 * points);
  }
  else if (name_ == "Precision")
  {
    hit_ += (1.0 * points);
  }
  else if (name_ == "Improved Holy Shield" && points == 2)
  {
    blockChance_ += 30.0;
  }
}

double Character::get_dodge_chance_with_dr()
{
  double agi_to_dodge = 0;
  if (get_class() == CharacterClass::Paladin)
  {
    agi_to_dodge = 0.04;
  }
  else if (get_class() == CharacterClass::Druid)
  {
    agi_to_dodge = 0.07;
  }
  // double a_b = basePrimStats_.get_stat(PrimaryAttributes::Agility) / r_d;
  double a_u = get_tot_prim_stat(PrimaryAttributes::Agility) * agi_to_dodge;
  double d_u = (get_tot_sec_stat(SecondaryAttributes::DodgeRating)) * myRDodge_;
  double f_u = std::max(0.0, ((int)(get_tot_sec_stat(SecondaryAttributes::DefenseRating) * rDef_ + defense_ - 5 * boss_->get_lvl())) * 0.04);
  double u = a_u + d_u + f_u;
  double talents_dodge = 0;
  std::map<std::string, unsigned int>::iterator it = talents.find("Feral Swiftness");
  if (it != talents.end() && (bearForm_ || catForm_))
  {
    talents_dodge = (it->second * 2.0);
  }
  return u * cD_ / (u + k_ * cD_) + dodge_ + talents_dodge;
}

double Character::get_glancing_blow_chance()
{
  double result = 6 + 5 * (boss_->get_lvl() - level_) * 6 / 5.0;
  return result / 100.0;
}

double Character::get_glancing_blow_damage()
{
  double result;
  double min_damage = std::max(std::min(1.3 - 0.05 * (boss_->get_lvl() - level_) * 5, 0.91), 0.01);
  double max_damage = std::max(std::min(1.2 - 0.03 * (boss_->get_lvl() - level_) * 5, 0.99), 0.2);
  result = (1 - (max_damage + min_damage) / 2.0) * get_white_damage();
  return result;
}

double Character::get_dodge_chance()
{
  double agi_to_dodge = 0;
  double offset = 0;
  if (get_class() == CharacterClass::Paladin)
  {
    agi_to_dodge = 0.04;
  }
  else if (get_class() == CharacterClass::Druid)
  {
    agi_to_dodge = 1 / 14.784; // 0.0680132;
    offset = -5.07842;         //-1.87215;
  }
  double root_fit_r_dodge = 1 / 17.4537;
  double root_fit_r_def = 1 / 0.928253;
  double a_u = get_tot_prim_stat(PrimaryAttributes::Agility) * agi_to_dodge;
  double d_u = get_tot_sec_stat(SecondaryAttributes::DodgeRating) * root_fit_r_dodge;
  double f_u = std::max(0.0, round(get_tot_sec_stat(SecondaryAttributes::DefenseRating) * root_fit_r_def + defense_ - 5 * boss_->get_lvl()) * 0.04);
  double u = a_u + d_u + f_u + dodge_ + offset;
  std::map<std::string, unsigned int>::iterator it = talents.find("Feral Swiftness");
  if (it != talents.end() && (bearForm_ || catForm_))
  {
    u += (it->second * 2.0);
  }
  return u;
}

unsigned int Character::get_armor(unsigned int debuff)
{
  double temp_armor = get_tot_prim_stat(PrimaryAttributes::Armor) + get_tot_sec_stat(SecondaryAttributes::GreenArmor);
  temp_armor += (get_tot_prim_stat(PrimaryAttributes::Agility) * 2);
  return round(temp_armor) - debuff;
}

double Character::get_armor_reduction(unsigned int debuff)
{
  unsigned int armor = get_armor(debuff);
  double result = armor / (armor + 467.5 * boss_->get_lvl() - 22167.5);
  if (result > 0.75)
  {
    result = 0.75;
  }
  return result;
}

double Character::get_parry()
{
  if (bearForm_ || catForm_)
  {
    return 0;
  }
  double temp_defense = std::max(0.0, get_tot_sec_stat(SecondaryAttributes::DefenseRating) / fDef_ * myH_ + defense_ - 5 * boss_->get_lvl());
  return get_tot_sec_stat(SecondaryAttributes::ParryRating) / fParry_ * myH_ + parry_ + 0.04 * (int)temp_defense;
}

double Character::get_block(bool dual_wield)
{
  if (get_class() == CharacterClass::Paladin || get_class() == CharacterClass::Warrior)
  {
    double temp_block = std::max(0.0, get_tot_sec_stat(SecondaryAttributes::DefenseRating) / fDef_ * myH_ + defense_ - 5 * boss_->get_lvl());
    double result = get_tot_sec_stat(SecondaryAttributes::BlockChanceRating) / fBlock_ * myH_ + blockChance_ + 0.04 * (int)temp_block;
    if (get_avoidance(dual_wield) + result > 100.0)
    {
      result = 100.0 - get_avoidance(dual_wield);
      if (result < 0)
      {
        return 0;
      }
    }
    if (gear[Slot::Libram].get_name() == "Libram of Repentance" && get_class() == CharacterClass::Paladin)
    {
      result += (43 * myH_ / fBlock_);
    }
    return result / 100.0;
  }
  return 0;
}

double Character::get_missed(bool dual_wield)
{
  double temp_defense = std::max(0.0, get_tot_sec_stat(SecondaryAttributes::DefenseRating) / fDef_ * myH_ + defense_ - 5 * boss_->get_lvl());
  double result = (int)temp_defense * 0.04 + 5.0;
  if (dual_wield)
  {
    result += 19;
  }
  return result;
}

double Character::get_eff_hp(double time_in_seconds_)
{
  if (!parryHaste_)
  {
    parry_haste_sim();
  }
  double time_in_seconds = time_in_seconds_;
  set_encounter(nDDs_);
  if (time_in_seconds_ == 0.0)
  {
    time_in_seconds = timeNeeded_;
  }
  double block_value = get_block_value();
  double tot_block_chance = get_block() + get_effective_redoubt_chance();
  unsigned int sanctuary_absorbtion = 0;
  if (sanctuary_)
  {
    sanctuary_absorbtion = 80 * (unsigned int)(time_in_seconds / boss_->get_attack_speed() * (1 - get_avoidance() / 100.0));
  }

  if (gear[Slot::Libram].get_name() == "Libram of Repentance")
  {
    tot_block_chance += (43 * myH_ / fBlock_);
  }
  check_block_chance(tot_block_chance);
  double critted_chance = (5 + 0.2 * (boss_->get_lvl() - level_)) / 100.0 - red_chance_to_get_crit();
  double physical =
      (time_in_seconds * get_hps() + get_hp() + (unsigned int)(tot_block_chance / 100.0 * time_in_seconds / boss_->get_attack_speed()) * block_value + sanctuary_absorbtion) /
      ((1 - get_armor_reduction()) * (1 - get_avoidance() / 100.0 + critted_chance + 0.5 * get_crush()));
  // double unblockable_physical = (time_in_seconds * hps + heal + get_hp() / (1 - get_avoidance() / 100.0) + sanctuary_absorbtion) / ((1 - get_armor_reduction()) * (1 - critted_chance - get_crush() + 2 * critted_chance + 1.5 * get_crush()));
  // double magical_arcane = (time_in_seconds * hps + get_hp()) / (1 - average_resistance("Arcane"));
  // double magical_fire = (time_in_seconds * hps + get_hp()) / (1 - average_resistance("Fire"));
  // double magical_frost = (time_in_seconds * hps + get_hp()) / (1 - average_resistance("Frost"));
  // double frost_based_melee = (time_in_seconds * hps + get_hp() / (1 - get_avoidance() / 100.0)) / ((1 - average_resistance("Frost")) * (1 - critted_chance + 2 * critted_chance));
  // double magical_nature = (time_in_seconds * hps + get_hp()) / (1 - average_resistance("Nature"));
  // double magical_shadow = (time_in_seconds * hps + get_hp()) / (1 - average_resistance("Shadow"));

  double result = physical;
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "Improved Righteous Fury")
    {
      result /= (1.0 - 0.02 * it->second);
      break;
    }
  }
  if (result < 0)
  {
    std::cout << "eff hp is smaller than 0!" << std::endl;
    std::cout << "tot block chance=" << tot_block_chance << std::endl;

    std::cout << "dodge chance=" << get_dodge_chance() << std::endl;
    std::cout << "parry chance=" << get_parry() << std::endl;
    std::cout << "miss chance=" << get_missed() << std::endl;
    std::cout << "armor reduction=" << get_armor_reduction() * 100.0 << std::endl;
    std::cout << "tot avoidance=" << (1 - get_armor_reduction()) * (1 - get_avoidance() / 100.0) << std::endl;
    abort();
  }
  return result;
}

void Character::equip(Gear gear_piece)
{
  parryHaste_ = false;
  saveMetric_ = true;
  saveTps_ = true;
  saveHps_ = true;
  saveWorstCase_ = true;
  saveDps_ = true;
  recursions_ = 1;
  if ((uint)gear_piece.get_slot() == (uint)Slot::Ring && number_of_rings < 2)
  {
    Slot tempSlot;
    if (number_of_rings == 0)
    {
      tempSlot = Slot::Trinket1;
    }
    else
    {
      tempSlot = Slot::Trinket2;
    }
    gear_piece.set_slot(tempSlot);
    number_of_rings++;
  }
  else if ((uint)gear_piece.get_slot() == (uint)Slot::Ring && number_of_rings >= 2)
  {
    std::cout << "Too many rings equipped." << std::endl;
    abort();
  }
  else if (gear_piece.get_slot() == Slot::Trinket && number_of_trinkets < 2)
  {
    Slot tempSlot;
    if (number_of_trinkets == 0)
    {
      tempSlot = Slot::Trinket1;
    }
    else
    {
      tempSlot = Slot::Trinket2;
    }
    gear_piece.set_slot(tempSlot);
    number_of_trinkets++;
  }
  reset_boni();
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "Toughness")
    {
      gear_piece.set_prim_stat(PrimaryAttributes::Armor, round(gear_piece.get_prim_stat(PrimaryAttributes::Armor) * (1.0 + it->second * 0.02)));
      break;
    }
    else if (it->first == "Thick Hide")
    {
      if (it->second == 1)
      {
        gear_piece.set_prim_stat(PrimaryAttributes::Armor, round(gear_piece.get_prim_stat(PrimaryAttributes::Armor) * (1.04)));
      }
      else if (it->second == 2)
      {
        gear_piece.set_prim_stat(PrimaryAttributes::Armor, round(gear_piece.get_prim_stat(PrimaryAttributes::Armor) * (1.07)));
      }
      else if (it->second == 3)
      {
        gear_piece.set_prim_stat(PrimaryAttributes::Armor, round(gear_piece.get_prim_stat(PrimaryAttributes::Armor) * (1.1)));
      }
      break;
    }
  }
  if (bearForm_)
  {
    gear_piece.set_prim_stat(PrimaryAttributes::Armor, gear_piece.get_prim_stat(PrimaryAttributes::Armor) * 5);
  }
  for (uint i = 0; i < gear[Slot::Head].gems.size(); i++)
  {
    if (find(gear[Slot::Head].gems[i].get_color().begin(), gear[Slot::Head].gems[i].get_color().end(), Color::Meta) != gear[Slot::Head].gems[i].get_color().end())
    {
      if (gear[Slot::Head].gems[i].active)
      {
        gear[Slot::Head].gems[i].active = false;
        if (gear[Slot::Head].gems[i].get_name() == "Tenacious Earthstorm Diamond" || gear[Slot::Head].gems[i].get_name() == "Eternal Earthstorm Diamond")
        {
          secondaryStats_.add_stat(SecondaryAttributes::DefenseRating, -12);
        }
        else if (gear[Slot::Head].gems[i].get_name() == "Powerful Earthstorm Diamond")
        {
          primaryStats_.add_stat(PrimaryAttributes::Stamina, -18);
        }
      }
    }
  }

  if (gear.find(gear_piece.get_slot()) != gear.end())
  {
    // set_prim_stats(get_prim_stats() - gear[gear_piece.get_slot()].get_prim_stats());
    // set_sec_stats(get_sec_stats() - gear[gear_piece.get_slot()].get_sec_stats());
    gear[gear_piece.get_slot()] = gear_piece;
    // set_prim_stats(get_prim_stats() + gear_piece.get_prim_stats());
    // set_sec_stats(get_sec_stats() + gear_piece.get_sec_stats());
    // gear[gear_piece.get_slot()].equipped = true;
  }
  else
  {
    gear.insert(std::pair<Slot, Gear>(gear_piece.get_slot(), gear_piece));
    // set_prim_stats(get_prim_stats() + gear_piece.get_prim_stats());
    // set_sec_stats(get_sec_stats() + gear_piece.get_sec_stats());
    // gear[gear_piece.get_slot()].equipped = true;
  }
}

double Character::red_chance_to_get_crit()
{
  double result = ((int)(get_tot_sec_stat(SecondaryAttributes::DefenseRating) * rDef_ + defense_ - 5 * boss_->get_lvl())) * 0.04 + get_tot_sec_stat(SecondaryAttributes::ResilienceRating) * 0.025339367;
  std::map<std::string, unsigned int>::iterator it = talents.find("Survival of the Fittest");
  if (it != talents.end())
  {
    result += it->second * 1.0;
  }
  return std::min(result / 100.0, (5 + 0.2 * (boss_->get_lvl() - level_)) / 100.0);
}

double Character::get_critted_chance()
{
  double result = (5 + 0.2 * (boss_->get_lvl() - level_)) / 100.0 - red_chance_to_get_crit();
  return result;
}

double Character::get_tps()
{
  double result = savedTps_;
  if (gear[Slot::Trinket1].get_uptime() > 0 && gear[Slot::Trinket2].get_uptime() > 0 && recursions_ > 0)
  {
    recursions_--;
    double tps00 = get_tps() * (std::max(gear[Slot::Trinket1].get_cooldown(), gear[Slot::Trinket2].get_cooldown()) - std::max(gear[Slot::Trinket1].get_uptime(), gear[Slot::Trinket2].get_uptime())) / std::max(gear[Slot::Trinket1].get_cooldown(), gear[Slot::Trinket2].get_cooldown());
    double tps00_serial = get_tps() * (1 - gear[Slot::Trinket1].get_uptime() / gear[Slot::Trinket1].get_cooldown() - gear[Slot::Trinket2].get_uptime() / gear[Slot::Trinket2].get_cooldown());
    gear[Slot::Trinket1].activate();
    gear[Slot::Trinket2].activate();
    compute_stats();
    double tps11 = std::min(gear[Slot::Trinket1].get_uptime(), gear[Slot::Trinket2].get_uptime()) * get_tps() / std::max(gear[Slot::Trinket1].get_cooldown(), gear[Slot::Trinket2].get_cooldown());
    double tps01_serial = 0;
    double tps10_serial = 0;
    if (gear[Slot::Trinket1].get_uptime() > gear[Slot::Trinket2].get_uptime())
    {
      gear[Slot::Trinket1].deactivate();
      compute_stats();
      tps01_serial = get_tps() * gear[Slot::Trinket2].get_uptime() / gear[Slot::Trinket2].get_cooldown();
      gear[Slot::Trinket1].activate();
      gear[Slot::Trinket2].deactivate();
      compute_stats();
      tps10_serial = get_tps() * gear[Slot::Trinket1].get_uptime() / gear[Slot::Trinket1].get_cooldown();
    }
    else
    {
      gear[Slot::Trinket2].deactivate();
      compute_stats();
      tps10_serial = get_tps() * gear[Slot::Trinket1].get_uptime() / gear[Slot::Trinket1].get_cooldown();
      gear[Slot::Trinket2].activate();
      gear[Slot::Trinket1].deactivate();
      compute_stats();
      tps01_serial = get_tps() * gear[Slot::Trinket2].get_uptime() / gear[Slot::Trinket2].get_cooldown();
    }

    double tps01 = get_tps() * (std::max(gear[Slot::Trinket1].get_uptime(), gear[Slot::Trinket2].get_uptime()) - std::min(gear[Slot::Trinket1].get_uptime(), gear[Slot::Trinket2].get_uptime())) / std::max(gear[Slot::Trinket1].get_cooldown(), gear[Slot::Trinket2].get_cooldown());
    gear[Slot::Trinket1].deactivate();
    gear[Slot::Trinket2].deactivate();
    compute_stats();
    double tps_parallel = tps00 + tps01 + tps11;
    double tps_serial = tps00_serial + tps01_serial + tps10_serial;
    result = std::max(tps_parallel, tps_serial);
  }
  else if ((gear[Slot::Trinket1].get_uptime() > 0 || gear[Slot::Trinket2].get_uptime() > 0) && recursions_ > 0)
  {
    recursions_--;
    double tps0 = get_tps() * (1 - std::max(gear[Slot::Trinket1].get_uptime(), gear[Slot::Trinket2].get_uptime()) / std::max(gear[Slot::Trinket1].get_cooldown(), gear[Slot::Trinket2].get_cooldown()));
    double tps1 = 0;
    if (gear[Slot::Trinket1].get_uptime() > 0)
    {
      gear[Slot::Trinket1].activate();
      compute_stats();
      double temp_tps = get_tps();
      tps1 = temp_tps * gear[Slot::Trinket1].get_uptime() / gear[Slot::Trinket1].get_cooldown();
      gear[Slot::Trinket1].deactivate();
    }
    else if (gear[Slot::Trinket2].get_uptime() > 0)
    {
      gear[Slot::Trinket2].activate();
      compute_stats();
      double temp_tps = get_tps();
      tps1 = temp_tps * gear[Slot::Trinket2].get_uptime() / gear[Slot::Trinket2].get_cooldown();
      gear[Slot::Trinket2].deactivate();
    }
    else
    {
      std::cout << "error" << std::endl;
      abort();
    }
    compute_stats();
    result = tps0 + tps1;
  }
  else
  {
    recursions_--;
    if (get_class() == CharacterClass::Druid)
    {
      result = get_bear_tps();
    }
    else if (get_class() == CharacterClass::Paladin)
    {
      result = get_paladin_tps();
    }
    else
    {
      std::cout << "Class not implemented" << std::endl;
      abort();
    }
  }
  if (result == 0)
  {
    abort();
  }
  saveTps_ = false;
  return result;
}

void Character::compute_stats()
{
  primaryStats_.reset();
  secondaryStats_.reset();
  bonusPrimStats_.reset();
  bonusSecStats_.reset();
  for (uint i = 0; i < buffs_.size(); i++)
  {
    for (uint j = (uint)PrimaryAttributes::FirstPrimary; j < (uint)PrimaryAttributes::LastPrimary; j++)
    {
      primaryStats_.add_stat((PrimaryAttributes)j, buffs_[i].get_prim_stat((PrimaryAttributes)j));
    }
    for (uint j = (uint)SecondaryAttributes::FirstSecondary; j < (uint)SecondaryAttributes::LastSecondary; j++)
    {
      secondaryStats_.add_stat((SecondaryAttributes)j, buffs_[i].get_sec_stat((SecondaryAttributes)j));
    }
  }
  for (uint i = 0; i < elixirs_.size(); i++)
  {
    for (uint j = (uint)PrimaryAttributes::FirstPrimary; j < (uint)PrimaryAttributes::LastPrimary; j++)
    {
      primaryStats_.add_stat((PrimaryAttributes)j, elixirs_[i].get_prim_stat((PrimaryAttributes)j));
    }
    for (uint j = (uint)SecondaryAttributes::FirstSecondary; j < (uint)SecondaryAttributes::LastSecondary; j++)
    {
      secondaryStats_.add_stat((SecondaryAttributes)j, elixirs_[i].get_sec_stat((SecondaryAttributes)j));
    }
  }
  for (uint j = (uint)PrimaryAttributes::FirstPrimary; j < (uint)PrimaryAttributes::LastPrimary; j++)
  {
    primaryStats_.add_stat((PrimaryAttributes)j, buffFood_.get_prim_stat((PrimaryAttributes)j));
  }
  for (uint j = (uint)SecondaryAttributes::FirstSecondary; j < (uint)SecondaryAttributes::LastSecondary; j++)
  {
    secondaryStats_.add_stat((SecondaryAttributes)j, buffFood_.get_sec_stat((SecondaryAttributes)j));
  }

  std::map<std::string, unsigned int>::iterator holy_guidance = talents.begin(), combat_expertise = talents.begin(), sacred_duty = talents.begin(), shield_specialization = talents.begin(),
                                                imp_devotion_aura = talents.begin();
  compute_set_boni();
  std::vector<Socket> gems;
  if (bearForm_)
  {
    set_base_prim_stat(PrimaryAttributes::AttackSpeed, 2.5);
  }
  else if (catForm_)
  {
    set_base_prim_stat(PrimaryAttributes::AttackSpeed, 1.0);
  }
  bonusPrimStats_.set_stat(PrimaryAttributes::AttackSpeed, -(1.0 - 1.0 / (1.0 + get_haste())) * get_prim_stat(PrimaryAttributes::AttackSpeed));
  for (std::unordered_map<Slot, Gear, std::hash<uint>>::iterator it = gear.begin(); it != gear.end(); it++)
  {
    // if (!it->second.equipped)
    // {
    set_prim_stats(get_prim_stats() + it->second.get_prim_stats());
    set_sec_stats(get_sec_stats() + it->second.get_sec_stats());
    it->second.equipped = true;
    // }
    gems.insert(gems.end(), it->second.gems.begin(), it->second.gems.end());
  }

  for (uint i = 0; i < gear[Slot::Head].gems.size(); i++)
  {
    if (find(gear[Slot::Head].gems[i].get_color().begin(), gear[Slot::Head].gems[i].get_color().end(), Color::Meta) != gear[Slot::Head].gems[i].get_color().end())
    {
      if (gear[Slot::Head].gems[i].is_active(gems))
      {
        if (gear[Slot::Head].gems[i].get_name() == "Tenacious Earthstorm Diamond" || gear[Slot::Head].gems[i].get_name() == "Eternal Earthstorm Diamond")
        {
          secondaryStats_.add_stat(SecondaryAttributes::DefenseRating, 12);
        }
        else if (gear[Slot::Head].gems[i].get_name() == "Powerful Earthstorm Diamond")
        {
          primaryStats_.add_stat(PrimaryAttributes::Stamina, 18);
        }
        gear[Slot::Head].socket_bonus();
      }
    }
  }
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "Divine Strength")
    {
      bonusPrimStats_.add_stat(PrimaryAttributes::Strength, round((basePrimStats_.get_stat(PrimaryAttributes::Strength) + get_prim_stat(PrimaryAttributes::Strength)) * (1 + it->second * 0.02)));
    }
    else if (it->first == "Divine Intellect")
    {
      bonusPrimStats_.add_stat(PrimaryAttributes::Intelligence, round((basePrimStats_.get_stat(PrimaryAttributes::Intelligence) + get_prim_stat(PrimaryAttributes::Intelligence)) * (1 + it->second * 0.02)));
    }
    else if (it->first == "Holy Guidance")
    {
      holy_guidance = it;
    }
    else if (it->first == "Sacred Duty")
    {
      sacred_duty = it;
    }
    else if (it->first == "Combat Expertise")
    {
      combat_expertise = it;
    }
    else if (it->first == "Shield Specialization")
    {
      shield_specialization = it;
    }
    else if (it->first == "Improved Devotion Aura")
    {
      imp_devotion_aura = it;
    }
    else if (it->first == "Predatory Strikes")
    {
      bonusSecStats_.add_stat(SecondaryAttributes::AttackPower, (1.5 * level_));
    }
    else if (it->first == "Heart of the Wild")
    {
      bonusPrimStats_.add_stat(PrimaryAttributes::Intelligence, 0.2 * get_tot_prim_stat(PrimaryAttributes::Intelligence));
      if (bearForm_)
      {
        bonusPrimStats_.add_stat(PrimaryAttributes::Stamina, 0.2 * get_tot_prim_stat(PrimaryAttributes::Stamina));
      }
      else if (catForm_)
      {
        bonusSecStats_.add_stat(SecondaryAttributes::AttackPower, 0.1 * (get_sec_stat(SecondaryAttributes::AttackPower) + get_bonus_sec_stat(SecondaryAttributes::AttackPower)));
      }
    }
    else if (it->first == "Survival of the Fittest")
    {
      double bonus = it->second * 0.01;
      bonusPrimStats_.add_stat(PrimaryAttributes::Strength, bonus * (get_prim_stat(PrimaryAttributes::Strength) + get_base_prim_stat(PrimaryAttributes::Strength)));
      bonusPrimStats_.add_stat(PrimaryAttributes::Agility, bonus * (get_prim_stat(PrimaryAttributes::Agility) + get_base_prim_stat(PrimaryAttributes::Agility)));
      bonusPrimStats_.add_stat(PrimaryAttributes::Stamina, bonus * (get_prim_stat(PrimaryAttributes::Stamina) + get_base_prim_stat(PrimaryAttributes::Stamina)));
      bonusPrimStats_.add_stat(PrimaryAttributes::Intelligence, bonus * (get_prim_stat(PrimaryAttributes::Intelligence) + get_base_prim_stat(PrimaryAttributes::Intelligence)));
      bonusPrimStats_.add_stat(PrimaryAttributes::Spirit, bonus * (get_prim_stat(PrimaryAttributes::Spirit) + get_base_prim_stat(PrimaryAttributes::Spirit)));
    }
  }
  if (bearForm_)
  {
    bonusPrimStats_.add_stat(PrimaryAttributes::Stamina, 0.25 * (get_prim_stat(PrimaryAttributes::Stamina) + get_base_prim_stat(PrimaryAttributes::Stamina)));
    bonusSecStats_.add_stat(SecondaryAttributes::AttackPower, 210);
  }

  double stamina_bonus = 0;
  if (sacred_duty->first == "Sacred Duty" && combat_expertise->first == "Combat Expertise")
  {
    stamina_bonus = ((basePrimStats_.get_stat(PrimaryAttributes::Stamina) + get_prim_stat(PrimaryAttributes::Stamina)) * (1 + sacred_duty->second * 0.03) * (1 + combat_expertise->second * 0.02)) - basePrimStats_.get_stat(PrimaryAttributes::Stamina) - get_prim_stat(PrimaryAttributes::Stamina);
  }
  else if (sacred_duty->first == "Sacred Duty" && combat_expertise->first != "Combat Expertise")
  {
    stamina_bonus = ((basePrimStats_.get_stat(PrimaryAttributes::Stamina) + get_prim_stat(PrimaryAttributes::Stamina)) * sacred_duty->second * 0.03);
  }
  else if (sacred_duty->first != "Sacred Duty" && combat_expertise->first == "Combat Expertise")
  {
    stamina_bonus = ((basePrimStats_.get_stat(PrimaryAttributes::Stamina) + get_prim_stat(PrimaryAttributes::Stamina)) * combat_expertise->second * 0.02);
  }
  bonusPrimStats_.add_stat(PrimaryAttributes::Stamina, round(stamina_bonus));
  if (kings_)
  {
    bonusPrimStats_.add_stat(PrimaryAttributes::Stamina, round(0.1 * get_tot_prim_stat(PrimaryAttributes::Stamina)));
    bonusPrimStats_.set_stat(PrimaryAttributes::Strength, round(0.1 * get_tot_prim_stat(PrimaryAttributes::Strength)));
    bonusPrimStats_.set_stat(PrimaryAttributes::Agility, round(0.1 * get_tot_prim_stat(PrimaryAttributes::Agility)));
    bonusPrimStats_.set_stat(PrimaryAttributes::Intelligence, round(0.1 * get_tot_prim_stat(PrimaryAttributes::Intelligence)));
    bonusPrimStats_.set_stat(PrimaryAttributes::Spirit, round(0.1 * get_tot_prim_stat(PrimaryAttributes::Spirit)));
  }
  if (holy_guidance->first == "Holy Guidance")
  {
    bonusSecStats_.set_stat(SecondaryAttributes::SpellPower, round(get_tot_prim_stat(PrimaryAttributes::Intelligence) * (holy_guidance->second * 0.07)));
    bonusSecStats_.set_stat(SecondaryAttributes::Healing, round(get_tot_prim_stat(PrimaryAttributes::Intelligence) * (holy_guidance->second * 0.07)));
  }
  if (gear[Slot::Libram].get_name() == "Libram of Truth")
  {
    double armor_temp = 861;
    if (imp_devotion_aura->first == "Improved Devotion Aura")
    {
      armor_temp *= (1 + 0.08 * imp_devotion_aura->second);
    }
    bonusPrimStats_.add_stat(PrimaryAttributes::Armor, (110 + armor_temp));
  }
  if (get_race() == Race::Tauren)
  {
    bonusPrimStats_.set_stat(PrimaryAttributes::Health, round((get_tot_prim_stat(PrimaryAttributes::Health) + get_tot_prim_stat(PrimaryAttributes::Stamina) * 10) * 0.05));
  }
  if (get_class() == CharacterClass::Paladin)
  {
    bonusSecStats_.set_stat(SecondaryAttributes::AttackPower, get_tot_prim_stat(PrimaryAttributes::Strength) * 2 + level_ * 3 - 20);
  }
  bonusPrimStats_.set_stat(PrimaryAttributes::WeaponDamage, get_attackpower() / 3.5 * get_tot_prim_stat(PrimaryAttributes::AttackSpeed));
  // bonusPrimStats_.add_stat(PrimaryAttributes::Mana, (basePrimStats_.get_stat(PrimaryAttributes::Intelligence) * 15 + get_prim_stat(PrimaryAttributes::Intelligence) * 15));
  /*if (shield_specialization->first == "Shield Specialization") {
    bonusSecStats_.block_value += round(get_tot_sec_stat(SecondaryAttribute::BlockValue) * shield_specialization->second * 0.1);
  }
  for (uint i = 0; i < gear[Slot::Head].gems.size(); i++) {
    if (gear[Slot::Head].gems[i].get_name() == "Eternal Earthstorm Diamond" && gear[Slot::Head].gems[i].active) {
      bonusSecStats_.block_value += (0.1 * secondaryStats_.block_value);
    }
  }*/
  set_encounter(nDDs_);
}

void Character::print_gear()
{
  std::function<void(std::pair<const Slot, Gear>)> tempPrintGear = [](std::pair<const Slot, Gear> in){std::cout<<in.second.get_slot()<<"\t\t"<<in.second.get_name()<<std::endl;};
  std::for_each(gear.begin(),gear.end(),tempPrintGear);
  // for (std::unordered_map<Slot, Gear, std::hash<uint>>::iterator it = gear.begin(); it != gear.end(); it++)
  // {
  //   if (it->first == Slot::NoSlot)
  //   {
  //     continue;
  //   }
  //   std::cout << it->first << "\t\t" << it->second.get_name() << std::endl;
  // }
}

double Character::get_spell_hit_chance() { return 83.0 + get_tot_sec_stat(SecondaryAttributes::SpellhitRating) * myH_ / fSpellHit_; }
double Character::get_spell_crit_chance()
{
  return spellCrit_ + get_tot_prim_stat(PrimaryAttributes::Intelligence) / 80.05 + get_tot_sec_stat(SecondaryAttributes::SpellCritRating) * myH_ / fCrit_;
}

double Character::get_hp()
{
  unsigned int stamina = get_tot_prim_stat(PrimaryAttributes::Stamina);
  unsigned int hp = get_tot_prim_stat(PrimaryAttributes::Health);
  return hp + stamina * 10;
}

void Character::print_elixirs()
{
  std::cout << "Consumed Elixirs/Flask:" << std::endl;
  for (uint i = 0; i < elixirs_.size(); i++)
  {
    std::cout << elixirs_[i].get_name() << std::endl;
  }
}

double Character::get_avoidance(bool dual_wield)
{
  double result = get_dodge_chance() + get_parry() + get_missed(dual_wield);
  return std::min(result, 100.0);
}

// void Character::find_best_gems(Gear *gear_piece, std::vector<Socket> *gems)
// {
//   reset_boni();
//   double temp_metric = DBL_MAX;
//   if (gear_piece->get_sockets() == 1)
//   {
//     unsigned int max_i;
//     for (uint i = 0; i < gems->size(); i++)
//     {
//       Gear temp = (*gear_piece);
//       temp.add_gem(gems->at(i));
//       equip(temp);
//       compute_stats();
//       if (metric() < temp_metric)
//       {
//         temp_metric = metric();
//         max_i = i;
//       }
//       reset_boni();
//     }
//     gear_piece->add_gem(gems->at(max_i));
//   }
//   else if (gear_piece->get_sockets() == 2)
//   {
//     unsigned int max_i, max_j;
//     for (uint i = 0; i < gems->size(); i++)
//     {
//       for (uint j = 0; j < gems->size(); j++)
//       {
//         if (gems->at(i).get_color()[0] == Color::Meta && gems->at(j).get_color()[0] == Color::Meta)
//         {
//           continue;
//         }
//         Gear temp = (*gear_piece);
//         temp.add_gem(gems->at(i));
//         temp.add_gem(gems->at(j));
//         equip(temp);
//         compute_stats();
//         if (metric() < temp_metric)
//         {
//           temp_metric = metric();
//           max_i = i;
//           max_j = j;
//         }
//         if (gear_piece->get_slot() == Slot::Head && (gems->at(i).get_color()[0] == Color::Meta || gems->at(j).get_color()[0] == Color::Meta))
//         {
//           for (uint bla = 0; bla < gear_piece->gems.size(); bla++)
//           {
//             if (gear_piece->gems[bla].active)
//             {
//               std::cout << "blubb" << std::endl;
//             }
//           }
//         }
//         reset_boni();
//       }
//     }
//     gear_piece->add_gem(gems->at(max_i));
//     gear_piece->add_gem(gems->at(max_j));
//   }
//   else if (gear_piece->get_sockets() == 3)
//   {
//     unsigned int max_i, max_j, max_k;
//     for (uint i = 0; i < gems->size(); i++)
//     {
//       for (uint j = 0; j < gems->size(); j++)
//       {
//         for (uint k = 0; k < gems->size(); k++)
//         {
//           Gear temp = (*gear_piece);
//           temp.add_gem(gems->at(i));
//           temp.add_gem(gems->at(j));
//           temp.add_gem(gems->at(k));
//           equip(temp);
//           compute_stats();
//           if (metric() < temp_metric)
//           {
//             temp_metric = metric();
//             max_i = i;
//             max_j = j;
//             max_k = k;
//           }
//           reset_boni();
//         }
//       }
//     }
//     gear_piece->add_gem(gems->at(max_i));
//     gear_piece->add_gem(gems->at(max_j));
//     gear_piece->add_gem(gems->at(max_k));
//     // std::cout << "gear_piece_gems.size=" << gear_piece->gems.size() << std::endl;
//   }
//   reset_boni();
// }

void Character::reset_boni()
{
  PrimaryStats temp;
  bonusPrimStats_ = temp;
  SecondaryStats temp2;
  bonusSecStats_ = temp2;
  for (uint i = 0; i < elixirs_.size(); i++)
  {
    bonusPrimStats_.add_stat(PrimaryAttributes::Armor, elixirs_[i].get_prim_stat(PrimaryAttributes::Armor));
  }
  for (uint i = 0; i < buffs_.size(); i++)
  {
    bonusPrimStats_.add_stat(PrimaryAttributes::Armor, buffs_[i].get_prim_stat(PrimaryAttributes::Armor));
  }
}

double Character::average_resistance(MagicSchool school)
{
  unsigned int resistance;
  PrimaryAttributes index=PrimaryAttributes::FirstPrimary;
  switch (school){
    case MagicSchool::Arcane:
      index = PrimaryAttributes::ArcaneResistance;
      break;
    case MagicSchool::Fire:
      index = PrimaryAttributes::FireResistance;
      break;
    case MagicSchool::Frost:
      index = PrimaryAttributes::FrostResistance;
      break;
    case MagicSchool::Nature:
      index = PrimaryAttributes::NatureResistance;
      break;
    case MagicSchool::Shadow:
      index = PrimaryAttributes::ShadowResistance;
      break;
    default:
      return 0;
  }
  resistance = get_prim_stat(index) + bonusPrimStats_.get_stat(index);
  double result = resistance / (boss_->get_lvl() * 5.0) * 0.75;
  if (result > 0.75)
  {
    return 0.75;
  }
  return result;
}
// warr,pala,schami,rogue,mage,wl,priest,druid,hunter
void Character::set_encounter(unsigned int inNDDs)
{
  nDDs_ = inNDDs;
  double tps = 0;
  if (saveTps_)
  {
    tps = get_tps();
    saveTps_ = false;
    savedTps_ = tps;
  }
  else
  {
    tps = savedTps_;
  }

  double raid_dps = calc_average_raid_dps(tps) * nDDs_;
  if (bearForm_)
  {
    raid_dps += get_bear_dps();
  }

  timeNeeded_ = boss_->get_health() / raid_dps;
  boss_->set_raid_dps(raid_dps);
  // std::vector<double>::iterator max_dps_it=max_element(begin(average_t4_kara_dps_vec), end(average_t4_kara_dps_vec));
}

double Character::get_crush(bool dual_wield)
{
  double result = 0.02 * (boss_->get_lvl() * 5.0 - level_ * 5.0) - 0.15;
  if (result < 0)
  {
    return 0;
  }
  return std::min(result, 1 - get_avoidance(dual_wield) / 100.0 - get_block() / 100.0);
}

bool Character::survives_worst_case_szenario(unsigned int *out)
{
  if (!saveWorstCase_)
  {
    (*out) = savedWorstCaseN_;
    return savedWorstCase_;
  }
  saveWorstCase_ = false;
  bool result = true;
  unsigned int n = 0;
  for (uint i = 0; i < boss_->get_worst_case_szenario()->size(); i++)
  {
    double temp = get_hp() - boss_->get_worst_case_szenario()->at(i).get_max_damage(this);
    if (temp < 0)
    {
      n++;
      result = false;
    }
  }
  (*out) = n;
  savedWorstCase_ = result;
  savedWorstCaseN_ = n;
  return result;
}

void Character::add_buff(Buff in)
{
  if (find(buffs_.begin(), buffs_.end(), in) == buffs_.end())
  {
    set_prim_stats(get_prim_stats() + in.get_prim_stats());
    set_sec_stats(get_sec_stats() + in.get_sec_stats());
    if (in.get_name() == "Blessing of Kings")
    {
      kings_ = true;
    }
    else if (in.get_name() == "Blessing of Sanctuary")
    {
      sanctuary_ = true;
    }
    buffs_.push_back(in);
  }
}

void Character::get_raid_buffed()
{
  MarkOfTheWild motw;
  ArcaneIntellect ai;
  PowerWordFortitude pwf;
  BlessingOfKings bok;
  BlessingOfSanctuary bos;
  add_buff(motw);
  add_buff(ai);
  add_buff(pwf);
  add_buff(bok);
  add_buff(bos);
}

void Character::print_buffs()
{
  std::cout << "Buffs:" << std::endl;
  for (uint i = 0; i < buffs_.size(); i++)
  {
    std::cout << buffs_[i].get_name() << std::endl;
  }
  std::cout << buffFood_.get_name() << std::endl;
}

double Character::get_mp()
{
  double result = bonusPrimStats_.get_stat(PrimaryAttributes::Mana) + get_prim_stat(PrimaryAttributes::Mana) + basePrimStats_.get_stat(PrimaryAttributes::Mana);
  double temp_int = bonusPrimStats_.get_stat(PrimaryAttributes::Intelligence) + get_prim_stat(PrimaryAttributes::Intelligence) + basePrimStats_.get_stat(PrimaryAttributes::Intelligence);
  if (temp_int > 20)
  {
    result += ((temp_int - 20) * 15 + 20);
  }
  else
  {
    result += (temp_int);
  }
  return result;
}

void Character::print_base_stats()
{
  std::cout << "Strength=" << get_tot_prim_stat(PrimaryAttributes::Strength) << std::endl;
  std::cout << "Agility=" << get_tot_prim_stat(PrimaryAttributes::Agility) << std::endl;
  std::cout << "Stamina=" << get_tot_prim_stat(PrimaryAttributes::Stamina) << std::endl;
  std::cout << "Intellect=" << get_tot_prim_stat(PrimaryAttributes::Intelligence) << std::endl;
  std::cout << "Spirit=" << get_tot_prim_stat(PrimaryAttributes::Spirit) << std::endl;
  std::cout << "Armor=" << get_armor() << std::endl;
  std::cout << "HP=" << get_hp() << std::endl;
  std::cout << "Dodge Rating=" << get_tot_sec_stat(SecondaryAttributes::DodgeRating) << std::endl;
  std::cout << "Dodge=" << get_dodge_chance() << std::endl;
  if (get_class() != CharacterClass::Druid)
  {
    std::cout << "Parry=" << get_parry() << std::endl;
    std::cout << "Block Chance=" << get_block() << std::endl;
    std::cout << "Block Value=" << get_block_value() << std::endl;
  }
  std::cout << "Crit=" << get_melee_crit_chance() * 100 << std::endl;
  std::cout << "Attack Power=" << get_attackpower() << std::endl;
  if (get_class() == CharacterClass::Paladin)
  {
    std::cout << "Seal: " << seal_ << std::endl;
  }
}

unsigned int Character::get_defense()
{
  double result = get_tot_sec_stat(SecondaryAttributes::DefenseRating) * rDef_ + defense_;
  return round(result);
}

unsigned int Character::get_block_value()
{
  if (get_class() == CharacterClass::Paladin || get_class() == CharacterClass::Warrior)
  {
    double result = std::max(0.0, get_tot_prim_stat(PrimaryAttributes::Strength) / 50.0 * 3.0 - 2.0);
    result += get_tot_sec_stat(SecondaryAttributes::BlockValue);
    std::map<std::string, unsigned int>::iterator it = talents.find("Shield Specialization");
    if (it != talents.end())
    {
      result *= (1 + 0.1 * it->second);
    }
    for (uint i = 0; i < gear[Slot::Head].gems.size(); i++)
    {
      if (gear[Slot::Head].gems[i].get_name() == "Eternal Earthstorm Diamond" && gear[Slot::Head].gems[i].active)
      {
        result *= 1.1;
      }
    }
    return round(result);
  }
  return 0;
}

double Character::total_damage_taken(double time_in_seconds_)
{
  if (!parryHaste_)
  {
    parry_haste_sim();
  }
  set_encounter(nDDs_);
  double tot_block_chance = get_block();
  double result = 0;
  check_block_chance(tot_block_chance);
  result = get_encounter()->get_total_damage_dealt(this);
  double friendly_fire = 0;
  if (get_class() == CharacterClass::Paladin && get_race() == Race::Bloodelf)
  {
    friendly_fire = get_seal_of_blood_recoil() + get_judgement_of_blood_recoil();
  }
  result -= ((get_hps() - friendly_fire) * get_time_of_encounter());
  return std::max(result, 0.0);
}

double Character::get_parried_chance()
{
  double result = get_tot_sec_stat(SecondaryAttributes::ExpertiseRating) / 14.7904396057 / 100.0 + expertise_ * 0.25 / 100.0;
  double boss_base_parry_chance = boss_->get_parry_chance();
  result = std::max(boss_base_parry_chance + (boss_->get_lvl() - level_) * 5 * 0.04 / 100.0 - result, 0.0);
  return result;
}

double Character::get_dodged_chance()
{
  double expertise_bonus = get_tot_sec_stat(SecondaryAttributes::ExpertiseRating) / 14.7904396057 + expertise_ * 0.25;
  double base_boss_dodge_chance = 5; // assumption
  double result = (base_boss_dodge_chance + (boss_->get_lvl() - level_) * 5 * 0.1) - expertise_bonus;
  return std::max(result / 100.0, 0.0);
}

double Character::get_blocked_chance()
{
  return boss_->get_block_chance();
}

double Character::get_miss_chance()
{
  double result = (boss_->get_lvl() - level_) * 5;
  if (result > 10)
  {
    result = 5 + result * 0.2;
  }
  else
  {
    result = 5 + result * 0.1;
  }
  if (get_class() == CharacterClass::Rogue)
  {
    result = result * 0.8 + 20;
  }
  double temp_hit = get_tot_sec_stat(SecondaryAttributes::HitRating) / 15.8 + hit_;
  return std::max((result - temp_hit) / 100.0, 0.0);
}

double Character::get_hit_chance(bool yellow_damage)
{
  double result = 1 - get_miss_chance() - get_dodged_chance() - get_parried_chance() - get_blocked_chance() - get_melee_crit_chance();
  if (!yellow_damage)
  {
    result -= get_glancing_blow_chance();
  }
  return result;
}

double Character::get_seal_of_blood_damage()
{ // per second
  double damage_multiplier = 0;
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "One-Handed Weapon Specialization")
    {
      damage_multiplier = (it->second * 0.01 + 1);
      break;
    }
  }
  double weaponDPS = get_tot_prim_stat(PrimaryAttributes::WeaponDamage) / get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  double result = (1 - get_miss_chance() - get_parried_chance() - get_dodged_chance()) * 0.48 * weaponDPS * (1 - get_melee_crit_chance() + get_melee_crit_chance() * 2); // TO CHECK
  unsigned int t4_set = 0;
  if (gear[Slot::Head].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Shoulders].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Chest].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Hands].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Legs].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (t4_set >= 2)
  {
    result *= 1.1;
  }
  return result * damage_multiplier;
}

double Character::get_judgement_of_blood_damage()
{
  double time_reduction = 0;
  double damage_multiplier = 0;
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "One-Handed Weapon Specialization")
    {
      damage_multiplier = (it->second * 0.01 + 1);
    }
    else if (it->first == "Improved Judgement")
    {
      time_reduction = it->second * 1.0;
    }
  }
  double result = damage_multiplier * (0.26 * get_tot_prim_stat(PrimaryAttributes::WeaponDamage) + 0.11 * get_attackpower() + 0.18 * get_spellpower(SecondaryAttributes::HolySpellPower)) / (10 - time_reduction) * get_spell_hit_chance() / 100.0 * (1 - get_spell_crit_chance() / 100.0 + get_spell_crit_chance() / 100.0 * 1.5); // TO CHECK
  unsigned int t4_set = 0;
  if (gear[Slot::Head].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Shoulders].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Chest].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Hands].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Legs].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (t4_set >= 2)
  {
    result *= 1.1;
  }
  return result;
}

double Character::get_melee_crit_chance()
{
  double result = crit_ + get_tot_sec_stat(SecondaryAttributes::CritRating) / 22.1 - std::max((boss_->get_lvl() - level_) * 5 * 0.2, 0.0);
  if (get_class() == CharacterClass::Druid)
  {
    result += std::max(0.0, get_tot_prim_stat(PrimaryAttributes::Agility) / 25.0 - 2.68);
  }
  else if (get_class() == CharacterClass::Paladin)
  {
    result += (get_tot_prim_stat(PrimaryAttributes::Agility) / 25.0);
  }

  std::map<std::string, unsigned int>::iterator it = talents.find("Sharpened Claws");
  if (it != talents.end() && (bearForm_ || catForm_))
  {
    result += (it->second * 2.0);
  }
  it = talents.find("Leader of the Pack");
  if (it != talents.end())
  {
    result += 5.0;
  }
  return result / 100.0;
}

double Character::get_active_rage_generation()
{
  double d = get_white_damage() * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double c;
  if (level_ <= 70)
  {
    c = 0.0091107836 * level_ * level_ + 3.225598133 * level_ + 4.2652911;
  }
  else
  {
    std::cout << "rage conversion for level >70 not implemented" << std::endl;
    abort();
  }
  double f = 3.5;
  double r = std::min(15 * d / (4.0 * c) + f * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) / 2.0, 15 * d / c);
  r *= (get_hit_chance(false));

  double r_glancing = std::min(15 * get_glancing_blow_damage() * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration))) / (4.0 * c) + f * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) / 2.0, 15 * d / c);
  r_glancing *= get_glancing_blow_chance();
  std::map<std::string, unsigned int>::iterator it = talents.find("Predatory Instincts");
  double crit_bonus = 0;
  if (it != talents.end())
  {
    crit_bonus = it->second * 0.02;
  }
  d *= (2 + crit_bonus); // crit
  f *= 2;                // crit
  double r_crit = std::min(15 * d / (4.0 * c) + f * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) / 2.0, 15 * d / c);
  r_crit *= get_melee_crit_chance();
  return r + r_crit + r_glancing;
}

double Character::get_passive_rage_generation()
{
  double critted_chance = (5 + 0.2 * (boss_->get_lvl() - level_)) / 100.0 - red_chance_to_get_crit();
  double d = boss_->get_attack_damage() * (1 - get_avoidance() / 100.0 - get_crush() - critted_chance);
  double d_crush = boss_->get_attack_damage() * 1.5 * get_crush();
  double d_crit = boss_->get_attack_damage() * 2 * critted_chance;
  double c;
  if (level_ <= 70)
  {
    c = 0.0091107836 * level_ * level_ + 3.225598133 * level_ + 4.2652911;
  }
  else
  {
    std::cout << "rage conversion for level >70 not implemented" << std::endl;
    abort();
  }
  double result = 5 / 2.0 * (d + d_crit + d_crush) * (1 - get_armor_reduction()) / c;
  return std::min(result, 100.0);
}

double Character::get_bear_tps(bool simplify)
{
  if (simplify)
  {
    return simple_bear_tps();
  }
  uint r_maul = 15;
  uint r_swipe = 20;
  uint r_mangle = 20;
  uint r_lacerate = 15;
  uint primalFuryTalents = 0;
  std::map<std::string, unsigned int>::iterator it = talents.find("Primal Fury");
  if (it != talents.end())
  {
    primalFuryTalents = it->second;
  }
  double p5 = 0;
  double n5 = 0;
  uint i = 0;
  while (i * get_global_cd() < 15)
  {
    for (uint j = 0; j <= i; j++)
    {
      for (uint k = 0; k <= i - j; k++)
      {
        uint l = i - j - k;
        std::vector<uint> k_vec = {5, j, k, l};
        double temp2 = multinomialCoefficients(5 + i, &k_vec) * pow(get_hit_chance(true) + get_melee_crit_chance(), 5) * pow(get_miss_chance(), j) * pow(get_dodged_chance(), k) * pow(get_parried_chance(), l);
        p5 += (temp2);
        n5 += (temp2 * (i + 5));
      }
    }
    i++;
  }
  n5 /= p5;
  n_min_lacerate = n5;
  ROOT::Math::Minimizer *minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
  std::function<double(const double *)> tps_fit = fit_tps(this, n5);
  std::function<double(const double *)> tps_fit_output = fit_tps_output(tps_fit);
  minimizer->SetMaxFunctionCalls(0);
  std::vector<std::string> temp_names = {"n_auto_attacks", "n_maul", "n_filler"};
  ROOT::Math::Functor f = ROOT::Math::Functor(tps_fit, temp_names.size());
  minimizer->SetFunction(f);
  double raid_dps = 0;
  double tps = 0;
  uint counter = 0;
  while (tps == 0 || counter < tpsFitAttempts_)
  {
    std::vector<double> initial_values(temp_names.size(), 0);
    for (uint i = 0; i < 2; i++)
    {
      initial_values[i] = rand() % 300;
      minimizer->SetLowerLimitedVariable(i, temp_names[i].c_str(), initial_values[i], pow(10, -5), 0);
    }
    double initial_time_estimation = (initial_values[0] + initial_values[1]) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
    double max_filler = initial_time_estimation / get_global_cd() - initial_time_estimation / 15.0 - initial_time_estimation / 6.0 - n_min_lacerate;
    initial_values[2] = max_filler * rand() / (double)RAND_MAX;
    minimizer->SetLowerLimitedVariable(2, temp_names[2].c_str(), initial_values[2], pow(10, -5), 0);
    minimizer->Minimize();

    std::vector<double> args_vec(temp_names.size());
    for (uint i = 0; i < temp_names.size(); i++)
    {
      args_vec[i] = minimizer->X()[i];
    }
    double *args = args_vec.data();
    double temp_raid_dps = -tps_fit(args);
    double time_estimation = (minimizer->X()[1] + minimizer->X()[0]) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
    n_mangle = time_estimation / std::max(6 / (1.0 + get_haste()), 1.0);
    double rage_use_per_second = get_passive_rage_generation() / get_encounter()->get_attack_speed() + get_active_rage_generation() * minimizer->X()[0] / time_estimation;
    double rage_use = (get_hit_chance(true) * (1 - get_melee_crit_chance()) + get_miss_chance()) * (r_maul * minimizer->X()[1] + r_swipe * minimizer->X()[2] + r_mangle * n_mangle + r_lacerate * minimizer->X()[3]) + (get_hit_chance(true) * get_melee_crit_chance()) * (r_maul * minimizer->X()[1] + r_swipe * minimizer->X()[2] + r_mangle * n_mangle + r_lacerate * minimizer->X()[3] - primalFuryTalents / 2.0 * 5 * (minimizer->X()[1] + minimizer->X()[2] + minimizer->X()[3])) + (get_dodged_chance() + get_parried_chance()) * 0.25 * (r_maul * minimizer->X()[1] + r_swipe * minimizer->X()[2] + r_mangle * n_mangle + r_lacerate * minimizer->X()[3]);
    rage_use_per_second -= rage_use / time_estimation;
    if (temp_raid_dps >= 0 && rage_use_per_second >= 0)
    {
      double bear_tps = calc_bear_tps(minimizer->X()[0], minimizer->X()[1], minimizer->X()[2], minimizer->X()[3] + n_min_lacerate);
      if (temp_raid_dps > raid_dps)
      {
        tps = bear_tps;
        raid_dps = temp_raid_dps;
        n_auto = minimizer->X()[0];
        n_maul = minimizer->X()[1];
        n_filler = minimizer->X()[2];
        n_lacerate = n_min_lacerate;
        n_mangle = 1.0 / 6.0 * (n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
        if (isLacerateFiller_)
        {
          n_lacerate += n_filler;
        }
        else
        {
          n_swipe = n_filler;
        }
      }
    }
    if (counter > tpsFitAttempts_ && tps == 0)
    {
      std::cout << "fit failed." << std::endl;
      abort();
    }
    counter++;
  }
  return tps;
  // double lacerateDirectBonusThreat_ = 11941 / 27.0;
  // double lacerateDirectThreatMultiplier_ = 27 / 31.0;
  // // double maulBonusThreat_ = 236067 / 821.0;
  // // double maulThreatMultiplier_ = 821 / 541.0;
  // double maulBonusThreat_ = 0;
  // double maulThreatMultiplier_ = 1.3 * 1.15;
  // // double mangleBonusThreat_ = -7 / 3.0 * 9 / 17.0;
  // // double mangleThreatMultiplier_ = 17 / 9.0;
  // double mangleBonusThreat_ = 0;
  // double mangleThreatMultiplier_ = 1.3 * 1.15;
  // // double white_bonus_threat = -1021 / 59.0;
  // // double white_threat_multiplier = 295 / 191.0;
  // double white_bonus_threat = 0;
  // double white_threat_multiplier = 1.3 * 1.15;
  // std::map<std::string, unsigned int>::iterator it = talents.find("Shredding Attacks");
  // double rage_cost_reduction = 0;
  // if (it != talents.end())
  // {
  //   rage_cost_reduction = it->second;
  // }
  // it = talents.find("Omen of Clarity");
  // double omen_bonus = 1.0;
  // if (it != talents.end())
  // {
  //   omen_bonus = 0.9;
  // }
  // double d = get_parried_chance() + get_dodged_chance();
  // double m = get_miss_chance();
  // double average_rage_cost_coefficient = get_hit_chance() * (1 - 0.75 * d) / pow(1 - d - m, 2);
  // double average_gc_coefficient = get_hit_chance() / pow(1 - d - m, 2);
  // double rage_cost_lacerate = (15 - rage_cost_reduction) * average_rage_cost_coefficient * omen_bonus;
  // double rage_cost_lacerate_one_time = (15 - rage_cost_reduction) * (get_hit_chance() + get_miss_chance() + 0.25 * get_parried_chance() + 0.25 * get_dodged_chance()) * omen_bonus;
  // double lacerate_rage_refund = 0.75 * rage_cost_lacerate / omen_bonus;

  // it = talents.find("Predatory Instincts");
  // double crit_bonus = 2;
  // if (it != talents.end())
  // {
  //   crit_bonus += (it->second * 0.02);
  // }
  // double crit_factor = (1 + get_melee_crit_chance() * (crit_bonus - 1)) * get_hit_chance();
  // double lacerate_direct_dmg = 31 + 0.01 * get_attackpower();
  // double lacerate_dot_dmg = 155 + get_attackpower() / 20; // for lvl 70
  // if (gear[Slot::Idol].get_name() == "Idol of Ursoc")
  // {
  //   lacerate_direct_dmg += 8;
  //   lacerate_dot_dmg += 8;
  // }
  // lacerate_direct_dmg *= (crit_factor); // for lvl 70
  // double lacerate_direct_threat = (lacerate_direct_dmg + lacerateDirectBonusThreat_) * lacerateDirectThreatMultiplier_;
  // double lacerate_dot_threat = lacerate_dot_dmg * 7 / 24.0;
  // double maul_damage = get_white_damage() + 176;
  // if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  // {
  //   maul_damage += 50;
  // }
  // maul_damage *= (crit_factor * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)))); // for lvl 70
  // double maul_threat = (maul_damage + maulBonusThreat_) * maulThreatMultiplier_;
  // double mangle_damage = get_white_damage() * 1.15 + 207; // for lvl 70
  // if (gear[Slot::Idol].get_name() == "Idol of the Wild")
  // {
  //   mangle_damage += 51.75;
  // }
  // mangle_damage *= (crit_factor * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration))));
  // double mangle_threat = (mangle_damage + mangleBonusThreat_) * mangleThreatMultiplier_;
  // it = talents.find("Primal Fury");
  // double bonus_rage = 0;
  // if (it != talents.end())
  // {
  //   bonus_rage = it->second * 2.5;
  // }
  // it = talents.find("Ferocity");

  // if (it != talents.end())
  // {
  //   rage_cost_reduction = it->second;
  // }
  // double rage_cost_maul = (15 - rage_cost_reduction) * (get_hit_chance() + get_miss_chance() + 0.25 * get_parried_chance() + 0.25 * get_dodged_chance()) * omen_bonus;
  // double rage_cost_mangle = (20.0 - (double)rage_cost_reduction) * (get_hit_chance() + get_miss_chance() + 0.25 * get_parried_chance() + 0.25 * get_dodged_chance()) * omen_bonus;
  // double rage_cost_swipe = (20 - rage_cost_reduction) * (get_hit_chance() + get_miss_chance() + 0.25 * get_parried_chance() + 0.25 * get_dodged_chance()) * omen_bonus;
  // n_maul = (6.0 * (get_passive_rage_generation() / boss_->get_attack_speed() + get_active_rage_generation() / get_tot_prim_stat(PrimaryAttributes::AttackSpeed)) + bonus_rage * get_hit_chance() * get_melee_crit_chance() * (1 + 2 * get_melee_crit_chance()) - rage_cost_mangle - rage_cost_lacerate) / (2 * get_active_rage_generation() / get_tot_prim_stat(PrimaryAttributes::AttackSpeed) + rage_cost_maul);
  // double n_maul_max = 6.0 / get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  // if (n_maul < 0 || n_maul_max < 0)
  // {
  //   std::cout << "rage cost red=" << rage_cost_reduction << std::endl;
  //   std::cout << "passive rage gen=" << get_passive_rage_generation() << std::endl;
  //   std::cout << "active rage gen=" << get_active_rage_generation() << std::endl;
  //   std::cout << "n_maul=" << n_maul << std::endl;
  //   std::cout << "term 1=" << 6.0 * (get_passive_rage_generation() / boss_->get_attack_speed() + get_active_rage_generation() / get_tot_prim_stat(PrimaryAttributes::AttackSpeed)) << std::endl;
  //   std::cout << "term 2=" << bonus_rage * get_hit_chance() * get_melee_crit_chance() * (1 + 2 * get_melee_crit_chance()) << std::endl;
  //   std::cout << "term 3=" << rage_cost_mangle << std::endl;
  //   std::cout << "term 4=" << rage_cost_lacerate << std::endl;
  //   std::cout << "n_maul_max=" << n_maul_max << std::endl;
  //   abort();
  // }
  // double result = get_hit_chance() * (1 + get_melee_crit_chance() * crit_bonus) * (mangle_threat / 6.0 + lacerate_direct_threat / 15.0) + lacerate_dot_threat * 5 * (pow(1 - get_hit_chance(), 2) + 1.3 * (1 - pow(1 - get_hit_chance(), 2))) / 15.0;
  // if (n_maul >= n_maul_max)
  // {
  //   double swipe_damage = get_attackpower() * 0.171 + 84;
  //   if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  //   {
  //     swipe_damage += 10;
  //   }
  //   swipe_damage *= (crit_factor * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration))));
  //   double swipeBonusThreat_ = 0;               //-212/3.0
  //   double swipeThreatMultiplier_ = 1.3 * 1.15; // 3
  //   double swipe_threat = (swipe_damage + swipeBonusThreat_) * swipeThreatMultiplier_;
  //   double left_over_rage = std::min(n_maul, n_maul_max) * bonus_rage * get_hit_chance() * get_melee_crit_chance() + (n_maul - n_maul_max) * rage_cost_maul;
  //   double n_swipes = std::min(left_over_rage / rage_cost_swipe, (6 - get_global_cd() * (1 + average_gc_coefficient)) / (get_global_cd() * average_gc_coefficient));
  //   double n_lacerate = std::min(left_over_rage / rage_cost_lacerate_one_time, (6 - get_global_cd() * (1 + average_gc_coefficient)) / (get_global_cd() * average_gc_coefficient));
  //   double left_over_threat = std::max(n_lacerate * lacerate_direct_threat, n_swipes * swipe_threat);
  //   result += (left_over_threat) / 6.0;
  //   if (n_lacerate * lacerate_direct_threat > n_swipes * swipe_threat)
  //   {
  //     n_filler = n_lacerate;
  //   }
  //   else
  //   {
  //     n_filler = n_swipes;
  //   }
  //   n_maul = n_maul_max;
  // }
  // result += (n_maul * maul_threat);
  // double white_threat = (get_white_damage() * crit_factor * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration))) + white_bonus_threat) * white_threat_multiplier;
  // result += (n_maul_max - n_maul) * white_threat / 6.0;
  // if (gear[Slot::Hands].get_enchantment().get_name() == "Threat")
  // {
  //   result *= 1.02;
  // }
  // for (std::map<Slot, Gear>::iterator it = gear.begin(); it != gear.end(); it++)
  // {
  //   if (it->second.get_name() == "Darkmoon Card: Vengeance")
  //   {
  //     result = result + 0.1 * (1 - get_avoidance() / 100.0) * (95.0 + 116.0) / boss_->get_attack_speed() * ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 1.5);
  //     break;
  //   }
  // }
  // if (result < 0)
  // {
  //   std::cout << "miscalculation in threat" << std::endl;
  //   std::cout << "step 1=" << get_hit_chance() * (1 + get_melee_crit_chance() * crit_bonus) * (mangle_threat / 6.0 + lacerate_direct_threat / 15.0) + lacerate_dot_threat * 5 * (pow(1 - get_hit_chance(), 2) + 1.3 * (1 - pow(1 - get_hit_chance(), 2))) / 15.0 << std::endl;
  //   std::cout << "n_maul=" << n_maul << std::endl;
  //   std::cout << "maul threat=" << maul_threat << std::endl;
  //   std::cout << "white threat=" << white_threat << std::endl;
  //   abort();
  // }
  // savedTps_ = result;
  // return result;
}

double Character::get_global_cd()
{
  double result = 1.5 / (1.0 + get_haste());
  return std::max(result, 1.0);
}

double Character::get_haste()
{
  double result = get_tot_sec_stat(SecondaryAttributes::SpellHasteRating) / 15.77 / 100.0; // for lvl 70
  return result;
}

double Character::get_white_damage()
{
  double result = 157.5;
  double m = 0.071464646464647;
  double b = -0.045202020202027;
  if (catForm_ && get_race() == Race::Tauren)
  {
    result = 62.9;
    m = 0.071455223880597;
    b = -0.041977611940297;
  }
  result += (m * get_attackpower() + b) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  std::map<std::string, unsigned int>::iterator it = talents.find("Naturalist");
  if (it != talents.end())
  {
    result *= (1 + it->second * 0.02);
  }
  return result;
}

double Character::get_paladin_tps()
{
  double result = 0.0;
  double threat_multiplier = 0.0;
  double time_reduction = 0.0;
  double damage_multiplier = 0.0;
  double tot_block_chance = get_block();
  for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
  {
    if (it->first == "One-Handed Weapon Specialization")
    {
      damage_multiplier = (it->second * 0.01 + 1);
    }
    else if (it->first == "Improved Righteous Fury")
    {
      threat_multiplier = round(0.5 / 3.0 * it->second);
      threat_multiplier = 1 + 0.6 * (1 + threat_multiplier);
    }
    else if (it->first == "Improved Judgement")
    {
      time_reduction = it->second * 1.0;
    }
  }
  if (gear[Slot::Hands].get_enchantment().get_name() == "Threat")
  {
    threat_multiplier *= 1.02;
  }
  unsigned int t4_set = 0;
  if (gear[Slot::Head].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Shoulders].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Chest].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Hands].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  if (gear[Slot::Legs].get_name().find("Justicar") != std::string::npos)
  {
    t4_set++;
  }
  tot_block_chance += get_effective_redoubt_chance();
  if (gear[Slot::Libram].get_name() == "Libram of Repentance")
  {
    tot_block_chance += (43 * myH_ / fBlock_);
  }
  tot_block_chance = check_block_chance(tot_block_chance);
  // consecration
  result = result + (64 + 0.042 * get_spellpower(SecondaryAttributes::HolySpellPower)) * threat_multiplier;
  // holy shield
  double t4_HS_multiplier = 1.0;
  if (t4_set >= 4)
  {
    t4_HS_multiplier = 1.15;
  }
  result = result + (1.0 / boss_->get_attack_speed() * tot_block_chance / 100.0) * (155 + 0.05 * get_spellpower(SecondaryAttributes::HolySpellPower)) * (threat_multiplier + 0.35) * t4_HS_multiplier;
  // blessing of sanctuary
  if (sanctuary_)
  {
    result = result + (1.0 / boss_->get_attack_speed() * tot_block_chance / 100.0) * (46 + get_spellpower(SecondaryAttributes::HolySpellPower) * 0.01) * threat_multiplier;
  }
  // seal of vengeance
  double t4_seal_multiplier = 1.0;
  if (t4_set >= 2)
  {
    t4_seal_multiplier = 1.1;
  }
  double sealOfVengeance = t4_seal_multiplier * ((150 + get_spellpower(SecondaryAttributes::HolySpellPower) * 0.190985485) * 5.0 / 15.0 * threat_multiplier +
                                                 (120 + get_spellpower(SecondaryAttributes::HolySpellPower) * 0.478736949) * 5.0 / (10 - time_reduction) *
                                                     ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 1.5) * threat_multiplier * get_spell_hit_chance() / 100.0);
  // seal of blood
  double sealOfBlood = get_seal_of_blood_damage() * threat_multiplier;
  // seal of righteousness
  double libram_of_divine_purpose_bonus = 0;
  if (gear[Slot::Libram].get_name() == "Libram of Divine Purpose")
  {
    libram_of_divine_purpose_bonus = 94;
  }
  double sealOfRighteousness = get_hit_chance(true) * threat_multiplier * (0.022 * get_attackpower() + 0.044 * (get_spellpower(SecondaryAttributes::HolySpellPower) + libram_of_divine_purpose_bonus)) * get_spell_hit_chance() / 100.0 + (1 + 0.225 * get_attackpower() + 0.355 * (get_spellpower(SecondaryAttributes::HolySpellPower) + libram_of_divine_purpose_bonus)) / (10 - time_reduction) *
                                                                                                                                                                                                                                              ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 1.5) * threat_multiplier * get_spell_hit_chance() / 100.0;
  double bestSeal = std::max(std::max(sealOfVengeance, sealOfBlood), sealOfRighteousness);
  result = result + bestSeal;
  if (bestSeal == sealOfVengeance)
  {
    seal_ = "Seal of Vengeance";
  }
  else if (bestSeal == sealOfBlood)
  {
    seal_ = "Seal of Blood";
  }
  else if (bestSeal == sealOfRighteousness)
  {
    seal_ = "Seal of Righteousness";
  }
  // retribution aura
  if (gear[Slot::Libram].get_name() != "Libram of Truth")
  {
    result = result + (26 + get_spellpower(SecondaryAttributes::HolySpellPower) / 30.3) * threat_multiplier / boss_->get_attack_speed();
  }
  if (gear[Slot::Trinket1].get_name() == "Darkmoon Card: Vengeance" || gear[Slot::Trinket2].get_name() == "Darkmoon Card: Vengeance")
  {
    double temp_sp = 0.001 * get_tot_sec_stat(SecondaryAttributes::SpellPower) + 0.0025 * get_tot_sec_stat(SecondaryAttributes::HolySpellPower);
    temp_sp += 219 * 0.0025; // crusader judgement lvl 70
    double vengenace_damage = (95.0 + 115.0) / 2.0;
    std::map<std::string, unsigned int>::iterator it = talents.find("One-Handed Weapon Specialization");
    vengenace_damage *= (it->second * 0.01 + 1);
    vengenace_damage += temp_sp;
    result = result + 0.1 * (1 - get_avoidance() / 100.0) * vengenace_damage * threat_multiplier / boss_->get_attack_speed() * ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 2);
  }
  savedTps_ = result * damage_multiplier;
  return savedTps_;
}

double Character::get_spellpower(SecondaryAttributes in = SecondaryAttributes::SpellPower)
{
  double result = baseSecStats_.get_stat(SecondaryAttributes::SpellPower) + secondaryStats_.get_stat(SecondaryAttributes::SpellPower) + bonusSecStats_.get_stat(SecondaryAttributes::SpellPower);
  if (in != SecondaryAttributes::SpellPower)
  {
    result += baseSecStats_.get_stat(in) + secondaryStats_.get_stat(in) + bonusSecStats_.get_stat(in);
  }
  return result;
}

double Character::get_attackpower()
{
  double result = get_tot_sec_stat(SecondaryAttributes::AttackPower) + 2 * get_tot_prim_stat(PrimaryAttributes::Strength) - 20;
  return result;
}

void Character::compute_set_boni()
{
  unsigned int s1_set_pieces = 0;
  unsigned int wastewalker_set = 0;
  unsigned int primalstrike_set = 0;
  for (std::unordered_map<Slot, Gear, std::hash<uint>>::iterator it = gear.begin(); it != gear.end(); it++)
  {
    if (it->second.get_name().find("Gladiator") != std::string::npos)
    {
      s1_set_pieces++;
    }
    else if (it->second.get_name().find("Wastewalker") != std::string::npos)
    {
      wastewalker_set++;
    }
    else if (it->second.get_name().find("Primalstrike") != std::string::npos)
    {
      primalstrike_set++;
    }
  }
  if (s1_set_pieces >= 2)
  {
    bonusSecStats_.add_stat(SecondaryAttributes::ResilienceRating, 35);
  }
  if (wastewalker_set >= 2)
  {
    bonusSecStats_.add_stat(SecondaryAttributes::HitRating, 35);
  }
  if (primalstrike_set == 3)
  {
    bonusSecStats_.add_stat(SecondaryAttributes::AttackPower, 40);
  }
}

double Character::get_bear_dps()
{
  if (!saveDps_)
  {
    return savedDps_;
  }
  saveDps_ = false;
  std::map<std::string, unsigned int>::iterator it = talents.find("Predatory Instincts");
  double crit_bonus = 2;
  if (it != talents.end())
  {
    crit_bonus += (it->second * 0.02);
  }
  double lacerate_direct_dmg = (31 + 0.01 * get_attackpower()); // for lvl 70
  double lacerate_dot_dmg = 155 + get_attackpower() / 20;       // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of Ursoc")
  {
    lacerate_dot_dmg += 8;
    lacerate_direct_dmg += 8;
  }
  // lacerate_direct_dmg *= (crit_factor);
  // double lacerate_dot_threat = lacerate_dot_dmg * 7 / 24.0;
  double maul_damage = get_white_damage() + 176; // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    maul_damage += 50;
  }
  maul_damage *= (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  // double maul_threat = (maul_damage + maulBonusThreat_) * maulThreatMultiplier_;
  double mangle_damage = (get_white_damage() * 1.15 + 207); // for lvl 70
  if (gear[Slot::Idol].get_name() == "Idol of the Wild")
  {
    mangle_damage += 51.75;
  }
  mangle_damage *= (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double swipe_damage = (get_attackpower() * 0.171 + 84);
  if (gear[Slot::Idol].get_name() == "Idol of Brutality")
  {
    swipe_damage += 10;
  }
  swipe_damage *= (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double white_damage = get_white_damage() * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double glancing_damage = get_glancing_blow_damage() * (1 - boss_->getDamageReductionFromArmor(level_, get_tot_sec_stat(SecondaryAttributes::ArmorPenetration)));
  double result = n_auto * white_damage * (get_hit_chance(false) + get_melee_crit_chance() * crit_bonus) + n_auto * get_glancing_blow_chance() * glancing_damage + (n_maul * maul_damage + n_swipe * swipe_damage + n_lacerate * lacerate_direct_dmg + n_mangle * mangle_damage) * (get_hit_chance(true) * (1 - get_melee_crit_chance()) + crit_bonus * get_hit_chance(true) * get_melee_crit_chance());
  result /= ((n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed));
  savedDps_ = result;
  return result;
}

void Character::exclude_source(Source in)
{
  excludedSrcs_.push_back(in);
}

bool Character::is_excluded(Source in)
{
  if (find(excludedSrcs_.begin(), excludedSrcs_.end(), in) != excludedSrcs_.end())
  {
    return true;
  }
  return false;
}

bool Character::is_excluded(Gear *in)
{
  if (find(excludedSrcs_.begin(), excludedSrcs_.end(), in->get_src()) != excludedSrcs_.end())
  {
    return true;
  }
  if (in->get_phase() > maxPhase_)
  {
    return true;
  }
  for (uint i = 0; i < in->gems.size(); i++)
  {
    if (in->gems[i].get_phase() > maxPhase_)
    {
      return true;
    }
  }
  return false;
}

double Character::metric(double time_in_seconds_)
{
  if (saveMetric_)
  {
    saveTps_ = true;
    double serial_tps = get_tps();
    double serial_metric = total_damage_taken(time_in_seconds_) - get_hp();
    if (gear[Slot::Trinket1].get_uptime() == 0 && gear[Slot::Trinket2].get_uptime() == 0)
    {
      savedMetric_ = serial_metric;
      savedTps_ = serial_tps;
      saveMetric_ = false;
      saveTps_ = false;
      return savedMetric_;
    }
    use_trinkets_parallel();
    saveTps_ = true;
    double parallel_tps = get_tps();
    double parallel_metric = total_damage_taken(time_in_seconds_) - get_hp();
    savedTps_ = parallel_tps;
    if (parallel_metric > serial_metric)
    {
      trinketsParallel_ = false;
      savedTps_ = serial_tps;
    }
    savedMetric_ = std::min(serial_metric, parallel_metric);
    saveMetric_ = false;
    saveTps_ = false;
  }
  return savedMetric_;
}

void Character::parry_haste_sim()
{
  if (parryHaste_)
  {
    return;
  }
  double player_hit_timer = get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
  double npc_hit_timer = boss_->get_attack_speed();
  double time_in_sec = npc_hit_timer * 100000;
  double parry_haste = 0.4;
  double parry_haste_threshold = 0.2;
  unsigned int n_npc = 0;
  unsigned int n_player = 0;
  double step_size = 0.01;
  for (double i = 0; i < time_in_sec; i += step_size)
  {
    player_hit_timer -= step_size;
    npc_hit_timer -= step_size;

    if (player_hit_timer <= 0 && player_hit_timer <= npc_hit_timer)
    {
      n_player++;
      double temp = rand() % 101;
      if (temp <= get_parried_chance() * 100)
      {
        if (npc_hit_timer - parry_haste * (boss_->get_attack_speed()) >= parry_haste_threshold * npc_hit_timer)
        {
          npc_hit_timer -= parry_haste * (boss_->get_attack_speed());
        }
      }
      player_hit_timer = get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
    }
    if (npc_hit_timer <= 0 && npc_hit_timer <= player_hit_timer)
    {
      n_npc++;
      double temp = rand() % 101;
      if (temp <= get_parry() && get_parry() > 0)
      {
        if (player_hit_timer - parry_haste * get_tot_prim_stat(PrimaryAttributes::AttackSpeed) >= parry_haste_threshold * player_hit_timer)
        {
          player_hit_timer -= parry_haste * get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
        }
      }
      npc_hit_timer = boss_->get_attack_speed();
    }
    if (player_hit_timer <= 0 && player_hit_timer <= npc_hit_timer)
    {
      n_player++;
      double temp = rand() % 101;
      if (temp <= get_parried_chance() * 100)
      {
        if (npc_hit_timer - parry_haste * (boss_->get_attack_speed()) >= parry_haste_threshold * npc_hit_timer)
        {
          npc_hit_timer -= parry_haste * (boss_->get_attack_speed());
        }
      }
      player_hit_timer = get_tot_prim_stat(PrimaryAttributes::AttackSpeed);
    }
  }
  double effective_npc_swing_timer = time_in_sec / n_npc;
  double effective_player_swing_timer = time_in_sec / n_player;
  bonusPrimStats_.set_stat(PrimaryAttributes::AttackSpeed, effective_player_swing_timer - get_tot_prim_stat(PrimaryAttributes::AttackSpeed));
  boss_->set_effective_swing_timer(effective_npc_swing_timer);
  parryHaste_ = true;
}

double Character::get_leader_of_the_pack_hps()
{
  double result = 0;
  double white_attacks_per_second = std::min((get_hit_chance(false) + get_melee_crit_chance()) / get_tot_prim_stat(PrimaryAttributes::AttackSpeed), n_auto * (get_hit_chance(false) + get_melee_crit_chance()) / ((n_auto + n_maul) * get_tot_prim_stat(PrimaryAttributes::AttackSpeed)));
  double yellow_attacks_per_second = ((n_maul + n_filler + n_mangle) * get_hit_chance(true) + 5 * (uint)(n_min_lacerate / 5)) / get_time_of_encounter();
  if (n_auto == 0)
  { // simplification
    yellow_attacks_per_second = get_hit_chance(true) * (1 / get_tot_prim_stat(PrimaryAttributes::AttackSpeed) + 1 / get_global_cd());
  }
  double attacks_per_second = yellow_attacks_per_second + white_attacks_per_second;
  uint n_attacks_6 = (uint)(attacks_per_second * 6);
  uint n_attacks_total = (uint)(attacks_per_second * get_time_of_encounter());
  std::map<std::string, unsigned int>::iterator tempIt = talents.find("Improved Leader of the Pack");
  if (tempIt == talents.end())
  {
    return result;
  }
  double normConst = 0;
  for (uint k = 0; k <= n_attacks_total - n_attacks_6 * k + k; k++)
  {
    double p = binomialCoefficients(n_attacks_total - n_attacks_6 * k + k, k) * pow(get_melee_crit_chance(), k) * pow(1 - get_melee_crit_chance(), n_attacks_total - n_attacks_6 * k); // only true if no white hits
    double temp = p * get_hp() * tempIt->second * 0.02 * k;
    result += temp;
    normConst += p;
  }
  return result / (get_time_of_encounter() * normConst);
}

double Character::get_hps()
{
  double result = get_leader_of_the_pack_hps();
  for (uint i = 0; i < gear[Slot::Head].gems.size(); i++)
  {
    if (gear[Slot::Head].gems[i].get_color()[0] == Color::Meta)
    {
      if (gear[Slot::Head].gems[i].get_name() == "Tenacious Earthstorm Diamond" && gear[Slot::Head].gems[i].active)
      {
        result += (50.0 * 2.0 / 60.0);
      }
    }
  }
  for (uint i = 0; i < elixirs_.size(); i++)
  {
    if (elixirs_[i].get_name() == "Elixir of Major Fortitude")
    {
      result += (10.0 / 5.0);
      break;
    }
  }
  if (gear[Slot::Libram].get_name() == "Libram of Saints Departed")
  {
    double imp_judgement = 0.0;
    for (std::map<std::string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++)
    {
      if (it->first == "Improved Judgement")
      {
        imp_judgement = it->second * 1.0;
      }
    }
    result += ((41 + 49) / 2.0 / (10.0 - imp_judgement));
  }
  if ((gear[Slot::Trinket1].get_name() == "Figurine of the Colossus" && gear[Slot::Trinket1].is_active()) || (gear[Slot::Trinket2].get_name() == "Figurine of the Colossus" && gear[Slot::Trinket2].is_active()))
  {
    FigurineOfTheColossus temp_trinket;
    unsigned int activations = get_time_of_encounter() / (temp_trinket.get_uptime() + temp_trinket.get_cooldown()) + 1;
    unsigned int single_activation_heal = (unsigned int)(temp_trinket.get_uptime() / boss_->get_attack_speed() * get_block()) * 120;
    result += (activations * single_activation_heal / get_time_of_encounter());
  }
  if (gear[Slot::Trinket1].get_name() == "Talisman of the Horde" || gear[Slot::Trinket2].get_name() == "Talisman of the Horde")
  {
    TalismanOfTheHorde temp_trinket;
    result += ((877 + 969) / 2.0 / temp_trinket.get_cooldown());
  }
  if (get_class() == CharacterClass::Druid)
  {
    double potion_hps = (1500 + 2500) / 2.0 / 120.0;
    if (gear[Slot::Trinket1].get_name() == "Alchemist's Stone" || gear[Slot::Trinket2].get_name() == "Alchemist's Stone")
    {
      potion_hps *= 1.4;
    }
  }
  return result;
}

void Character::print_all_stats()
{
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i < (uint)PrimaryAttributes::LastPrimary; i++)
  {
    std::cout << Names::primaryAttributesNames[i] << "=" << get_base_prim_stat((PrimaryAttributes)i) << " + " << get_prim_stat((PrimaryAttributes)i) << " + " << get_bonus_prim_stat((PrimaryAttributes)i) << " = " << get_tot_prim_stat((PrimaryAttributes)i) << std::endl;
  }
  for (uint i = (uint)SecondaryAttributes::FirstSecondary; i < (uint)SecondaryAttributes::LastSecondary; i++)
  {
    std::cout << Names::secondaryAttributesNames[i] << "=" << get_base_sec_stat((SecondaryAttributes)i) << " + " << get_sec_stat((SecondaryAttributes)i) << " + " << get_bonus_sec_stat((SecondaryAttributes)i) << " = " << get_sec_stat((SecondaryAttributes)i) << std::endl;
  }
}