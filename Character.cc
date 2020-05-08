#include "Character.hh"

void Character::add_elixir(Elixir in) {
  bool add = true;
  for (uint i = 0; i < elixirs.size(); i++) {
    if ((elixirs[i].guardian_elixir && in.guardian_elixir) || (elixirs[i].battle_elixir && in.battle_elixir)) {
      add = false;
      break;
    }
  }
  if (add) {
    elixirs.push_back(in);
    primary_stats = primary_stats + in.primary_stats;
    secondary_stats = secondary_stats + in.secondary_stats;
    primary_stats.armor = primary_stats.armor - in.primary_stats.armor;
  }
}

double Character::check_block_chance(double in) {
  if (get_avoidance() + in > 100) {
    double result = 100 - get_avoidance();
    if (result < 0) {
      return 0;
    }
    return result;
  }
  return in;
}

double Character::get_effective_redoubt_chance() {
  bool skilled = false;
  for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
    if (it->first == "Redoubt") {
      if (it->second != 5) {
        cout << "Not yet understood." << endl;
        abort();
      }
      skilled = true;
    }
  }
  if (!skilled) {
    return 0;
  }
  double tot_block_chance = get_block();
  if (gear["Libram"].name == "Libram of Repentance") {
    tot_block_chance += (43 * my_h / f_block);
  }
  tot_block_chance = check_block_chance(tot_block_chance);
  double x1 = 40 - tot_block_chance;
  double x2 = 100 - tot_block_chance;
  double y1 = tot_block_chance / 100.0 + 0.206309 - x1 * 0.00185542;
  double y2 = tot_block_chance / 100.0;
  double avoidance = get_dodge_chance() + get_parry() + get_missed();
  if (avoidance < x1) {
    return (0.206309 - avoidance * 0.00185542) * 100;
  } else if (avoidance >= x1 && avoidance < x2) {
    double c = 0.645623 * tot_block_chance / 100.0 + 0.348888;
    double b = 0.00365483 * tot_block_chance / 100.0 - 0.00675105;
    double a = -6.66862 * pow(10, -6) * tot_block_chance / 100.0 + 3.2928 * pow(10, -5);
    double result = a * avoidance * avoidance + b * avoidance + c - tot_block_chance / 100.0;
    return result * 100.0;
  }
  return 0;
}

void Character::operator=(Character b) {
  talents = b.talents;
  class_ = b.class_;
  race_ = b.race_;
  base_stats = b.base_stats;
  primary_stats = b.primary_stats;
  secondary_stats = b.secondary_stats;
  defense = b.defense;
  expertise = b.expertise;
  level = b.level;
  dodge = b.dodge;
  parry = b.parry;
  block_chance = b.block_chance;
  crit = b.crit;
  spell_crit = b.spell_crit;
  hit = b.hit;
  spell_hit = b.spell_hit;
  r_expertise = b.r_expertise;
  r_hit = b.r_hit;
  r_spell_hit = b.r_spell_hit;
  r_crit = b.r_crit;
  r_haste = b.r_haste;
  r_armor_pen = b.r_armor_pen;
  r_def = b.r_def;
  r_def_avoidance = b.r_def_avoidance;
  r_dodge = b.r_dodge;
  r_parry = b.r_parry;
  r_block = b.r_block;
  r_resilience = b.r_resilience;
  c_d = b.c_d;
  c_p = b.c_p;
  c_m = b.c_m;
  k = b.k;
  f_expertise = b.f_expertise;
  f_hit = b.f_hit;
  f_spell_hit = b.f_spell_hit;
  f_crit = b.f_crit;
  f_haste = b.f_haste;
  f_armor_pen = b.f_armor_pen;
  f_def = b.f_def;
  f_def_avoidance = b.f_def_avoidance;
  f_dodge = b.f_dodge;
  f_parry = b.f_parry;
  f_block = b.f_block;
  f_resilience = b.f_resilience;
  h = b.h;
  gear = b.gear;
  number_of_rings = b.number_of_rings;
  number_of_trinkets = b.number_of_trinkets;
  elixirs = b.get_elixirs();
  boss = b.get_encounter();
  n_dd = b.get_n_dds();
  time_needed = b.get_time_of_encounter();
  my_h = b.my_h;
  my_r_dodge = b.my_r_dodge;
}

