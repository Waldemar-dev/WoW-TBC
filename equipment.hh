#ifndef _EQUIPMENT_HH_
#define _EQUIPMENT_HH_

#include "enchantments.hh"
#include "gems.hh"
#include "stats.hh"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Gear {
public:
  Gear();
  ~Gear() = default;

  string get_name();
  string slot, name;
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
  PrimaryStats bonus_prim_stats;
  SecondaryStats bonus_sec_stats;
  vector<Socket> gems;
  void set_blue(unsigned int);
  void set_red(unsigned int);
  void set_yellow(unsigned int);
  void set_meta(unsigned int);
  void add_gem(Socket);
  void socket_bonus();
  void set_cd(double in) { cooldown = in; }
  void set_uptime(double in) { uptime = in; }
  bool computed_socket_bonus = false;
  bool equipped = false;
  unsigned int get_sockets() { return sockets; }
  double get_cooldown() { return cooldown; }
  double get_uptime() { return uptime; }
  Enchantment get_enchantment() { return enchantment; }
  void set_enchantment(Enchantment); // to do
  bool is_enchanted() { return enchanted; }
  void operator=(Gear);

private:
  Enchantment enchantment;
  bool enchanted = false;
  unsigned int blue, yellow, red, meta;
  unsigned int sockets = 0;
  double cooldown;
  double uptime;
};

class FelsteelHelm : public Gear {
public:
  FelsteelHelm();
};

class NatashasBattleChain : public Gear {
public:
  NatashasBattleChain();
};

class SpauldersOfTheRighteous : public Gear {
public:
  SpauldersOfTheRighteous();
};

class CloakOfEternity : public Gear {
public:
  CloakOfEternity();
};

class BracersOfTheGreenFortress : public Gear {
public:
  BracersOfTheGreenFortress();
};

class FelsteelGloves : public Gear {
public:
  FelsteelGloves();
};

class ShatariVindicatorsWaistguard : public Gear {
public:
  ShatariVindicatorsWaistguard();
};

class TimewardensLeggings : public Gear {
public:
  TimewardensLeggings();
};

class IronsoleClompers : public Gear {
public:
  IronsoleClompers();
};

class IronBandOfTheUnbreakable : public Gear {
public:
  IronBandOfTheUnbreakable();
};

class CenarionRingOfCasting : public Gear {
public:
  CenarionRingOfCasting();
};

class ContinuumBlade : public Gear {
public:
  ContinuumBlade();
};

class AegisOfTheSunbird : public Gear {
public:
  AegisOfTheSunbird();
};

