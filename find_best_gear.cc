#include "Character.hh"
#include "buffs.hh"
#include "enchantments.hh"
#include "equipment.hh"
#include "gems.hh"
#include "support_functions.hh"

using namespace std;

int main() {
  vector<Gear> heads, necks, shoulders, backs, chests, bracers, hands, belts, legs, boots, rings, trinkets, mainhands, offhands, librams;
  Character prot_quidea1("Paladin", "Draenei");
  BlessingOfSanctuary bos;
  prot_quidea1.add_buff(bos);
  // prot_quidea1.get_raid_buffed();
  PrinceMalchezaar prince_malchezaar;
  prince_malchezaar.set_lvl(prot_quidea1.level + 3);
  Hydros hydros;
  hydros.set_lvl(prot_quidea1.level + 3);
  prot_quidea1.set_boss(hydros);
  prot_quidea1.set_n_ally_dd(5);
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
  // Gems

  Socket QuickDawnstone("yellow");
  QuickDawnstone.secondary_stats.haste_rating = 8;
  Socket PotentNobleTopaz("orange");
  PotentNobleTopaz.secondary_stats.spellpower = 5;
  PotentNobleTopaz.secondary_stats.spellcrit_rating = 4;
  Socket VeiledNobleTopaz("orange");
  VeiledNobleTopaz.secondary_stats.spellpower = 5;
  VeiledNobleTopaz.secondary_stats.spellhit_rating = 4;
  Socket LuminousNobleTopaz("orange");
  LuminousNobleTopaz.secondary_stats.spellpower = 5;
  LuminousNobleTopaz.primary_stats.intelligence = 4;
  Socket RecklessNobleTopaz("orange");
  RecklessNobleTopaz.secondary_stats.spellpower = 5;
  RecklessNobleTopaz.secondary_stats.haste_rating = 4;
  Socket NimbleFireOpal("orange");
  NimbleFireOpal.secondary_stats.dodge_rating = 5;
  NimbleFireOpal.secondary_stats.hit_rating = 4;

  // Gear
  FelsteelHelm head4;
  heads.push_back(head4);
  HelmOfTheStalwartDefender head1;
  heads.push_back(head1);
  OathkeepersHelm head2;
  heads.push_back(head2);
  GreathelmOfTheUnbreakable head3;
  heads.push_back(head3);
  X52TechniciansHelm head5;
  heads.push_back(head5);
  TankatronicGoggles head6;
  heads.push_back(head6);
  MyrmidonsHeaddress head7;
  heads.push_back(head7);
  HelmOfTheRighteous head8;
  heads.push_back(head8);
  FaceguardOfDetermination head9; // badges of justice
  heads.push_back(head9);
  WarhelmOfTheBold head10;
  heads.push_back(head10);
  EterniumGreathelm head11; // Karazhan
  heads.push_back(head11);
  JusticarFaceguard head12; // Karazhan
  heads.push_back(head12);
  ThunderingGreathelm head13; // Magtheridon
  heads.push_back(head13);
  IceguardHelm head14;
  heads.push_back(head14);

  NatashasBattleChain neck1;
  necks.push_back(neck1);
  NecklaceOfTheJuggernaut neck2; // 25 badges of justice
  necks.push_back(neck2);
  StrengthOfTheUntamed neck3;
  necks.push_back(neck3);
  MaladaarsBlessedChaplet neck4;
  necks.push_back(neck4);
  SteamHingeChainOfValor neck5;
  necks.push_back(neck5);
  ThalodiensCharm neck6;
  necks.push_back(neck6);
  MarkOfTheRavenguard neck7; // high eff hp
  necks.push_back(neck7);
  MedallionOfTheValiantGuardian neck8;
  necks.push_back(neck8);
  EnchantedThoriumTorque neck9;
  necks.push_back(neck9);
  EthereumTorqueOfTheKnight neck10;
  necks.push_back(neck10);
  EthereumTorqueOfTheChampion neck11;
  necks.push_back(neck11);
  ChainOfTheTwilightOwl neck12; // high tps
  necks.push_back(neck12);
  BroochOfUnquenchableFury neck13; // Karazhan
  necks.push_back(neck13);
  BarbedChokerOfDiscipline neck14; // Karazhan
  necks.push_back(neck14);
  MithrilChainOfHeroism neck15; // Karazhan
  necks.push_back(neck15);
  PendantOfThawing neck16;
  necks.push_back(neck16);

  SpauldersOfTheRighteous shoulder1;
  shoulders.push_back(shoulder1);
  FanbladePauldrons shoulder2;
  shoulders.push_back(shoulder2);
  SpauldersOfDementia shoulder3; // high eff hp
  shoulders.push_back(shoulder3);
  WarchiefsMantle shoulder4;
  shoulders.push_back(shoulder4);
  KaylaansSpaulders shoulder5; // high tps
  shoulders.push_back(shoulder5);
  ShoulderguardsOfTheBold shoulder6;
  shoulders.push_back(shoulder6);
  MantleOfAbrahmis shoulder7; // Karazhan
  shoulders.push_back(shoulder7);
  JusticarShoulderguards shoulder8; // Gruul
  shoulders.push_back(shoulder8);

  CloakOfEternity back1; // highest eff hp and tps
  backs.push_back(back1);
  DevilsharkCape back2;
  backs.push_back(back2);
  FarstriderDefendersCloak back3; // 25 Badge of justice
  backs.push_back(back3);
  BurnooseOfShiftingAges back4;
  backs.push_back(back4);
  BogstrokScaleCloak back5;
  backs.push_back(back5);
  ThoriumweaveCloak back6;
  backs.push_back(back6);
  CloakOfTheValiantDefender back7;
  backs.push_back(back7);
  IronscaleWarCloak back8;
  backs.push_back(back8);
  RoyalCloakOfArathiKings back9; // Karazhan
  backs.push_back(back9);
  ShadowCloakOfDalaran back10; // Karazhan
  backs.push_back(back10);
  GildedThoriumCloak back11; // Karazhan
  backs.push_back(back11);
  SlikksCloakOfPlacation back12; // 35 Badge of Justice
  backs.push_back(back12);

  ScavengedBreastplate chest5;
  chests.push_back(chest5);
  BreastplateOfTheRighteous chest1; // highest tps
  chests.push_back(chest1);
  JadeSkullBreastplate chest2; // highest eff hp
  chests.push_back(chest2);
  VindicatorsHauberk chest3;
  chests.push_back(chest3);
  BreastplateOfTheWarbringer chest4;
  chests.push_back(chest4);
  BreastplateOfTheBold chest6;
  chests.push_back(chest6);
  ChestguardOfTheStoicGuardian chest7; // 75 BoJ
  chests.push_back(chest7);
  ChestplateOfStoicisim chest8; // 100 BoJ
  chests.push_back(chest8);
  ShattrathProtectoratesBreastplate chest9; // 100 BoJ
  chests.push_back(chest9);
  PanzarTharBreastplate chest10; // Karazhan
  chests.push_back(chest10);
  JusticarChestguard chest11; // Magtheridon
  chests.push_back(chest11);
  IceguardBreastplate chest12;
  chests.push_back(chest12);

  BracersOfTheGreenFortress wrist1;
  bracers.push_back(wrist1);
  BracersOfDignity wrist2; // highest tps
  bracers.push_back(wrist2);
  AmberBandsOfTheAggressor wrist3;
  bracers.push_back(wrist3);
  ShatariWroughtArmguards wrist4;
  bracers.push_back(wrist4);
  VambracesOfDaring wrist5; // highest eff hp
  bracers.push_back(wrist5);
  ThadellsBracers wrist6;
  bracers.push_back(wrist6);
  JuniorTechnician3rdGradeBracers wrist7;
  bracers.push_back(wrist7);
  BracersOfTheAncientPhalanx wrist8;
  bracers.push_back(wrist8);
  VambracesOfCourage wrist9; // Karazhan
  bracers.push_back(wrist9);

  FelsteelGloves hands1;
  hands.push_back(hands1);
  GauntletsOfTheIronTower hands2;
  hands.push_back(hands2);
  GauntletsOfDissension hands3;
  hands.push_back(hands3);
  GauntletsOfTheRighteous hands4;
  hands.push_back(hands4);
  GauntletsOfTheBold hands5;
  hands.push_back(hands5);
  ThatiasSelfCorrectingGauntlets hands6;
  hands.push_back(hands6);
  GauntletsOfTheChosen hands7;
  hands.push_back(hands7);
  DauntlessHandguards hands8;
  hands.push_back(hands8);
  BonefistGauntlets hands9; // badges of justice
  hands.push_back(hands9);
  IronGauntletsOfTheMaiden hands10; // Karazhan
  hands.push_back(hands10);
  JusticarHandguard hands11; // Karazhan
  hands.push_back(hands11);

  ShatariVindicatorsWaistguard waist1;
  belts.push_back(waist1);
  GirdleOfValorousDeeds waist2;
  belts.push_back(waist2);
  LionsHeartGirdle waist3;
  belts.push_back(waist3);
  GirdleOfTheImmovable waist4;
  belts.push_back(waist4);
  GirdleOfTheProtector waist5; // 60 Badges of Justice
  belts.push_back(waist5);
  GirdleOfTheFearless waist6; // 75 BoJ
  belts.push_back(waist6);
  CrimsonGirdleOfTheIndomitable waist7; // Karazhan
  belts.push_back(waist7);
  IrontuskGirdle waist8; // 60 Badges of Justice
  belts.push_back(waist8);

  TimewardensLeggings legs1; // highest eff hp
  legs.push_back(legs1);
  FelsteelLeggings legs2;
  legs.push_back(legs2);
  GreavesOfTheShatterer legs3;
  legs.push_back(legs3);
  LegguardsOfTheResoluteDefender legs4;
  legs.push_back(legs4);
  LegplatesOfTheRighteous legs5;
  legs.push_back(legs5);
  KirinvarDefendersChausses legs6; // highest tps
  legs.push_back(legs6);
  LegplatesOfTheBold legs7;
  legs.push_back(legs7);
  UnwaveringLegguards legs8; // 75 badge of justice
  legs.push_back(legs8);
  SunguardLegplates legs9; // 100 BoJ
  legs.push_back(legs9);
  InscribedLegplatesOfTheAldor legs10; // 100 BoJ
  legs.push_back(legs10);
  WrynnDynastyGreaves legs11; // Karazhan
  legs.push_back(legs11);
  JusticarLegguards legs12; // Gruul
  legs.push_back(legs12);
  IceguardLeggings legs13;
  legs.push_back(legs13);

  SabatonsOfTheRighteousDefender feet1; // 60 badges of justice
  boots.push_back(feet1);
  BootsOfTheRighteousPath feet2; // highest eff hp and tps
  boots.push_back(feet2);
  BootsOfTheColossus feet3;
  boots.push_back(feet3);
  FleshBeastsMetalGreaves feet4;
  boots.push_back(feet4);
  EaglecrestWarboots feet5;
  boots.push_back(feet5);
  BootsOfRighteousFortitude feet6;
  boots.push_back(feet6);
  AscendantsBoots feet7;
  boots.push_back(feet7);
  BloodguardsGreaves feet8;
  boots.push_back(feet8);
  StarcallersPlatedStompers feet9;
  boots.push_back(feet9);
  ShatariWroughtGreaves feet10;
  boots.push_back(feet10);
  BluesGreavesOfTheRighteousGuardian feet12; // 75 BoJ
  boots.push_back(feet12);
  RedHavocBoots feet13;
  boots.push_back(feet13);
  BootsOfElusion feet14; // Karazhan
  boots.push_back(feet14);
  IronstridersOfUrgency feet15; // Karazhan
  boots.push_back(feet15);
  BattlescarBoots feet16; // Karazhan
  boots.push_back(feet16);

  IronBandOfTheUnbreakable ring1; // high tps
  rings.push_back(ring1);
  CenarionRingOfCasting ring2;
  rings.push_back(ring2);
  BandOfImpenetrableDefenses ring3; // high tps and eff hp
  rings.push_back(ring3);
  RingOfUnyieldingForce ring4; // 25 badges of justice
  rings.push_back(ring4);
  YorsRevenge ring5; // high eff hp
  rings.push_back(ring5);
  ElementiumBandOfTheSentry ring6;
  rings.push_back(ring6);
  LieutenantsSignetOfLordaeron ring7;
  rings.push_back(ring7);
  AndormusTear ring8;
  rings.push_back(ring8);
  DelicateEterniumRing ring9;
  rings.push_back(ring9);
  ProtectorsMarkOfTheRedemption ring10;
  rings.push_back(ring10);
  DathRemarsRingOfDefense ring11;
  rings.push_back(ring11);
  RingOfTheStalwartProtector ring12; // 60 BoJ
  rings.push_back(ring12);
  SpectralBandOfInnervation ring13; // Karazhan
  rings.push_back(ring13);
  ShermanarGreatRing ring14; // Karazhan
  rings.push_back(ring14);
  AdalsSignetOfDefense ring15; // Magtheridon
  rings.push_back(ring15);
  BandOfUrsol ring16;
  rings.push_back(ring16);
  RingOfTheSilverHand ring17;
  rings.push_back(ring17);
  RingOfTheStonebark ring18;
  rings.push_back(ring18);
  VioletSignet ring19; // Karazhan
  rings.push_back(ring19);
  TheFrozenEye ring20;
  rings.push_back(ring20);

  ContinuumBlade weapon1; // highest eff hp
  mainhands.push_back(weapon1);
  GreatswordOfHorridDreams weapon2;
  mainhands.push_back(weapon2);
  ManaWrath weapon3;
  mainhands.push_back(weapon3);
  CrystalforgedSword weapon4;
  mainhands.push_back(weapon4);
  GavelOfUnearthedSecrets weapon5; // highest tps
  mainhands.push_back(weapon5);
  MercilessGladiatorsGavel weapon6;
  /*WeaponMajorSpellpower temp_enchant;
  weapon6.set_enchantment(temp_enchant);*/
  mainhands.push_back(weapon6);

  AegisOfTheSunbird shield1;
  offhands.push_back(shield1);
  CrestOfTheShatar shield2;
  offhands.push_back(shield2);
  PlatinumShieldOfTheValorous shield3; // highest eff hp
  offhands.push_back(shield3);
  NetherwingDefendersShield shield4; // highest tps
  offhands.push_back(shield4);
  OgrilaAegis shield5;
  offhands.push_back(shield5);
  ShieldOfTheWaywardFootman shield6;
  offhands.push_back(shield6);
  AzureShieldOfColdarra shield7; // 33 badges of justice
  offhands.push_back(shield7);
  GladiatorsShieldWall shield8;
  offhands.push_back(shield8);
  ShieldOfImpenetrableDarkness shield9; // Karazhan
  offhands.push_back(shield9);
  AldoriLegacyDefender shield10; // Gruul
  offhands.push_back(shield10);

  AdamantineFigurine trinket1;
  // trinkets.push_back(trinket1);
  DabirisEnigma trinket2;
  // trinkets.push_back(trinket2);
  DarkmoonCardVengeance trinket3;
  trinkets.push_back(trinket3);
  GnomereganAutoBlocker600 trinket4; // 41 badges of justice
  trinkets.push_back(trinket4);
  BattlemastersAudacity trinket5; // BoJ
  trinkets.push_back(trinket5);
  CharmOfAlacrity trinket6;
  // trinkets.push_back(trinket6);
  FigurineOfTheColossus trinket7;
  // trinkets.push_back(trinket7);
  MoroesLuckyPocketWatch trinket8; // Karazhan
  trinkets.push_back(trinket8);

  LibramOfSaintsDeparted libram1;
  librams.push_back(libram1);
  LibramOfRepentance libram2; // 15 badges of justice
  librams.push_back(libram2);

  vector<Gear> rings1, rings2;
  for (uint i = 0; i < rings.size(); i++) {
    rings1.push_back(rings[i]);
    rings2.push_back(rings[i]);
    rings1[i].slot = "Ring0";
    rings2[i].slot = "Ring1";
  }
  vector<Gear> trinkets1, trinkets2;
  for (uint i = 0; i < trinkets.size(); i++) {
    trinkets1.push_back(trinkets[i]);
    trinkets2.push_back(trinkets[i]);
    trinkets1[i].slot = "Trinket0";
    trinkets2[i].slot = "Trinket1";
  }

  // Enchanting
  vector<Gear> heads_enchanted = enchant_gear(&heads);
  vector<Gear> chests_enchanted = enchant_gear(&chests);
  vector<Gear> shoulders_enchanted = enchant_gear(&shoulders);
  vector<Gear> backs_enchanted = enchant_gear(&backs);
  vector<Gear> bracers_enchanted = enchant_gear(&bracers);
  vector<Gear> hands_enchanted = enchant_gear(&hands);
  vector<Gear> legs_enchanted = enchant_gear(&legs);
  vector<Gear> boots_enchanted = enchant_gear(&boots);
  vector<Gear> mainhands_enchanted = enchant_gear(&mainhands);
  vector<Gear> offhands_enchanted = enchant_gear(&offhands);

  vector<vector<Gear>> all_gear = {heads_enchanted, necks,  shoulders_enchanted, backs_enchanted, chests_enchanted,    bracers_enchanted,  hands_enchanted, belts, legs_enchanted, boots_enchanted,
                                   rings1,          rings2, trinkets1,           trinkets2,       mainhands_enchanted, offhands_enchanted, librams};
  // prot_quidea1.equip(head6);
  prot_quidea1.equip(head14);
  prot_quidea1.equip(neck1);
  prot_quidea1.equip(shoulder1);
  prot_quidea1.equip(back2);
  // prot_quidea1.equip(chest8);
  prot_quidea1.equip(chest12);
  prot_quidea1.equip(wrist5);
  prot_quidea1.equip(hands6);
  prot_quidea1.equip(waist1);
  prot_quidea1.equip(legs13);
  prot_quidea1.equip(ring1);
  prot_quidea1.equip(ring2);
  prot_quidea1.equip(weapon6);
  prot_quidea1.equip(shield1);
  prot_quidea1.equip(trinket4);
  prot_quidea1.equip(trinket8);
  prot_quidea1.equip(feet13);
  prot_quidea1.equip(libram2);
  prot_quidea1.compute_stats();
  convergent_gearing(&prot_quidea1, &all_gear);
  /*
  cout << endl;
  cout << "Base Quidea stats:" << endl;
  cout << "base hp=" << prot_quidea1.base_stats.health << endl;
  cout << "prim hp=" << prot_quidea1.primary_stats.health << endl;
  cout << "hp=" << prot_quidea1.base_stats.health + prot_quidea1.primary_stats.health << endl;
  cout << "mana=" << prot_quidea1.base_stats.mana + prot_quidea1.primary_stats.mana << endl;
  cout << "dodge=" << prot_quidea1.get_dodge_chance() << endl;
  cout << "parry=" << prot_quidea1.get_parry() << endl;
  cout << "block chance=" << prot_quidea1.get_block() << endl;*/
  return 0;
}
