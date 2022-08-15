#include "NPCs.hh"
#include "Character.hh"
#include "buffs.hh"
#include "enchantments.hh"
#include "equipment.hh"
#include "gems.hh"
#include "support_functions.hh"
// #include "enums.hh"
#include <fstream>
#include <iostream>
#include <random>
#include <iterator>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// -*- compile-command: "clang++ -ggdb -o random_selection -std=c++0x -stdlib=libc++ random_selection.cpp" -*-
// template <typename RandomGenerator = std::default_random_engine>
// struct random_selector
// {
//   //On most platforms, you probably want to use std::random_device("/dev/urandom")()
//   random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
//       : gen(g) {}

//   template <typename Iter>
//   Iter select(Iter start, Iter end)
//   {
//     std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
//     std::advance(start, dis(gen));
//     return start;
//   }

//   //convenience function
//   template <typename Iter>
//   Iter operator()(Iter start, Iter end)
//   {
//     return select(start, end);
//   }

//   //convenience function that works on anything with a sensible begin() and end(), and returns with a ref to the value type
//   template <typename Container>
//   auto operator()(const Container &c) -> decltype(*begin(c)) &
//   {
//     return *select(begin(c), end(c));
//   }

// private:
//   RandomGenerator gen;
// };

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g)
{
  std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
  std::advance(start, dis(g));
  return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

int main()
{
  std::cout.precision(3);
  tbb::task_scheduler_init init(15);
  Race race = Race::Tauren;
  CharacterClass player_class = CharacterClass::Druid;
  const unsigned int level=70;
  PrinceMalchezaar prince_malchezaar;
  prince_malchezaar.set_lvl(level + 3);
  // Character prot_quidea1("Paladin", "Draenei");
  Character bear_munkro1(player_class, race, level, &prince_malchezaar);
  bear_munkro1.set_bear(true);
  bear_munkro1.set_source(raid);
  bear_munkro1.exclude_source(raid);
  // bear_munkro1.exclude_source(heroicdungeon);
  // bear_munkro1.exclude_source(boj);
  bear_munkro1.set_phase(1);
  // BlessingOfSanctuary bos;
  // prot_quidea1.add_buff(bos);
  // prot_quidea1.get_raid_buffed();
  
  // Hydros hydros;
  // hydros.set_lvl(prot_quidea1.level + 3);
  // prot_quidea1.set_boss(prince_malchezaar);
  // prot_quidea1.set_n_ally_dd(5);
  // prot_quidea1.set_talent("Redoubt", 5);
  // prot_quidea1.set_talent("Toughness", 5);
  // prot_quidea1.set_talent("Precision", 3);
  // prot_quidea1.set_talent("Improved Righteous Fury", 3);
  // prot_quidea1.set_talent("Shield Specialization", 3);
  // prot_quidea1.set_talent("Anticipation", 5);
  // prot_quidea1.set_talent("Spell Warding", 2);
  // prot_quidea1.set_talent("Sacred Duty", 2);
  // prot_quidea1.set_talent("One-Handed Weapon Specialization", 5);
  // prot_quidea1.set_talent("Ardent Defender", 5);
  // prot_quidea1.set_talent("Combat Expertise", 5);
  // prot_quidea1.set_talent("Blessing of Sanctuary", 1);
  // prot_quidea1.set_talent("Holy Shield", 1);
  // prot_quidea1.set_talent("Improved Holy Shield", 2);
  // prot_quidea1.set_talent("Improved Judgement", 2);
  // prot_quidea1.set_talent("Deflection", 5);
  // bear_munkro1.set_boss(&prince_malchezaar);
  bear_munkro1.set_n_ally_dd(5);
  bear_munkro1.set_talent("Ferocity", 5);
  bear_munkro1.set_talent("Thick Hide", 3);
  bear_munkro1.set_talent("Sharpened Claws", 3);
  bear_munkro1.set_talent("Feral Swiftness", 2);
  bear_munkro1.set_talent("Predatory Strikes", 3);
  bear_munkro1.set_talent("Primal Fury", 2);
  bear_munkro1.set_talent("Shredding Attacks", 2);
  bear_munkro1.set_talent("Heart of the Wild", 5);
  bear_munkro1.set_talent("Survival of the Fittest", 3);
  bear_munkro1.set_talent("Leader of the Pack", 1);
  bear_munkro1.set_talent("Improved Leader of the Pack", 2);
  bear_munkro1.set_talent("Predatory Instincts", 5);
  bear_munkro1.set_talent("Mangle", 1);
  bear_munkro1.set_talent("Naturalist", 5);
  bear_munkro1.set_talent("Intensity", 3);
  bear_munkro1.set_talent("Omen of Clarity", 1);

  // Gear
  // vector<Gear> heads={HelmOfTheStalwartDefender(), OathkeepersHelm(), GreathelmOfTheUnbreakable(), FelsteelHelm(), X52TechniciansHelm(), TankatronicGoggles(), MyrmidonsHeaddress(), HelmOfTheRighteous(), FaceguardOfDetermination(), WarhelmOfTheBold(), EterniumGreathelm(), JusticarFaceguard(), ThunderingGreathelm(), IceguardHelm()}; // Paladin

  // vector<Gear> necks={NecklaceOfTheJuggernaut(), MaladaarsBlessedChaplet(), MarkOfTheRavenguard(), EnchantedThoriumTorque(), StrengthOfTheUntamed(), MaimfistsChoker(), BroochOfDeftness(), NatashasBattleChain(), SteamHingeChainOfValor(), ThalodiensCharm(), MedallionOfTheValiantGuardian(), EthereumTorqueOfTheKnight(), EthereumTorqueOfTheChampion(), ChainOfTheTwilightOwl(), BroochOfUnquenchableFury(), BarbedChokerOfDiscipline(), MithrilChainOfHeroism(), PendantOfThawing()}; // Paladin

  // vector<Gear> shoulders={SpauldersOfTheRighteous(), FanbladePauldrons(), SpauldersOfDementia(), WarchiefsMantle(), KaylaansSpaulders(), ShoulderguardsOfTheBold(), MantleOfAbrahmis(), JusticarShoulderguards()}; // Paladin

  // vector<Gear> backs={CloakOfEternity(), ThoriumweaveCloak(), SlikksCloakOfPlacation(), DevilsharkCape(), FarstriderDefendersCloak(), BurnooseOfShiftingAges(), BogstrokScaleCloak(), CloakOfTheValiantDefender(), IronscaleWarCloak(), RoyalCloakOfArathiKings(), ShadowCloakOfDalaran(), GildedThoriumCloak()}; // Paladin

  // vector<Gear> chests={ScavengedBreastplate(), BreastplateOfTheRighteous(), JadeSkullBreastplate(), VindicatorsHauberk(), BreastplateOfTheWarbringer(), BreastplateOfTheBold(), ChestguardOfTheStoicGuardian(), ChestplateOfStoicisim(), ShattrathProtectoratesBreastplate(), PanzarTharBreastplate(), JusticarChestguard(), IceguardBreastplate()}; // Paladin

  // vector<Gear> bracers={BracersOfTheGreenFortress(), BracersOfDignity(), AmberBandsOfTheAggressor(), ShatariWroughtArmguards(), VambracesOfDaring(), ThadellsBracers(), JuniorTechnician3rdGradeBracers(), BracersOfTheAncientPhalanx(), VambracesOfCourage()}; // Paladin

  // vector<Gear> hands={FelsteelGloves(), GauntletsOfTheIronTower(), GauntletsOfDissension(), GauntletsOfTheRighteous(), GauntletsOfTheBold(), ThatiasSelfCorrectingGauntlets(), GauntletsOfTheChosen(), DauntlessHandguards(), BonefistGauntlets(), IronGauntletsOfTheMaiden(), JusticarHandguard()}; // Paladin

  // vector<Gear> belts={ShatariVindicatorsWaistguard(), GirdleOfValorousDeeds(), LionsHeartGirdle(), GirdleOfTheImmovable(), GirdleOfTheProtector(), GirdleOfTheFearless(), CrimsonGirdleOfTheIndomitable(), IrontuskGirdle()}; // Paladin

  // vector<Gear> legs={TimewardensLeggings(), FelsteelLeggings(), GreavesOfTheShatterer(), LegguardsOfTheResoluteDefender(), LegplatesOfTheRighteous(), KirinvarDefendersChausses(), LegplatesOfTheBold(), UnwaveringLegguards(), SunguardLegplates(), InscribedLegplatesOfTheAldor(), WrynnDynastyGreaves(), JusticarLegguards(), IceguardLeggings()}; // Paladin

  // vector<Gear> boots={BattlescarBoots(), IronstridersOfUrgency(), BootsOfElusion(), RedHavocBoots(), BluesGreavesOfTheRighteousGuardian(), ShatariWroughtGreaves(), StarcallersPlatedStompers(), BloodguardsGreaves(), AscendantsBoots(), BootsOfRighteousFortitude(), EaglecrestWarboots(), FleshBeastsMetalGreaves(), BootsOfTheColossus(), BootsOfTheRighteousPath(), SabatonsOfTheRighteousDefender()};

  //  cross check rings again
  // vector<Gear> rings={CenarionRingOfCasting(), LieutenantsSignetOfLordaeron(), AndormusTear(), ProtectorsMarkOfTheRedemption(), DathRemarsRingOfDefense(), RingOfTheStalwartProtector(), SpectralBandOfInnervation(), ShapeshiftersSignet(), WindTradersBand(), RingOfTheStonebark(), DelicateEterniumRing(), ElementiumBandOfTheSentry(), YorsRevenge(), RingOfUnyieldingForce(), BandOfImpenetrableDefenses(), IronBandOfTheUnbreakable(), TheFrozenEye(), VioletSignet(), RingOfTheSilverHand(), BandOfUrsol(), AdalsSignetOfDefense(), ShermanarGreatRing()}; // Paladin

  // vector<Gear> trinkets = {RegalProtectorate(), AdamantineFigurine(), DarkmoonCardVengeance(), CharmOfAlacrity(), DabirisEnigma(), GnomereganAutoBlocker600(), TalismanOfTheHorde(), BroochOfTheImmortalKing(), FigurineOfTheColossus(), BattlemastersAudacity(), MoroesLuckyPocketWatch()};                                                                                                                                                                    // Paladin
  sql::Driver *driver;
  sql::Connection *con;
  sql::ConnectOptionsMap connection_properties;
  connection_properties["hostName"] = "tcp://127.0.0.1:3306";
  connection_properties["userName"] = "wow";
  connection_properties["password"] = "$herlock_H0lmes#";
  connection_properties["OPT_RECONNECT"] = true;
  sql::Statement *stmt;
  sql::ResultSet *res;
  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect(connection_properties);
  /* Connect to the MySQL database */
  con->setSchema("tbcGear");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT count(*) AS columns FROM information_schema.columns WHERE table_name ='phase1PreRaidDruid'");
  res->next();
  uint columns = std::stoi(res->getString(1));
  res = stmt->executeQuery("SELECT * FROM phase1PreRaidDruid as _allGear;");
  vector<vector<Gear>> all_gear2;
  all_gear2.reserve((uint)Slot::Twohand + 2);
  for (uint i = (Slot)Slot::NoSlot; i <= (uint)Slot::Twohand; i++)
  {
    vector<Gear> temp;
    all_gear2.push_back(temp);
  }
  all_gear2.shrink_to_fit();
  while (res->next())
  {
    stringstream temp_item_ss;
    for (uint i = 0; i < columns; i++)
    {
      temp_item_ss << res->getString(i + 1) << "\t";
    }
    Gear temp_item;
    temp_item_ss >> temp_item;
    if (bear_munkro1.is_excluded(&temp_item) || prince_malchezaar.useless_gear(&temp_item, &bear_munkro1))
    {
      continue;
    }
    if (temp_item.get_slot() == Slot::Ring)
    {
      Gear temp_item2 = temp_item;
      temp_item.set_slot(Slot::Ring1);
      temp_item2.set_slot(Slot::Ring2);
      all_gear2[temp_item2.get_slot()].push_back(temp_item2);
    }
    else if (temp_item.get_slot() == Slot::Trinket)
    {
      Gear temp_item2 = temp_item;
      temp_item.set_slot(Slot::Trinket1);
      temp_item2.set_slot(Slot::Trinket2);
      all_gear2[temp_item2.get_slot()].push_back(temp_item2);
    }
    if (temp_item.get_slot() != Slot::NoSlot)
    {
      all_gear2[temp_item.get_slot()].push_back(temp_item);
    }
  }
  vector<vector<Gear> *> all_gear;
  all_gear.reserve(all_gear2.size());
  for (uint i = 0; i < all_gear2.size(); i++)
  {
    all_gear.push_back(&all_gear2[i]);
  }
  all_gear.shrink_to_fit();
  // prot_quidea1.equip(head6);
  // prot_quidea1.equip(head1);
  // prot_quidea1.equip(neck1);
  // prot_quidea1.equip(shoulder1);
  // prot_quidea1.equip(back1);
  // prot_quidea1.equip(chest8);
  // prot_quidea1.equip(chest1);
  // prot_quidea1.equip(wrist1);
  // prot_quidea1.equip(hands1);
  // prot_quidea1.equip(waist1);
  // prot_quidea1.equip(legs1);
  // prot_quidea1.equip(ring1);
  // prot_quidea1.equip(ring2);
  // prot_quidea1.equip(weapon6);
  // prot_quidea1.equip(shield1);
  // prot_quidea1.equip(trinket4);
  // prot_quidea1.equip(trinket1);
  // prot_quidea1.equip(feet6);
  // prot_quidea1.equip(libram2);
  // prot_quidea1.compute_stats();
  // SolidStarOfElune blue_gem1;
  // RigidDawnstone yellow_gem1;
  // leather_chest1.add_gem(blue_gem1);
  // leather_chest1.add_gem(yellow_gem1);
  // leather_chest1.add_gem(yellow_gem1);
  // leather_legs1.add_gem(blue_gem1);
  // leather_legs1.add_gem(blue_gem1);
  // leather_legs1.add_gem(yellow_gem1);
  // leather_boots1.add_gem(blue_gem1);
  // leather_boots1.add_gem(yellow_gem1);
  // random_selector<> selector{};
  double metric = DBL_MAX;
  Character best_char(player_class, race, level, &prince_malchezaar);
  srand(time(NULL));
  for (uint i = 0; i < 10; i++)
  {
    for (uint j = 0; j < all_gear.size(); j++)
    {
      if (all_gear[j]->size() == 0)
      {
        continue;
      }
      // bear_munkro1.equip(selector(*(*it)));
      uint randomIndex = rand();
      randomIndex = randomIndex % (all_gear[j]->size());
      Gear randomGear = (*all_gear[j])[randomIndex];
      bear_munkro1.equip(randomGear);
    }
    if (rand() % 2 == 1 || i == 0)
    {
      equip_random_set_pieces(&bear_munkro1, &all_gear);
    }
    bear_munkro1.compute_stats();
    bear_munkro1 = char_with_best_consumables(&bear_munkro1);
    std::cout << "starting with:" << std::endl;
    bear_munkro1.print_base_stats();
    bear_munkro1.print_gear();
    bear_munkro1 = convergent_gearing(&bear_munkro1, &all_gear);
    double temp_metric = bear_munkro1.metric();
    if (temp_metric < metric)
    {
      best_char = bear_munkro1;
      metric = temp_metric;
    }
  }
  cout << "Best metric = " << metric << std::endl;
  cout << "Best gear:" << endl;
  best_char.print_gear();
  best_char.print_elixirs();
  best_char.print_buffs();
  // bear_munkro1.equip(leather_head2);
  // bear_munkro1.equip(neck17);
  // bear_munkro1.equip(leather_shoulder1);
  // bear_munkro1.equip(back13);
  // bear_munkro1.equip(leather_chest1);
  // bear_munkro1.equip(leather_wrist1);
  // bear_munkro1.equip(leather_hand1);
  // bear_munkro1.equip(leather_waist1);
  // NethercleftLegArmor leg_ench;
  // leather_legs1.set_enchantment(leg_ench);
  // bear_munkro1.equip(leather_legs1);
  // bear_munkro1.equip(leather_boots1);
  // bear_munkro1.equip(ring18);
  // bear_munkro1.equip(ring21);
  // bear_munkro1.equip(twohand1);
  // bear_munkro1.equip(trinket10);
  // bear_munkro1.equip(trinket9);
  // 21.21% dodge
  // 1181 ap
  // 21.78% crit

  /*cout << endl;
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
