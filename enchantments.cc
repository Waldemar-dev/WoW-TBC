
#include "enchantments.hh"

void Enchantment::operator=(Enchantment in) {
  primary_stats = in.primary_stats;
  secondary_stats = in.secondary_stats;
  name = in.name;
  slot = in.slot;
}

GlyphOfTheDefender::GlyphOfTheDefender() {
  name = "Glyph of the Defender";
  secondary_stats.dodge_rating = 17;
  secondary_stats.defense_rating = 16;
  slot = "Head";
}

ArcanumOfPower::ArcanumOfPower() {
  name = "Arcanum of Power";
  slot = "Head";
  secondary_stats.spellpower = 22;
  secondary_stats.spellhit_rating = 14;
}

ArcanumOfFrostWarding::ArcanumOfFrostWarding() {
  name = "Arcanum of Frost Warding";
  slot = "Head";
  primary_stats.frost_resistance = 20;
}

ArcanumOfTheGladiator::ArcanumOfTheGladiator() {
  name = "Arcanum of the Gladiator";
  slot = "Head";
  primary_stats.stamina = 18;
  secondary_stats.resilience_rating = 20;
}

LesserArcanumOfTenacity::LesserArcanumOfTenacity() {
  name = "Lesser Arcanum of Tenacity";
  slot = "Head";
  primary_stats.armor = 125;
}

SyncretistsSigil::SyncretistsSigil() {
  name = "Syncretist's Sigil";
  slot = "Head";
  primary_stats.stamina += 10;
  secondary_stats.dodge_rating += 10;
  secondary_stats.spellpower += 12;
}

InscriptionOfWarding::InscriptionOfWarding() {
  name = "Inscription of Warding";
  slot = "Shoulder";
  secondary_stats.dodge_rating += 13;
}

GreaterInscriptionOfWarding::GreaterInscriptionOfWarding() {
  name = "Greater Inscription of Warding";
  slot = "Shoulder";
  secondary_stats.defense_rating += 10;
  secondary_stats.dodge_rating += 15;
}

GreaterInscriptionOfTheKnight::GreaterInscriptionOfTheKnight() {
  name = "Greater Inscription of the Knight";
  slot = "Shoulder";
  secondary_stats.defense_rating += 15;
  secondary_stats.dodge_rating += 10;
}

HeavyKnothideArmorKit::HeavyKnothideArmorKit() {
  name = "Heavy Knothide Armor Kit";
  slot = "Shoulder";
  primary_stats.stamina = 10;
}

FortitudeOfTheScourge::FortitudeOfTheScourge() {
  name = "Fortitude of the Scourge";
  slot = "Shoulder";
  primary_stats.stamina = 16;
  primary_stats.armor = 100;
}

InscriptionOfEndurance::InscriptionOfEndurance() {
  name = "Inscription of Endurance";
  slot = "Shoulder";
  primary_stats.fire_resistance = 7;
  primary_stats.frost_resistance = 7;
  primary_stats.nature_resistance = 7;
  primary_stats.shadow_resistance = 7;
  primary_stats.arcane_resistance = 7;
}

WeaponMajorSpellpower::WeaponMajorSpellpower() {
  name = "40 SP";
  slot = "Mainhand";
  secondary_stats.spellpower = 40;
}

Steelweave::Steelweave() {
  name = "Steelweave";
  slot = "Back";
  secondary_stats.defense_rating = 12;
}

MajorArmor::MajorArmor() {
  name = "Major Armor";
  slot = "Back";
  primary_stats.armor = 120;
}

Dodge::Dodge() {
  name = "Dodge";
  slot = "Back";
  secondary_stats.dodge_rating = 12;
}

BackGreaterAgility::BackGreaterAgility() {
  name = "Greater Agility";
  slot = "Back";
  primary_stats.agility = 12;
}

BackGreaterNatureResistance::BackGreaterNatureResistance() {
  name = "Greater Nature Resistance";
  slot = "Back";
  primary_stats.nature_resistance = 15;
}

NethercleftLegArmor::NethercleftLegArmor() {
  name = "Nethercleft Leg Armor";
  slot = "Legs";
  primary_stats.agility += 12;
  primary_stats.stamina += 40;
}

ExceptionalStats::ExceptionalStats() {
  name = "Exceptional Stats";
  slot = "Chest";
  primary_stats.strength = 6;
  primary_stats.agility = 6;
  primary_stats.stamina = 6;
  primary_stats.intelligence = 6;
  primary_stats.spirit = 6;
}

ExceptionalHealth::ExceptionalHealth() {
  name = "Exceptional Health";
  slot = "Chest";
  primary_stats.health = 150;
}

HandsSuperiorAgility::HandsSuperiorAgility() {
  name = "Superior Agility";
  slot = "Hands";
  primary_stats.agility = 15;
}

HandsMajorStrength::HandsMajorStrength() {
  name = "Major Strength";
  slot = "Hands";
  primary_stats.strength = 15;
}

ToughShield::ToughShield() {
  name = "Tough Shield";
  slot = "Offhand";
  secondary_stats.block_value = 18;
}

Brawn::Brawn() {
  name = "Brawn";
  slot = "Wrist";
  primary_stats.strength = 12;
}

HeavyKnothideArmorKitHands::HeavyKnothideArmorKitHands() {
  name = "Heavy Knothide Armor Kit";
  slot = "Hands";
  primary_stats.stamina = 10;
}

BootsDexterity::BootsDexterity() {
  name = "Dexterity";
  slot = "Feet";
  primary_stats.agility = 12;
}

ChestDefense::ChestDefense() {
  name = "Defense";
  slot = "Chest";
  secondary_stats.defense_rating = 15;
}

ChestFrostArmorKit::ChestFrostArmorKit() {
  name = "Frost Armor Kit";
  slot = "Chest";
  primary_stats.frost_resistance = 8;
}

LegsFrostArmorKit::LegsFrostArmorKit() {
  name = "Frost Armor Kit";
  slot = "Legs";
  primary_stats.frost_resistance = 8;
}

HandsFrostArmorKit::HandsFrostArmorKit() {
  name = "Frost Armor Kit";
  slot = "Hands";
  primary_stats.frost_resistance = 8;
}

FeetFrostArmorKit::FeetFrostArmorKit() {
  name = "Frost Armor Kit";
  slot = "Feet";
  primary_stats.frost_resistance = 8;
}

ShieldResistance::ShieldResistance() {
  name = "Resistance";
  slot = "Offhand";
  primary_stats.frost_resistance = 5;
  primary_stats.fire_resistance = 5;
  primary_stats.nature_resistance = 5;
  primary_stats.shadow_resistance = 5;
  primary_stats.arcane_resistance = 5;
}

BackMajorResistance::BackMajorResistance() {
  name = "Major Resistance";
  slot = "Back";
  primary_stats.fire_resistance = 7;
  primary_stats.frost_resistance = 7;
  primary_stats.nature_resistance = 7;
  primary_stats.shadow_resistance = 7;
  primary_stats.arcane_resistance = 7;
}