Character::Character(string class_name, string race_name) {
  level = 70;
  class_ = class_name;
  race_ = race_name;
  h = -3.0 / 82.0 * level + 131.0 / 41.0;
  my_h = 0.6313425;
  f_expertise = 2.5;
  f_def = 1.5;
  f_dodge = 13.8;
  f_parry = 13.8;
  f_block = 5.0;
  f_hit = 10.0;
  f_crit = 14.0;
  f_haste = 10.0;
  f_spell_hit = 8.0;
  f_resilience = 28.75;
  f_armor_pen = 3.756097412;

  r_expertise = my_h / f_expertise;
  r_hit = my_h / f_hit;
  r_spell_hit = my_h / f_spell_hit;
  r_crit = my_h / f_crit;
  r_haste = my_h / f_haste;
  r_armor_pen = my_h / f_armor_pen;
  r_def = my_h / f_def;
  r_def_avoidance = 14.8125;
  r_dodge = my_h / f_dodge;
  my_r_dodge = 0.0528579;
  r_parry = my_h / f_dodge;
  r_block = my_h / f_block;
  r_resilience = my_h / f_resilience;

  dodge = 0.0;
  parry = 5.0;
  block_chance = 5.0;
  crit = 0.0;
  spell_crit = 0.0;
  hit = 0.0;
  spell_hit = 0.0;
  defense = 5 * level;
  if (class_name == "Paladin") {
    dodge += 0.65;
    c_d = 88.129021;
    c_p = 47.003525;
    c_m = 16;
    k = 0.956;
    spell_crit += 3.336;
    if (race_name == "Draenei") {
      base_stats.strength = 127;
      base_stats.agility = 74;
      base_stats.stamina = 123; // 138
      base_stats.intelligence = 84;
      base_stats.spirit = 91;
      base_stats.armor = 0;     // 148
      base_stats.health = 3377; // 4577
      base_stats.mana = 2953;   // 3933
    } else {
      cout << "Incomplete." << endl;
      abort();
    }
  } else {
    cout << "Incomplete." << endl;
    abort();
  }
}

void Character::set_talent(string name_, unsigned int points) {
  talents.insert(pair<string, unsigned int>(name_, points));
  if (name_ == "Deflection") {
    parry += (1.0 * points);
  } else if (name_ == "Improved Seal of the Crusader") {
    crit += (points * 1.0);
    spell_crit += (points * 1.0);
  } else if (name_ == "Conviction") {
    crit += (points * 1.0);
  } else if (name_ == "Vengeance") {
    crit += (1.0 * points * 3.0);
    spell_crit += (1.0 * points * 3.0);
  } else if (name_ == "Sanctified Seals") {
    crit += (1.0 * points);
    spell_crit += (1.0 * points);
  } else if (name_ == "Anticipation") {
    defense += (4 * points);
  } else if (name_ == "Combat Expertise") {
    expertise += (1 * points);
  } else if (name_ == "Holy Power") {
    spell_crit += (1.0 * points);
  } else if (name_ == "Precision") {
    hit += (1.0 * points);
  } else if (name_ == "Improved Holy Shield" && points == 2) {
    block_chance += 30.0;
  }
}

double Character::get_dodge_chance_with_dr() {
  double result;
  // double a_b = base_stats.agility / r_d;
  double a_u = primary_stats.agility * 0.04;
  double d_u = secondary_stats.dodge_rating * my_r_dodge;
  double f_u = max(0.0, ((int)(secondary_stats.defense_rating * r_def + defense - 5 * boss.get_lvl())) * 0.04);
  double u = a_u + d_u + f_u;
  return u * c_d / (u + k * c_d) + dodge;
}

double Character::get_dodge_chance() {
  double a_u = (primary_stats.agility + bonus_prim_stats.agility + base_stats.agility) * 0.04;
  double d_u = (secondary_stats.dodge_rating + bonus_sec_stats.dodge_rating) * my_r_dodge;
  double f_u = max(0.0, (int)((secondary_stats.defense_rating + bonus_sec_stats.defense_rating) * r_def + defense - 5 * boss.get_lvl()) * 0.04);
  double u = a_u + d_u + f_u + dodge;
  return u;
}

unsigned int Character::get_armor() {
  double temp_armor = primary_stats.armor + bonus_prim_stats.armor + base_stats.armor;
  temp_armor += (primary_stats.agility + bonus_prim_stats.agility + base_stats.agility) * 2;
  return round(temp_armor);
}

double Character::get_armor_reduction() {
  unsigned int armor = get_armor();
  double result = armor / (armor + 467.5 * boss.get_lvl() - 22167.5);
  if (result > 0.75) {
    result = 0.75;
  }
  return result;
}

double Character::get_parry() {
  double temp_defense = max(0.0, ((double)secondary_stats.defense_rating + bonus_sec_stats.defense_rating) / f_def * my_h + defense - 5 * boss.get_lvl());
  return ((double)secondary_stats.parry_rating + bonus_sec_stats.parry_rating) / f_parry * my_h + parry + 0.04 * (int)temp_defense;
}

