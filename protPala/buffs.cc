#include "buffs.hh"


Buff::Buff(bool inBuffFood) : name_("NoName"), buffFood_(inBuffFood){}

Buff::Buff(const Buff& in) : primaryStats_(in.get_prim_stats()), secondaryStats_(in.get_sec_stats()), name_(in.get_name()), buffFood_(in.is_buffFood()){

}

void Buff::operator=(Buff in)
{
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    set_prim_stat((PrimaryAttributes)i, in.get_prim_stat((PrimaryAttributes)i));
  }
  for (uint index = (uint)SecondaryAttributes::FirstSecondary; index <= (uint)SecondaryAttributes::LastSecondary; index++)
  {
    set_sec_stat((SecondaryAttributes)index, in.get_sec_stat((SecondaryAttributes)index));
  }
  set_name(in.get_name());
  buffFood_ = in.is_buffFood();
}

bool Buff::operator==(Buff in)
{
  if (get_name() == in.get_name())
  {
    return true;
  }
  return false;
}

BuffFood::BuffFood() : Buff(true){}

// void BuffFood::operator=(BuffFood in)
// {
//   for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
//   {
//     set_prim_stat((PrimaryAttributes)i, in.get_prim_stat((PrimaryAttributes)i));
//   }
//   for (uint index = (uint)SecondaryAttributes::FirstSecondary; index <= (uint)SecondaryAttributes::LastSecondary; index++)
//   {
//     set_sec_stat((SecondaryAttributes)index, in.get_sec_stat((SecondaryAttributes)index));
//   }
//   set_name(in.get_name());
// }

BlackenedBasilisk::BlackenedBasilisk()
{
  set_sec_stat(SecondaryAttributes::SpellPower, 23);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Blackened Basilisk/Crunchy Serpent");
  set_buffFood();
}

BlackenedSporefish::BlackenedSporefish()
{
  set_prim_stat(PrimaryAttributes::Stamina, 20);
  set_sec_stat(SecondaryAttributes::MP5, 8);
  set_name("Blackened Sporefish");
  set_buffFood();
}

BroiledBloodfin::BroiledBloodfin()
{
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 8);
  set_prim_stat(PrimaryAttributes::FireResistance, 8);
  set_prim_stat(PrimaryAttributes::FrostResistance, 8);
  set_prim_stat(PrimaryAttributes::NatureResistance, 8);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 8);
  set_name("Boiled Bloodfin");
  set_buffFood();
}

BuzzardBites::BuzzardBites()
{
  set_prim_stat(PrimaryAttributes::Stamina, 20);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Buzzard Bites/Clam Bar");
  set_buffFood();
}

DirgesKickinChimaerokChops::DirgesKickinChimaerokChops()
{
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_name("Dirge's Kickin' Chimaerok Chops");
  set_buffFood();
}

GrilledMudfish::GrilledMudfish()
{
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Grilled Mudfish/Warp Burger");
  set_buffFood();
}

RoastedClefthoof::RoastedClefthoof()
{
  set_prim_stat(PrimaryAttributes::Strength, 20);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Roasted Clefthoof");
  set_buffFood();
}

Stormchops::Stormchops()
{
  set_name("Stormchops");
  set_buffFood();
}

FishermensFeast::FishermensFeast()
{
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Fishermen's Feast/Spicy Crawdad");
  set_buffFood();
}

SkullfishSoup::SkullfishSoup()
{
  set_sec_stat(SecondaryAttributes::SpellCritRating, 20);
  set_name("Skullfish Soup");
  set_buffFood();
}

SpicyHotTalbulk::SpicyHotTalbulk()
{
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_prim_stat(PrimaryAttributes::Spirit, 20);
  set_name("Spicy Hot Talbulk");
  set_buffFood();
}

BlessingOfSanctuary::BlessingOfSanctuary() { set_name("Blessing of Sanctuary"); }

BlessingOfKings::BlessingOfKings() { set_name("Blessing Of Kings"); }

BlessingOfWisdom::BlessingOfWisdom()
{
  set_sec_stat(SecondaryAttributes::MP5, 41);
  set_name("Blessing of Wisdom");
}

