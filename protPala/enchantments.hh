#ifndef _ENCHANTMENTS_HH_
#define _ENCHANTMENTS_HH_

#include "buffs.hh"
// #include "enums.hh"
#include <string>
#include <sstream>
#include <iostream>
class Enchantment : public Buff {
public:
  Enchantment() = default;
  ~Enchantment() = default;

  void set_slot(Slot in){slot=in;}
  Slot get_slot() const {return slot;}
  void set_prim_stat(PrimaryAttributes inIndex, double inValue){primary_stats.set_stat(inIndex,inValue);}
  void set_sec_stat(SecondaryAttributes inIndex, double inValue){secondary_stats.set_stat(inIndex,inValue);}
  double get_prim_stat(PrimaryAttributes inIndex) const {return primary_stats.get_stat(inIndex);}
  double get_sec_stat(SecondaryAttributes inIndex) const {return secondary_stats.get_stat(inIndex);}
  PrimaryStats get_prim_stats() const {return primary_stats;}
  SecondaryStats get_sec_stats() const {return secondary_stats;}
  std::vector<std::string> get_names();
  std::string get_values();
  void operator=(Enchantment);
  friend std::ostream& operator<<(std::ostream& out, const Enchantment& ench){
    out<<ench.get_name()<<"\t"<<ench.get_slot()<<"\t"<<ench.get_prim_stats()<<"\t"<<ench.get_sec_stats();
    return out;
  };
  // friend std::istream& operator>>(std::istream& in, Enchantment& ench){
  //   std::string in_name, in_slot;
  //   in>>in_name>>in_slot>>primary_stats>>secondary_stats;
  //   ench.set_name(in_name);
  //   ench.set_slot(in_slot);
  //   ench.primary_stats=primary_stats;
  //   ench.secondary_stats=secondary_stats;
  //   cout<<"read enchantment"<<endl;
  //   return in;
  // }
  private:
    Slot slot=Slot::NoSlot;
    PrimaryStats primary_stats;
    SecondaryStats secondary_stats;
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

class TwoHandSavagery : public Enchantment {
  public:
  TwoHandSavagery();
};

class TwoHandMajorAgility : public Enchantment {
  public:
  TwoHandMajorAgility();
};

class ArcanumOfFerocity:public Enchantment{
  public:
  ArcanumOfFerocity();
};

class HeavyKnothideArmorKitHead:public Enchantment{
  public:
  HeavyKnothideArmorKitHead();
};

class ArcanumOfProtection:public Enchantment{
  public:
  ArcanumOfProtection();
};

class LesserArcanumOfVoracityAgility:public Enchantment{
  public:
  LesserArcanumOfVoracityAgility();
};

class RuggedArmorKitChest:public Enchantment{
  public:
  RuggedArmorKitChest();
};

class VindicatorsArmorKit:public Enchantment{
  public:
  VindicatorsArmorKit();
};

class MajorResilience:public Enchantment{
  public:
  MajorResilience();
};

class HeavyKnothideArmorKitChest:public Enchantment{
  public:
  HeavyKnothideArmorKitChest();
};

class WristsFortitude:public Enchantment{
  public:
  WristsFortitude();
};

class WristsMajorDefense:public Enchantment{
  public:
  WristsMajorDefense();
};

class WristsSpellpower:public Enchantment{
  public:
  WristsSpellpower();
};

class WristsStats:public Enchantment{
  public:
  WristsStats();
};

class HandsMajorSpellpower:public Enchantment{
  public:
  HandsMajorSpellpower();
};

class GloveReinforcements:public Enchantment{
  public:
  GloveReinforcements();
};

class VindicatorsArmorKitHands:public Enchantment{
  public:
  VindicatorsArmorKitHands();
};

class GlovesThreat:public Enchantment{
  public:
  GlovesThreat();
};

class RuggedArmorKitLegs:public Enchantment{
  public:
  RuggedArmorKitLegs();
};

class RunicSpellthread:public Enchantment{
  public:
  RunicSpellthread();
};

class BootsFortitude:public Enchantment{
  public:
  BootsFortitude();
};

class RuggedArmorKitFeet:public Enchantment{
  public:
  RuggedArmorKitFeet();
};

class GlyphOfShadowWarding:public Enchantment{
  public:
  GlyphOfShadowWarding();
};

class GlyphOfFireWarding:public Enchantment{
  public:
  GlyphOfFireWarding();
};

class CloakGreaterFireResistance:public Enchantment{
  public:
  CloakGreaterFireResistance();
};

class CloakGreaterShadowResistance:public Enchantment{
  public:
  CloakGreaterShadowResistance();
};

class ChestFlameArmorKit:public Enchantment{
  public:
  ChestFlameArmorKit();
};

class ChestShadowArmorKit:public Enchantment{
  public:
  ChestShadowArmorKit();
};

class GlovesFlameArmorKit:public Enchantment{
  public:
  GlovesFlameArmorKit();
};

class GlovesShadowArmorKit:public Enchantment{
  public:
  GlovesShadowArmorKit();
};

class FeetFlameArmorKit:public Enchantment{
  public:
  FeetFlameArmorKit();
};

class FeetShadowArmorKit:public Enchantment{
  public:
  FeetShadowArmorKit();
};

class ShieldBlock:public Enchantment{
  public:
  ShieldBlock();
};

class MajorStamina:public Enchantment {
  public:
  MajorStamina();
};

class RingSpellpower:public Enchantment{
  public:
  RingSpellpower();
};

class RingStats:public Enchantment{
  public:
  RingStats();
};

class RingStriking:public Enchantment{
  public:
  RingStriking();
};
#endif
