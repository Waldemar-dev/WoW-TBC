#ifndef _ENCHANTMENTS_HH_
#define _ENCHANTMENTS_HH_

#include "buffs.hh"
#include <string>

using namespace std;

class Enchantment : public Buff {
public:
  Enchantment() = default;
  ~Enchantment() = default;

  string slot;
  void operator=(Enchantment);
};

class GlyphOfTheDefender : public Enchantment {
public:
  GlyphOfTheDefender();
};

class ArcanumOfPower : public Enchantment {
public:
  ArcanumOfPower();
};

class ArcanumOfTheGladiator : public Enchantment {
public:
  ArcanumOfTheGladiator();
};

class LesserArcanumOfTenacity : public Enchantment {
public:
  LesserArcanumOfTenacity();
};

class SyncretistsSigil : public Enchantment {
public:
  SyncretistsSigil();
};

class InscriptionOfWarding : public Enchantment {
public:
  InscriptionOfWarding();
};

class GreaterInscriptionOfWarding : public Enchantment {
public:
  GreaterInscriptionOfWarding();
};

class GreaterInscriptionOfTheKnight : public Enchantment {
public:
  GreaterInscriptionOfTheKnight();
};

class HeavyKnothideArmorKit : public Enchantment {
public:
  HeavyKnothideArmorKit();
};

class FortitudeOfTheScourge : public Enchantment {
public:
  FortitudeOfTheScourge();
};

class WeaponMajorSpellpower : public Enchantment {
public:
  WeaponMajorSpellpower();
};

class Steelweave : public Enchantment {
public:
  Steelweave();
};

class MajorArmor : public Enchantment {
public:
  MajorArmor();
};

class BackGreaterAgility : public Enchantment {
public:
  BackGreaterAgility();
};

class NethercleftLegArmor : public Enchantment {
public:
  NethercleftLegArmor();
};

class ExceptionalStats : public Enchantment {
public:
  ExceptionalStats();
};

class HandsSuperiorAgility : public Enchantment {
public:
  HandsSuperiorAgility();
};

class HandsMajorStrength : public Enchantment {
public:
  HandsMajorStrength();
};

class ToughShield : public Enchantment {
public:
  ToughShield();
};

class ExceptionalHealth : public Enchantment {
public:
  ExceptionalHealth();
};

class Brawn : public Enchantment {
public:
  Brawn();
};

class HeavyKnothideArmorKitHands : public Enchantment {
public:
  HeavyKnothideArmorKitHands();
};

class BootsDexterity : public Enchantment {
public:
  BootsDexterity();
};

class Dodge : public Enchantment {
public:
  Dodge();
};

class ChestDefense : public Enchantment {
public:
  ChestDefense();
};

class ArcanumOfFrostWarding : public Enchantment {
public:
  ArcanumOfFrostWarding();
};

class InscriptionOfEndurance : public Enchantment {
public:
  InscriptionOfEndurance();
};

class BackGreaterNatureResistance : public Enchantment {
public:
  BackGreaterNatureResistance();
};

class BackMajorResistance : public Enchantment {
public:
  BackMajorResistance();
};

class ChestFrostArmorKit : public Enchantment {
public:
  ChestFrostArmorKit();
};

class LegsFrostArmorKit : public Enchantment {
public:
  LegsFrostArmorKit();
};

class HandsFrostArmorKit : public Enchantment {
public:
  HandsFrostArmorKit();
};

class FeetFrostArmorKit : public Enchantment {
public:
  FeetFrostArmorKit();
};

class ShieldResistance : public Enchantment {
public:
  ShieldResistance();
};

#endif
