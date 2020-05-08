#include "buffs.hh"

void Buff::operator=(Buff in) {
  primary_stats = in.primary_stats;
  secondary_stats = in.secondary_stats;
  name = in.name;
}

bool Buff::operator==(Buff in) {
  if (name == in.name) {
    return true;
  }
  return false;
}

BlackenedBasilisk::BlackenedBasilisk() {
  secondary_stats.spellpower = 23;
  primary_stats.spirit = 20;
  name = "Blackened Basilisk/Crunchy Serpent";
}

BlackenedSporefish::BlackenedSporefish() {
  primary_stats.stamina = 20;
  secondary_stats.mp5 = 8;
  name = "Blackened Sporefish";
}

BroiledBloodfin::BroiledBloodfin() {
  primary_stats.arcane_resistance = 8;
  primary_stats.fire_resistance = 8;
  primary_stats.frost_resistance = 8;
  primary_stats.nature_resistance = 8;
  primary_stats.shadow_resistance = 8;
  name = "Boiled Bloodfin";
}

BuzzardBites::BuzzardBites() {
  primary_stats.stamina = 20;
  primary_stats.spirit = 20;
  name = "Buzzard Bites/Clam Bar";
}

DirgesKickinChimaerokChops::DirgesKickinChimaerokChops() {
  primary_stats.stamina = 25;
  name = "Dirge's Kickin' Chimaerok Chops";
}

GrilledMudfish::GrilledMudfish() {
  primary_stats.agility = 20;
  primary_stats.spirit = 20;
  name = "Grilled Mudfish/Warp Burger";
}

RoastedClefthoof::RoastedClefthoof() {
  primary_stats.strength = 20;
  primary_stats.spirit = 20;
  name = "Roasted Clefthoof";
}

Stormchops::Stormchops() { name = "Stormchops"; }

FishermensFeast::FishermensFeast() {
  primary_stats.stamina = 30;
  primary_stats.spirit = 20;
  name = "Fishermen's Feast/Spicy Crawdad";
}

SkullfishSoup::SkullfishSoup() {
  secondary_stats.spellcrit_rating = 20;
  name = "Skullfish Soup";
}

SpicyHotTalbulk::SpicyHotTalbulk() {
  secondary_stats.hit_rating = 20;
  primary_stats.spirit = 20;
  name = "Spicy Hot Talbulk";
}

BlessingOfSanctuary::BlessingOfSanctuary() { name = "Blessing of Sanctuary"; }

BlessingOfKings::BlessingOfKings() { name = "Blessing Of Kings"; }

BlessingOfWisdom::BlessingOfWisdom() {
  secondary_stats.mp5 = 41;
  name = "Blessing of Wisdom";
}

MarkOfTheWild::MarkOfTheWild() {
  primary_stats.armor = 340;
  primary_stats.strength = 14;
  primary_stats.agility = 14;
  primary_stats.stamina = 14;
  primary_stats.intelligence = 14;
  primary_stats.spirit = 14;
  primary_stats.arcane_resistance = 25;
  primary_stats.fire_resistance = 25;
  primary_stats.frost_resistance = 25;
  primary_stats.nature_resistance = 25;
  primary_stats.shadow_resistance = 25;
  name = "Mark of the Wild";
}

ArcaneIntellect::ArcaneIntellect() {
  primary_stats.intelligence = 40;
  name = "Arcane Intellect";
}

PowerWordFortitude::PowerWordFortitude() {
  primary_stats.stamina = 79;
  name = "Power Word: Fortitude";
}

FlaskOfFortification::FlaskOfFortification() {
  primary_stats.health = 500;
  secondary_stats.defense_rating = 10;
  battle_elixir = true;
  guardian_elixir = true;
  name = "Flask of Fortification";
}

FlaskOfBlindingLight::FlaskOfBlindingLight() {
  secondary_stats.spellpower = 80;
  battle_elixir = true;
  guardian_elixir = true;
  name = "Flask of Blinding Light";
}

ElixirOfMajorDefense::ElixirOfMajorDefense() {
  primary_stats.armor = 550;
  guardian_elixir = true;
  name = "Elixir of Major Defense";
}

ElixirOfMajorAgility::ElixirOfMajorAgility() {
  primary_stats.agility = 35;
  secondary_stats.crit_rating = 20;
  battle_elixir = true;
  name = "Elixir of Major Agility";
}

ElixirOfMastery::ElixirOfMastery() {
  primary_stats.strength = 15;
  primary_stats.agility = 15;
  primary_stats.stamina = 15;
  primary_stats.intelligence = 15;
  primary_stats.spirit = 15;
  battle_elixir = true;
  name = "Elixir of Mastery";
}

ElixirOfMajorStrength::ElixirOfMajorStrength() {
  primary_stats.strength = 24;
  battle_elixir = true;
  name = "Elixir of Major Strength";
}

ElixirOfMajorFortitude::ElixirOfMajorFortitude() {
  primary_stats.health = 250;
  guardian_elixir = true;
  name = "Elixir of Major Fortitude";
}

EarthernElixir::EarthernElixir() {
  guardian_elixir = true;
  name = "Earthern Elixir";
}

ElixirOfIronskin::ElixirOfIronskin() {
  secondary_stats.resilience_rating = 20;
  guardian_elixir = true;
  name = "Elixir of Ironskin";
}