double Character::get_block() {
  double temp_block = max(0.0, ((double)secondary_stats.defense_rating + bonus_sec_stats.defense_rating) / f_def * my_h + defense - 5 * boss.get_lvl());
  double result = ((double)secondary_stats.block_chance_rating + bonus_sec_stats.block_chance_rating) / f_block * my_h + block_chance + 0.04 * (int)temp_block;
  if (get_avoidance() + result > 100.0) {
    result = 100.0 - get_avoidance();
    if (result < 0) {
      return 0;
    }
  }
  return result;
}

double Character::get_missed() {
  double temp_defense = max(0.0, (secondary_stats.defense_rating + bonus_sec_stats.defense_rating) / f_def * my_h + defense - 5 * boss.get_lvl());
  return (int)temp_defense * 0.04 + 5.0;
}

double Character::get_eff_hp(double time_in_seconds_) {
  double time_in_seconds = time_in_seconds_;
  set_encounter(boss, n_dd);
  if (time_in_seconds_ == 0.0) {
    time_in_seconds = time_needed;
  }
  unsigned int stamina = primary_stats.stamina + base_stats.stamina + bonus_prim_stats.stamina;
  unsigned int hp = primary_stats.health + base_stats.health + bonus_prim_stats.health;
  double block_value = get_block_value();
  double tot_block_chance = get_block() + get_effective_redoubt_chance();
  unsigned int sanctuary_absorbtion = 0;
  if (sanctuary) {
    sanctuary_absorbtion = 80 * (unsigned int)(time_in_seconds / boss.get_attack_speed() * (1 - get_avoidance() / 100.0));
  }

  double hps = 0.0;
  for (uint i = 0; i < gear["Head"].gems.size(); i++) {
    if (gear["Head"].gems[i].color[0] == "meta") {
      if (gear["Head"].gems[i].name == "Tenacious Earthstorm Diamond" && gear["Head"].gems[i].active) {
        hps += (50.0 * 2.0 / 60.0);
      }
    }
  }
  for (uint i = 0; i < elixirs.size(); i++) {
    if (elixirs[i].name == "Elixir of Major Fortitude") {
      hps += (10.0 / 5.0);
      break;
    }
  }
  if (gear["Libram"].name == "Libram of Saints Departed") {
    double imp_judgement = 0.0;
    for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
      if (it->first == "Improved Judgement") {
        imp_judgement = it->second * 1.0;
      }
    }
    hps += ((41 + 49) / 2.0 / (10.0 - imp_judgement));
  } else if (gear["Libram"].name == "Libram of Repentance") {
    tot_block_chance += (43 * my_h / f_block);
  }
  check_block_chance(tot_block_chance);
  double heal = 0.0;
  if (gear["Trinket0"].name == "Figurine of the Colossus" || gear["Trinket1"].name == "Figurine of the Colossus") {
    FigurineOfTheColossus temp_trinket;
    unsigned int activations = time_in_seconds / (temp_trinket.get_uptime() + temp_trinket.get_cooldown()) + 1;
    unsigned int single_activation_heal = (unsigned int)(temp_trinket.get_uptime() / boss.get_attack_speed() * tot_block_chance / 100.0) * 120;
    heal += (activations * single_activation_heal);
  }
  double pseudo_heal = 0.0;
  if (gear["Trinket0"].name == "Gnomeregan Auto-Blocker 600" || gear["Trinket1"].name == "Gnomeregan Auto-Blocker 600") {
    GnomereganAutoBlocker600 temp_trinket;
    unsigned int activations = time_in_seconds / (temp_trinket.get_uptime() + temp_trinket.get_cooldown()) + 1;
    unsigned int single_activation_pseudo_heal = (unsigned int)(temp_trinket.get_uptime() / boss.get_attack_speed() * tot_block_chance / 100.0) * 200;
    pseudo_heal += (activations * single_activation_pseudo_heal);
    for (uint i = 0; i < gear["Head"].gems.size(); i++) {
      if (gear["Head"].gems[i].name == "Eternal Earthstorm Diamond" && gear["Head"].gems[i].active) {
        pseudo_heal *= 1.1;
      }
    }
    map<string, unsigned int>::iterator it;
    it = talents.find("Shield Specialization");
    if (it != talents.end()) {
      pseudo_heal *= (1 + it->second * 0.1);
    }
  }
  double physical =
      (time_in_seconds * hps + heal + pseudo_heal + hp + stamina * 10 + (unsigned int)(tot_block_chance / 100.0 * time_in_seconds / boss.get_attack_speed()) * block_value + sanctuary_absorbtion) /
      ((1 - get_armor_reduction()) * (1 - get_avoidance() / 100.0));
  double unblockable_physical = (time_in_seconds * hps + heal + hp + stamina * 10 + sanctuary_absorbtion) / ((1 - get_armor_reduction()) * (1 - get_avoidance() / 100.0));
  double crit_chance_reduction = min(red_chance_to_get_crit(), 5.6 / 100.0);
  double magical_arcane = (time_in_seconds * hps + hp + stamina * 10) / (1 - average_resistance("Arcane"));
  double magical_fire = (time_in_seconds * hps + hp + stamina * 10) / (1 - average_resistance("Fire"));
  double magical_frost = (time_in_seconds * hps + hp + stamina * 10) / (1 - average_resistance("Frost"));
  double frost_based_melee = (time_in_seconds * hps + hp + stamina * 10) / ((1 - average_resistance("Frost")) * (1 + 5.6 / 100.0 - crit_chance_reduction) * (1 - get_avoidance() / 100.0));
  double magical_nature = (time_in_seconds * hps + hp + stamina * 10) / (1 - average_resistance("Nature"));
  double magical_shadow = (time_in_seconds * hps + hp + stamina * 10) / (1 - average_resistance("Shadow"));
  double result = physical;
  for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
    if (it->first == "Improved Righteous Fury") {
      result /= (1.0 - 0.02 * it->second);
      break;
    }
  }
  if (result < 0) {
    cout << "eff hp is smaller than 0!" << endl;
    cout << "tot block chance=" << tot_block_chance << endl;

    cout << "dodge chance=" << get_dodge_chance() << endl;
    cout << "parry chance=" << get_parry() << endl;
    cout << "miss chance=" << get_missed() << endl;
    cout << "armor reduction=" << get_armor_reduction() * 100.0 << endl;
    cout << "tot avoidance=" << (1 - get_armor_reduction()) * (1 - get_avoidance() / 100.0) << endl;
    abort();
  }
  return result;
}