class AdamantineFigurine : public Gear {
public:
  AdamantineFigurine();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class DabirisEnigma : public Gear {
public:
  DabirisEnigma();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BootsOfTheRighteousPath : public Gear {
public:
  BootsOfTheRighteousPath();
};

class BootsOfTheColossus : public Gear {
public:
  BootsOfTheColossus();
};

class FleshBeastsMetalGreaves : public Gear {
public:
  FleshBeastsMetalGreaves();
};

class EaglecrestWarboots : public Gear {
public:
  EaglecrestWarboots();
};

class GladiatorsLamellarHelm : public Gear {
public:
  GladiatorsLamellarHelm();
};

class HelmOfTheStalwartDefender : public Gear {
public:
  HelmOfTheStalwartDefender();
};

class GreathelmOfTheUnbreakable : public Gear {
public:
  GreathelmOfTheUnbreakable();
};

class OathkeepersHelm : public Gear {
public:
  OathkeepersHelm();
};

class DevilsharkCape : public Gear {
public:
  DevilsharkCape();
};

class FarstriderDefendersCloak : public Gear {
public:
  FarstriderDefendersCloak();
};

class BurnooseOfShiftingAges : public Gear {
public:
  BurnooseOfShiftingAges();
};

class BandOfImpenetrableDefenses : public Gear {
public:
  BandOfImpenetrableDefenses();
};

class RingOfUnyieldingForce : public Gear {
public:
  RingOfUnyieldingForce();
};

class YorsRevenge : public Gear {
public:
  YorsRevenge();
};

class ElementiumBandOfTheSentry : public Gear {
public:
  ElementiumBandOfTheSentry();
};

class LieutenantsSignetOfLordaeron : public Gear {
public:
  LieutenantsSignetOfLordaeron();
};

class AndormusTear : public Gear {
public:
  AndormusTear();
};

class NecklaceOfTheJuggernaut : public Gear {
public:
  NecklaceOfTheJuggernaut();
};

class StrengthOfTheUntamed : public Gear {
public:
  StrengthOfTheUntamed();
};

class MaladaarsBlessedChaplet : public Gear {
public:
  MaladaarsBlessedChaplet();
};

class SteamHingeChainOfValor : public Gear {
public:
  SteamHingeChainOfValor();
};

class DarkmoonCardVengeance : public Gear {
public:
  DarkmoonCardVengeance();
};

class FanbladePauldrons : public Gear {
public:
  FanbladePauldrons();
};

class SpauldersOfDementia : public Gear {
public:
  SpauldersOfDementia();
};

class JadeSkullBreastplate : public Gear {
public:
  JadeSkullBreastplate();
};

class VindicatorsHauberk : public Gear {
public:
  VindicatorsHauberk();
};

class BracersOfDignity : public Gear {
public:
  BracersOfDignity();
};

class AmberBandsOfTheAggressor : public Gear {
public:
  AmberBandsOfTheAggressor();
};

class GauntletsOfTheIronTower : public Gear {
public:
  GauntletsOfTheIronTower();
};

class GauntletsOfDissension : public Gear {
public:
  GauntletsOfDissension();
};

class GauntletsOfTheRighteous : public Gear {
public:
  GauntletsOfTheRighteous();
};

class GirdleOfValorousDeeds : public Gear {
public:
  GirdleOfValorousDeeds();
};

class LionsHeartGirdle : public Gear {
public:
  LionsHeartGirdle();
};

class GirdleOfTheImmovable : public Gear {
public:
  GirdleOfTheImmovable();
};

class FaceguardOfDetermination : public Gear {
public:
  FaceguardOfDetermination();
};

class TankatronicGoggles : public Gear { // TO DO
public:
  TankatronicGoggles();
};

class X52TechniciansHelm : public Gear {
public:
  X52TechniciansHelm();
};

class MyrmidonsHeaddress : public Gear {
public:
  MyrmidonsHeaddress();
};

class HelmOfTheRighteous : public Gear {
public:
  HelmOfTheRighteous();
};

class ThalodiensCharm : public Gear {
public:
  ThalodiensCharm();
};

class MarkOfTheRavenguard : public Gear {
public:
  MarkOfTheRavenguard();
};

class MedallionOfTheValiantGuardian : public Gear {
public:
  MedallionOfTheValiantGuardian();
};

class EnchantedThoriumTorque : public Gear {
public:
  EnchantedThoriumTorque();
};

class EthereumTorqueOfTheKnight : public Gear {
public:
  EthereumTorqueOfTheKnight();
};

class EthereumTorqueOfTheChampion : public Gear {
public:
  EthereumTorqueOfTheChampion();
};

class ChainOfTheTwilightOwl : public Gear {
public:
  ChainOfTheTwilightOwl();
};

class LibramOfSaintsDeparted : public Gear {
public:
  LibramOfSaintsDeparted();
};

class LibramOfTruth : public Gear {
public:
  LibramOfTruth();
};

class DelicateEterniumRing : public Gear {
public:
  DelicateEterniumRing();
};

class ProtectorsMarkOfTheRedemption : public Gear {
public:
  ProtectorsMarkOfTheRedemption();
};

class DathRemarsRingOfDefense : public Gear {
public:
  DathRemarsRingOfDefense();
};

class WarchiefsMantle : public Gear {
public:
  WarchiefsMantle();
};

class KaylaansSpaulders : public Gear {
public:
  KaylaansSpaulders();
};

class BogstrokScaleCloak : public Gear {
public:
  BogstrokScaleCloak();
};

class ThoriumweaveCloak : public Gear {
public:
  ThoriumweaveCloak();
};

class CloakOfTheValiantDefender : public Gear {
public:
  CloakOfTheValiantDefender();
};

class BootsOfRighteousFortitude : public Gear {
public:
  BootsOfRighteousFortitude();
};

class AscendantsBoots : public Gear {
public:
  AscendantsBoots();
};

class BloodguardsGreaves : public Gear {
public:
  BloodguardsGreaves();
};

class StarcallersPlatedStompers : public Gear {
public:
  StarcallersPlatedStompers();
};

class FelsteelLeggings : public Gear {
public:
  FelsteelLeggings();
};

class GreavesOfTheShatterer : public Gear {
public:
  GreavesOfTheShatterer();
};

class LegguardsOfTheResoluteDefender : public Gear {
public:
  LegguardsOfTheResoluteDefender();
};

class LegplatesOfTheRighteous : public Gear {
public:
  LegplatesOfTheRighteous();
};

class KirinvarDefendersChausses : public Gear {
public:
  KirinvarDefendersChausses();
};

class BreastplateOfTheWarbringer : public Gear {
public:
  BreastplateOfTheWarbringer();
};

class BreastplateOfTheRighteous : public Gear {
public:
  BreastplateOfTheRighteous();
};

class ScavengedBreastplate : public Gear {
public:
  ScavengedBreastplate();
};

class ShatariWroughtArmguards : public Gear {
public:
  ShatariWroughtArmguards();
};

class VambracesOfDaring : public Gear {
public:
  VambracesOfDaring();
};

class ThadellsBracers : public Gear {
public:
  ThadellsBracers();
};

class JuniorTechnician3rdGradeBracers : public Gear {
public:
  JuniorTechnician3rdGradeBracers();
};

class GreatswordOfHorridDreams : public Gear {
public:
  GreatswordOfHorridDreams();
};

class ManaWrath : public Gear {
public:
  ManaWrath();
};

class CrystalforgedSword : public Gear {
public:
  CrystalforgedSword();
};

class GavelOfUnearthedSecrets : public Gear {
public:
  GavelOfUnearthedSecrets();
};

class CrestOfTheShatar : public Gear {
public:
  CrestOfTheShatar();
};

class PlatinumShieldOfTheValorous : public Gear {
public:
  PlatinumShieldOfTheValorous();
};

class NetherwingDefendersShield : public Gear {
public:
  NetherwingDefendersShield();
};

class OgrilaAegis : public Gear {
public:
  OgrilaAegis();
};

class ShieldOfTheWaywardFootman : public Gear {
public:
  ShieldOfTheWaywardFootman();
};

class WarhelmOfTheBold : public Gear {
public:
  WarhelmOfTheBold();
};

class ShoulderguardsOfTheBold : public Gear {
public:
  ShoulderguardsOfTheBold();
};

class BreastplateOfTheBold : public Gear {
public:
  BreastplateOfTheBold();
};

class GauntletsOfTheBold : public Gear {
public:
  GauntletsOfTheBold();
};

class ThatiasSelfCorrectingGauntlets : public Gear {
public:
  ThatiasSelfCorrectingGauntlets();
};

class GauntletsOfTheChosen : public Gear {
public:
  GauntletsOfTheChosen();
};

class DauntlessHandguards : public Gear {
public:
  DauntlessHandguards();
};

class LegplatesOfTheBold : public Gear {
public:
  LegplatesOfTheBold();
};

class ShatariWroughtGreaves : public Gear {
public:
  ShatariWroughtGreaves();
};

class SabatonsOfTheRighteousDefender : public Gear {
public:
  SabatonsOfTheRighteousDefender();
};

class AzureShieldOfColdarra : public Gear {
public:
  AzureShieldOfColdarra();
};

class BattlemastersAudacity : public Gear {
public:
  BattlemastersAudacity();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BonefistGauntlets : public Gear {
public:
  BonefistGauntlets();
};

class BracersOfTheAncientPhalanx : public Gear {
public:
  BracersOfTheAncientPhalanx();
};

class ChestguardOfTheStoicGuardian : public Gear {
public:
  ChestguardOfTheStoicGuardian();
};

class GirdleOfTheProtector : public Gear {
public:
  GirdleOfTheProtector();
};

class GnomereganAutoBlocker600 : public Gear {
public:
  GnomereganAutoBlocker600();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class LibramOfRepentance : public Gear {
public:
  LibramOfRepentance();
};

class UnwaveringLegguards : public Gear {
public:
  UnwaveringLegguards();
};

class CharmOfAlacrity : public Gear {
public:
  CharmOfAlacrity();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class FigurineOfTheColossus : public Gear {
public:
  FigurineOfTheColossus();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class IronscaleWarCloak : public Gear {
public:
  IronscaleWarCloak();
};

class SunguardLegplates : public Gear {
public:
  SunguardLegplates();
};

class ChestplateOfStoicisim : public Gear {
public:
  ChestplateOfStoicisim();
};

class GirdleOfTheFearless : public Gear {
public:
  GirdleOfTheFearless();
};

class InscribedLegplatesOfTheAldor : public Gear {
public:
  InscribedLegplatesOfTheAldor();
};

class ShattrathProtectoratesBreastplate : public Gear {
public:
  ShattrathProtectoratesBreastplate();
};

class BluesGreavesOfTheRighteousGuardian : public Gear {
public:
  BluesGreavesOfTheRighteousGuardian();
};

class RingOfTheStalwartProtector : public Gear {
public:
  RingOfTheStalwartProtector();
};

class RedHavocBoots : public Gear {
public:
  RedHavocBoots();
};

class MercilessGladiatorsGavel : public Gear {
public:
  MercilessGladiatorsGavel();
};

class GladiatorsShieldWall : public Gear {
public:
  GladiatorsShieldWall();
};

class BandOfUrsol : public Gear {
public:
  BandOfUrsol();
};

class RingOfTheSilverHand : public Gear {
public:
  RingOfTheSilverHand();
};

class RingOfTheStonebark : public Gear {
public:
  RingOfTheStonebark();
};

class BootsOfElusion : public Gear { // Karazhan
public:
  BootsOfElusion();
};

class SpectralBandOfInnervation : public Gear { // Karazhan
public:
  SpectralBandOfInnervation();
};

class VambracesOfCourage : public Gear { // Karazhan
public:
  VambracesOfCourage();
};

class RoyalCloakOfArathiKings : public Gear { // Karazhan
public:
  RoyalCloakOfArathiKings();
};

class ShadowCloakOfDalaran : public Gear { // Karazhan
public:
  ShadowCloakOfDalaran();
};

class CrimsonGirdleOfTheIndomitable : public Gear { // Karazhan
public:
  CrimsonGirdleOfTheIndomitable();
};

class BroochOfUnquenchableFury : public Gear { // Karazhan
public:
  BroochOfUnquenchableFury();
};

class MoroesLuckyPocketWatch : public Gear { // Karazhan
public:
  MoroesLuckyPocketWatch();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class IronGauntletsOfTheMaiden : public Gear { // Karazhan
public:
  IronGauntletsOfTheMaiden();
};

class BarbedChokerOfDiscipline : public Gear { // Karazhan
public:
  BarbedChokerOfDiscipline();
};

class EterniumGreathelm : public Gear { // Karazhan
public:
  EterniumGreathelm();
};

class WrynnDynastyGreaves : public Gear { // Karazhan
public:
  WrynnDynastyGreaves();
};

class GildedThoriumCloak : public Gear { // Karazhan
public:
  GildedThoriumCloak();
};

class ShermanarGreatRing : public Gear { // Karazhan
public:
  ShermanarGreatRing();
};

class MantleOfAbrahmis : public Gear { // Karazhan
public:
  MantleOfAbrahmis();
};

class PanzarTharBreastplate : public Gear { // Karazhan
public:
  PanzarTharBreastplate();
};

class IronstridersOfUrgency : public Gear { // Karazhan
public:
  IronstridersOfUrgency();
};

class ShieldOfImpenetrableDarkness : public Gear { // Karazhan
public:
  ShieldOfImpenetrableDarkness();
};

class BattlescarBoots : public Gear { // Karazhan
public:
  BattlescarBoots();
};

class MithrilChainOfHeroism : public Gear { // Karazhan
public:
  MithrilChainOfHeroism();
};

class JusticarFaceguard : public Gear { // Karazhan
public:
  JusticarFaceguard();
};

class JusticarShoulderguards : public Gear { // Gruul
public:
  JusticarShoulderguards();
};

class JusticarChestguard : public Gear { // Magtheridon
public:
  JusticarChestguard();
};

class JusticarHandguard : public Gear { // Karazhan
public:
  JusticarHandguard();
};

class JusticarLegguards : public Gear { // Gruul
public:
  JusticarLegguards();
};

class AldoriLegacyDefender : public Gear { // Gruul
public:
  AldoriLegacyDefender();
};

class ThunderingGreathelm : public Gear { // Magtheridon
public:
  ThunderingGreathelm();
};

class AdalsSignetOfDefense : public Gear { // Magtheridon
public:
  AdalsSignetOfDefense();
};

class VioletSignet : public Gear {
public:
  VioletSignet();
};

class SlikksCloakOfPlacation : public Gear {
public:
  SlikksCloakOfPlacation();
};

class IrontuskGirdle : public Gear {
public:
  IrontuskGirdle();
};

class IceguardBreastplate : public Gear {
public:
  IceguardBreastplate();
};

class IceguardHelm : public Gear {
public:
  IceguardHelm();
};

class IceguardLeggings : public Gear {
public:
  IceguardLeggings();
};

class PendantOfThawing : public Gear {
public:
  PendantOfThawing();
};

class TheFrozenEye : public Gear {
public:
  TheFrozenEye();
};

#endif
