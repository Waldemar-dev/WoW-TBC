#include "equipment.hh"

Gear::Gear() {
  blue = 0;
  yellow = 0;
  red = 0;
  meta = 0;
}
void Gear::operator=(Gear b) {
  slot = b.slot;
  name = b.name;
  primary_stats = b.primary_stats;
  secondary_stats = b.secondary_stats;
  bonus_prim_stats = b.bonus_prim_stats;
  bonus_sec_stats = b.bonus_sec_stats;
  gems = b.gems;
  computed_socket_bonus = b.computed_socket_bonus;
  equipped = b.equipped;
  enchantment = b.enchantment;
  enchanted = b.is_enchanted();
  sockets = b.get_sockets();
}

void Gear::add_gem(Socket gem) {
  if (gems.size() < sockets) {
    if (meta > 0 && gem.color[0] == "meta") {
      bool add = true;
      for (uint i = 0; i < gems.size(); i++) {
        if (gems[i].color[0] == "meta") {
          add = false;
        }
      }
      if (add) {
        gems.push_back(gem);
      }
    } else if (meta > 0 && gem.color[0] != "meta") {
      if (gems.size() <= sockets - meta) {
        gems.push_back(gem);
        primary_stats = primary_stats + gem.primary_stats;
        secondary_stats = secondary_stats + gem.secondary_stats;
      }
    } else if (meta == 0 && gem.color[0] == "meta") {
      return;
    } else {
      gems.push_back(gem);
      if (find(gem.color.begin(), gem.color.end(), "meta") == gem.color.end()) {
        primary_stats = primary_stats + gem.primary_stats;
        secondary_stats = secondary_stats + gem.secondary_stats;
      }
    }
  }
  socket_bonus();
}

void Gear::set_meta(unsigned int in) {
  meta = in;
  sockets = blue + red + yellow + meta;
}

void Gear::set_blue(unsigned int in) {
  blue = in;
  sockets = blue + red + yellow + meta;
}

void Gear::set_red(unsigned int in) {
  red = in;
  sockets = blue + red + yellow + meta;
}

void Gear::set_yellow(unsigned int in) {
  yellow = in;
  sockets = blue + red + yellow + meta;
}

void Gear::socket_bonus() {
  if (gems.size() == sockets) {
    unsigned int temp_blue = 0;
    unsigned int temp_red = 0;
    unsigned int temp_yellow = 0;
    unsigned int temp_meta = 0;
    for (uint i = 0; i < gems.size(); i++) {
      for (uint j = 0; j < gems[i].color.size(); j++) {
        if (gems[i].color[j] == "blue") {
          temp_blue++;
        } else if (gems[i].color[j] == "red") {
          temp_red++;
        } else if (gems[i].color[j] == "yellow") {
          temp_yellow++;
        } else if (gems[i].color[j] == "meta" && gems[i].active) {
          temp_meta++;
        }
      }
    }
    if (temp_blue >= blue && temp_red >= red && temp_yellow >= yellow && temp_meta == meta && !computed_socket_bonus) {
      primary_stats = primary_stats + bonus_prim_stats;
      secondary_stats = secondary_stats + bonus_sec_stats;
      computed_socket_bonus = true;
    }
  }
}

void Gear::set_enchantment(Enchantment in) {
  if (!enchanted) {
    enchantment = in;
    primary_stats = primary_stats + in.primary_stats;
    secondary_stats = secondary_stats + in.secondary_stats;
    enchanted = true;
  } else {
    cout << name << " already enchanted" << endl;
  }
}

string Gear::get_name() {
  string result = name;
  if (enchanted) {
    result = result + " + " + enchantment.name;
  }
  for (uint i = 0; i < gems.size(); i++) {
    result = result + " + " + gems[i].name;
  }
  return result;
}

FelsteelHelm::FelsteelHelm() {
  primary_stats.armor = 1284;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 33;
  slot = "Head";
  name = "Felsteel Helm";
  set_blue(2);
  set_red(1);
  bonus_sec_stats.hit_rating = 4;
}

NatashasBattleChain::NatashasBattleChain() {
  primary_stats.stamina = 37;
  secondary_stats.defense_rating = 13;
  secondary_stats.block_value = 15;
  slot = "Neck";
  name = "Natasha's Battle Chain";
}

SpauldersOfTheRighteous::SpauldersOfTheRighteous() {
  primary_stats.armor = 873;
  primary_stats.stamina = 22;
  primary_stats.intelligence = 22;
  secondary_stats.defense_rating = 20;
  secondary_stats.spellpower = 15;
  slot = "Shoulder";
  name = "Spaulders Of The Righteous";
  set_blue(1);
  set_red(1);
  bonus_sec_stats.defense_rating = 3;
}

CloakOfEternity::CloakOfEternity() {
  primary_stats.stamina = 36;
  primary_stats.armor = 76;
  secondary_stats.defense_rating = 23;
  slot = "Back";
  name = "Cloak Of Eternity";
}

BracersOfTheGreenFortress::BracersOfTheGreenFortress() {
  primary_stats.armor = 581;
  primary_stats.stamina = 39;
  secondary_stats.defense_rating = 17;
  secondary_stats.dodge_rating = 10;
  slot = "Wrist";
  name = "Bracers Of The Green Fortress";
}

FelsteelGloves::FelsteelGloves() {
  primary_stats.armor = 943;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 25;
  slot = "Hands";
  name = "Felsteel Gloves";
  set_blue(1);
  set_red(1);
  bonus_sec_stats.parry_rating = 3;
}

ShatariVindicatorsWaistguard::ShatariVindicatorsWaistguard() {
  primary_stats.armor = 655;
  primary_stats.stamina = 33;
  secondary_stats.block_value = 29;
  secondary_stats.defense_rating = 20;
  secondary_stats.block_chance_rating = 24;
  slot = "Waist";
  name = "Shatari Vindicator's Waistguard";
}

TimewardensLeggings::TimewardensLeggings() {
  primary_stats.armor = 1019;
  primary_stats.stamina = 57;
  secondary_stats.defense_rating = 18;
  secondary_stats.dodge_rating = 11;
  slot = "Legs";
  name = "Timewarden's Leggings";
  set_blue(1);
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.block_value = 6;
}

IronsoleClompers::IronsoleClompers() {
  primary_stats.armor = 600;
  primary_stats.stamina = 19;
  primary_stats.strength = 14;
  secondary_stats.defense_rating = 19;
  slot = "Feet";
  name = "Ironsole Clompers";
  set_red(1);
  set_blue(1);
  bonus_sec_stats.defense_rating = 3;
}

IronBandOfTheUnbreakable::IronBandOfTheUnbreakable() {
  primary_stats.armor = 170;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 17;
  slot = "Ring";
  name = "Iron Band Of The Unbreakable";
}

CenarionRingOfCasting::CenarionRingOfCasting() {
  primary_stats.stamina = 24;
  primary_stats.intelligence = 16;
  secondary_stats.spellpower = 18;
  slot = "Ring";
  name = "Cenarion Ring Of Casting";
}

ContinuumBlade::ContinuumBlade() {
  primary_stats.weapondamage = (84 + 45) / 2;
  primary_stats.attack_speed = 1.8;
  primary_stats.stamina = 35;
  secondary_stats.spellpower = 122;
  secondary_stats.spellhit_rating = 8;
  slot = "Mainhand";
  name = "Continuum Blade";
}

AegisOfTheSunbird::AegisOfTheSunbird() {
  primary_stats.armor = 3806;
  secondary_stats.block_value = 86 + 29;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 19;
  slot = "Offhand";
  name = "Aegis Of The Sunbird";
}