void Character::equip(Gear gear_piece) {
  if (gear_piece.slot == "Ring" && number_of_rings < 2) {
    gear_piece.slot = gear_piece.slot + to_string(number_of_rings);
    number_of_rings++;
  } else if (gear_piece.slot == "Ring" && number_of_rings >= 2) {
    abort();
  } else if (gear_piece.slot == "Trinket" && number_of_trinkets < 2) {
    gear_piece.slot = gear_piece.slot + to_string(number_of_trinkets);
    number_of_trinkets++;
  }
  reset_boni();
  for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
    if (it->first == "Toughness") {
      gear_piece.primary_stats.armor = round(gear_piece.primary_stats.armor * (1.0 + it->second * 0.02));
      break;
    }
  }

  for (uint i = 0; i < gear["Head"].gems.size(); i++) {
    if (find(gear["Head"].gems[i].color.begin(), gear["Head"].gems[i].color.end(), "meta") != gear["Head"].gems[i].color.end()) {
      if (gear["Head"].gems[i].active) {
        gear["Head"].gems[i].active = false;
        if (gear["Head"].gems[i].name == "Tenacious Earthstorm Diamond" || gear["Head"].gems[i].name == "Eternal Earthstorm Diamond") {
          secondary_stats.defense_rating -= 12;
        } else if (gear["Head"].gems[i].name == "Powerful Earthstorm Diamond") {
          primary_stats.stamina -= 18;
        }
      }
    }
  }

  if (gear.find(gear_piece.slot) != gear.end()) {
    primary_stats = primary_stats - gear[gear_piece.slot].primary_stats;
    secondary_stats = secondary_stats - gear[gear_piece.slot].secondary_stats;
    gear[gear_piece.slot] = gear_piece;
    primary_stats = primary_stats + gear_piece.primary_stats;
    secondary_stats = secondary_stats + gear_piece.secondary_stats;
    gear[gear_piece.slot].equipped = true;
  } else {
    gear.insert(pair<string, Gear>(gear_piece.slot, gear_piece));
  }
}

double Character::red_chance_to_get_crit() {
  double result = ((int)(secondary_stats.defense_rating * r_def + defense - 5 * boss.get_lvl())) * 0.04 + secondary_stats.resilience_rating * 0.025339367;
  return result;
}

