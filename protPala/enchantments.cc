
#include "enchantments.hh"

void Enchantment::operator=(Enchantment in)
{
  for (uint i=(uint)PrimaryAttributes::FirstPrimary; i<=(uint)PrimaryAttributes::LastPrimary;i++){
    set_prim_stat((PrimaryAttributes)i,in.get_prim_stat((PrimaryAttributes)i));
  }
  for (uint index=(uint)SecondaryAttributes::FirstSecondary; index<=(uint)SecondaryAttributes::LastSecondary;index++){
    set_sec_stat((SecondaryAttributes)index,in.get_sec_stat((SecondaryAttributes)index));
  }
  set_name(in.get_name());
  set_slot(in.get_slot());
}

std::vector<std::string> Enchantment::get_names(){
  std::vector<std::string> result={"EnchantmentName TEXT", "EnchantmentSlot INT"};
  result.reserve(result.size()+Names::primaryAttributesNames.size()+Names::secondaryAttributesNames.size());
  for (uint i=0;i<Names::primaryAttributesNames.size();i++){
    std::string temp_name="Enchantment" + Names::primaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i=0;i<Names::secondaryAttributesNames.size();i++){
    std::string temp_name="Enchantment" + Names::secondaryAttributesNames[i];
    result.push_back(temp_name);
  }
  result.shrink_to_fit();
  return result;
}

std::string Enchantment::get_values(){
  std::stringstream result;
  result<<"'"<<get_name()<<"', "<<(uint)get_slot()<<", ";
  for (uint i=(uint)PrimaryAttributes::FirstPrimary; i<=(uint)PrimaryAttributes::LastPrimary;i++){
    result<<get_prim_stat((PrimaryAttributes)i)<<", ";
  }
  for (uint i=(uint)SecondaryAttributes::FirstSecondary; i<=(uint)SecondaryAttributes::LastSecondary;i++){
    result<<get_sec_stat((SecondaryAttributes)i)<<", ";
  }
  return result.str();
}

GlyphOfTheDefender::GlyphOfTheDefender()
{
  set_name("Glyph of the Defender");
  set_sec_stat(SecondaryAttributes::DodgeRating, 17);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_slot(Slot::Head);
}

ArcanumOfPower::ArcanumOfPower()
{
  set_name("Arcanum of Power");
  set_slot(Slot::Head);
  set_sec_stat(SecondaryAttributes::SpellPower, 22);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 14);
}

ArcanumOfFrostWarding::ArcanumOfFrostWarding()
{
  set_name("Arcanum of Frost Warding");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::FrostResistance, 20);
}

ArcanumOfTheGladiator::ArcanumOfTheGladiator()
{
  set_name("Arcanum of the Gladiator");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 20);
}

LesserArcanumOfTenacity::LesserArcanumOfTenacity()
{
  set_name("Lesser Arcanum of Tenacity");
  set_slot(Slot::Head);
  set_sec_stat(SecondaryAttributes::GreenArmor, 125);
}

SyncretistsSigil::SyncretistsSigil()
{
  set_name("Syncretist''s Sigil");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Stamina, 10);
  set_sec_stat(SecondaryAttributes::DodgeRating, 10);
  set_sec_stat(SecondaryAttributes::SpellPower, 12);
}

InscriptionOfWarding::InscriptionOfWarding()
{
  set_name("Inscription of Warding");
  set_slot(Slot::Shoulders);
  set_sec_stat(SecondaryAttributes::DodgeRating, 13);
}

GreaterInscriptionOfWarding::GreaterInscriptionOfWarding()
{
  set_name("Greater Inscription of Warding");
  set_slot(Slot::Shoulders);
  set_sec_stat(SecondaryAttributes::DefenseRating, 10);
  set_sec_stat(SecondaryAttributes::DodgeRating, 15);
}

GreaterInscriptionOfTheKnight::GreaterInscriptionOfTheKnight()
{
  set_name("Greater Inscription of the Knight");
  set_slot(Slot::Shoulders);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_sec_stat(SecondaryAttributes::DodgeRating, 10);
}

HeavyKnothideArmorKit::HeavyKnothideArmorKit()
{
  set_name("Heavy Knothide Armor Kit");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Stamina, 10);
}

FortitudeOfTheScourge::FortitudeOfTheScourge()
{
  set_name("Fortitude of the Scourge");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Stamina, 16);
  set_sec_stat(SecondaryAttributes::GreenArmor, 100);
}

InscriptionOfEndurance::InscriptionOfEndurance()
{
  set_name("Inscription of Endurance");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::FireResistance, 7);
  set_prim_stat(PrimaryAttributes::FrostResistance, 7);
  set_prim_stat(PrimaryAttributes::NatureResistance, 7);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 7);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 7);
}

WeaponMajorSpellpower::WeaponMajorSpellpower()
{
  set_name("Major Spellpower");
  set_slot(Slot::Mainhand);
  set_sec_stat(SecondaryAttributes::SpellPower, 40);
}

Steelweave::Steelweave()
{
  set_name("Steelweave");
  set_slot(Slot::Back);
  set_sec_stat(SecondaryAttributes::DefenseRating, 12);
}