AdamantineFigurine::AdamantineFigurine() {
  secondary_stats.defense_rating = 32;
  slot = "Trinket";
  name = "Adamantine Figurine";
  set_uptime(20.0);
  set_cd(120.0);
}

void AdamantineFigurine::activate() {
  if (!active) {
    active = true;
    primary_stats.armor = 1281;
  }
}

void AdamantineFigurine::deactivate() {
  if (active) {
    active = false;
    primary_stats.armor = 0;
  }
}

DabirisEnigma::DabirisEnigma() {
  secondary_stats.defense_rating = 30;
  slot = "Trinket";
  name = "Dabiri's Enigma";
  set_uptime(15.0);
  set_cd(90.0);
}

void DabirisEnigma::activate() {
  if (!active) {
    active = true;
    secondary_stats.block_chance_rating = 126;
  }
}

void DabirisEnigma::deactivate() {
  if (active) {
    active = false;
    secondary_stats.block_chance_rating = 0;
  }
}

BootsOfTheRighteousPath::BootsOfTheRighteousPath() {
  primary_stats.armor = 955;
  primary_stats.stamina = 34;
  primary_stats.intelligence = 26;
  secondary_stats.defense_rating = 23;
  secondary_stats.spellpower = 29;
  slot = "Feet";
  name = "Boots Of The Righteous Path";
}

BootsOfTheColossus::BootsOfTheColossus() {
  primary_stats.armor = 800;
  primary_stats.stamina = 27;
  primary_stats.strength = 22;
  secondary_stats.defense_rating = 19;
  slot = "Feet";
  name = "BootsOfTheColossus";
  set_blue(1);
  set_yellow(1);
  bonus_sec_stats.defense_rating = 3;
}

FleshBeastsMetalGreaves::FleshBeastsMetalGreaves() {
  primary_stats.armor = 680;
  primary_stats.stamina = 25;
  secondary_stats.defense_rating = 18;
  secondary_stats.dodge_rating = 28;
  slot = "Feet";
  name = "Flesh Beast's Metal Greaves";
}

EaglecrestWarboots::EaglecrestWarboots() {
  primary_stats.armor = 955;
  primary_stats.strength = 29;
  primary_stats.agility = 21;
  primary_stats.stamina = 33;
  secondary_stats.defense_rating = 24;
  slot = "Feet";
  name = "Eaglecrest Warboots";
}

GladiatorsLamellarHelm::GladiatorsLamellarHelm() {
  primary_stats.armor = 1257;
  primary_stats.stamina = 57;
  primary_stats.intelligence = 21;
  secondary_stats.resilience_rating = 32;
  secondary_stats.spellcrit_rating = 22;
  secondary_stats.spellpower = 34;
  slot = "Head";
  name = "Gladiator's Lamellar Helm";
  set_red(1);
  set_meta(1);
  bonus_sec_stats.resilience_rating = 4;
}

HelmOfTheStalwartDefender::HelmOfTheStalwartDefender() {
  primary_stats.armor = 1366;
  primary_stats.stamina = 47;
  secondary_stats.resilience_rating = 23;
  secondary_stats.defense_rating = 23;
  slot = "Head";
  name = "Helm Of The Stalwart Defender";
  set_blue(1);
  set_red(1);
  set_yellow(1);
  bonus_prim_stats.strength = 4;
}

GreathelmOfTheUnbreakable::GreathelmOfTheUnbreakable() {
  primary_stats.armor = 922;
  primary_stats.stamina = 48;
  primary_stats.strength = 36;
  secondary_stats.defense_rating = 30;
  slot = "Head";
  name = "Greathelm Of The Unbreakable";
}

OathkeepersHelm::OathkeepersHelm() {
  primary_stats.armor = 1080;
  primary_stats.stamina = 40;
  primary_stats.intelligence = 22;
  secondary_stats.spellpower = 27;
  secondary_stats.defense_rating = 15;
  secondary_stats.mp5 = 10;
  slot = "Head";
  name = "Oathkeeper's Helm";
  set_red(1);
  set_blue(1);
  set_yellow(1);
  bonus_sec_stats.spellhit_rating = 4;
}

DevilsharkCape::DevilsharkCape() {
  primary_stats.armor = 78;
  primary_stats.stamina = 22;
  secondary_stats.defense_rating = 20;
  secondary_stats.dodge_rating = 18;
  secondary_stats.block_value = 30;
  slot = "Back";
  name = "Devilshark Cape";
}

FarstriderDefendersCloak::FarstriderDefendersCloak() {
  primary_stats.armor = 267;
  primary_stats.stamina = 30;
  secondary_stats.block_value = 39;
  slot = "Back";
  name = "Farstrider Defender's Cloak";
}

BurnooseOfShiftingAges::BurnooseOfShiftingAges() {
  primary_stats.armor = 216;
  primary_stats.stamina = 15;
  secondary_stats.defense_rating = 26;
  secondary_stats.block_value = 29;
  slot = "Back";
  name = "Burnoose Of Shifting Ages";
}

BandOfImpenetrableDefenses::BandOfImpenetrableDefenses() {
  primary_stats.stamina = 36;
  secondary_stats.defense_rating = 26;
  slot = "Ring";
  name = "Band of Impenetrable Defenses";
}

RingOfUnyieldingForce::RingOfUnyieldingForce() {
  primary_stats.armor = 294;
  primary_stats.stamina = 31;
  secondary_stats.defense_rating = 22;
  slot = "Ring";
  name = "Ring of Unyielding Force";
}

YorsRevenge::YorsRevenge() {
  primary_stats.armor = 190;
  primary_stats.stamina = 30;
  secondary_stats.defense_rating = 20;
  slot = "Ring";
  name = "Yor's Revenge";
}

ElementiumBandOfTheSentry::ElementiumBandOfTheSentry() {
  primary_stats.stamina = 24;
  secondary_stats.defense_rating = 20;
  secondary_stats.dodge_rating = 19;
  slot = "Ring";
  name = "Elementium Band Of The Sentry";
}

LieutenantsSignetOfLordaeron::LieutenantsSignetOfLordaeron() {
  primary_stats.armor = 143;
  primary_stats.stamina = 30;
  secondary_stats.dodge_rating = 21;
  slot = "Ring";
  name = "Lieutenant’s Signet of Lordaeron";
}

AndormusTear::AndormusTear() {
  secondary_stats.defense_rating = 10;
  secondary_stats.dodge_rating = 26;
  secondary_stats.block_chance_rating = 15;
  slot = "Ring";
  name = "Andormu’s Tear";
}

NecklaceOfTheJuggernaut::NecklaceOfTheJuggernaut() {
  primary_stats.stamina = 33;
  primary_stats.agility = 19;
  secondary_stats.defense_rating = 22;
  slot = "Neck";
  name = "Necklace of the Juggernaut";
}

StrengthOfTheUntamed::StrengthOfTheUntamed() {
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 19;
  secondary_stats.dodge_rating = 18;
  slot = "Neck";
  name = "Strength of the Untamed";
}

MaladaarsBlessedChaplet::MaladaarsBlessedChaplet() {
  primary_stats.stamina = 30;
  secondary_stats.dodge_rating = 12;
  secondary_stats.defense_rating = 20;
  slot = "Neck";
  name = "Maladaar’s Blessed Chaplet";
}

SteamHingeChainOfValor::SteamHingeChainOfValor() {
  primary_stats.stamina = 26;
  secondary_stats.block_chance_rating = 19;
  secondary_stats.block_value = 29;
  slot = "Neck";
  name = "Steam-Hinge Chain of Valor";
}

