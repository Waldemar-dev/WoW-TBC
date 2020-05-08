#include "stats.hh"

PrimaryStats::PrimaryStats() {
  strength = 0;
  agility = 0;
  stamina = 0;
  intelligence = 0;
  spirit = 0;
  armor = 0;
  arcane_resistance = 0;
  fire_resistance = 0;
  frost_resistance = 0;
  shadow_resistance = 0;
  nature_resistance = 0;
  weapondamage = 0;
  attack_speed = 0.0;
  health = 0.0;
  mana = 0.0;
}

PrimaryStats PrimaryStats::operator+(PrimaryStats b) {
  PrimaryStats result;
  result.strength = strength + b.strength;
  result.agility = agility + b.agility;
  result.stamina = stamina + b.stamina;
  result.intelligence = intelligence + b.intelligence;
  result.spirit = spirit + b.spirit;
  result.armor = armor + b.armor;
  result.arcane_resistance = arcane_resistance + b.arcane_resistance;
  result.fire_resistance = fire_resistance + b.fire_resistance;
  result.frost_resistance = frost_resistance + b.frost_resistance;
  result.shadow_resistance = shadow_resistance + b.shadow_resistance;
  result.nature_resistance = nature_resistance + b.nature_resistance;
  result.weapondamage = weapondamage + b.weapondamage;
  result.attack_speed = attack_speed + b.attack_speed;
  result.health = health + b.health;
  result.mana = mana + b.mana;
  return result;
}

PrimaryStats PrimaryStats::operator-(PrimaryStats b) {
  PrimaryStats result;
  result.strength = strength - b.strength;
  if (agility == 0) { // 0-0 yielded max_uint
    result.agility = agility;
  } else {
    result.agility = agility - b.agility;
  }
  result.stamina = stamina - b.stamina;
  result.intelligence = intelligence - b.intelligence;
  result.spirit = spirit - b.spirit;
  result.armor = armor - b.armor;
  result.arcane_resistance = arcane_resistance - b.arcane_resistance;
  result.fire_resistance = fire_resistance - b.fire_resistance;
  result.frost_resistance = frost_resistance - b.frost_resistance;
  result.shadow_resistance = shadow_resistance - b.shadow_resistance;
  result.nature_resistance = nature_resistance - b.nature_resistance;
  result.weapondamage = weapondamage - b.weapondamage;
  result.attack_speed = attack_speed - b.attack_speed;
  result.health = health - b.health;
  result.mana = mana - b.mana;
  return result;
}

void PrimaryStats::operator=(PrimaryStats b) {
  strength = b.strength;
  agility = b.agility;
  stamina = b.stamina;
  intelligence = b.intelligence;
  spirit = b.spirit;
  armor = b.armor;
  arcane_resistance = b.arcane_resistance;
  fire_resistance = b.fire_resistance;
  frost_resistance = b.frost_resistance;
  shadow_resistance = b.shadow_resistance;
  nature_resistance = b.nature_resistance;
  weapondamage = b.weapondamage;
  attack_speed = b.attack_speed;
  health = b.health;
  mana = b.mana;
}

SecondaryStats::SecondaryStats() {
  dodge_rating = 0;
  parry_rating = 0;
  block_chance_rating = 0;
  block_value = 0;
  defense_rating = 0;
  hit_rating = 0;
  spellhit_rating = 0;
  spellpower = 0;
  crit_rating = 0;
  spellcrit_rating = 0;
  healing = 0;
  mp5 = 0;
  haste_rating = 0;
  spell_haste_rating = 0;
  attackpower = 0;
  resilience_rating = 0;
  expertise_rating = 0;
}

SecondaryStats SecondaryStats::operator+(SecondaryStats b) {
  SecondaryStats result;
  result.dodge_rating = dodge_rating + b.dodge_rating;
  result.parry_rating = parry_rating + b.parry_rating;
  result.block_chance_rating = block_chance_rating + b.block_chance_rating;
  result.block_value = block_value + b.block_value;
  result.defense_rating = defense_rating + b.defense_rating;
  result.hit_rating = hit_rating + b.hit_rating;
  result.spellhit_rating = spellhit_rating + b.spellhit_rating;
  result.spellpower = spellpower + b.spellpower;
  result.crit_rating = crit_rating + b.crit_rating;
  result.spellcrit_rating = spellcrit_rating + b.spellcrit_rating;
  result.healing = healing + b.healing;
  result.mp5 = mp5 + b.mp5;
  result.haste_rating = haste_rating + b.haste_rating;
  result.spell_haste_rating = spell_haste_rating + b.spell_haste_rating;
  result.attackpower = attackpower + b.attackpower;
  result.resilience_rating = resilience_rating + b.resilience_rating;
  result.expertise_rating = expertise_rating + b.expertise_rating;
  return result;
}

SecondaryStats SecondaryStats::operator-(SecondaryStats b) {
  SecondaryStats result;
  result.dodge_rating = dodge_rating - b.dodge_rating;
  result.parry_rating = parry_rating - b.parry_rating;
  result.block_chance_rating = block_chance_rating - b.block_chance_rating;
  result.block_value = block_value - b.block_value;
  result.defense_rating = defense_rating - b.defense_rating;
  result.hit_rating = hit_rating - b.hit_rating;
  result.spellhit_rating = spellhit_rating - b.spellhit_rating;
  result.spellpower = spellpower - b.spellpower;
  if (b.crit_rating == 0) { // 0-0=max_uint
    result.crit_rating = crit_rating;
  } else {
    result.crit_rating = crit_rating - b.crit_rating;
  }
  if (b.spellcrit_rating == 0) {
    result.spellcrit_rating = spellcrit_rating;
  } else {
    result.spellcrit_rating = spellcrit_rating - b.spellcrit_rating;
  }
  result.healing = healing - b.healing;
  result.mp5 = mp5 - b.mp5;
  result.haste_rating = haste_rating - b.haste_rating;
  result.spell_haste_rating = spell_haste_rating - b.spell_haste_rating;
  result.attackpower = attackpower - b.attackpower;
  result.resilience_rating = resilience_rating - b.resilience_rating;
  result.expertise_rating = expertise_rating - b.expertise_rating;
  return result;
}

void SecondaryStats::operator=(SecondaryStats b) {
  dodge_rating = b.dodge_rating;
  parry_rating = b.parry_rating;
  block_chance_rating = b.block_chance_rating;
  block_value = b.block_value;
  defense_rating = b.defense_rating;
  hit_rating = b.hit_rating;
  spellpower = b.spellpower;
  spellhit_rating = b.spellhit_rating;
  crit_rating = crit_rating + b.crit_rating;
  spellcrit_rating = b.spellcrit_rating;
  healing = b.healing;
  mp5 = b.mp5;
  haste_rating = b.haste_rating;
  spell_haste_rating = b.spell_haste_rating;
  attackpower = b.attackpower;
  resilience_rating = b.resilience_rating;
  expertise_rating = b.expertise_rating;
}