MarkOfTheWild::MarkOfTheWild()
{
  set_prim_stat(PrimaryAttributes::Armor, 340);
  set_prim_stat(PrimaryAttributes::Strength, 14);
  set_prim_stat(PrimaryAttributes::Agility, 14);
  set_prim_stat(PrimaryAttributes::Stamina, 14);
  set_prim_stat(PrimaryAttributes::Intelligence, 14);
  set_prim_stat(PrimaryAttributes::Spirit, 14);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 25);
  set_prim_stat(PrimaryAttributes::FireResistance, 25);
  set_prim_stat(PrimaryAttributes::FrostResistance, 25);
  set_prim_stat(PrimaryAttributes::NatureResistance, 25);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 25);
  set_name("Mark of the Wild");
}

ArcaneIntellect::ArcaneIntellect()
{
  set_prim_stat(PrimaryAttributes::Intelligence, 40);
  set_name("Arcane Intellect");
}

PowerWordFortitude::PowerWordFortitude()
{
  set_prim_stat(PrimaryAttributes::Stamina, 79);
  set_name("Power Word: Fortitude");
}

FlaskOfFortification::FlaskOfFortification()
{
  set_prim_stat(PrimaryAttributes::Health, 500);
  set_sec_stat(SecondaryAttributes::DefenseRating, 10);
  set_battle_elixir();
  set_guardian_elixir();
  set_name("Flask of Fortification");
}

FlaskOfBlindingLight::FlaskOfBlindingLight()
{
  set_sec_stat(SecondaryAttributes::NatureSpellPower, 80);
  set_sec_stat(SecondaryAttributes::HolySpellPower, 80);
  set_sec_stat(SecondaryAttributes::ArcaneSpellPower, 80);
  set_battle_elixir();
  set_guardian_elixir();
  set_name("Flask of Blinding Light");
}

FlaskOfRelentlessAssault::FlaskOfRelentlessAssault()
{
  set_sec_stat(SecondaryAttributes::AttackPower, 120);
  set_battle_elixir();
  set_guardian_elixir();
  set_name("Flask of Relentless Assault");
}

FlaskOfChromaticWonder::FlaskOfChromaticWonder()
{
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_prim_stat(PrimaryAttributes::Strength, 18);
  set_prim_stat(PrimaryAttributes::Agility, 18);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::Spirit, 18);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 35);
  set_prim_stat(PrimaryAttributes::FireResistance, 35);
  set_prim_stat(PrimaryAttributes::FrostResistance, 35);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 35);
  set_prim_stat(PrimaryAttributes::NatureResistance, 35);
  set_battle_elixir();
  set_guardian_elixir();
  set_name("Flask of Chromatic Wonder");
}

ElixirOfMajorDefense::ElixirOfMajorDefense()
{
  set_prim_stat(PrimaryAttributes::Armor, 550);
  set_guardian_elixir();
  set_name("Elixir of Major Defense");
}

ElixirOfMajorAgility::ElixirOfMajorAgility()
{
  set_prim_stat(PrimaryAttributes::Agility, 35);
  set_sec_stat(SecondaryAttributes::CritRating, 20);
  set_battle_elixir();
  set_name("Elixir of Major Agility");
}

ElixirOfMastery::ElixirOfMastery()
{
  set_prim_stat(PrimaryAttributes::Strength, 15);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::Intelligence, 15);
  set_prim_stat(PrimaryAttributes::Spirit, 15);
  set_battle_elixir();
  set_name("Elixir of Mastery");
}

ElixirOfMajorStrength::ElixirOfMajorStrength()
{
  set_prim_stat(PrimaryAttributes::Strength, 24);
  set_battle_elixir();
  set_name("Elixir of Major Strength");
}

ElixirOfMajorFortitude::ElixirOfMajorFortitude()
{
  set_prim_stat(PrimaryAttributes::Health, 250);
  set_guardian_elixir();
  set_name("Elixir of Major Fortitude");
}

EarthernElixir::EarthernElixir()
{
  set_guardian_elixir();
  set_name("Earthern Elixir");
}

ElixirOfIronskin::ElixirOfIronskin()
{
  set_sec_stat(SecondaryAttributes::ResilienceRating, 20);
  set_guardian_elixir();
  set_name("Elixir of Ironskin");
}

FelStrengthElixir::FelStrengthElixir()
{
  set_sec_stat(SecondaryAttributes::AttackPower, 90);
  set_prim_stat(PrimaryAttributes::Stamina, -10);
  set_battle_elixir();
  set_name("Fel Strength Elixir");
}