double Character::get_tps() {
  double result = 0.0;
  double threat_multiplier = 0.0;
  double time_reduction = 0.0;
  double damage_multiplier = 0.0;
  double tot_block_chance = get_block();
  for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
    if (it->first == "One-Handed Weapon Specialization") {
      damage_multiplier = (it->second * 0.01 + 1);
    } else if (it->first == "Improved Righteous Fury") {
      threat_multiplier = round(0.5 / 3.0 * it->second);
      threat_multiplier = 1 + 0.6 * (1 + threat_multiplier);
    } else if (it->first == "Improved Judgement") {
      time_reduction = it->second * 1.0;
    }
  }
  if (class_ == "Paladin") {
    unsigned int t4_set = 0;
    if (gear["Head"].name.find("Justicar") != string::npos) {
      t4_set++;
    }
    if (gear["Shoulder"].name.find("Justicar") != string::npos) {
      t4_set++;
    }
    if (gear["Chest"].name.find("Justicar") != string::npos) {
      t4_set++;
    }
    if (gear["Hands"].name.find("Justicar") != string::npos) {
      t4_set++;
    }
    if (gear["Legs"].name.find("Justicar") != string::npos) {
      t4_set++;
    }
    tot_block_chance += get_effective_redoubt_chance();
    if (gear["Libram"].name == "Libram of Repentance") {
      tot_block_chance += (43 * my_h / f_block);
    }
    tot_block_chance = check_block_chance(tot_block_chance);
    // consecration
    result = result + (64 + 0.042 * secondary_stats.spellpower) * threat_multiplier;
    // holy shield
    double t4_HS_multiplier = 1.0;
    if (t4_set >= 4) {
      t4_HS_multiplier = 1.15;
    }
    result = result + (1.0 / boss.get_attack_speed() * tot_block_chance / 100.0) * (155 + 0.05 * secondary_stats.spellpower) * (threat_multiplier + 0.35) * t4_HS_multiplier;
    // blessing of sanctuary
    if (sanctuary) {
      result = result + (1.0 / boss.get_attack_speed() * tot_block_chance / 100.0) * (46 * secondary_stats.spellpower * 0.01) * threat_multiplier;
    }
    // seal of vengeance
    double t4_SoV_multiplier = 1.0;
    if (t4_set >= 2) {
      t4_SoV_multiplier = 1.1;
    }
    result = result + t4_SoV_multiplier * ((150 + secondary_stats.spellpower * 0.190985485) * 5.0 / 15.0 * threat_multiplier +
                                           (120 + secondary_stats.spellpower * 0.478736949) * 5.0 / (10 - time_reduction) *
                                               ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 1.5) * threat_multiplier * get_spell_hit_chance() / 100.0);
    // retribution aura
    if (gear["Libram"].name != "Libram of Truth") {
      result = result + (26 + secondary_stats.spellpower / 30.3) * threat_multiplier / boss.get_attack_speed();
    }
    // Darkmoon Card
    for (map<string, Gear>::iterator it = gear.begin(); it != gear.end(); it++) {
      if (it->second.name == "Darkmoon Card: Vengeance") {
        result = result + 0.1 * (1 - get_avoidance() / 100.0) * (95.0 + 116.0) / 2.0 * threat_multiplier * ((1 - get_spell_crit_chance() / 100.0) + get_spell_crit_chance() / 100.0 * 1.5);
      }
    }
  } else {
    cout << "Incomplete." << endl;
    abort();
  }
  return result * damage_multiplier;
}

