#ifndef _EQUIPMENT_HH_
#define _EQUIPMENT_HH_

#include "enchantments.hh"
#include "gems.hh"
#include "stats.hh"
// #include "enums.hh"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class AbstractGear
{
public:
  AbstractGear();
  virtual ~AbstractGear() = 0;

  std::string get_base_name() const { return name_; }
  void set_source(Source in) { src_ = in; }
  void set_dungeon(Dungeon in) { dng_ = in; }
  void set_faction(Faction in) { rep_ = in; }
  void set_raid(Raid in) { raidInstance_ = in; }
  void set_ArmorClass(ArmorClass in) { armorClass_ = in; }
  void set_cd(double in) { cooldown_ = in; }
  void set_uptime(double in) { uptime_ = in; }
  void set_phase(unsigned int in) { phase_ = in; }
  void set_prim_stats(PrimaryStats in) { primary_stats = in; }
  void set_bonus_prim_stats(PrimaryStats in) { bonus_prim_stats = in; }
  void set_sec_stats(SecondaryStats in) { secondary_stats = in; }
  void set_bonus_sec_stats(SecondaryStats in) { bonus_sec_stats = in; }
  void set_stat(PrimaryAttributes inIndex, double inValue) { set_prim_stat(inIndex, inValue); }
  void set_stat(SecondaryAttributes inIndex, double inValue) { set_sec_stat(inIndex, inValue); }
  void set_prim_stat(PrimaryAttributes inIndex, double inValue) { primary_stats.set_stat(inIndex, inValue); }
  void set_sec_stat(SecondaryAttributes inIndex, double inValue) { secondary_stats.set_stat(inIndex, inValue); }
  void set_bonus_prim_stat(PrimaryAttributes inIndex, double inValue) { bonus_prim_stats.set_stat(inIndex, inValue); }
  void set_bonus_sec_stat(SecondaryAttributes inIndex, double inValue) { bonus_sec_stats.set_stat(inIndex, inValue); }
  void set_name(std::string in) { name_ = in; }
  void set_slot(Slot in) { slot_ = in; }
  void set_blue(unsigned int);
  void set_red(unsigned int);
  void set_yellow(unsigned int);
  void set_meta(unsigned int);
  void mark_as_set_piece() { setPiece_ = true; }
  void activate() { active_ = true; }
  void deactivate() { active_ = false; }
  void set_sockets(uint in){sockets_=in;}
  void setFreeMeta(bool in) { freeMeta_ = in; }
  void add_to_name(std::string in){name_ +=in;}
  void set_enchantment(Enchantment in, bool add_stats = true);
  void clearEnchantment();
  uint get_n_blue() const { return blue_; }
  uint get_n_red() const { return red_; }
  uint get_n_yellow() const { return yellow_; }
  uint get_n_meta() const { return meta_; }
  unsigned int get_sockets() const { return sockets_; }
  unsigned int get_free_sockets() const { return blue_ + yellow_ + red_ + meta_ - sockets_; }
  unsigned int get_phase() const { return phase_; }
  Source get_src() const { return src_; }
  Dungeon get_dng() const { return dng_; }
  Faction get_rep() const { return rep_; }
  ArmorClass get_ArmorClass() const { return armorClass_; }
  Raid get_raid() const {return raidInstance_;}
  bool is_active() const { return active_; }
  bool is_set_piece() const { return setPiece_; }
  bool is_enchanted() const { return enchanted_; }
  bool has_free_meta_place() const { return freeMeta_; }
  bool has_meta() const { return (bool)meta_; }
  Slot get_slot() const { return slot_; }
  double get_cooldown() const { return cooldown_; }
  double get_uptime() const { return uptime_; }
  double get_prim_stat(PrimaryAttributes in) const { return primary_stats.get_stat(in); }
  double get_bonus_prim_stat(PrimaryAttributes in) const { return bonus_prim_stats.get_stat(in); }
  double get_sec_stat(SecondaryAttributes in) const { return secondary_stats.get_stat(in); }
  double get_bonus_sec_stat(SecondaryAttributes in) const { return bonus_sec_stats.get_stat(in); }
  PrimaryStats get_prim_stats() const { return primary_stats; }
  PrimaryStats get_bonus_prim_stats() const { return bonus_prim_stats; }
  SecondaryStats get_sec_stats() const { return secondary_stats; }
  SecondaryStats get_bonus_sec_stats() const { return bonus_sec_stats; }
  Enchantment get_enchantment() const { return enchantment_; }

private:
  Enchantment enchantment_;
  unsigned int blue_, yellow_, red_, meta_;
  bool enchanted_;
  bool setPiece_;
  bool freeMeta_;
  bool active_;
  unsigned int sockets_;
  unsigned int phase_;
  double cooldown_;
  double uptime_;
  std::string name_;
  Source src_;
  Dungeon dng_;
  Faction rep_;
  Raid raidInstance_;
  Slot slot_;
  ArmorClass armorClass_;
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
  PrimaryStats bonus_prim_stats;
  SecondaryStats bonus_sec_stats;
};

class Gear : public AbstractGear
{
public:
  Gear();
  ~Gear();

