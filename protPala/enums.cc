#include "enums.hh"

namespace Names {
  std::vector<std::string> primaryAttributesNames={"Armor DOUBLE", "Strength DOUBLE", "Agility DOUBLE", "Stamina DOUBLE", "Intelligence DOUBLE", "Spirit DOUBLE", "ArcaneResistance DOUBLE", "FireResistance DOUBLE", "FrostResistance DOUBLE", "ShadowResistance DOUBLE", "NatureResistance DOUBLE", "WeaponDamage DOUBLE", "AttackSpeed DOUBLE", "Health DOUBLE", "Mana DOUBLE"};
  std::vector<std::string> secondaryAttributesNames={"GreenArmor DOUBLE", "DodgeRating DOUBLE", "ParryRating DOUBLE", "BlockChanceRating DOUBLE", "BlockValue DOUBLE", "DefenseRating DOUBLE", "HitRating DOUBLE", "SpellhitRating DOUBLE", "SpellPower DOUBLE", "CritRating DOUBLE", "SpellCritRating DOUBLE", "Healing DOUBLE", "MP5 DOUBLE", "HasteRating DOUBLE", "SpellHasteRating DOUBLE", "AttackPower DOUBLE", "ResilienceRating DOUBLE", "ExpertiseRating DOUBLE", "ArmorPenetration DOUBLE", "ArcaneSpellPower DOUBLE", "FireSpellPower DOUBLE", "FrostSpellPower DOUBLE", "ShadowSpellPower DOUBLE", "NatureSpellPower DOUBLE", "HolySpellPower DOUBLE"};
  std::vector<std::string> sourceNames={"No Source", "Random Drop", "Solo Quest", "Crafting", "Group Quest", "Normal Dungeon", "Heroic Dungeon", "Reputation", "BOJ", "PvP", "Raid"};
}

PrimaryAttributes operator++(PrimaryAttributes& x) {
    return x = (PrimaryAttributes)(std::underlying_type<PrimaryAttributes>::type(x) + 1); 
}

PrimaryAttributes operator*(PrimaryAttributes c) {
    return c;
}

SecondaryAttributes operator++(SecondaryAttributes& x) {
    return x = (SecondaryAttributes)(std::underlying_type<SecondaryAttributes>::type(x) + 1); 
}

SecondaryAttributes operator*(SecondaryAttributes c) {
    return c;
}

PrimaryAttributes begin(PrimaryAttributes r) {
    return PrimaryAttributes::FirstPrimary;
}

PrimaryAttributes end(PrimaryAttributes r) {
    PrimaryAttributes l=PrimaryAttributes::LastPrimary;
    return ++l;
}

SecondaryAttributes begin(SecondaryAttributes r) {
    return SecondaryAttributes::FirstSecondary;
}

SecondaryAttributes end(SecondaryAttributes r) {
    SecondaryAttributes l=SecondaryAttributes::LastSecondary;
    return ++l;
}

MagicSchool operator++(MagicSchool& x) {
    return x = (MagicSchool)(std::underlying_type<MagicSchool>::type(x) + 1); 
}

namespace std
{
    template<>
    struct less<MagicSchool>
    {
        bool operator()(MagicSchool const& lhs, MagicSchool const& rhs) const
        {
            return ((uint)lhs<(uint)rhs);
        }
    };

    template<>
    struct less<Slot>
    {
        bool operator()(Slot const& lhs, Slot const& rhs) const
        {
            return ((uint)lhs<(uint)rhs);
        }
    };
}