void Character::compute_stats() {
  map<string, unsigned int>::iterator holy_guidance = talents.begin(), combat_expertise = talents.begin(), sacred_duty = talents.begin(), shield_specialization = talents.begin(),
                                      imp_devotion_aura = talents.begin();
  // cout << "computing" << endl;
  vector<Socket> gems;
  for (map<string, Gear>::iterator it = gear.begin(); it != gear.end(); it++) {
    if (!it->second.equipped) {
      primary_stats = primary_stats + it->second.primary_stats;
      secondary_stats = secondary_stats + it->second.secondary_stats;
      it->second.equipped = true;
    }
    gems.insert(gems.end(), it->second.gems.begin(), it->second.gems.end());
  }

  for (uint i = 0; i < gear["Head"].gems.size(); i++) {
    if (find(gear["Head"].gems[i].color.begin(), gear["Head"].gems[i].color.end(), "meta") != gear["Head"].gems[i].color.end()) {
      if (gear["Head"].gems[i].is_active(gems)) {
        if (gear["Head"].gems[i].name == "Tenacious Earthstorm Diamond" || gear["Head"].gems[i].name == "Eternal Earthstorm Diamond") {
          secondary_stats.defense_rating += 12;
        } else if (gear["Head"].gems[i].name == "Powerful Earthstorm Diamond") {
          primary_stats.stamina += 18;
        }
        gear["Head"].socket_bonus();
      }
    }
  }
  for (map<string, unsigned int>::iterator it = talents.begin(); it != talents.end(); it++) {
    if (it->first == "Divine Strength") {
      bonus_prim_stats.strength += round((base_stats.strength + primary_stats.strength) * (1 + it->second * 0.02));
    } else if (it->first == "Divine Intellect") {
      bonus_prim_stats.intelligence += round((base_stats.intelligence + primary_stats.intelligence) * (1 + it->second * 0.02));
    } else if (it->first == "Holy Guidance") {
      holy_guidance = it;
    } else if (it->first == "Sacred Duty") {
      sacred_duty = it;
    } else if (it->first == "Combat Expertise") {
      combat_expertise = it;
    } else if (it->first == "Shield Specialization") {
      shield_specialization = it;
    } else if (it->first == "Improved Devotion Aura") {
      imp_devotion_aura = it;
    }
  }

  double stamina_bonus = 0;
  if (sacred_duty->first == "Sacred Duty" && combat_expertise->first == "Combat Expertise") {
    stamina_bonus = ((base_stats.stamina + primary_stats.stamina) * (1 + sacred_duty->second * 0.03) * (1 + combat_expertise->second * 0.02)) - base_stats.stamina - primary_stats.stamina;
  } else if (sacred_duty->first == "Sacred Duty" && combat_expertise->first != "Combat Expertise") {
    stamina_bonus = ((base_stats.stamina + primary_stats.stamina) * sacred_duty->second * 0.03);
  } else if (sacred_duty->first != "Sacred Duty" && combat_expertise->first == "Combat Expertise") {
    stamina_bonus = ((base_stats.stamina + primary_stats.stamina) * combat_expertise->second * 0.02);
  }
  bonus_prim_stats.stamina += round(stamina_bonus);

  if (kings) {
    bonus_prim_stats.stamina = round(bonus_prim_stats.stamina * 1.1 + 0.1 * (primary_stats.stamina));
    bonus_prim_stats.strength = round(bonus_prim_stats.strength * 1.1 + 0.1 * (primary_stats.strength));
    bonus_prim_stats.agility = round(bonus_prim_stats.agility * 1.1 + 0.1 * (primary_stats.agility));
    bonus_prim_stats.intelligence = round(bonus_prim_stats.intelligence * 1.1 + 0.1 * (primary_stats.intelligence));
    bonus_prim_stats.spirit = round(bonus_prim_stats.spirit * 1.1 + 0.1 * (primary_stats.spirit));
  }
  if (holy_guidance->first == "Holy Guidance") {
    bonus_sec_stats.spellpower = round((primary_stats.intelligence + base_stats.intelligence) * (holy_guidance->second * 0.07));
    bonus_sec_stats.healing = round((primary_stats.intelligence + base_stats.intelligence) * (holy_guidance->second * 0.07));
  }
  // bonus_prim_stats.armor += (base_stats.agility * 2 + primary_stats.agility * 2 + bonus_prim_stats.agility * 2);
  if (gear["Libram"].name == "Libram of Truth") {
    double armor_temp = 861;
    if (imp_devotion_aura->first == "Improved Devotion Aura") {
      armor_temp *= (1 + 0.08 * imp_devotion_aura->second);
    }
    bonus_prim_stats.armor += (110 + armor_temp);
  }
  if (race_ == "Tauren") {
    bonus_prim_stats.health = round(bonus_prim_stats.health + (base_stats.stamina * 10 + primary_stats.stamina * 10 + bonus_prim_stats.stamina * 10 + base_stats.health + primary_stats.health) * 0.05);
  }

  // bonus_prim_stats.mana += (base_stats.intelligence * 15 + primary_stats.intelligence * 15);
  /*if (shield_specialization->first == "Shield Specialization") {
    bonus_sec_stats.block_value += round((secondary_stats.block_value + bonus_sec_stats.block_value) * shield_specialization->second * 0.1);
  }
  for (uint i = 0; i < gear["Head"].gems.size(); i++) {
    if (gear["Head"].gems[i].name == "Eternal Earthstorm Diamond" && gear["Head"].gems[i].active) {
      bonus_sec_stats.block_value += (0.1 * secondary_stats.block_value);
    }
  }*/
  set_encounter(boss, n_dd);
}

void Character::print_gear() {
  for (map<string, Gear>::iterator it = gear.begin(); it != gear.end(); it++) {
    cout << it->second.slot << "\t" << it->second.get_name() << endl;
  }
}

double Character::get_spell_hit_chance() { return 83.0 + secondary_stats.spellhit_rating * my_h / f_spell_hit; }
double Character::get_spell_crit_chance() {
  return spell_crit + (primary_stats.intelligence + base_stats.intelligence + bonus_prim_stats.intelligence) / 80.05 + secondary_stats.spellcrit_rating * my_h / f_crit;
}