DarkmoonCardVengeance::DarkmoonCardVengeance() {
  primary_stats.stamina = 51;
  slot = "Trinket";
  name = "Darkmoon Card: Vengeance";
}

FanbladePauldrons::FanbladePauldrons() {
  primary_stats.armor = 873;
  primary_stats.strength = 16;
  primary_stats.stamina = 22;
  secondary_stats.defense_rating = 20;
  secondary_stats.parry_rating = 15;
  slot = "Shoulder";
  name = "Fanblade Pauldrons";
  set_blue(1);
  set_red(1);
  bonus_sec_stats.parry_rating = 3;
}

SpauldersOfDementia::SpauldersOfDementia() {
  primary_stats.armor = 1042;
  primary_stats.stamina = 34;
  primary_stats.strength = 25;
  primary_stats.agility = 24;
  secondary_stats.defense_rating = 23;
  slot = "Shoulder";
  name = "Spaulders of Dementia";
}

JadeSkullBreastplate::JadeSkullBreastplate() {
  primary_stats.armor = 1164;
  primary_stats.strength = 30;
  primary_stats.stamina = 50;
  secondary_stats.defense_rating = 25;
  secondary_stats.block_chance_rating = 23;
  slot = "Chest";
  name = "Jade-Skull Breastplate";
}

VindicatorsHauberk::VindicatorsHauberk() {
  primary_stats.armor = 1164;
  primary_stats.stamina = 39;
  secondary_stats.dodge_rating = 19;
  secondary_stats.defense_rating = 46;
  slot = "Chest";
  name = "Vindicator’s Hauberk";
}

BracersOfDignity::BracersOfDignity() {
  primary_stats.armor = 608;
  primary_stats.stamina = 30;
  primary_stats.intelligence = 12;
  secondary_stats.defense_rating = 21;
  secondary_stats.spellpower = 20;
  slot = "Wrist";
  name = "Bracers of Dignity";
}

AmberBandsOfTheAggressor::AmberBandsOfTheAggressor() {
  primary_stats.armor = 608;
  primary_stats.strength = 22;
  primary_stats.agility = 18;
  primary_stats.stamina = 25;
  secondary_stats.defense_rating = 15;
  slot = "Wrist";
  name = "Amber Bands of the Aggressor";
}

GauntletsOfTheIronTower::GauntletsOfTheIronTower() {
  primary_stats.armor = 831;
  primary_stats.stamina = 30;
  secondary_stats.resilience_rating = 26;
  secondary_stats.defense_rating = 20;
  slot = "Hands";
  name = "Gauntlets of the Iron Tower";
  set_blue(1);
  set_yellow(1);
  bonus_prim_stats.strength = 3;
}

GauntletsOfDissension::GauntletsOfDissension() {
  primary_stats.armor = 868;
  primary_stats.strength = 24;
  primary_stats.agility = 23;
  primary_stats.stamina = 36;
  secondary_stats.defense_rating = 24;
  slot = "Hands";
  name = "Gauntlets of Dissension";
}

GauntletsOfTheRighteous::GauntletsOfTheRighteous() {
  primary_stats.armor = 728;
  primary_stats.stamina = 22;
  primary_stats.intelligence = 20;
  secondary_stats.spellpower = 22;
  secondary_stats.defense_rating = 19;
  secondary_stats.mp5 = 8;
  slot = "Hands";
  name = "Guantlets of the Righteous";
}

GirdleOfValorousDeeds::GirdleOfValorousDeeds() {
  primary_stats.armor = 782;
  primary_stats.stamina = 37;
  primary_stats.intelligence = 22;
  secondary_stats.defense_rating = 24;
  secondary_stats.block_chance_rating = 16;
  secondary_stats.spellpower = 21;
  slot = "Waist";
  name = "Girdle of Valorous Deeds";
}

LionsHeartGirdle::LionsHeartGirdle() {
  primary_stats.armor = 782;
  primary_stats.strength = 26;
  primary_stats.agility = 22;
  primary_stats.stamina = 31;
  secondary_stats.defense_rating = 23;
  slot = "Waist";
  name = "Lion’s Heart Girdle";
}

GirdleOfTheImmovable::GirdleOfTheImmovable() {
  primary_stats.armor = 655;
  primary_stats.strength = 17;
  primary_stats.stamina = 33;
  secondary_stats.defense_rating = 18;
  secondary_stats.block_chance_rating = 12;
  slot = "Waist";
  name = "Girdle of the Immovable";
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.dodge_rating = 3;
}

FaceguardOfDetermination::FaceguardOfDetermination() {
  primary_stats.armor = 1129;
  primary_stats.stamina = 36;
  secondary_stats.defense_rating = 32;
  secondary_stats.dodge_rating = 24;
  secondary_stats.block_chance_rating = 24;
  slot = "Head";
  name = "Faceguard of Determination";
  set_meta(1);
  set_blue(1);
  bonus_prim_stats.stamina = 6;
}

TankatronicGoggles::TankatronicGoggles() {
  primary_stats.armor = 1296;
  primary_stats.stamina = 67;
  secondary_stats.defense_rating = 38;
  secondary_stats.hit_rating = 13;
  secondary_stats.dodge_rating = 22;
  slot = "Head";
  name = "Tankatronic Goggles";
  set_meta(1);
  set_yellow(1);
  bonus_prim_stats.stamina = 6;
}

X52TechniciansHelm::X52TechniciansHelm() {
  primary_stats.armor = 875;
  primary_stats.stamina = 36;
  primary_stats.strength = 38;
  primary_stats.intelligence = 16;
  secondary_stats.defense_rating = 16;
  secondary_stats.mp5 = 7;
  slot = "Head";
  name = "X-52 Technician’s Helm";
}

MyrmidonsHeaddress::MyrmidonsHeaddress() {
  primary_stats.armor = 946;
  primary_stats.stamina = 37;
  primary_stats.strength = 17;
  secondary_stats.defense_rating = 33;
  slot = "Head";
  name = "Myrmidon's Headdress";
  set_meta(1);
  set_red(1);
  bonus_prim_stats.strength = 4;
}

HelmOfTheRighteous::HelmOfTheRighteous() {
  primary_stats.armor = 946;
  primary_stats.stamina = 30;
  primary_stats.intelligence = 20;
  secondary_stats.defense_rating = 21;
  secondary_stats.spellpower = 23;
  secondary_stats.mp5 = 6;
  slot = "Head";
  name = "Helm of the Righteous";
  set_meta(1);
  set_yellow(1);
  bonus_prim_stats.intelligence = 4;
}

ThalodiensCharm::ThalodiensCharm() {
  primary_stats.stamina = 37;
  secondary_stats.defense_rating = 15;
  secondary_stats.block_value = 15;
  slot = "Neck";
  name = "Thalodien's Charm";
}

MarkOfTheRavenguard::MarkOfTheRavenguard() {
  primary_stats.stamina = 40;
  secondary_stats.defense_rating = 17;
  slot = "Neck";
  name = "Mark of the Ravenguard";
}

MedallionOfTheValiantGuardian::MedallionOfTheValiantGuardian() {
  primary_stats.stamina = 27;
  primary_stats.strength = 17;
  secondary_stats.defense_rating = 18;
  slot = "Neck";
  name = "Medallion of the Valiant Guardian";
}

EnchantedThoriumTorque::EnchantedThoriumTorque() {
  primary_stats.stamina = 27;
  secondary_stats.dodge_rating = 21;
  secondary_stats.hit_rating = 16;
  slot = "Neck";
  name = "Enchanted Thorium Torque";
}