MajorArmor::MajorArmor()
{
  set_name("Major Armor");
  set_slot(Slot::Back);
  set_sec_stat(SecondaryAttributes::GreenArmor, 120);
}

Dodge::Dodge()
{
  set_name("Dodge");
  set_slot(Slot::Back);
  set_sec_stat(SecondaryAttributes::DodgeRating, 12);
}

BackGreaterAgility::BackGreaterAgility()
{
  set_name("Greater Agility");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Agility, 12);
}

BackGreaterNatureResistance::BackGreaterNatureResistance()
{
  set_name("Greater Nature Resistance");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::NatureResistance, 15);
}

NethercleftLegArmor::NethercleftLegArmor()
{
  set_name("Nethercleft Leg Armor");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Agility, 12);
  set_prim_stat(PrimaryAttributes::Stamina, 40);
}

ExceptionalStats::ExceptionalStats()
{
  set_name("Exceptional Stats");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Strength, 6);
  set_prim_stat(PrimaryAttributes::Agility, 6);
  set_prim_stat(PrimaryAttributes::Stamina, 6);
  set_prim_stat(PrimaryAttributes::Intelligence, 6);
  set_prim_stat(PrimaryAttributes::Spirit, 6);
}

ExceptionalHealth::ExceptionalHealth()
{
  set_name("Exceptional Health");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Health, 150);
}

HandsSuperiorAgility::HandsSuperiorAgility()
{
  set_name("Superior Agility");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Agility, 15);
}

HandsMajorStrength::HandsMajorStrength()
{
  set_name("Major Strength");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Strength, 15);
}

ToughShield::ToughShield()
{
  set_name("Tough Shield");
  set_slot(Slot::Offhand);
  set_sec_stat(SecondaryAttributes::BlockValue, 18);
}

Brawn::Brawn()
{
  set_name("Brawn");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Strength, 12);
}

HeavyKnothideArmorKitHands::HeavyKnothideArmorKitHands()
{
  set_name("Heavy Knothide Armor Kit");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Stamina, 10);
}

BootsDexterity::BootsDexterity()
{
  set_name("Dexterity");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Agility, 12);
}

ChestDefense::ChestDefense()
{
  set_name("Defense");
  set_slot(Slot::Chest);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
}

ChestFrostArmorKit::ChestFrostArmorKit()
{
  set_name("Frost Armor Kit");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::FrostResistance, 8);
}

LegsFrostArmorKit::LegsFrostArmorKit()
{
  set_name("Frost Armor Kit");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::FrostResistance, 8);
}

HandsFrostArmorKit::HandsFrostArmorKit()
{
  set_name("Frost Armor Kit");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::FrostResistance, 8);
}

FeetFrostArmorKit::FeetFrostArmorKit()
{
  set_name("Frost Armor Kit");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::FrostResistance, 8);
}

ShieldResistance::ShieldResistance()
{
  set_name("Resistance");
  set_slot(Slot::Offhand);
  set_prim_stat(PrimaryAttributes::FrostResistance, 5);
  set_prim_stat(PrimaryAttributes::FireResistance, 5);
  set_prim_stat(PrimaryAttributes::NatureResistance, 5);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 5);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 5);
}

BackMajorResistance::BackMajorResistance()
{
  set_name("Major Resistance");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::FireResistance, 7);
  set_prim_stat(PrimaryAttributes::FrostResistance, 7);
  set_prim_stat(PrimaryAttributes::NatureResistance, 7);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 7);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 7);
}

TwoHandSavagery::TwoHandSavagery()
{
  set_name("Savagery");
  set_slot(Slot::Twohand);
  set_sec_stat(SecondaryAttributes::AttackPower, 70);
}

TwoHandMajorAgility::TwoHandMajorAgility()
{
  set_name("Major Agility");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Agility, 35);
}

ArcanumOfFerocity::ArcanumOfFerocity()
{
  set_name("Arcanum of Ferocity");
  set_slot(Slot::Head);
  set_sec_stat(SecondaryAttributes::AttackPower, 34);
  set_sec_stat(SecondaryAttributes::HitRating, 16);
}

HeavyKnothideArmorKitHead::HeavyKnothideArmorKitHead()
{
  set_name("Heavy Knothide Armor Kit");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Stamina, 10);
}

ArcanumOfProtection::ArcanumOfProtection()
{
  set_name("Arcanum of Protection");
  set_slot(Slot::Head);
  set_sec_stat(SecondaryAttributes::DodgeRating, 12);
}

LesserArcanumOfVoracityAgility::LesserArcanumOfVoracityAgility()
{
  set_name("Lesser Arcanum of Voracity");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Agility, 8);
}

RuggedArmorKitChest::RuggedArmorKitChest()
{
  set_name("Rugged Armor Kit");
  set_slot(Slot::Chest);
  set_sec_stat(SecondaryAttributes::GreenArmor, 40);
}

VindicatorsArmorKit::VindicatorsArmorKit()
{
  set_name("Vindicator''s Armor Kit");
  set_slot(Slot::Chest);
  set_sec_stat(SecondaryAttributes::DodgeRating, 8);
}