double Character::get_hp() {
  unsigned int stamina = primary_stats.stamina + base_stats.stamina + bonus_prim_stats.stamina;
  unsigned int hp = primary_stats.health + base_stats.health + bonus_prim_stats.health;
  return hp + stamina * 10 - 180;
}

void Character::print_elixirs() {
  cout << "Consumed Elixirs/Flask:" << endl;
  for (uint i = 0; i < elixirs.size(); i++) {
    cout << elixirs[i].name << endl;
  }
}

double Character::get_avoidance() {
  double result = get_dodge_chance() + get_parry() + get_missed();
  if (result > 100) {
    return 100;
  }
  return result;
}

void Character::find_best_gems(Gear *gear_piece, vector<Socket> *gems) {
  reset_boni();
  double max_eff_hp = 0;
  if (gear_piece->get_sockets() == 1) {
    unsigned int max_i;
    for (uint i = 0; i < gems->size(); i++) {
      Gear temp = (*gear_piece);
      temp.add_gem(gems->at(i));
      equip(temp);
      compute_stats();
      if (get_eff_hp() > max_eff_hp) {
        max_eff_hp = get_eff_hp();
        max_i = i;
      }
      reset_boni();
    }
    gear_piece->add_gem(gems->at(max_i));
  } else if (gear_piece->get_sockets() == 2) {
    unsigned int max_i, max_j;
    for (uint i = 0; i < gems->size(); i++) {
      for (uint j = 0; j < gems->size(); j++) {
        if (gems->at(i).color[0] == "meta" && gems->at(j).color[0] == "meta") {
          continue;
        }
        Gear temp = (*gear_piece);
        temp.add_gem(gems->at(i));
        temp.add_gem(gems->at(j));
        equip(temp);
        compute_stats();
        if (get_eff_hp() > max_eff_hp) {
          max_eff_hp = get_eff_hp();
          max_i = i;
          max_j = j;
        }
        if (gear_piece->slot == "Head" && (gems->at(i).color[0] == "meta" || gems->at(j).color[0] == "meta")) {
          for (uint bla = 0; bla < gear_piece->gems.size(); bla++) {
            if (gear_piece->gems[bla].active) {
              cout << "blubb" << endl;
            }
          }
        }
        reset_boni();
      }
    }
    gear_piece->add_gem(gems->at(max_i));
    gear_piece->add_gem(gems->at(max_j));
  } else if (gear_piece->get_sockets() == 3) {
    unsigned int max_i, max_j, max_k;
    for (uint i = 0; i < gems->size(); i++) {
      for (uint j = 0; j < gems->size(); j++) {
        for (uint k = 0; k < gems->size(); k++) {
          Gear temp = (*gear_piece);
          temp.add_gem(gems->at(i));
          temp.add_gem(gems->at(j));
          temp.add_gem(gems->at(k));
          equip(temp);
          compute_stats();
          if (get_eff_hp() > max_eff_hp) {
            max_eff_hp = get_eff_hp();
            max_i = i;
            max_j = j;
            max_k = k;
          }
          reset_boni();
        }
      }
    }
    gear_piece->add_gem(gems->at(max_i));
    gear_piece->add_gem(gems->at(max_j));
    gear_piece->add_gem(gems->at(max_k));
    // cout << "gear_piece_gems.size=" << gear_piece->gems.size() << endl;
  }
  reset_boni();
}

void Character::reset_boni() {
  PrimaryStats temp;
  bonus_prim_stats = temp;
  SecondaryStats temp2;
  bonus_sec_stats = temp2;
  for (uint i = 0; i < elixirs.size(); i++) {
    bonus_prim_stats.armor += elixirs[i].primary_stats.armor;
  }
  for (uint i = 0; i < buffs.size(); i++) {
    bonus_prim_stats.armor += buffs[i].primary_stats.armor;
  }
}