EthereumTorqueOfTheKnight::EthereumTorqueOfTheKnight() {
  primary_stats.stamina = 27;
  secondary_stats.spellpower = 21;
  secondary_stats.defense_rating = 18;
  slot = "Neck";
  name = "Ethereum Torque of the Knight";
}

EthereumTorqueOfTheChampion::EthereumTorqueOfTheChampion() {
  primary_stats.stamina = 27;
  primary_stats.strength = 18;
  secondary_stats.defense_rating = 18;
  slot = "Neck";
  name = "Ethereum Torque of the Champion";
}

ChainOfTheTwilightOwl::ChainOfTheTwilightOwl() {
  primary_stats.intelligence = 19;
  secondary_stats.defense_rating = 18;
  secondary_stats.spellpower = 21;
  secondary_stats.spellcrit_rating = 45;
  slot = "Neck";
  name = "Chain of the Twilight Owl";
}

LibramOfSaintsDeparted::LibramOfSaintsDeparted() {
  slot = "Libram";
  name = "Libram of Saints Departed";
}

LibramOfTruth::LibramOfTruth() {
  slot = "Libram";
  name = "Libram of Truth";
}

DelicateEterniumRing::DelicateEterniumRing() {
  primary_stats.stamina = 15;
  primary_stats.agility = 25;
  secondary_stats.dodge_rating = 16;
  slot = "Ring";
  name = "Delicate Eternium Ring";
}

ProtectorsMarkOfTheRedemption::ProtectorsMarkOfTheRedemption() {
  primary_stats.stamina = 22;
  secondary_stats.defense_rating = 25;
  secondary_stats.block_value = 15;
  slot = "Ring";
  name = "Protector's Mark of the Redemption";
}

DathRemarsRingOfDefense::DathRemarsRingOfDefense() {
  primary_stats.stamina = 15;
  secondary_stats.block_chance_rating = 15;
  secondary_stats.block_value = 39;
  slot = "Ring";
  name = "Dath'Remar's Ring of Defense";
}

WarchiefsMantle::WarchiefsMantle() {
  primary_stats.armor = 786;
  primary_stats.strength = 23;
  primary_stats.stamina = 27;
  secondary_stats.parry_rating = 18;
  slot = "Shoulder";
  name = "Warchief's Mantle";
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.crit_rating = 3;
}

KaylaansSpaulders::KaylaansSpaulders() {
  primary_stats.armor = 787;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 18;
  secondary_stats.spellpower = 30;
  slot = "Shoulder";
  name = "Kaylaan's Spaulders";
}

BogstrokScaleCloak::BogstrokScaleCloak() {
  primary_stats.armor = 271;
  primary_stats.stamina = 22;
  secondary_stats.defense_rating = 16;
  slot = "Back";
  name = "BogstrokScale Cloak";
}

ThoriumweaveCloak::ThoriumweaveCloak() {
  primary_stats.armor = 390;
  primary_stats.stamina = 35;
  slot = "Back";
  name = "Thoriumweave Cloak";
}

CloakOfTheValiantDefender::CloakOfTheValiantDefender() {
  primary_stats.armor = 262;
  primary_stats.stamina = 21;
  secondary_stats.defense_rating = 15;
  slot = "Back";
  name = "Cloak of the Valiant Defender";
}

BootsOfRighteousFortitude::BootsOfRighteousFortitude() {
  primary_stats.armor = 800;
  primary_stats.stamina = 37;
  primary_stats.intelligence = 14;
  secondary_stats.defense_rating = 19;
  secondary_stats.spellpower = 29;
  slot = "Feet";
  name = "Boots of Righteous Fortitude";
}

AscendantsBoots::AscendantsBoots() {
  primary_stats.armor = 722;
  primary_stats.stamina = 22;
  secondary_stats.defense_rating = 21;
  secondary_stats.block_value = 23;
  slot = "Feet";
  name = "Ascendant's Boots";
  set_blue(1);
  set_yellow(1);
  bonus_prim_stats.stamina = 4;
}

BloodguardsGreaves::BloodguardsGreaves() {
  primary_stats.armor = 685;
  primary_stats.stamina = 42;
  primary_stats.strength = 11;
  secondary_stats.defense_rating = 16;
  slot = "Feet";
  name = "Bloodguard’s Greaves";
}

StarcallersPlatedStompers::StarcallersPlatedStompers() {
  primary_stats.armor = 722;
  primary_stats.stamina = 21;
  primary_stats.intelligence = 14;
  secondary_stats.defense_rating = 13;
  secondary_stats.spellpower = 17;
  slot = "Feet";
  name = "Starcaller’s Plated Stompers";
}

FelsteelLeggings::FelsteelLeggings() {
  primary_stats.armor = 1257;
  primary_stats.stamina = 39;
  secondary_stats.defense_rating = 33;
  slot = "Legs";
  name = "Felsteel Leggings";
  set_blue(1);
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.dodge_rating = 4;
}

GreavesOfTheShatterer::GreavesOfTheShatterer() {
  primary_stats.armor = 1019;
  primary_stats.stamina = 37;
  primary_stats.strength = 25;
  secondary_stats.defense_rating = 25;
  slot = "Legs";
  name = "Greaves of the Shatterer";
  set_blue(1);
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.block_value = 6;
}

LegguardsOfTheResoluteDefender::LegguardsOfTheResoluteDefender() {
  primary_stats.armor = 942;
  primary_stats.stamina = 42;
  primary_stats.agility = 23;
  secondary_stats.defense_rating = 31;
  secondary_stats.parry_rating = 21;
  slot = "Legs";
  name = "Legguards of the Resolute Defender";
}

LegplatesOfTheRighteous::LegplatesOfTheRighteous() {
  primary_stats.armor = 1019;
  primary_stats.stamina = 27;
  primary_stats.intelligence = 24;
  secondary_stats.defense_rating = 26;
  secondary_stats.spellpower = 29;
  secondary_stats.mp5 = 11;
  slot = "Legs";
  name = "Legplates of the Righteous";
}

KirinvarDefendersChausses::KirinvarDefendersChausses() {
  primary_stats.armor = 895;
  primary_stats.intelligence = 18;
  primary_stats.stamina = 27;
  secondary_stats.defense_rating = 19;
  secondary_stats.spellpower = 31;
  secondary_stats.mp5 = 8;
  slot = "Legs";
  name = "Kirin’var Defender’s Chausses";
}

BreastplateOfTheWarbringer::BreastplateOfTheWarbringer() {
  primary_stats.armor = 1048;
  primary_stats.stamina = 45;
  secondary_stats.hit_rating = 30;
  secondary_stats.defense_rating = 31;
  slot = "Chest";
  name = "Breastplate of the Warbringer";
}

BreastplateOfTheRighteous::BreastplateOfTheRighteous() {
  primary_stats.armor = 1164;
  primary_stats.stamina = 30;
  primary_stats.intelligence = 28;
  secondary_stats.defense_rating = 20;
  secondary_stats.spellpower = 24;
  slot = "Chest";
  name = "Breastplate of the Righteous";
  set_blue(1);
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.mp5 = 2;
}

ScavengedBreastplate::ScavengedBreastplate() {
  primary_stats.armor = 996;
  primary_stats.stamina = 36;
  primary_stats.strength = 14;
  primary_stats.agility = 15;
  secondary_stats.defense_rating = 25;
  secondary_stats.hit_rating = 14;
  slot = "Chest";
  name = "Scavenged Breastplate";
}