MajorResilience::MajorResilience()
{
  set_name("Major Resilience");
  set_slot(Slot::Chest);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 15);
}

HeavyKnothideArmorKitChest::HeavyKnothideArmorKitChest()
{
  set_name("Heavy Knothide Armor Kit");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Stamina, 10);
}

WristsFortitude::WristsFortitude()
{
  set_name("Fortitude");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Stamina, 12);
}

WristsMajorDefense::WristsMajorDefense()
{
  set_name("Major Defense");
  set_slot(Slot::Bracers);
  set_sec_stat(SecondaryAttributes::DefenseRating, 12);
}

WristsSpellpower::WristsSpellpower()
{
  set_name("Spellpower");
  set_slot(Slot::Bracers);
  set_sec_stat(SecondaryAttributes::SpellPower, 15);
}

WristsStats::WristsStats()
{
  set_name("Stats");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Strength, 4);
  set_prim_stat(PrimaryAttributes::Agility, 4);
  set_prim_stat(PrimaryAttributes::Stamina, 4);
  set_prim_stat(PrimaryAttributes::Intelligence, 4);
  set_prim_stat(PrimaryAttributes::Spirit, 4);
}

HandsMajorSpellpower::HandsMajorSpellpower()
{
  set_name("Major Spellpower");
  set_slot(Slot::Hands);
  set_sec_stat(SecondaryAttributes::SpellPower, 20);
}

GloveReinforcements::GloveReinforcements()
{
  set_name("Glove Reinforcements");
  set_slot(Slot::Hands);
  set_sec_stat(SecondaryAttributes::GreenArmor, 240);
}

VindicatorsArmorKitHands::VindicatorsArmorKitHands()
{
  set_name("Vindicator''s Armor Kit");
  set_slot(Slot::Hands);
  set_sec_stat(SecondaryAttributes::DodgeRating, 8);
}

GlovesThreat::GlovesThreat()
{
  set_name("Threat");
  set_slot(Slot::Hands);
}

RuggedArmorKitLegs::RuggedArmorKitLegs()
{
  set_name("Rugged Armor Kit");
  set_slot(Slot::Legs);
  set_sec_stat(SecondaryAttributes::GreenArmor, 40);
}

RunicSpellthread::RunicSpellthread()
{
  set_name("Runic Spellthread");
  set_slot(Slot::Legs);
  set_sec_stat(SecondaryAttributes::SpellPower, 35);
  set_prim_stat(PrimaryAttributes::Stamina, 20);
}

BootsFortitude::BootsFortitude()
{
  set_name("Fortitude");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Stamina, 12);
}

RuggedArmorKitFeet::RuggedArmorKitFeet()
{
  set_name("Rugged Armor Kit");
  set_slot(Slot::Boots);
  set_sec_stat(SecondaryAttributes::GreenArmor, 40);
}

GlyphOfShadowWarding::GlyphOfShadowWarding()
{
  set_name("Glyph of Shadow Warding");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 20);
}

GlyphOfFireWarding::GlyphOfFireWarding()
{
  set_name("Glyph of Fire Warding");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::FireResistance, 20);
}

CloakGreaterFireResistance::CloakGreaterFireResistance()
{
  set_name("Greater Fire Resistance");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::FireResistance, 15);
}

CloakGreaterShadowResistance::CloakGreaterShadowResistance()
{
  set_name("Greater Shadow Resistance");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 15);
}

ChestFlameArmorKit::ChestFlameArmorKit()
{
  set_name("Flame Armor Kit");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::FireResistance, 8);
}

ChestShadowArmorKit::ChestShadowArmorKit()
{
  set_name("Shadow Armor Kit");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 8);
}

GlovesFlameArmorKit::GlovesFlameArmorKit()
{
  set_name("Flame Armor Kit");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::FireResistance, 8);
}

GlovesShadowArmorKit::GlovesShadowArmorKit()
{
  set_name("Shadow Armor Kit");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 8);
}
FeetFlameArmorKit::FeetFlameArmorKit()
{
  set_name("Flame Armor Kit");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::FireResistance, 8);
}

FeetShadowArmorKit::FeetShadowArmorKit()
{
  set_name("Shadow Armor Kit");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 8);
}

ShieldBlock::ShieldBlock(){
  set_name("Shield Block");
  set_slot(Slot::Offhand);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 15);
}

MajorStamina::MajorStamina(){
  set_name("Major Stamina");
  set_slot(Slot::Offhand);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
}

RingSpellpower::RingSpellpower(){
  set_name("Spellpower");
  set_slot(Slot::Ring);
  set_sec_stat(SecondaryAttributes::SpellPower,12);
}

RingStats::RingStats(){
  set_name("Stats");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Intelligence, 4);
  set_prim_stat(PrimaryAttributes::Spirit, 4);
  set_prim_stat(PrimaryAttributes::Stamina, 4);
  set_prim_stat(PrimaryAttributes::Agility, 4);
  set_prim_stat(PrimaryAttributes::Strength, 4);
}

RingStriking::RingStriking(){
  set_name("Striking");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::WeaponDamage,2);
}