double Character::average_resistance(string school) {
  unsigned int resistance = 0;
  if (school == "Arcane") {
    resistance = primary_stats.arcane_resistance + bonus_prim_stats.arcane_resistance;
  } else if (school == "Fire") {
    resistance = primary_stats.fire_resistance + bonus_prim_stats.fire_resistance;
  } else if (school == "Frost") {
    resistance = primary_stats.frost_resistance + bonus_prim_stats.frost_resistance;
  } else if (school == "Nature") {
    resistance = primary_stats.nature_resistance + bonus_prim_stats.nature_resistance;
  } else if (school == "Shadow") {
    resistance = primary_stats.shadow_resistance + bonus_prim_stats.shadow_resistance;
  }
  double result = resistance / (boss.get_lvl() * 5.0) * 0.75;
  if (result > 0.75) {
    return 0.75;
  }
  return result;
}
// warr,pala,schami,rogue,mage,wl,priest,druid,hunter
void Character::set_encounter(Boss boss_, unsigned int n_dd_) {
  boss = boss_;
  n_dd = n_dd_;
  double average_relative_aggro_threshold = (5.0 * 1.1 + 6.0 * 1.3) / 11.0;
  double average_dps = get_tps() / 0.7 * average_relative_aggro_threshold;
  time_needed = boss_.get_health() / (average_dps * (double)n_dd);
}

double Character::get_crush() {
  double result = 0.02 * (boss.get_lvl() * 5.0 - level * 5.0) - 0.15;
  if (result < 0) {
    return 0;
  }
  return min(result, 1 - get_avoidance() - get_block());
}

bool Character::survives_worst_case_szenario() {
  double factor = 1.0;
  double blocked_dmg = get_block_value();
  if (get_crush() > 0) {
    factor = 1.5;
    blocked_dmg = 0;
  }
  double physical_dmg = (get_encounter().get_worst_case_szenario()->get_white_dmg() * factor * get_armor_reduction() - blocked_dmg) * get_encounter().get_worst_case_szenario()->get_n_hits();
  double magical_dmg = 0;
  if (get_encounter().get_worst_case_szenario()->get_magic_school() != "") {
    magical_dmg = get_encounter().get_worst_case_szenario()->get_magic_dmg() * average_resistance(get_encounter().get_worst_case_szenario()->get_magic_school());
  }
  unsigned int stamina = primary_stats.stamina + base_stats.stamina + bonus_prim_stats.stamina;
  unsigned int hp = primary_stats.health + base_stats.health + bonus_prim_stats.health;
  if (stamina * 10 + hp > physical_dmg + magical_dmg) {
    return true;
  }
  return false;
}

void Character::add_buff(Buff in) {
  if (find(buffs.begin(), buffs.end(), in) == buffs.end()) {
    primary_stats = primary_stats + in.primary_stats;
    secondary_stats = secondary_stats + in.secondary_stats;
    if (in.name == "Blessing of Kings") {
      kings = true;
    } else if (in.name == "Blessing of Sanctuary") {
      sanctuary = true;
    }
    buffs.push_back(in);
  }
}

void Character::get_raid_buffed() {
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

void Character::print_buffs() {
  cout << "Buffs:" << endl;
  for (uint i = 0; i < buffs.size(); i++) {
    cout << buffs[i].name << endl;
  }
}

double Character::get_mp() {
  double result = bonus_prim_stats.mana + primary_stats.mana + base_stats.mana;
  double temp_int = bonus_prim_stats.intelligence + primary_stats.intelligence + base_stats.intelligence;
  if (temp_int > 20) {
    result += ((temp_int - 20) * 15 + 20);
  } else {
    result += (temp_int);
  }
  return result;
}

void Character::print_base_stats() {
  cout << "Strength=" << primary_stats.strength + bonus_prim_stats.strength + base_stats.strength << endl;
  cout << "Agility=" << primary_stats.agility + bonus_prim_stats.agility + base_stats.agility << endl;
  cout << "Stamina=" << primary_stats.stamina + bonus_prim_stats.stamina + base_stats.stamina << endl;
  cout << "Intellect=" << primary_stats.intelligence + bonus_prim_stats.intelligence + base_stats.intelligence << endl;
  cout << "Spirit=" << primary_stats.spirit + bonus_prim_stats.spirit + base_stats.spirit << endl;
  cout << "Armor=" << get_armor() << endl;
}

unsigned int Character::get_defense() {
  double result = (secondary_stats.defense_rating + bonus_sec_stats.defense_rating) * r_def + defense;
  return round(result);
}

unsigned int Character::get_block_value() {
  double result = max(0.0, (primary_stats.strength + bonus_prim_stats.strength + base_stats.strength) / 50.0 * 3.0 - 2.0);
  result += (secondary_stats.block_value + bonus_sec_stats.block_value);
  map<string, unsigned int>::iterator it = talents.find("Shield Specialization");
  if (it != talents.end()) {
    result *= (1 + 0.1 * it->second);
  }
  for (uint i = 0; i < gear["Head"].gems.size(); i++) {
    if (gear["Head"].gems[i].name == "Eternal Earthstorm Diamond" && gear["Head"].gems[i].active) {
      result *= 1.1;
    }
  }
  return round(result);
}