ShatariWroughtArmguards::ShatariWroughtArmguards() {
  primary_stats.armor = 509;
  primary_stats.strength = 20;
  primary_stats.stamina = 18;
  secondary_stats.defense_rating = 12;
  slot = "Wrist";
  name = "Sha’tari Wrought Armguards";
  set_yellow(1);
  bonus_prim_stats.stamina = 3;
}

VambracesOfDaring::VambracesOfDaring() {
  primary_stats.armor = 509;
  primary_stats.stamina = 26;
  primary_stats.strength = 18;
  secondary_stats.defense_rating = 11;
  secondary_stats.block_value = 23;
  slot = "Wrist";
  name = "Vambraces of Daring";
}

ThadellsBracers::ThadellsBracers() {
  primary_stats.armor = 448;
  primary_stats.intelligence = 12;
  primary_stats.stamina = 21;
  secondary_stats.defense_rating = 9;
  secondary_stats.spellpower = 17;
  slot = "Wrist";
  name = "Thadell’s Bracers";
}

JuniorTechnician3rdGradeBracers::JuniorTechnician3rdGradeBracers() {
  primary_stats.armor = 436;
  primary_stats.stamina = 24;
  primary_stats.agility = 10;
  secondary_stats.defense_rating = 11;
  secondary_stats.hit_rating = 11;
  slot = "Wrist";
  name = "Junior Technician 3rd Grade Bracers";
}

GreatswordOfHorridDreams::GreatswordOfHorridDreams() {
  primary_stats.stamina = 15;
  primary_stats.intelligence = 14;
  secondary_stats.spellhit_rating = 14;
  secondary_stats.spellpower = 131;
  slot = "Mainhand";
  name = "Greatsword Of Horrid Dreams";
}

ManaWrath::ManaWrath() {
  primary_stats.stamina = 24;
  primary_stats.intelligence = 18;
  secondary_stats.spellpower = 127;
  slot = "Mainhand";
  name = "Mana Wrath";
}

CrystalforgedSword::CrystalforgedSword() {
  primary_stats.stamina = 30;
  primary_stats.intelligence = 8;
  secondary_stats.block_chance_rating = 11;
  secondary_stats.spellpower = 122;
  slot = "Mainhand";
  name = "Crystalforged Sword";
}

GavelOfUnearthedSecrets::GavelOfUnearthedSecrets() {
  primary_stats.stamina = 24;
  primary_stats.intelligence = 16;
  secondary_stats.spellcrit_rating = 15;
  secondary_stats.spellpower = 160;
  slot = "Mainhand";
  name = "Gavel of Unearthed Secrets";
}

CrestOfTheShatar::CrestOfTheShatar() {
  primary_stats.armor = 4465;
  primary_stats.stamina = 19;
  secondary_stats.block_value = 108 + 25;
  secondary_stats.defense_rating = 13;
  slot = "Offhand";
  name = "Crest of the Sha’tar";
  set_blue(2);
  bonus_sec_stats.dodge_rating = 3;
}

PlatinumShieldOfTheValorous::PlatinumShieldOfTheValorous() {
  primary_stats.armor = 3711;
  primary_stats.stamina = 33;
  secondary_stats.block_value = 83;
  secondary_stats.defense_rating = 24;
  slot = "Offhand";
  name = "Platinum Shield of the Valorous";
}

NetherwingDefendersShield::NetherwingDefendersShield() {
  primary_stats.armor = 3615;
  primary_stats.stamina = 21;
  primary_stats.intelligence = 13;
  secondary_stats.defense_rating = 13;
  secondary_stats.block_value = 80 + 19;
  secondary_stats.spellpower = 15;
  slot = "Offhand";
  name = "Netherwing Defender's Shield";
}

OgrilaAegis::OgrilaAegis() {
  primary_stats.armor = 3806;
  primary_stats.stamina = 18;
  secondary_stats.defense_rating = 23;
  secondary_stats.block_value = 86 + 23;
  slot = "Offhand";
  name = "Ogri'la Aegis";
  set_red(2);
  bonus_sec_stats.block_chance_rating = 3;
}

ShieldOfTheWaywardFootman::ShieldOfTheWaywardFootman() {
  primary_stats.armor = 3329;
  primary_stats.stamina = 24;
  secondary_stats.defense_rating = 16;
  secondary_stats.block_chance_rating = 18;
  secondary_stats.block_value = 71;
  slot = "Offhand";
  name = "Shield of the Wayward Footman";
}

WarhelmOfTheBold::WarhelmOfTheBold() {
  primary_stats.armor = 946;
  primary_stats.strength = 24;
  primary_stats.agility = 22;
  primary_stats.stamina = 23;
  secondary_stats.defense_rating = 20;
  set_blue(1);
  set_meta(1);
  bonus_prim_stats.strength = 4;
  name = "Warhelm of the Bold";
  slot = "Head";
}

ShoulderguardsOfTheBold::ShoulderguardsOfTheBold() {
  primary_stats.armor = 873;
  primary_stats.strength = 25;
  primary_stats.stamina = 25;
  secondary_stats.defense_rating = 17;
  set_yellow(1);
  set_blue(1);
  bonus_sec_stats.dodge_rating = 3;
  name = "Shoulderguards of the Bold";
  slot = "Shoulder";
}

BreastplateOfTheBold::BreastplateOfTheBold() {
  primary_stats.armor = 1164;
  primary_stats.strength = 23;
  primary_stats.agility = 21;
  primary_stats.stamina = 33;
  secondary_stats.defense_rating = 19;
  set_red(2);
  set_blue(1);
  bonus_sec_stats.defense_rating = 4;
  name = "Breastplate of the Bold";
  slot = "Chest";
}

GauntletsOfTheBold::GauntletsOfTheBold() {
  name = "Gauntlets of the Bold";
  slot = "Hands";
  primary_stats.armor = 728;
  primary_stats.strength = 17;
  primary_stats.agility = 16;
  primary_stats.stamina = 31;
  secondary_stats.defense_rating = 14;
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.parry_rating = 3;
}

ThatiasSelfCorrectingGauntlets::ThatiasSelfCorrectingGauntlets() {
  name = "Thatia's Self-Correcting Gauntlets";
  slot = "Hands";
  primary_stats.armor = 728;
  primary_stats.strength = 16;
  primary_stats.stamina = 35;
  secondary_stats.defense_rating = 18;
  secondary_stats.block_value = 40;
}

GauntletsOfTheChosen::GauntletsOfTheChosen() {
  name = "Gauntlets of the Chosen";
  slot = "Hands";
  primary_stats.armor = 728;
  primary_stats.stamina = 30;
  primary_stats.agility = 15;
  secondary_stats.defense_rating = 35;
}

DauntlessHandguards::DauntlessHandguards() {
  name = "Dauntless Handguards";
  slot = "Hands";
  primary_stats.armor = 722;
  primary_stats.stamina = 36;
  secondary_stats.block_chance_rating = 25;
  secondary_stats.block_value = 39;
}

LegplatesOfTheBold::LegplatesOfTheBold() {
  name = "Legplates of the Bold";
  slot = "Legs";
  primary_stats.armor = 1019;
  primary_stats.strength = 31;
  primary_stats.agility = 19;
  primary_stats.stamina = 45;
  secondary_stats.defense_rating = 26;
}

ShatariWroughtGreaves::ShatariWroughtGreaves() {
  name = "Sha'tari Wrought Greaves";
  slot = "Feet";
  primary_stats.armor = 800;
  primary_stats.strength = 24;
  primary_stats.agility = 21;
  primary_stats.stamina = 22;
  set_red(1);
  set_blue(1);
  bonus_sec_stats.resilience_rating = 3;
}

