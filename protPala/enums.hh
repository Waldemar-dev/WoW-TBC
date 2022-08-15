#ifndef _ENUMS_HH_
#define _ENUMS_HH_

#include <type_traits>
#include <vector>
#include <string>
#include <iostream>

enum MagicSchool
{
  Fire,
  Frost,
  Nature,
  Shadow,
  Arcane,
  Holy,
  Physical,
  FirstSchool=Fire,
  LastSchool=Physical
};

enum Race
{
  Human,
  Dwarf,
  Gnome,
  Nightelf,
  Draenei,
  Orc,
  Troll,
  Tauren,
  Undead,
  Bloodelf
};

enum CharacterClass
{
  Warrior,
  Paladin,
  DeathKnight,
  Shaman,
  Hunter,
  Rogue,
  Druid,
  Mage,
  Warlock,
  Priest
};

enum Slot
{
  NoSlot,
  Head,
  Shoulders,
  Back,
  Neck,
  Chest,
  Bracers,
  Hands,
  Belt,
  Legs,
  Boots,
  Ring,
  Ring1,
  Ring2,
  Trinket,
  Trinket1,
  Trinket2,
  RangeSlot,
  Relic,
  Libram,
  Idol,
  Mainhand,
  Offhand,
  Twohand
};

enum PrimaryAttributes
{
  Armor=0,
  Strength,
  Agility,
  Stamina,
  Intelligence,
  Spirit,
  ArcaneResistance,
  FireResistance,
  FrostResistance,
  ShadowResistance,
  NatureResistance,
  WeaponDamage,
  AttackSpeed,
  Health,
  Mana,
  PrimAttCount,
  FirstPrimary = Armor,
  SecondLastPrimary = Health,
  LastPrimary = Mana
};

namespace Names{
  extern std::vector<std::string> primaryAttributesNames;
  extern std::vector<std::string> secondaryAttributesNames;
  extern std::vector<std::string> sourceNames;
};

enum SecondaryAttributes
{
  GreenArmor=0,
  DodgeRating,
  ParryRating,
  BlockChanceRating,
  BlockValue,
  DefenseRating,
  HitRating,
  SpellhitRating,
  SpellPower,
  CritRating,
  SpellCritRating,
  Healing,
  MP5,
  HasteRating,
  SpellHasteRating,
  AttackPower,
  ResilienceRating,
  ExpertiseRating,
  ArmorPenetration,
  ArcaneSpellPower,
  FireSpellPower,
  FrostSpellPower,
  ShadowSpellPower,
  NatureSpellPower,
  HolySpellPower,
  SecAttCount,
  FirstSecondary = GreenArmor,
  SecondLastSecondary = NatureSpellPower,
  LastSecondary = HolySpellPower
};

enum Source
{
  noSource,
  randomdrop,
  soloquest,
  crafting,
  groupquest,
  normaldungeon,
  heroicdungeon,
  reputation,
  boj,
  pvp,
  raid
};
enum Dungeon
{
  noDungeon,
  stratholme,
  blackrock,
  ramparts,
  blood_furnace,
  shattered_halls,
  underbog,
  slave_pens,
  steamvault,
  manatomb,
  auchenaicrypt,
  sethekk_halls,
  shadow_lab,
  ohf,
  black_morast,
  botanika,
  mechanar,
  arcatraz,
  magisters_terrace
};

enum Faction
{
  noFaction,
  thrallmar,
  cenarion_expedition,
  lower_city,
  consortium,
  keepers_of_time,
  shatar,
  shatari_skyguard,
  ogrila,
  aldor,
  scryers,
  shattered_sun,
  violet_eye,
  scale_of_the_sands,
  ashtounge_deathsworn,
  the_maghar
};

enum Color
{
  Red,
  Blue,
  Yellow,
  Purple,
  Green,
  Orange,
  Meta,
  Dummy
};

enum Raid
{
  noRaid,
  karazhan,
  gruuls_lair,
  magtheridon,
  ssc,
  the_eye,
  mount_hyjal,
  black_temple,
  zul_aman,
  sunwell,
  blackwingLair,
  emeriss,
  molten_core
};

enum ArmorClass
{
  NoClass,
  Cloth,
  Leather,
  Mail,
  Plate,
  OneHandSword,
  TwoHandSword,
  OneHandMace,
  TwoHandMace,
  Staff,
  OneHandAxe,
  TwoHandAxe,
  Shield
};

#endif