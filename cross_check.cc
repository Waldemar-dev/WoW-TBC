#include "Character.hh"
#include "buffs.hh"
#include "enchantments.hh"
#include "equipment.hh"
#include "gems.hh"
#include "support_functions.hh"

using namespace std;

int main() {
  Character prot_quidea1("Paladin", "Draenei");
  BlessingOfSanctuary bos;
  prot_quidea1.add_buff(bos);
  // prot_quidea1.get_raid_buffed();
  PrinceMalchezaar prince_malchezaar;
  prince_malchezaar.set_lvl(prot_quidea1.level);
  prot_quidea1.set_boss(prince_malchezaar);
  prot_quidea1.set_n_ally_dd(13);
  prot_quidea1.set_talent("Redoubt", 5);
  prot_quidea1.set_talent("Toughness", 5);
  prot_quidea1.set_talent("Precision", 3);
  prot_quidea1.set_talent("Improved Righteous Fury", 3);
  prot_quidea1.set_talent("Shield Specialization", 3);
  prot_quidea1.set_talent("Anticipation", 5);
  prot_quidea1.set_talent("Spell Warding", 2);
  prot_quidea1.set_talent("Sacred Duty", 2);
  prot_quidea1.set_talent("One-Handed Weapon Specialization", 5);
  prot_quidea1.set_talent("Ardent Defender", 5);
  prot_quidea1.set_talent("Combat Expertise", 5);
  prot_quidea1.set_talent("Blessing of Sanctuary", 1);
  prot_quidea1.set_talent("Holy Shield", 1);
  prot_quidea1.set_talent("Improved Holy Shield", 2);
  prot_quidea1.set_talent("Improved Judgement", 2);
  prot_quidea1.set_talent("Deflection", 5);

  // Gear
  TankatronicGoggles head6;
  GlyphOfTheDefender head_ench;
  head6.set_enchantment(head_ench);
  EternalEarthstormDiamond meta_gem;
  ThickDawnstone gem1;
  head6.add_gem(meta_gem);
  head6.add_gem(gem1);
  prot_quidea1.equip(head6);

  NatashasBattleChain neck1;
  SteamHingeChainOfValor neck5;
  prot_quidea1.equip(neck5);

  SpauldersOfTheRighteous shoulder1;
  InscriptionOfWarding shoulder_ench;
  shoulder1.set_enchantment(shoulder_ench);
  SubtleLivingRuby gem2;
  SolidStarOfElune gem3;
  shoulder1.add_gem(gem2);
  shoulder1.add_gem(gem3);
  prot_quidea1.equip(shoulder1);

  CloakOfEternity back1; // highest eff hp and tps
  BurnooseOfShiftingAges back4;
  Steelweave back_ench;
  back4.set_enchantment(back_ench);
  IronscaleWarCloak back8;
  prot_quidea1.equip(back4);

  BreastplateOfTheRighteous chest1; // highest tps
  ExceptionalHealth chest_ench;
  chest1.set_enchantment(chest_ench);
  EnduringTalasit gem4;
  chest1.add_gem(gem2);
  chest1.add_gem(gem3);
  chest1.add_gem(gem4);
  prot_quidea1.equip(chest1);

  BracersOfTheGreenFortress wrist1;
  VambracesOfDaring wrist5; // highest eff hp
  Brawn wrist_ench;
  wrist5.set_enchantment(wrist_ench);
  prot_quidea1.equip(wrist5);

  ThatiasSelfCorrectingGauntlets hands1;
  HandsSuperiorAgility hands_ench;
  hands1.set_enchantment(hands_ench);
  RegalNightseye gem5;
  hands1.add_gem(gem5);
  hands1.add_gem(gem3);
  GauntletsOfTheRighteous hands4;
  prot_quidea1.equip(hands1);

  ShatariVindicatorsWaistguard waist1;
  GirdleOfValorousDeeds waist2;
  LionsHeartGirdle waist3;
  prot_quidea1.equip(waist1);

  TimewardensLeggings legs1; // highest eff hp
  NethercleftLegArmor leg_ench;
  legs1.set_enchantment(leg_ench);
  legs1.add_gem(gem5);
  legs1.add_gem(gem1);
  legs1.add_gem(gem4);
  FelsteelLeggings legs2;
  LegplatesOfTheRighteous legs5;
  prot_quidea1.equip(legs1);

  ShatariWroughtGreaves feet10;
  RedHavocBoots feet13;
  BootsDexterity feet_ench;
  feet13.set_enchantment(feet_ench);
  prot_quidea1.equip(feet13);

  IronBandOfTheUnbreakable ring1; // high tps
  CenarionRingOfCasting ring2;
  AndormusTear ring8;
  ProtectorsMarkOfTheRedemption ring10;
  BandOfUrsol ring16;
  RingOfTheSilverHand ring17;
  RingOfTheStonebark ring18;
  prot_quidea1.equip(ring1);
  prot_quidea1.equip(ring10);

  ContinuumBlade weapon1; // highest eff hp
  GreatswordOfHorridDreams weapon2;
  ManaWrath weapon3;
  CrystalforgedSword weapon4;
  GavelOfUnearthedSecrets weapon5;  // highest tps
  MercilessGladiatorsGavel weapon6; // is being skipped in cenvergent_gearing
  WeaponMajorSpellpower temp_enchant;
  weapon6.set_enchantment(temp_enchant);
  prot_quidea1.equip(weapon6);

  AegisOfTheSunbird shield1;
  prot_quidea1.equip(shield1);

  AdamantineFigurine trinket1;
  DabirisEnigma trinket2;
  DarkmoonCardVengeance trinket3;
  CharmOfAlacrity trinket6;
  FigurineOfTheColossus trinket7;
  prot_quidea1.equip(trinket1);
  prot_quidea1.equip(trinket2);

  LibramOfSaintsDeparted libram1;
  LibramOfRepentance libram2; // 15 badges of justice
  prot_quidea1.equip(libram2);

  prot_quidea1.compute_stats();
  cout << "base q eff hp:" << prot_quidea1.get_eff_hp() << endl;
  cout << "Base Quidea stats:" << endl;
  cout << "hp=" << prot_quidea1.get_hp() << endl;
  cout << "mana=" << prot_quidea1.get_mp() << endl;
  prot_quidea1.print_base_stats();
  cout << "Defense=" << prot_quidea1.get_defense() << endl;
  cout << "dodge=" << prot_quidea1.get_dodge_chance() << endl;
  cout << "parry=" << prot_quidea1.get_parry() << endl;
  cout << "miss=" << prot_quidea1.get_missed() << endl;
  cout << "avoidance=" << prot_quidea1.get_avoidance() << endl;
  cout << "block chance=" << prot_quidea1.get_block() << endl;
  cout << "block_value=" << prot_quidea1.get_block_value() << endl;
  prot_quidea1.print_gear();
  return 0;
}