SabatonsOfTheRighteousDefender::SabatonsOfTheRighteousDefender() {
  name = "Sabatons of the Righteous Defender";
  slot = "Feet";
  primary_stats.armor = 1105;
  primary_stats.stamina = 45;
  secondary_stats.spellhit_rating = 18;
  secondary_stats.defense_rating = 18;
  secondary_stats.block_value = 30;
  secondary_stats.spellpower = 23;
  set_red(1);
  set_blue(1);
  bonus_prim_stats.stamina = 4;
}

AzureShieldOfColdarra::AzureShieldOfColdarra() {
  primary_stats.armor = 4668;
  primary_stats.stamina = 31;
  secondary_stats.block_value = 115 + 34;
  secondary_stats.defense_rating = 22;
  name = "Azure-Shield of Coldarra";
  slot = "Offhand";
}

BattlemastersAudacity::BattlemastersAudacity() {
  name = "Battlemaster's Audacity";
  slot = "Trinket";
  secondary_stats.spellpower = 48;
  set_uptime(15.0);
  set_cd(180.0);
}

void BattlemastersAudacity::activate() {
  if (!active) {
    primary_stats.health = 1751;
    active = true;
  }
}

void BattlemastersAudacity::deactivate() {
  if (active) {
    primary_stats.health = 0;
    active = false;
  }
}

BonefistGauntlets::BonefistGauntlets() {
  name = "Bonefist Gauntlets";
  slot = "Hands";
  primary_stats.armor = 1005;
  primary_stats.stamina = 51;
  secondary_stats.parry_rating = 30;
  secondary_stats.hit_rating = 21;
  set_red(1);
  set_blue(1);
  bonus_prim_stats.stamina = 4;
}

BracersOfTheAncientPhalanx::BracersOfTheAncientPhalanx() {
  name = "Bracers of the Ancient Phalanx";
  slot = "Wrist";
  primary_stats.armor = 703;
  primary_stats.stamina = 45;
  secondary_stats.defense_rating = 23;
  secondary_stats.expertise_rating = 22;
}

ChestguardOfTheStoicGuardian::ChestguardOfTheStoicGuardian() {
  name = "Chestguard of the Stoic Guardian";
  slot = "Chest";
  primary_stats.armor = 1607;
  primary_stats.stamina = 60;
  secondary_stats.defense_rating = 22;
  secondary_stats.dodge_rating = 38;
  secondary_stats.spellpower = 36;
  set_red(1);
  set_yellow(1);
  set_blue(1);
  bonus_prim_stats.stamina = 6;
}

GirdleOfTheProtector::GirdleOfTheProtector() {
  primary_stats.armor = 904;
  primary_stats.stamina = 40;
  secondary_stats.dodge_rating = 27;
  secondary_stats.defense_rating = 11;
  secondary_stats.spellhit_rating = 18;
  secondary_stats.spellpower = 24;
  set_blue(1);
  set_yellow(1);
  bonus_prim_stats.stamina = 4;
  name = "Girdle of the Protector";
  slot = "Waist";
}

GnomereganAutoBlocker600::GnomereganAutoBlocker600() {
  secondary_stats.block_value = 59;
  name = "Gnomeregan Auto-Blocker 600";
  slot = "Trinket";
  set_uptime(20.0);
  set_cd(120.0);
}

void GnomereganAutoBlocker600::activate() {
  if (!active) {
    secondary_stats.block_value += 200;
    active = true;
  }
}

void GnomereganAutoBlocker600::deactivate() {
  if (active) {
    secondary_stats.block_value -= 200;
    active = false;
  }
}

LibramOfRepentance::LibramOfRepentance() {
  name = "Libram of Repentance";
  slot = "Libram";
}

UnwaveringLegguards::UnwaveringLegguards() {
  name = "Unwavering Legguards";
  slot = "Legs";
  primary_stats.armor = 1406;
  primary_stats.stamina = 73;
  secondary_stats.defense_rating = 22;
  secondary_stats.block_value = 60;
  secondary_stats.block_chance_rating = 30;
  set_red(1);
  set_yellow(1);
  set_blue(1);
  bonus_prim_stats.stamina = 6;
}

CharmOfAlacrity::CharmOfAlacrity() {
  name = "Charm of Alacrity";
  slot = "Trinket";
  set_uptime(10.0);
  set_cd(90.0);
}

void CharmOfAlacrity::activate() {
  if (!active) {
    secondary_stats.dodge_rating = 192;
    active = true;
  }
}

void CharmOfAlacrity::deactivate() {
  if (active) {
    secondary_stats.dodge_rating = 0;
    active = false;
  }
}

FigurineOfTheColossus::FigurineOfTheColossus() {
  name = "Figurine of the Colossus";
  slot = "Trinket";
  secondary_stats.block_chance_rating = 32;
  set_cd(120.0);
  set_uptime(20.0);
}

void FigurineOfTheColossus::activate() {
  if (!active) {
    active = true;
  }
}

void FigurineOfTheColossus::deactivate() {
  if (active) {
    active = false;
  }
}

IronscaleWarCloak::IronscaleWarCloak() {
  primary_stats.stamina = 26;
  primary_stats.armor = 78;
  secondary_stats.block_chance_rating = 19;
  secondary_stats.block_value = 29;
  slot = "Back";
  name = "Ironscale War Cloak";
}

SunguardLegplates::SunguardLegplates() {
  primary_stats.armor = 1544;
  primary_stats.stamina = 78;
  secondary_stats.dodge_rating = 35;
  secondary_stats.defense_rating = 43;
  secondary_stats.expertise_rating = 23;
  slot = "Legs";
  name = "Sunguard Legplates";
  set_blue(1);
  set_red(1);
  bonus_sec_stats.dodge_rating = 3;
}

ChestplateOfStoicisim::ChestplateOfStoicisim() {
  primary_stats.armor = 1765;
  primary_stats.stamina = 78;
  secondary_stats.dodge_rating = 34;
  secondary_stats.defense_rating = 51;
  secondary_stats.block_value = 39;
  slot = "Chest";
  name = "Chestplate of Stoicisim";
  set_red(1);
  bonus_prim_stats.stamina = 3;
}

GirdleOfTheFearless::GirdleOfTheFearless() {
  primary_stats.armor = 993;
  primary_stats.stamina = 58;
  secondary_stats.hit_rating = 23;
  secondary_stats.defense_rating = 34;
  secondary_stats.expertise_rating = 22;
  slot = "Waist";
  name = "Girdle of the Fearless";
  set_red(1);
  bonus_prim_stats.stamina = 3;
}

InscribedLegplatesOfTheAldor::InscribedLegplatesOfTheAldor() {
  primary_stats.armor = 1544;
  primary_stats.stamina = 78;
  secondary_stats.dodge_rating = 43;
  secondary_stats.defense_rating = 25;
  secondary_stats.spellpower = 37;
  slot = "Legs";
  name = "Inscribed Legplates of the Aldor";
  set_red(1);
  set_yellow(1);
  bonus_prim_stats.stamina = 4;
}

ShattrathProtectoratesBreastplate::ShattrathProtectoratesBreastplate() {
  primary_stats.armor = 1765;
  primary_stats.stamina = 78;
  secondary_stats.spellhit_rating = 34;
  secondary_stats.defense_rating = 26;
  secondary_stats.spellpower = 60;
  slot = "Chest";
  name = "Shattrath Protectorate's Breastplate";
  set_blue(1);
  bonus_sec_stats.dodge_rating = 2;
}