  std::string get_name() const;
  std::string get_source() const;
  std::vector<Socket> gems;
  void add_gem(Socket gem, bool add_stats = true);
  void socket_bonus();
  bool computed_socket_bonus = false;
  bool equipped = false;
  bool has_gem(Socket *) const;
  std::vector<std::string> get_names() const;
  std::string get_values() const;
  Socket get_meta() const;
  void print() const;
  void operator=(Gear);
  bool operator<=(Gear);
  bool operator>=(Gear);
  friend std::ostream &operator<<(std::ostream &out, const Gear &gear)
  {
    out << gear.get_slot() << "\t" << gear.get_name() << "\t" << gear.get_prim_stats() << "\t" << gear.get_sec_stats() << "\t" << gear.get_bonus_prim_stats() << "\t" << gear.get_bonus_sec_stats() << "\t";
    if (gear.gems.size() > 0)
    {
      for (uint i = 0; i < gear.gems.size() - 1; i++)
      {
        out << gear.gems[i] << "\t";
      }
      out << gear.gems[gear.gems.size() - 1] << "\t";
      for (uint i = gear.gems.size(); i < 3; i++)
      {
        DummyGem tempGem;
        out << tempGem << "\t";
      }
    }
    else
    {
      DummyGem tempGem;
      out << tempGem << "\t" << tempGem << "\t" << tempGem << "\t";
    }
    out << gear.get_enchantment() << "\t" << (uint)gear.is_enchanted() << "\t" << (uint)gear.is_set_piece() << "\t" << (uint)gear.has_free_meta_place() << "\t" << gear.get_n_blue() << "\t" << gear.get_n_yellow() << "\t" << gear.get_n_red() << "\t" << gear.get_n_meta() << "\t" << gear.get_sockets() << "\t" << gear.get_cooldown() << "\t" << gear.get_uptime() << "\t" << gear.get_src() << "\t" << gear.get_dng() << "\t" << gear.get_rep() << "\t" << gear.get_raid() << "\t" << gear.get_phase();
    return out;
  }
  friend std::istream &operator>>(std::istream &in, Gear &gear)
  {
    std::string input_str(std::istreambuf_iterator<char>(in), {});
    std::vector<std::string> inputs;
    std::string delimiter = "\t";
    size_t pos = 0;
    while ((pos = input_str.find(delimiter)) != std::string::npos)
    {
      inputs.push_back(input_str.substr(0, pos));
      input_str.erase(0, pos + delimiter.length());
    }
    inputs.shrink_to_fit();
    gear.set_slot((Slot)std::stoi(inputs.front()));
    pos = inputs[1].find(" + ");
    gear.set_name(inputs[1].substr(0, pos));
    inputs.erase(inputs.begin(), inputs.begin() + 2);
    for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
    {
      gear.set_prim_stat((PrimaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
    {
      gear.set_sec_stat((SecondaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
    {
      gear.set_bonus_prim_stat((PrimaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
    {
      gear.set_bonus_sec_stat((SecondaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    std::vector<Socket> gems;
    gems.reserve(3);
    for (uint i = 0; i < 3; i++)
    {
      std::string temp_name = inputs.front();
      std::string temp_color = inputs[1];
      Socket tempSocket((Color)std::stoi(temp_color));
      tempSocket.set_name(temp_name);
      inputs.erase(inputs.begin(), inputs.begin() + 2);
      for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
      {
        tempSocket.set_prim_stat((PrimaryAttributes)i, std::stoi(inputs.front()));
        inputs.erase(inputs.begin());
      }
      for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
      {
        tempSocket.set_sec_stat((SecondaryAttributes)i, std::stoi(inputs.front()));
        inputs.erase(inputs.begin());
      }
      tempSocket.set_phase(std::stoi(inputs[0]));
      tempSocket.set_source((Source)std::stoi(inputs[1]));
      tempSocket.set_dungeon((Dungeon)std::stoi(inputs[2]));
      tempSocket.set_faction((Faction)std::stoi(inputs[3]));
      inputs.erase(inputs.begin(), inputs.begin() + 4);
      if (tempSocket.get_name() != "Dummy Gem")
      {
        gems.push_back(tempSocket);
      }
    }
    Enchantment temp_enchantment;
    temp_enchantment.set_name(inputs.front());
    temp_enchantment.set_slot((Slot)std::stoi(inputs[1]));
    inputs.erase(inputs.begin(), inputs.begin() + 2);
    for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
    {
      temp_enchantment.set_prim_stat((PrimaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
    {
      temp_enchantment.set_sec_stat((SecondaryAttributes)i, std::stoi(inputs.front()));
      inputs.erase(inputs.begin());
    }
    if (temp_enchantment.get_name() != "NoName")
    {
      gear.set_enchantment(temp_enchantment, false);
    }
    inputs.erase(inputs.begin());
    if (inputs.front() == "1")
    {
      gear.mark_as_set_piece();
    }
    inputs.erase(inputs.begin());
    gear.setFreeMeta(std::stoi(inputs[0]));
    gear.set_blue(std::stoi(inputs[1]));
    gear.set_yellow(std::stoi(inputs[2]));
    gear.set_red(std::stoi(inputs[3]));
    gear.set_meta(std::stoi(inputs[4]));
    gear.set_sockets(std::stoi(inputs[5]));
    gear.set_cd(std::stoi(inputs[6]));
    gear.set_uptime(std::stoi(inputs[7]));
    gear.set_source((Source)std::stoi(inputs[8]));
    gear.set_dungeon((Dungeon)std::stoi(inputs[9]));
    gear.set_faction((Faction)std::stoi(inputs[10]));
    gear.set_raid((Raid)std::stoi(inputs[11]));
    gear.set_phase(std::stoi(inputs[12]));
    inputs.erase(inputs.begin(), inputs.begin() + 13);
    for (uint i = 0; i < gems.size(); i++)
    {
      gear.add_gem(gems[i]);
    }
    if (inputs.size() > 0)
    {
      std::cout << "Error: Unused information (" << inputs.size() << ")" << std::endl;
      abort();
    }
    return in;
  }
};

class FelsteelHelm : public Gear
{
public:
  FelsteelHelm();
};

class NatashasBattleChain : public Gear
{
public:
  NatashasBattleChain();
};

class SpauldersOfTheRighteous : public Gear
{
public:
  SpauldersOfTheRighteous();
};

class CloakOfEternity : public Gear
{
public:
  CloakOfEternity();
};

class BracersOfTheGreenFortress : public Gear
{
public:
  BracersOfTheGreenFortress();
};

class FelsteelGloves : public Gear
{
public:
  FelsteelGloves();
};

class ShatariVindicatorsWaistguard : public Gear
{
public:
  ShatariVindicatorsWaistguard();
};

class TimewardensLeggings : public Gear
{
public:
  TimewardensLeggings();
};

class IronsoleClompers : public Gear
{
public:
  IronsoleClompers();
};

class IronBandOfTheUnbreakable : public Gear
{
public:
  IronBandOfTheUnbreakable();
};

class CenarionRingOfCasting : public Gear
{
public:
  CenarionRingOfCasting();
};

class ContinuumBlade : public Gear
{
public:
  ContinuumBlade();
};

class AegisOfTheSunbird : public Gear
{
public:
  AegisOfTheSunbird();
};

class AdamantineFigurine : public Gear
{
public:
  AdamantineFigurine();
  void activate();
  void deactivate();
};

class DabirisEnigma : public Gear
{
public:
  DabirisEnigma();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BootsOfTheRighteousPath : public Gear
{
public:
  BootsOfTheRighteousPath();
};

class BootsOfTheColossus : public Gear
{
public:
  BootsOfTheColossus();
};

class FleshBeastsMetalGreaves : public Gear
{
public:
  FleshBeastsMetalGreaves();
};

class EaglecrestWarboots : public Gear
{
public:
  EaglecrestWarboots();
};

class GladiatorsLamellarHelm : public Gear
{
public:
  GladiatorsLamellarHelm();
};

class HelmOfTheStalwartDefender : public Gear
{
public:
  HelmOfTheStalwartDefender();
};

class GreathelmOfTheUnbreakable : public Gear
{
public:
  GreathelmOfTheUnbreakable();
};

class OathkeepersHelm : public Gear
{
public:
  OathkeepersHelm();
};

class DevilsharkCape : public Gear
{
public:
  DevilsharkCape();
};

class FarstriderDefendersCloak : public Gear
{
public:
  FarstriderDefendersCloak();
};

class BurnooseOfShiftingAges : public Gear
{
public:
  BurnooseOfShiftingAges();
};

class BandOfImpenetrableDefenses : public Gear
{
public:
  BandOfImpenetrableDefenses();
};

class RingOfUnyieldingForce : public Gear
{
public:
  RingOfUnyieldingForce();
};

class YorsRevenge : public Gear
{
public:
  YorsRevenge();
};

class ElementiumBandOfTheSentry : public Gear
{
public:
  ElementiumBandOfTheSentry();
};

class LieutenantsSignetOfLordaeron : public Gear
{
public:
  LieutenantsSignetOfLordaeron();
};

class AndormusTear : public Gear
{
public:
  AndormusTear();
};

class NecklaceOfTheJuggernaut : public Gear
{
public:
  NecklaceOfTheJuggernaut();
};

class StrengthOfTheUntamed : public Gear
{
public:
  StrengthOfTheUntamed();
};

class MaladaarsBlessedChaplet : public Gear
{
public:
  MaladaarsBlessedChaplet();
};

class SteamHingeChainOfValor : public Gear
{
public:
  SteamHingeChainOfValor();
};

class DarkmoonCardVengeance : public Gear
{
public:
  DarkmoonCardVengeance();
};

class FanbladePauldrons : public Gear
{
public:
  FanbladePauldrons();
};

class SpauldersOfDementia : public Gear
{
public:
  SpauldersOfDementia();
};

class JadeSkullBreastplate : public Gear
{
public:
  JadeSkullBreastplate();
};

class VindicatorsHauberk : public Gear
{
public:
  VindicatorsHauberk();
};

class BracersOfDignity : public Gear
{
public:
  BracersOfDignity();
};

class AmberBandsOfTheAggressor : public Gear
{
public:
  AmberBandsOfTheAggressor();
};

class GauntletsOfTheIronTower : public Gear
{
public:
  GauntletsOfTheIronTower();
};

class GauntletsOfDissension : public Gear
{
public:
  GauntletsOfDissension();
};

class GauntletsOfTheRighteous : public Gear
{
public:
  GauntletsOfTheRighteous();
};

class GirdleOfValorousDeeds : public Gear
{
public:
  GirdleOfValorousDeeds();
};

class LionsHeartGirdle : public Gear
{
public:
  LionsHeartGirdle();
};

class GirdleOfTheImmovable : public Gear
{
public:
  GirdleOfTheImmovable();
};

class FaceguardOfDetermination : public Gear
{
public:
  FaceguardOfDetermination();
};

class TankatronicGoggles : public Gear
{ // TO DO
public:
  TankatronicGoggles();
};

class X52TechniciansHelm : public Gear
{
public:
  X52TechniciansHelm();
};

class MyrmidonsHeaddress : public Gear
{
public:
  MyrmidonsHeaddress();
};

class HelmOfTheRighteous : public Gear
{
public:
  HelmOfTheRighteous();
};

class ThalodiensCharm : public Gear
{
public:
  ThalodiensCharm();
};

class MarkOfTheRavenguard : public Gear
{
public:
  MarkOfTheRavenguard();
};

class MedallionOfTheValiantGuardian : public Gear
{
public:
  MedallionOfTheValiantGuardian();
};

class EnchantedThoriumTorque : public Gear
{
public:
  EnchantedThoriumTorque();
};

class EthereumTorqueOfTheKnight : public Gear
{
public:
  EthereumTorqueOfTheKnight();
};

class EthereumTorqueOfTheChampion : public Gear
{
public:
  EthereumTorqueOfTheChampion();
};

class ChainOfTheTwilightOwl : public Gear
{
public:
  ChainOfTheTwilightOwl();
};

class LibramOfSaintsDeparted : public Gear
{
public:
  LibramOfSaintsDeparted();
};

class LibramOfTruth : public Gear
{
public:
  LibramOfTruth();
};

class DelicateEterniumRing : public Gear
{
public:
  DelicateEterniumRing();
};

class ProtectorsMarkOfTheRedemption : public Gear
{
public:
  ProtectorsMarkOfTheRedemption();
};

class DathRemarsRingOfDefense : public Gear
{
public:
  DathRemarsRingOfDefense();
};

class WarchiefsMantle : public Gear
{
public:
  WarchiefsMantle();
};

class KaylaansSpaulders : public Gear
{
public:
  KaylaansSpaulders();
};

class BogstrokScaleCloak : public Gear
{
public:
  BogstrokScaleCloak();
};

class ThoriumweaveCloak : public Gear
{
public:
  ThoriumweaveCloak();
};

class CloakOfTheValiantDefender : public Gear
{
public:
  CloakOfTheValiantDefender();
};

class BootsOfRighteousFortitude : public Gear
{
public:
  BootsOfRighteousFortitude();
};

class AscendantsBoots : public Gear
{
public:
  AscendantsBoots();
};

class BloodguardsGreaves : public Gear
{
public:
  BloodguardsGreaves();
};

class StarcallersPlatedStompers : public Gear
{
public:
  StarcallersPlatedStompers();
};

class FelsteelLeggings : public Gear
{
public:
  FelsteelLeggings();
};

class GreavesOfTheShatterer : public Gear
{
public:
  GreavesOfTheShatterer();
};

class LegguardsOfTheResoluteDefender : public Gear
{
public:
  LegguardsOfTheResoluteDefender();
};

class LegplatesOfTheRighteous : public Gear
{
public:
  LegplatesOfTheRighteous();
};

class KirinvarDefendersChausses : public Gear
{
public:
  KirinvarDefendersChausses();
};

class BreastplateOfTheWarbringer : public Gear
{
public:
  BreastplateOfTheWarbringer();
};

class BreastplateOfTheRighteous : public Gear
{
public:
  BreastplateOfTheRighteous();
};

class ScavengedBreastplate : public Gear
{
public:
  ScavengedBreastplate();
};

class ShatariWroughtArmguards : public Gear
{
public:
  ShatariWroughtArmguards();
};

class VambracesOfDaring : public Gear
{
public:
  VambracesOfDaring();
};

class ThadellsBracers : public Gear
{
public:
  ThadellsBracers();
};

class JuniorTechnician3rdGradeBracers : public Gear
{
public:
  JuniorTechnician3rdGradeBracers();
};

class GreatswordOfHorridDreams : public Gear
{
public:
  GreatswordOfHorridDreams();
};

class ManaWrath : public Gear
{
public:
  ManaWrath();
};

class CrystalforgedSword : public Gear
{
public:
  CrystalforgedSword();
};

class GavelOfUnearthedSecrets : public Gear
{
public:
  GavelOfUnearthedSecrets();
};

class CrestOfTheShatar : public Gear
{
public:
  CrestOfTheShatar();
};

class PlatinumShieldOfTheValorous : public Gear
{
public:
  PlatinumShieldOfTheValorous();
};

class NetherwingDefendersShield : public Gear
{
public:
  NetherwingDefendersShield();
};

class OgrilaAegis : public Gear
{
public:
  OgrilaAegis();
};

class ShieldOfTheWaywardFootman : public Gear
{
public:
  ShieldOfTheWaywardFootman();
};

class WarhelmOfTheBold : public Gear
{
public:
  WarhelmOfTheBold();
};

class ShoulderguardsOfTheBold : public Gear
{
public:
  ShoulderguardsOfTheBold();
};

class BreastplateOfTheBold : public Gear
{
public:
  BreastplateOfTheBold();
};

class GauntletsOfTheBold : public Gear
{
public:
  GauntletsOfTheBold();
};

class ThatiasSelfCorrectingGauntlets : public Gear
{
public:
  ThatiasSelfCorrectingGauntlets();
};

class GauntletsOfTheChosen : public Gear
{
public:
  GauntletsOfTheChosen();
};

class DauntlessHandguards : public Gear
{
public:
  DauntlessHandguards();
};

class LegplatesOfTheBold : public Gear
{
public:
  LegplatesOfTheBold();
};

class ShatariWroughtGreaves : public Gear
{
public:
  ShatariWroughtGreaves();
};

class SabatonsOfTheRighteousDefender : public Gear
{
public:
  SabatonsOfTheRighteousDefender();
};

class AzureShieldOfColdarra : public Gear
{
public:
  AzureShieldOfColdarra();
};

class BattlemastersAudacity : public Gear
{
public:
  BattlemastersAudacity();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BonefistGauntlets : public Gear
{
public:
  BonefistGauntlets();
};

class BracersOfTheAncientPhalanx : public Gear
{
public:
  BracersOfTheAncientPhalanx();
};

class ChestguardOfTheStoicGuardian : public Gear
{
public:
  ChestguardOfTheStoicGuardian();
};

class GirdleOfTheProtector : public Gear
{
public:
  GirdleOfTheProtector();
};

class GnomereganAutoBlocker600 : public Gear
{
public:
  GnomereganAutoBlocker600();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class LibramOfRepentance : public Gear
{
public:
  LibramOfRepentance();
};

class UnwaveringLegguards : public Gear
{
public:
  UnwaveringLegguards();
};

class CharmOfAlacrity : public Gear
{
public:
  CharmOfAlacrity();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class FigurineOfTheColossus : public Gear
{
public:
  FigurineOfTheColossus();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class IronscaleWarCloak : public Gear
{
public:
  IronscaleWarCloak();
};

class SunguardLegplates : public Gear
{
public:
  SunguardLegplates();
};

class ChestplateOfStoicism : public Gear
{
public:
  ChestplateOfStoicism();
};

class GirdleOfTheFearless : public Gear
{
public:
  GirdleOfTheFearless();
};

class InscribedLegplatesOfTheAldor : public Gear
{
public:
  InscribedLegplatesOfTheAldor();
};

class ShattrathProtectoratesBreastplate : public Gear
{
public:
  ShattrathProtectoratesBreastplate();
};

class BluesGreavesOfTheRighteousGuardian : public Gear
{
public:
  BluesGreavesOfTheRighteousGuardian();
};

class RingOfTheStalwartProtector : public Gear
{
public:
  RingOfTheStalwartProtector();
};

class RedHavocBoots : public Gear
{
public:
  RedHavocBoots();
};

class MercilessGladiatorsGavel : public Gear
{
public:
  MercilessGladiatorsGavel();
};

class GladiatorsShieldWall : public Gear
{
public:
  GladiatorsShieldWall();
};

class BandOfUrsol : public Gear
{
public:
  BandOfUrsol();
};

class RingOfTheSilverHand : public Gear
{
public:
  RingOfTheSilverHand();
};

class RingOfTheStonebark : public Gear
{
public:
  RingOfTheStonebark();
};

class BootsOfElusion : public Gear
{ // Karazhan
public:
  BootsOfElusion();
};

class SpectralBandOfInnervation : public Gear
{ // Karazhan
public:
  SpectralBandOfInnervation();
};

class VambracesOfCourage : public Gear
{ // Karazhan
public:
  VambracesOfCourage();
};

class RoyalCloakOfArathiKings : public Gear
{ // Karazhan
public:
  RoyalCloakOfArathiKings();
};

class ShadowCloakOfDalaran : public Gear
{ // Karazhan
public:
  ShadowCloakOfDalaran();
};

class CrimsonGirdleOfTheIndomitable : public Gear
{ // Karazhan
public:
  CrimsonGirdleOfTheIndomitable();
};

class BroochOfUnquenchableFury : public Gear
{ // Karazhan
public:
  BroochOfUnquenchableFury();
};

class MoroesLuckyPocketWatch : public Gear
{ // Karazhan
public:
  MoroesLuckyPocketWatch();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class IronGauntletsOfTheMaiden : public Gear
{ // Karazhan
public:
  IronGauntletsOfTheMaiden();
};

class BarbedChokerOfDiscipline : public Gear
{ // Karazhan
public:
  BarbedChokerOfDiscipline();
};

class EterniumGreathelm : public Gear
{ // Karazhan
public:
  EterniumGreathelm();
};

class WrynnDynastyGreaves : public Gear
{ // Karazhan
public:
  WrynnDynastyGreaves();
};

class GildedThoriumCloak : public Gear
{ // Karazhan
public:
  GildedThoriumCloak();
};

class ShermanarGreatRing : public Gear
{ // Karazhan
public:
  ShermanarGreatRing();
};

class MantleOfAbrahmis : public Gear
{ // Karazhan
public:
  MantleOfAbrahmis();
};

class PanzarTharBreastplate : public Gear
{ // Karazhan
public:
  PanzarTharBreastplate();
};

class IronstridersOfUrgency : public Gear
{ // Karazhan
public:
  IronstridersOfUrgency();
};

class ShieldOfImpenetrableDarkness : public Gear
{ // Karazhan
public:
  ShieldOfImpenetrableDarkness();
};

class BattlescarBoots : public Gear
{ // Karazhan
public:
  BattlescarBoots();
};

class MithrilChainOfHeroism : public Gear
{ // Karazhan
public:
  MithrilChainOfHeroism();
};

class JusticarFaceguard : public Gear
{ // Karazhan
public:
  JusticarFaceguard();
};

class JusticarShoulderguards : public Gear
{ // Gruul
public:
  JusticarShoulderguards();
};

class JusticarChestguard : public Gear
{ // Magtheridon
public:
  JusticarChestguard();
};

class JusticarHandguard : public Gear
{ // Karazhan
public:
  JusticarHandguard();
};

class JusticarLegguards : public Gear
{ // Gruul
public:
  JusticarLegguards();
};

class AldoriLegacyDefender : public Gear
{ // Gruul
public:
  AldoriLegacyDefender();
};

class ThunderingGreathelm : public Gear
{ // Magtheridon
public:
  ThunderingGreathelm();
};

class AdalsSignetOfDefense : public Gear
{ // Magtheridon
public:
  AdalsSignetOfDefense();
};

class VioletSignet : public Gear
{
public:
  VioletSignet();
};

class SlikksCloakOfPlacation : public Gear
{
public:
  SlikksCloakOfPlacation();
};

class IrontuskGirdle : public Gear
{
public:
  IrontuskGirdle();
};

class IceguardBreastplate : public Gear
{
public:
  IceguardBreastplate();
};

class IceguardHelm : public Gear
{
public:
  IceguardHelm();
};

class IceguardLeggings : public Gear
{
public:
  IceguardLeggings();
};

class PendantOfThawing : public Gear
{
public:
  PendantOfThawing();
};

class TheFrozenEye : public Gear
{
public:
  TheFrozenEye();
};

class MurkbloodCoverOfTheBandit : public Gear
{
public:
  MurkbloodCoverOfTheBandit();
};

class SpauldersOfTheRing : public Gear
{
public:
  SpauldersOfTheRing();
};

class PerfectlyBalancedCape : public Gear
{
public:
  PerfectlyBalancedCape();
};

class HeavyClefthoofVest : public Gear
{
public:
  HeavyClefthoofVest();
};

class UmberhowlsCollar : public Gear
{
public:
  UmberhowlsCollar();
};

class SmugglersMitts : public Gear
{
public:
  SmugglersMitts();
};

class ManimalsCinch : public Gear
{
public:
  ManimalsCinch();
};

class HeavyClefthoofLeggings : public Gear
{
public:
  HeavyClefthoofLeggings();
};

class HeavyClefthoofBoots : public Gear
{
public:
  HeavyClefthoofBoots();
};

class OgreSlayersBand : public Gear
{
public:
  OgreSlayersBand();
};

class TerokkarTabletOfPrecision : public Gear
{
public:
  TerokkarTabletOfPrecision();
};

class RegalProtectorate : public Gear
{
public:
  RegalProtectorate();
};

class StaffOfBeasts : public Gear
{
public:
  StaffOfBeasts();
};

class GladiatorsDragonhideHelm : public Gear
{
public:
  GladiatorsDragonhideHelm();
};

class DeathblowX11Goggles : public Gear
{
public:
  DeathblowX11Goggles();
};

class HelmOfTheClaw : public Gear
{
public:
  HelmOfTheClaw();
};

class WastewalkerHelm : public Gear
{
public:
  WastewalkerHelm();
};

class CobrascaleHood : public Gear
{
public:
  CobrascaleHood();
};

class HelmOfAssassination : public Gear
{
public:
  HelmOfAssassination();
};

class StealthersHelmetOfSecondSight : public Gear
{
public:
  StealthersHelmetOfSecondSight();
};

class ExorcistsLeatherHelm : public Gear
{
public:
  ExorcistsLeatherHelm();
};

class StylinPurpleHat : public Gear
{
public:
  StylinPurpleHat();
};

class EnergizedHelm : public Gear
{
public:
  EnergizedHelm();
};

class NecklaceOfTheDeep : public Gear
{
public:
  NecklaceOfTheDeep();
};

class PendantOfTriumph : public Gear
{
public:
  PendantOfTriumph();
};

class BoneChainNecklace : public Gear
{
public:
  BoneChainNecklace();
};

class ChokerOfVileIntent : public Gear
{
public:
  ChokerOfVileIntent();
};

class MaimfistsChoker : public Gear
{
public:
  MaimfistsChoker();
};

class InsigniaOfTheMaghariHero : public Gear
{
public:
  InsigniaOfTheMaghariHero();
};

class GladiatorsDragonhideSpaulders : public Gear
{
public:
  GladiatorsDragonhideSpaulders();
};

class ShoulderpadsOfAssassination : public Gear
{
public:
  ShoulderpadsOfAssassination();
};

class WastewalkerShoulderpads : public Gear
{
public:
  WastewalkerShoulderpads();
};

class MantleOfPerenolde : public Gear
{
public:
  MantleOfPerenolde();
};

class MantleOfShadowyEmbrace : public Gear
{
public:
  MantleOfShadowyEmbrace();
};

class MantleOfTheUnforgiven : public Gear
{
public:
  MantleOfTheUnforgiven();
};

class TalbukHideSpaulders : public Gear
{
public:
  TalbukHideSpaulders();
};

class SergeantsHeavyCloak : public Gear
{
public:
  SergeantsHeavyCloak();
};

class BloodKnightWarCloak : public Gear
{
public:
  BloodKnightWarCloak();
};

class AuchenaiDeathShroud : public Gear
{
public:
  AuchenaiDeathShroud();
};

class DelicateGreenPoncho : public Gear
{
public:
  DelicateGreenPoncho();
};

class VengeanceWrap : public Gear
{
public:
  VengeanceWrap();
};

class NomadsWovenCloak : public Gear
{
public:
  NomadsWovenCloak();
};

class GladiatorsDragonhideTunic : public Gear
{
public:
  GladiatorsDragonhideTunic();
};

class WastewalkerTunic : public Gear
{
public:
  WastewalkerTunic();
};

class PrimalstrikeVest : public Gear
{
public:
  PrimalstrikeVest();
};

class TunicOfAssassination : public Gear
{
public:
  TunicOfAssassination();
};

class IllidariLordsTunic : public Gear
{
public:
  IllidariLordsTunic();
};

class VestOfVengeance : public Gear
{
public:
  VestOfVengeance();
};

class ChestguardOfTheProwler : public Gear
{
public:
  ChestguardOfTheProwler();
};

class AuchenaiMonksTunic : public Gear
{
public:
  AuchenaiMonksTunic();
};

class VindicatorsLeatherBracers : public Gear
{
public:
  VindicatorsLeatherBracers();
};

class ShardboundBracers : public Gear
{
public:
  ShardboundBracers();
};

class NightfallWristguards : public Gear
{
public:
  NightfallWristguards();
};

class PrimalstrikeBracers : public Gear
{
public:
  PrimalstrikeBracers();
};

class ShacklesOfQuagmirran : public Gear
{
public:
  ShacklesOfQuagmirran();
};

class SpymistresssWristguards : public Gear
{
public:
  SpymistresssWristguards();
};

class WastewalkerGloves : public Gear
{
public:
  WastewalkerGloves();
};

class GlovesOfTheUnbound : public Gear
{
public:
  GlovesOfTheUnbound();
};

class GladiatorsDragonhideGloves : public Gear
{
public:
  GladiatorsDragonhideGloves();
};

class VerdantGloves : public Gear
{
public:
  VerdantGloves();
};

class CobrascaleGloves : public Gear
{
public:
  CobrascaleGloves();
};

class HandgripsOfAssassination : public Gear
{
public:
  HandgripsOfAssassination();
};

class FelLeatherGloves : public Gear
{
public:
  FelLeatherGloves();
};

class GlovesOfTheNetherStalker : public Gear
{
public:
  GlovesOfTheNetherStalker();
};

class PredatoryGloves : public Gear
{
public:
  PredatoryGloves();
};

class VindicatorsLeatherBelt : public Gear
{
public:
  VindicatorsLeatherBelt();
};

class DunewindSash : public Gear
{
public:
  DunewindSash();
};

class PrimalstrikeBelt : public Gear
{
public:
  PrimalstrikeBelt();
};

class GirdleOfTheDeathdealer : public Gear
{
public:
  GirdleOfTheDeathdealer();
};

class EpochsWhisperingCinch : public Gear
{
public:
  EpochsWhisperingCinch();
};

class SocretharsGirdle : public Gear
{
public:
  SocretharsGirdle();
};

class NaaruBeltOfPrecision : public Gear
{
public:
  NaaruBeltOfPrecision();
};

class TreeMendersBelt : public Gear
{
public:
  TreeMendersBelt();
};

class EvasStrap : public Gear
{
public:
  EvasStrap();
};

class LeggingsOfTheUnrepentant : public Gear
{
public:
  LeggingsOfTheUnrepentant();
};

class WastewalkerLeggings : public Gear
{
public:
  WastewalkerLeggings();
};

class MidnightLegguards : public Gear
{
public:
  MidnightLegguards();
};

class GladiatorsDragonhideLegguards : public Gear
{
public:
  GladiatorsDragonhideLegguards();
};

class LeggingsOfAssassination : public Gear
{
public:
  LeggingsOfAssassination();
};

class FelLeatherLeggings : public Gear
{
public:
  FelLeatherLeggings();
};

class ForestwalkerKilt : public Gear
{
public:
  ForestwalkerKilt();
};

class OilclothBreeches : public Gear
{
public:
  OilclothBreeches();
};

class ClefthoofHideLeggings : public Gear
{
public:
  ClefthoofHideLeggings();
};

class VindicatorsDragonhideBoots : public Gear
{
public:
  VindicatorsDragonhideBoots();
};

class ShadowstepStriders : public Gear
{
public:
  ShadowstepStriders();
};

class BootsOfTheUnjust : public Gear
{
public:
  BootsOfTheUnjust();
};

class TheMastersTreads : public Gear
{
public:
  TheMastersTreads();
};

class FelboarHideShoes : public Gear
{
public:
  FelboarHideShoes();
};

class FelLeatherBoots : public Gear
{
public:
  FelLeatherBoots();
};

class FarahliteStuddedBoots : public Gear
{
public:
  FarahliteStuddedBoots();
};

class WindTradersBand : public Gear
{
public:
  WindTradersBand();
};

class RingOfArathiWarlords : public Gear
{
public:
  RingOfArathiWarlords();
};

class BandOfTriumph : public Gear
{
public:
  BandOfTriumph();
};

class RavenclawBand : public Gear
{
public:
  RavenclawBand();
};

class LongstridersLoop : public Gear
{
public:
  LongstridersLoop();
};

class ShapeshiftersSignet : public Gear
{
public:
  ShapeshiftersSignet();
};

class BroochOfTheImmortalKing : public Gear
{
public:
  BroochOfTheImmortalKing();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class IdolOfUrsoc : public Gear
{
public:
  IdolOfUrsoc();
};

class IdolOfBrutality : public Gear
{
public:
  IdolOfBrutality();
};

class IdolOfTheWild : public Gear
{
public:
  IdolOfTheWild();
};

class IdolOfTheRavenGoddess : public Gear
{
public:
  IdolOfTheRavenGoddess();
};

class GladiatorsMaul : public Gear
{
public:
  GladiatorsMaul();
};

class Earthwarden : public Gear
{
public:
  Earthwarden();
};

class FeralStaffOfLashing : public Gear
{
public:
  FeralStaffOfLashing();
};

class StaffOfNaturalFury : public Gear
{
public:
  StaffOfNaturalFury();
};

class VindicatorsLeatherBoots : public Gear
{
public:
  VindicatorsLeatherBoots();
};

class VindicatorsDragonhideBracers : public Gear
{
public:
  VindicatorsDragonhideBracers();
};

class VindicatorsDragonhideBelt : public Gear
{
public:
  VindicatorsDragonhideBelt();
};

class TalismanOfTheHorde : public Gear
{
public:
  TalismanOfTheHorde();
};

class MaskOfTheDeceiver : public Gear
{
public:
  MaskOfTheDeceiver();
};

class CowlOfBeastlyRage : public Gear
{
public:
  CowlOfBeastlyRage();
};

class NynjahsTabiBoots : public Gear
{
public:
  NynjahsTabiBoots();
};

class BroochOfDeftness : public Gear
{
public:
  BroochOfDeftness();
};

class ShallowgraveTrousers : public Gear
{
public:
  ShallowgraveTrousers();
};

class TrickstersStickyfingers : public Gear
{
public:
  TrickstersStickyfingers();
};

class MasterAssassinWristwraps : public Gear
{
public:
  MasterAssassinWristwraps();
};

class VestmentsOfHibernation : public Gear
{
public:
  VestmentsOfHibernation();
};

class BandOfTheSwiftPaw : public Gear
{
public:
  BandOfTheSwiftPaw();
};

class FootwrapsOfWildEncroachment : public Gear
{
public:
  FootwrapsOfWildEncroachment();
};

class WaistguardOfTheGreatBeast : public Gear
{
public:
  WaistguardOfTheGreatBeast();
};

class LibramOfDivinePurpose : public Gear
{
public:
  LibramOfDivinePurpose();
};

class LibramOfTheEternalRest : public Gear
{
public:
  LibramOfTheEternalRest();
};

class IconOfUnyieldingCourage : public Gear
{
public:
  IconOfUnyieldingCourage();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BloodlustBrooch : public Gear
{
public:
  BloodlustBrooch();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class BadgeOfTenacity : public Gear
{
public:
  BadgeOfTenacity();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class AlchemistsStone : public Gear
{
public:
  AlchemistsStone();

private:
  bool active = false;
};

class DrakeFangTalisman : public Gear
{
public:
  DrakeFangTalisman();

private:
  bool active = false;
};

class AbacusOfViolentOdds : public Gear
{
public:
  AbacusOfViolentOdds();
  void activate();
  void deactivate();

private:
  bool active = false;
};

class MarkOfTyranny : public Gear
{
public:
  MarkOfTyranny();
};

class TimelapseShard : public Gear
{
public:
  TimelapseShard();
};

class FleshHandlersGauntlets : public Gear
{
public:
  FleshHandlersGauntlets();
};

class ShattrathLeggings : public Gear
{
public:
  ShattrathLeggings();
};

class TamelessBreeches : public Gear
{
public:
  TamelessBreeches();
};

class LeggingsOfTheBetrayed : public Gear
{
public:
  LeggingsOfTheBetrayed();
};

class WarpscaleLeggings : public Gear
{
public:
  WarpscaleLeggings();
};

class GlovesOfImmortalDusk : public Gear
{
public:
  GlovesOfImmortalDusk();
};

class SunrageTreads : public Gear
{
public:
  SunrageTreads();
};

class CircletOfRestlessDreams : public Gear
{
public:
  CircletOfRestlessDreams();
};

class AgedCoreLeatherGloves : public Gear
{
public:
  AgedCoreLeatherGloves();
};

class CarapaceOfSunAndShadow : public Gear
{
public:
  CarapaceOfSunAndShadow();
};

class SwiftstrikeShoulders : public Gear
{
public:
  SwiftstrikeShoulders();
};

class SwiftstrikeBracers : public Gear
{
public:
  SwiftstrikeBracers();
};

class HandwrapsOfTheAggressor : public Gear
{
public:
  HandwrapsOfTheAggressor();
};

class EmbraceOfEverlastingProwess : public Gear
{
public:
  EmbraceOfEverlastingProwess();
};

class ShardOfContempt : public Gear
{
public:
  ShardOfContempt();
};
#endif