BluesGreavesOfTheRighteousGuardian::BluesGreavesOfTheRighteousGuardian() {
  primary_stats.armor = 1213;
  primary_stats.stamina = 58;
  secondary_stats.spellhit_rating = 23;
  secondary_stats.block_chance_rating = 34;
  secondary_stats.spellpower = 26;
  slot = "Feet";
  name = "Blue's Greaves of the Righteous Guardian";
  set_red(1);
  bonus_prim_stats.stamina = 3;
}

RingOfTheStalwartProtector::RingOfTheStalwartProtector() {
  primary_stats.armor = 392;
  primary_stats.stamina = 45;
  secondary_stats.dodge_rating = 28;
  slot = "Ring";
  name = "Ring of the Stalwart Protector";
}

RedHavocBoots::RedHavocBoots() {
  primary_stats.armor = 1105;
  primary_stats.stamina = 49;
  secondary_stats.defense_rating = 32;
  secondary_stats.block_value = 30;
  secondary_stats.block_chance_rating = 25;
  name = "Red Havoc Boots";
  slot = "Feet";
}

MercilessGladiatorsGavel::MercilessGladiatorsGavel() {
  primary_stats.stamina = 27;
  primary_stats.intelligence = 18;
  primary_stats.weapondamage = (18.0 + 113.0) / 2.0;
  primary_stats.attack_speed = 1.6;
  secondary_stats.spellpower = 225;
  secondary_stats.spellhit_rating = 15;
  secondary_stats.resilience_rating = 18;
  slot = "Mainhand";
  name = "Merciless Gladiator's Gavel";
}

GladiatorsShieldWall::GladiatorsShieldWall() {
  primary_stats.armor = 5197;
  primary_stats.stamina = 45;
  secondary_stats.block_value = 134;
  secondary_stats.resilience_rating = 29;
  name = "Gladiator's Shield Wall";
  slot = "Offhand";
}

BootsOfElusion::BootsOfElusion() {
  primary_stats.armor = 997;
  primary_stats.stamina = 34;
  secondary_stats.defense_rating = 23;
  secondary_stats.dodge_rating = 38;
  name = "Boots of Elusion";
  slot = "Feet";
}

SpectralBandOfInnervation::SpectralBandOfInnervation() {
  primary_stats.stamina = 22;
  primary_stats.intelligence = 24;
  secondary_stats.spellpower = 29;
  name = "Spectral Band of Innervation";
  slot = "Ring";
}

VambracesOfCourage::VambracesOfCourage() {
  primary_stats.armor = 634;
  primary_stats.stamina = 33;
  secondary_stats.defense_rating = 15;
  secondary_stats.block_value = 33;
  set_yellow(1);
  bonus_sec_stats.dodge_rating = 2;
  name = "Vambraces of Courage";
  slot = "Wrist";
}

RoyalCloakOfArathiKings::RoyalCloakOfArathiKings() {
  primary_stats.armor = 97;
  primary_stats.strength = 26;
  primary_stats.stamina = 31;
  secondary_stats.hit_rating = 16;
  name = "Royal Cloak of Arathi Kings";
  slot = "Back";
}

ShadowCloakOfDalaran::ShadowCloakOfDalaran() {
  primary_stats.intelligence = 18;
  primary_stats.armor = 97;
  primary_stats.stamina = 19;
  secondary_stats.spellpower = 36;
  name = "Shadow Cloak of Dalaran";
  slot = "Back";
}

CrimsonGirdleOfTheIndomitable::CrimsonGirdleOfTheIndomitable() {
  primary_stats.armor = 816;
  primary_stats.strength = 16;
  primary_stats.stamina = 36;
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.parry_rating = 3;
  secondary_stats.defense_rating = 24;
  secondary_stats.block_chance_rating = 20;
  name = "Crimson Girdle of the Indomitable";
  slot = "Waist";
}

BroochOfUnquenchableFury::BroochOfUnquenchableFury() {
  primary_stats.stamina = 24;
  primary_stats.intelligence = 21;
  secondary_stats.spellhit_rating = 15;
  secondary_stats.spellpower = 26;
  name = "Brooch of Unquenchable Fury";
  slot = "Neck";
}

MoroesLuckyPocketWatch::MoroesLuckyPocketWatch() {
  secondary_stats.dodge_rating = 38;
  name = "Moroes' Lucky Pocket Watch";
  slot = "Trinket";
  set_uptime(10.0);
  set_cd(120.0);
}

void MoroesLuckyPocketWatch::activate() {
  if (!active) {
    active = true;
    secondary_stats.dodge_rating += 300;
  }
}

void MoroesLuckyPocketWatch::deactivate() {
  if (active) {
    active = false;
    secondary_stats.dodge_rating -= 300;
  }
}

IronGauntletsOfTheMaiden::IronGauntletsOfTheMaiden() {
  primary_stats.armor = 906;
  primary_stats.stamina = 39;
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.block_chance_rating = 4;
  secondary_stats.defense_rating = 16;
  secondary_stats.block_chance_rating = 17;
  secondary_stats.block_value = 38;
  name = "Iron Gauntlets of the Maiden";
  slot = "Hands";
}

BarbedChokerOfDiscipline::BarbedChokerOfDiscipline() {
  primary_stats.stamina = 39;
  secondary_stats.dodge_rating = 21;
  secondary_stats.defense_rating = 16;
  slot = "Neck";
  name = "Barbed Choker of Discipline";
}

EterniumGreathelm::EterniumGreathelm() {
  primary_stats.armor = 1178;
  primary_stats.strength = 31;
  primary_stats.stamina = 48;
  set_red(1);
  set_yellow(1);
  set_blue(1);
  bonus_sec_stats.dodge_rating = 4;
  secondary_stats.defense_rating = 34;
  name = "Eternium Greathelm";
  slot = "Head";
}

WrynnDynastyGreaves::WrynnDynastyGreaves() {
  primary_stats.armor = 1269;
  primary_stats.strength = 24;
  primary_stats.stamina = 48;
  set_red(1);
  set_yellow(2);
  bonus_prim_stats.stamina = 6;
  secondary_stats.defense_rating = 27;
  secondary_stats.dodge_rating = 29;
  name = "Wrynn Dynasty Greaves";
  slot = "Legs";
}

GildedThoriumCloak::GildedThoriumCloak() {
  primary_stats.armor = 385;
  primary_stats.stamina = 30;
  secondary_stats.defense_rating = 24;
  name = "Gilded Thorium Cloak";
  slot = "Back";
}

ShermanarGreatRing::ShermanarGreatRing() {
  primary_stats.armor = 223;
  primary_stats.stamina = 36;
  secondary_stats.defense_rating = 23;
  name = "Shermanar Great Ring";
  slot = "Ring";
}

MantleOfAbrahmis::MantleOfAbrahmis() {
  primary_stats.armor = 1087;
  primary_stats.strength = 21;
  primary_stats.stamina = 43;
  set_red(1);
  set_yellow(1);
  bonus_sec_stats.dodge_rating = 3;
  secondary_stats.defense_rating = 23;
  name = "Mantle of Abrahmis";
  slot = "Shoulder";
}

PanzarTharBreastplate::PanzarTharBreastplate() {
  primary_stats.armor = 1450;
  primary_stats.stamina = 51;
  set_yellow(1);
  set_blue(2);
  bonus_sec_stats.block_chance_rating = 4;
  secondary_stats.defense_rating = 26;
  secondary_stats.block_chance_rating = 24;
  secondary_stats.block_value = 39;
  name = "Panzar'Thar Breastplate";
  slot = "Chest";
}

IronstridersOfUrgency::IronstridersOfUrgency() {
  primary_stats.armor = 997;
  primary_stats.strength = 33;
  primary_stats.agility = 20;
  primary_stats.stamina = 28;
  set_red(1);
  set_yellow(1);
  bonus_prim_stats.strength = 3;
  name = "Ironstriders Of Urgency";
  slot = "Feet";
}

ShieldOfImpenetrableDarkness::ShieldOfImpenetrableDarkness() {
  primary_stats.armor = 4872;
  secondary_stats.block_value = 122 + 33;
  primary_stats.stamina = 33;
  secondary_stats.defense_rating = 22;
  slot = "Offhand";
  name = "Shield of Impenetrable Darkness";
}

BattlescarBoots::BattlescarBoots() {
  primary_stats.armor = 997;
  primary_stats.strength = 18;
  primary_stats.stamina = 28;
  set_red(1);
  set_blue(1);
  bonus_sec_stats.parry_rating = 3;
  secondary_stats.defense_rating = 23;
  secondary_stats.parry_rating = 21;
  slot = "Feet";
  name = "Battlescar Boots";
}

MithrilChainOfHeroism::MithrilChainOfHeroism() {
  primary_stats.strength = 28;
  primary_stats.agility = 22;
  primary_stats.stamina = 22;
  slot = "Neck";
  name = "Mithril Chain of Heroism";
}

BandOfUrsol::BandOfUrsol() {
  primary_stats.strength = 23;
  primary_stats.agility = 12;
  primary_stats.stamina = 22;
  slot = "Ring";
  name = "Band Of Ursol";
}

RingOfTheSilverHand::RingOfTheSilverHand() {
  primary_stats.stamina = 18;
  primary_stats.intelligence = 18;
  secondary_stats.defense_rating = 19;
  secondary_stats.mp5 = 5;
  slot = "Ring";
  name = "Ring of the Silver Hand";
}

RingOfTheStonebark::RingOfTheStonebark() {
  primary_stats.agility = 12;
  primary_stats.stamina = 18;
  secondary_stats.defense_rating = 19;
  slot = "Ring";
  name = "Ring of the Stonebark";
}

JusticarFaceguard::JusticarFaceguard() { // Karazhan
  primary_stats.armor = 1227;
  primary_stats.stamina = 43;
  primary_stats.intelligence = 24;
  set_yellow(1);
  set_meta(1);
  bonus_sec_stats.dodge_rating = 4;
  secondary_stats.defense_rating = 29;
  secondary_stats.dodge_rating = 24;
  secondary_stats.spellpower = 27;
  name = "Justicar Faceguard";
  slot = "Head";
  //(2):SoR,SoV, SoB +10%Dmg
  //(4):HS +15%Dmg
}

JusticarShoulderguards::JusticarShoulderguards() { // Gruul
  primary_stats.armor = 1133;
  primary_stats.stamina = 37;
  primary_stats.intelligence = 14;
  set_blue(1);
  set_yellow(1);
  bonus_prim_stats.stamina = 4;
  secondary_stats.defense_rating = 15;
  secondary_stats.block_chance_rating = 17;
  secondary_stats.spellpower = 26;
  secondary_stats.block_value = 27;
  name = "Justicar Shoulderguards";
  slot = "Shoulder";
  // Set
}

JusticarChestguard::JusticarChestguard() { // Magtheridon
  primary_stats.armor = 1510;
  primary_stats.stamina = 48;
  primary_stats.intelligence = 30;
  set_red(1);
  set_blue(1);
  set_yellow(1);
  bonus_sec_stats.defense_rating = 4;
  secondary_stats.defense_rating = 23;
  secondary_stats.block_chance_rating = 23;
  secondary_stats.spellpower = 27;
  name = "Justicar Chestguard";
  slot = "Chest";
  // Set
}

JusticarHandguard::JusticarHandguard() { // Karazhan
  primary_stats.armor = 944;
  primary_stats.stamina = 34;
  primary_stats.intelligence = 24;
  secondary_stats.defense_rating = 23;
  secondary_stats.spellpower = 27;
  secondary_stats.block_value = 35;
  name = "Justicar Handguard";
  slot = "Hands";
  // Set
}

JusticarLegguards::JusticarLegguards() { // Gruul
  primary_stats.armor = 1322;
  primary_stats.stamina = 46;
  primary_stats.intelligence = 31;
  secondary_stats.defense_rating = 31;
  secondary_stats.parry_rating = 31;
  secondary_stats.spellpower = 36;
  name = "Justicar Legguards";
  slot = "Legs";
  // Set
}

AldoriLegacyDefender::AldoriLegacyDefender() { // Gruul
  primary_stats.armor = 5279;
  primary_stats.stamina = 39;
  secondary_stats.block_value = 137;
  set_blue(1);
  bonus_sec_stats.defense_rating = 2;
  secondary_stats.defense_rating = 19;
  secondary_stats.hit_rating = 15;
  name = "Aldori Legacy Defender";
  slot = "Offhand";
}

ThunderingGreathelm::ThunderingGreathelm() { // Magtheridon
  primary_stats.armor = 1276;
  primary_stats.strength = 50;
  primary_stats.agility = 43;
  primary_stats.stamina = 49;
  name = "Thundering Greathelm";
  slot = "Head";
}

AdalsSignetOfDefense::AdalsSignetOfDefense() { // Magtheridon
  primary_stats.armor = 367;
  primary_stats.stamina = 34;
  secondary_stats.defense_rating = 20;
  name = "Adal's Signet of Defense";
  slot = "Ring";
}

VioletSignet::VioletSignet() {
  name = "Violet Signet";
  slot = "Ring";
  primary_stats.armor = 392;
  primary_stats.stamina = 37;
  secondary_stats.defense_rating = 19;
}

SlikksCloakOfPlacation::SlikksCloakOfPlacation() {
  name = "Slikk's Cloak of Placation";
  slot = "Back";
  primary_stats.armor = 346;
  primary_stats.stamina = 37;
  secondary_stats.defense_rating = 16;
  secondary_stats.dodge_rating = 25;
}

IrontuskGirdle::IrontuskGirdle() {
  name = "Iron-Tusk Girdle";
  slot = "Waist";
  primary_stats.armor = 904;
  primary_stats.stamina = 45;
  secondary_stats.dodge_rating = 33;
  secondary_stats.defense_rating = 21;
  bonus_sec_stats.dodge_rating = 3;
  set_blue(1);
  set_yellow(1);
}

IceguardBreastplate::IceguardBreastplate() {
  primary_stats.armor = 1450;
  primary_stats.stamina = 49;
  primary_stats.frost_resistance = 60;
  secondary_stats.defense_rating = 10;
  name = "Iceguard Breastplate";
  slot = "Chest";
}

IceguardHelm::IceguardHelm() {
  primary_stats.armor = 1030;
  primary_stats.stamina = 64;
  primary_stats.frost_resistance = 50;
  secondary_stats.defense_rating = 20;
  slot = "Head";
  name = "Iceguard Helm";
}

IceguardLeggings::IceguardLeggings() {
  primary_stats.armor = 1110;
  primary_stats.stamina = 55;
  primary_stats.frost_resistance = 60;
  slot = "Legs";
  name = "Iceguard Leggings";
}

PendantOfThawing::PendantOfThawing() {
  primary_stats.stamina = 18;
  primary_stats.frost_resistance = 30;
  name = "Pendant of Thawing";
  slot = "Neck";
}

TheFrozenEye::TheFrozenEye() {
  name = "The Frozen Eye";
  slot = "Ring";
  primary_stats.stamina = 12;
  primary_stats.frost_resistance = 35;
}
