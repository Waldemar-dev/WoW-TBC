#include "equipment.hh"

AbstractGear::AbstractGear() : blue_(0), yellow_(0), red_(0), meta_(0), enchanted_(false), setPiece_(false), freeMeta_(false), active_(false), sockets_(0), phase_(1), cooldown_(0), uptime_(0), src_(Source::noSource), dng_(Dungeon::noDungeon), rep_(Faction::noFaction), raidInstance_(Raid::noRaid), slot_(Slot::NoSlot), armorClass_(ArmorClass::NoClass) {}

AbstractGear::~AbstractGear() {}

void AbstractGear::clearEnchantment(){
  enchanted_=false;
  enchantment_= Enchantment();
}

Gear::Gear()
{
}

Gear::~Gear() {}

void Gear::print() const
{
  std::cout << get_name() << std::endl;
  get_prim_stats().print();
  get_sec_stats().print();
  std::cout << get_enchantment().get_name() << std::endl;
  for (uint i = 0; i < gems.size(); i++)
  {
    std::cout << gems[i].get_name() << std::endl;
  }
  std::cout << std::endl;
}

void Gear::operator=(Gear b)
{
  set_slot(b.get_slot());
  set_name(b.get_base_name());
  set_prim_stats(b.get_prim_stats());
  set_sec_stats(b.get_sec_stats());
  set_bonus_prim_stats(b.get_bonus_prim_stats());
  set_bonus_sec_stats(b.get_bonus_sec_stats());
  set_uptime(b.get_uptime());
  set_cd(b.get_cooldown());
  gems = b.gems;
  computed_socket_bonus = b.computed_socket_bonus;
  equipped = b.equipped;
  clearEnchantment();
  if (b.is_enchanted()){
    set_enchantment(b.get_enchantment());
  }
  set_blue(b.get_n_blue());
  set_red(b.get_n_red());
  set_yellow(b.get_n_yellow());
  set_meta(b.get_n_meta());
  set_sockets(b.get_sockets());
  set_source(b.get_src());
  set_dungeon(b.get_dng());
  set_faction(b.get_rep());
}

Socket Gear::get_meta() const
{
  DummyGem result;
  for (uint i = 0; i < gems.size(); i++)
  {
    for (uint j = 0; j < gems[i].get_color().size(); j++)
    {
      if (gems[i].get_color()[j] == Color::Meta)
      {
        return gems[i];
      }
    }
  }
  return result;
}

bool Gear::operator<=(Gear b)
{
  bool case1 = (has_meta() != b.has_meta());
  bool case2 = (has_meta() && b.has_meta());
  bool case2a = (case2 && !(get_meta() == b.get_meta()));
  bool case3 = (get_sockets() == gems.size()) && (b.get_sockets() == b.gems.size());
  bool case4 = (get_slot() != b.get_slot());
  bool case4a = (get_slot() == Slot::Trinket);
  bool case4b = (get_slot() == Slot::Idol);
  bool case4c = (get_slot() == Slot::Libram);
  bool case4d = (get_slot() == Slot::Relic);
  bool case4A = (case4a || case4b || case4c || case4d);
  if (is_set_piece() || b.is_set_piece() || case1 || case2a || !case3 || case4 || case4A)
  {
    return false;
  }
  if (get_prim_stats() <= b.get_prim_stats() && get_sec_stats() <= b.get_sec_stats())
  {
    return true;
  }
  return false;
}

std::vector<std::string> Gear::get_names() const
{
  std::vector<std::string> result = {"GearSlot INT", "GearEquipmentName TEXT"};
  std::vector<std::string> temp_names = {"GearIsEnchanted INT", "GearIsSetPiece INT", "GearHasFreeMeta INT", "GearBlueSockets INT", "GearYellowSockets INT", "GearRedSockets INT", "GearMetaSockets INT", "GearTotalSockets INT", "GearCooldown DOUBLE", "GearUptime DOUBLE", "GearSource INT", "GearDungeon INT", "GearFaction INT", "GearRaid INT", "GearPhase INT"};
  std::vector<std::vector<std::string>> temp_gems_names;
  std::vector<std::string> enchantmentsNames = get_enchantment().get_names();
  Socket tempGem = DummyGem();
  temp_gems_names.reserve(gems.size());
  uint gems_reserve_int = tempGem.get_names(1).size() * 3;
  for (uint i = 0; i < gems.size(); i++)
  {
    temp_gems_names.push_back(gems[i].get_names(i + 1));
  }
  for (uint i = gems.size(); i < 3; i++)
  {
    temp_gems_names.push_back(tempGem.get_names(i + 1));
  }
  result.reserve(temp_names.size() + enchantmentsNames.size() + gems_reserve_int + (Names::primaryAttributesNames.size() + Names::secondaryAttributesNames.size()) * 2 + result.size());
  for (uint i = 0; i < Names::primaryAttributesNames.size(); i++)
  {
    std::string temp_name = "Gear" + Names::primaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i = 0; i < Names::secondaryAttributesNames.size(); i++)
  {
    std::string temp_name = "Gear" + Names::secondaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i = 0; i < Names::primaryAttributesNames.size(); i++)
  {
    std::string temp_name = "Bonus" + Names::primaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i = 0; i < Names::secondaryAttributesNames.size(); i++)
  {
    std::string temp_name = "Bonus" + Names::secondaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i = 0; i < temp_gems_names.size(); i++)
  {
    result.insert(result.end(), temp_gems_names[i].begin(), temp_gems_names[i].end());
  }
  result.insert(result.end(), enchantmentsNames.begin(), enchantmentsNames.end());
  result.insert(result.end(), temp_names.begin(), temp_names.end());
  result.shrink_to_fit();
  return result;
}

std::string Gear::get_values() const
{
  std::stringstream result;
  result << "(" << (uint)get_slot() << ", '" << get_base_name() << "', ";
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    result << get_prim_stat((PrimaryAttributes)i) << ", ";
  }
  for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
  {
    result << get_sec_stat((SecondaryAttributes)i) << ", ";
  }
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    result << get_bonus_prim_stat((PrimaryAttributes)i) << ", ";
  }
  for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
  {
    result << get_bonus_sec_stat((SecondaryAttributes)i) << ", ";
  }
  for (uint i = 0; i < gems.size(); i++)
  {
    result << gems[i].get_values() << ", ";
  }
  Socket tempGem = DummyGem();
  for (uint i = gems.size(); i < 3; i++)
  {
    result << tempGem.get_values() << ", ";
  }
  result << get_enchantment().get_values();
  result << (uint)is_enchanted() << ", " << (uint)is_set_piece() << ", " << (uint)has_free_meta_place() << ", " << get_n_blue() << ", " << get_n_yellow() << ", " << get_n_red() << ", " << get_n_meta() << ", " << get_sockets() << ", " << get_cooldown() << ", " << get_uptime() << ", " << (uint)get_src() << ", " << (uint)get_dng() << ", " << (uint)get_rep() << ", " << (uint)get_raid() << ", " << (uint)get_phase() << ")";
  return result.str();
}
// void Gear::set_primary_stats(std::vector<double> *in)
// {
//   for (uint i = 0; i < in->size(); i++)
//   {
//     primary_stats.set_stat((PrimaryAttributes)i, in->at(i));
//   }
// }

// void Gear::set_sec_stats(std::vector<double> *in)
// {
//   for (uint i = 0; i < in->size(); i++)
//   {
//     secondary_stats.set_stat((SecondaryAttributes)i, in->at(i));
//   }
// }

// void Gear::set_bonus_prim_stats(std::vector<double> *in)
// {
//   for (uint i = 0; i < in->size(); i++)
//   {
//     bonus_prim_stats.set_stat((PrimaryAttributes)i, in->at(i));
//   }
// }

// void Gear::set_bonus_sec_stats(std::vector<double> *in)
// {
//   for (uint i = 0; i < in->size(); i++)
//   {
//     bonus_sec_stats.set_stat((SecondaryAttributes)i, in->at(i));
//   }
// }

bool Gear::has_gem(Socket *in) const
{
  bool result = false;
  if (find(gems.begin(), gems.end(), (*in)) != gems.end())
  {
    result = true;
  }
  return result;
}

bool Gear::operator>=(Gear b)
{
  bool case1 = (has_meta() != b.has_meta());
  bool case2 = (has_meta() && b.has_meta());
  bool case2a = (case2 && !(get_meta() == b.get_meta()));
  bool case3 = (get_free_sockets() > 0) || (b.get_free_sockets() > 0);
  bool case4 = (get_slot() != b.get_slot());
  bool case4a = (get_slot() == Slot::Trinket);
  bool case4b = (get_slot() == Slot::Idol);
  bool case4c = (get_slot() == Slot::Libram);
  bool case4d = (get_slot() == Slot::Relic);
  bool case4A = (case4a || case4b || case4c || case4d);
  if (is_set_piece() || b.is_set_piece() || case1 || case2a || case3 || case4 || case4A)
  {
    return false;
  }
  if (get_prim_stats() + get_bonus_prim_stats() >= b.get_prim_stats() + b.get_bonus_prim_stats() && get_sec_stats() + get_bonus_sec_stats() >= b.get_sec_stats() + b.get_bonus_sec_stats())
  {
    return true;
  }
  return false;
}

void Gear::add_gem(Socket gem, bool add_stats)
{
  if (gems.size() < get_sockets())
  {
    if (get_n_meta() > 0 && gem.get_color()[0] == Color::Meta)
    {
      bool add = true;
      for (uint i = 0; i < gems.size(); i++)
      {
        if (gems[i].get_color()[0] == Color::Meta)
        {
          add = false;
        }
      }
      if (add)
      {
        gems.push_back(gem);
      }
      setFreeMeta(false);
    }
    else if (get_n_meta() > 0 && gem.get_color()[0] != Color::Meta)
    {
      if (gems.size() <= get_sockets() - get_n_meta())
      {
        gems.push_back(gem);
        if (add_stats)
        {
          set_prim_stats(get_prim_stats() + gem.get_prim_stats());
          set_sec_stats(get_sec_stats() + gem.get_sec_stats());
        }
      }
    }
    else if (get_n_meta() == 0 && gem.get_color()[0] == Color::Meta)
    {
      return;
    }
    else
    {
      gems.push_back(gem);
      std::vector<Color> tempColors=gem.get_color();
      if (find(tempColors.begin(), tempColors.end(), Color::Meta) == tempColors.end() && add_stats)
      {
        set_prim_stats(get_prim_stats() + gem.get_prim_stats());
        set_sec_stats(get_sec_stats() + gem.get_sec_stats());
      }
    }
  }
  socket_bonus();
}

void AbstractGear::set_meta(unsigned int in)
{
  meta_=in;
  setFreeMeta(true);
  set_sockets(get_n_blue() + get_n_red() + get_n_yellow() + get_n_meta());
}

void AbstractGear::set_blue(unsigned int in)
{
  blue_=in;
  set_sockets(in + get_n_red() + get_n_yellow() + get_n_meta());
}

void AbstractGear::set_red(unsigned int in)
{
  red_=in;
  set_sockets(get_n_blue() + get_n_red() + get_n_yellow() + get_n_meta());
}

void AbstractGear::set_yellow(unsigned int in)
{
  yellow_=in;
  sockets_=get_n_blue() + get_n_red() + in + get_n_meta();
}

void Gear::socket_bonus()
{
  if (gems.size() == get_sockets())
  {
    unsigned int temp_blue = 0;
    unsigned int temp_red = 0;
    unsigned int temp_yellow = 0;
    unsigned int temp_meta = 0;
    for (uint i = 0; i < gems.size(); i++)
    {
      for (uint j = 0; j < gems[i].get_color().size(); j++)
      {
        if (gems[i].get_color()[j] == Color::Blue || gems[i].get_color()[j] == Color::Purple || gems[i].get_color()[j] == Color::Green)
        {
          temp_blue++;
        }
        else if (gems[i].get_color()[j] == Color::Red || gems[i].get_color()[j] == Color::Purple || gems[i].get_color()[j] == Color::Orange)
        {
          temp_red++;
        }
        else if (gems[i].get_color()[j] == Color::Yellow || gems[i].get_color()[j] == Color::Green || gems[i].get_color()[j] == Color::Orange)
        {
          temp_yellow++;
        }
        else if (gems[i].get_color()[j] == Color::Meta && gems[i].active)
        {
          temp_meta++;
        }
      }
    }
    if (temp_blue >= get_n_blue() && temp_red >= get_n_red() && temp_yellow >= get_n_yellow() && temp_meta == get_n_meta() && !computed_socket_bonus)
    {
      set_prim_stats(get_prim_stats() + get_bonus_prim_stats());
      set_sec_stats(get_sec_stats() + get_bonus_sec_stats());
      computed_socket_bonus = true;
    }
  }
}

void AbstractGear::set_enchantment(Enchantment in, bool add_stats)
{
  if (!is_enchanted())
  {
    enchantment_ = in;
    if (add_stats)
    {
      set_prim_stats(get_prim_stats() + in.get_prim_stats());
      set_sec_stats(get_sec_stats() + in.get_sec_stats());
    }
    enchanted_ = true;
  }
  else
  {
    std::cout << "Cannot enchant "<<get_base_name() <<" + "<<enchantment_.get_name() << " with "<< in.get_name() << std::endl;
  }
}

std::string Gear::get_name() const
{
  std::stringstream result;
  result << get_base_name();
  if (is_enchanted())
  {
    result << " + " << get_enchantment().get_name();
  }
  for (uint i = 0; i < gems.size(); i++)
  {
    result << " + " << gems[i].get_name();
  }
  result << " from " << Names::sourceNames[(uint)get_src()];
  return result.str();
}

std::string Gear::get_source() const
{
  std::stringstream result;
  std::vector<std::string> sources = {"Random Drop", "Quest", "Crafting", "Group Quest", "Normal", "Heroic", "Reputation Reward", "Badge of Justice", "PvP"};
  std::vector<std::string> dungeons = {"Stratholme", "Black Rock Depths", "Ramparts", "Blood Furnace", "Shattered Halls", "Underbog", "Slave Pens", "Steamvault", "Mana-Tomb", "Auchenaicrypts", "Sethekk Halls", "Shadow Labyrinth", "Old Hillsbrand Foothills", "Black Morast", "Botanika", "Mechanar", "Arcatraz", "Magister''s Terrace"};
  std::vector<std::string> factions = {"Thrallmar", "Cenarion Expedition", "Lower City", "Consortium", "Keepers of Time", "Sha'tar", "Sha'tari Skyguard", "Ogri'la", "Aldor", "Scryers", "Shattered Sun Offensive", "Violet Eye", "Sclae of teh Sands", "Ashtounge Deathsworn", "The Mag'Har"};
  std::vector<std::string> raids = {"Karazhan", "Gruul''s Lair", "Magtheridon''s Lair", "Serpentshrine Cavern", "The Eye", "Mount Hyjal", "Black Temple", "Zul'Aman", "Sunwell Plateau"};
  if (get_src() != Source::raid)
  {
    int n1 = get_src();
    result << sources[n1];
    if (get_src() == Source::normaldungeon || get_src() == Source::heroicdungeon)
    {
      int n2 = get_dng();
      result << " " << dungeons[n2];
    }
    else if (get_src() == Source::reputation)
    {
      int n3 = get_rep();
      result << " " << factions[n3];
    }
  }
  else
  {
    int n4 = get_raid();
    result << raids[n4];
  }
  return result.str();
}

FelsteelHelm::FelsteelHelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1284);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 33);
  set_slot(Slot::Head);
  set_name("Felsteel Helm");
  set_blue(2);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 4);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

NatashasBattleChain::NatashasBattleChain()
{
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_sec_stat(SecondaryAttributes::DefenseRating, 13);
  set_sec_stat(SecondaryAttributes::BlockValue, 15);
  set_slot(Slot::Neck);
  set_name("Natasha''s Battle Chain");
  set_source(groupquest);
}

SpauldersOfTheRighteous::SpauldersOfTheRighteous()
{
  set_prim_stat(PrimaryAttributes::Armor, 873);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_prim_stat(PrimaryAttributes::Intelligence, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::SpellPower, 15);
  set_slot(Slot::Shoulders);
  set_name("Spaulders Of The Righteous");
  set_blue(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 3);
  set_source(normaldungeon);
  set_dungeon(botanika);
  set_ArmorClass(ArmorClass::Plate);
}

CloakOfEternity::CloakOfEternity()
{
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_prim_stat(PrimaryAttributes::Armor, 76);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_slot(Slot::Back);
  set_name("Cloak Of Eternity");
  set_source(crafting);
}

BracersOfTheGreenFortress::BracersOfTheGreenFortress()
{
  set_prim_stat(PrimaryAttributes::Armor, 581);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::DefenseRating, 17);
  set_sec_stat(SecondaryAttributes::DodgeRating, 10);
  set_slot(Slot::Bracers);
  set_name("Bracers Of The Green Fortress");
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

FelsteelGloves::FelsteelGloves()
{
  set_prim_stat(PrimaryAttributes::Armor, 943);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_slot(Slot::Hands);
  set_name("Felsteel Gloves");
  set_blue(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::ParryRating, 3);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

ShatariVindicatorsWaistguard::ShatariVindicatorsWaistguard()
{
  set_prim_stat(PrimaryAttributes::Armor, 655);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::BlockValue, 29);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 24);
  set_slot(Slot::Belt);
  set_name("Shatari Vindicator''s Waistguard");
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Plate);
}

TimewardensLeggings::TimewardensLeggings()
{
  set_prim_stat(PrimaryAttributes::Armor, 1019);
  set_prim_stat(PrimaryAttributes::Stamina, 57);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::DodgeRating, 11);
  set_slot(Slot::Legs);
  set_name("Timewarden''s Leggings");
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::BlockValue, 6);
  set_source(reputation);
  set_faction(keepers_of_time);
  set_ArmorClass(ArmorClass::Plate);
}

IronsoleClompers::IronsoleClompers()
{
  set_prim_stat(PrimaryAttributes::Armor, 600);
  set_prim_stat(PrimaryAttributes::Stamina, 19);
  set_prim_stat(PrimaryAttributes::Strength, 14);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_slot(Slot::Boots);
  set_name("Ironsole Clompers");
  set_red(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 3);
  set_source(normaldungeon);
  set_dungeon(ramparts);
  set_ArmorClass(ArmorClass::Plate);
}

IronBandOfTheUnbreakable::IronBandOfTheUnbreakable()
{
  set_prim_stat(PrimaryAttributes::Armor, 170);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 17);
  set_slot(Slot::Ring);
  set_name("Iron Band Of The Unbreakable");
  set_source(normaldungeon);
  set_dungeon(ohf);
}

CenarionRingOfCasting::CenarionRingOfCasting()
{
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Intelligence, 16);
  set_sec_stat(SecondaryAttributes::SpellPower, 18);
  set_slot(Slot::Ring);
  set_name("Cenarion Ring Of Casting");
  set_source(groupquest);
}

ContinuumBlade::ContinuumBlade()
{
  set_prim_stat(PrimaryAttributes::WeaponDamage, (84 + 45) / 2.0);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 1.8);
  set_prim_stat(PrimaryAttributes::Stamina, 35);
  set_sec_stat(SecondaryAttributes::SpellPower, 122);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 8);
  set_slot(Slot::Mainhand);
  set_name("Continuum Blade");
  set_source(reputation);
  set_faction(keepers_of_time);
  set_ArmorClass(ArmorClass::OneHandSword);
}

AegisOfTheSunbird::AegisOfTheSunbird()
{
  set_prim_stat(PrimaryAttributes::Armor, 3806);
  set_sec_stat(SecondaryAttributes::BlockValue, 86 + 29);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_slot(Slot::Offhand);
  set_name("Aegis Of The Sunbird");
  set_source(normaldungeon);
  set_dungeon(botanika);
  set_ArmorClass(ArmorClass::Shield);
}

AdamantineFigurine::AdamantineFigurine()
{
  set_sec_stat(SecondaryAttributes::DefenseRating, 32);
  set_slot(Slot::Trinket);
  set_name("Adamantine Figurine");
  set_uptime(20.0);
  set_cd(120.0);
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
}

void AdamantineFigurine::activate()
{
  if (!is_active())
  {
    activate();
    set_prim_stat(PrimaryAttributes::Armor, 1281);
  }
}

void AdamantineFigurine::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_prim_stat(PrimaryAttributes::Armor, 0);
  }
}

DabirisEnigma::DabirisEnigma()
{
  set_sec_stat(SecondaryAttributes::DefenseRating, 30);
  set_slot(Slot::Trinket);
  set_name("Dabiri''s Enigma");
  set_uptime(15.0);
  set_cd(90.0);
  set_source(groupquest);
}

void DabirisEnigma::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::BlockChanceRating, 126);
  }
}

void DabirisEnigma::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::BlockChanceRating, 0);
  }
}

BootsOfTheRighteousPath::BootsOfTheRighteousPath()
{
  set_prim_stat(PrimaryAttributes::Armor, 955);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_prim_stat(PrimaryAttributes::Intelligence, 26);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::SpellPower, 29);
  set_slot(Slot::Boots);
  set_name("Boots Of The Righteous Path");
  set_source(heroicdungeon);
  set_dungeon(shattered_halls);
  set_ArmorClass(ArmorClass::Plate);
}

BootsOfTheColossus::BootsOfTheColossus()
{
  set_prim_stat(PrimaryAttributes::Armor, 800);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_slot(Slot::Boots);
  set_name("BootsOfTheColossus");
  set_blue(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 3);
  set_source(heroicdungeon);
  set_dungeon(manatomb);
  set_ArmorClass(ArmorClass::Plate);
}

FleshBeastsMetalGreaves::FleshBeastsMetalGreaves()
{
  set_prim_stat(PrimaryAttributes::Armor, 680);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::DodgeRating, 28);
  set_slot(Slot::Boots);
  set_name("Flesh Beast''s Metal Greaves");
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Plate);
}

EaglecrestWarboots::EaglecrestWarboots()
{
  set_prim_stat(PrimaryAttributes::Armor, 955);
  set_prim_stat(PrimaryAttributes::Strength, 29);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_slot(Slot::Boots);
  set_name("Eaglecrest Warboots");
  set_source(heroicdungeon);
  set_dungeon(blood_furnace);
  set_ArmorClass(ArmorClass::Plate);
}

GladiatorsLamellarHelm::GladiatorsLamellarHelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1257);
  set_prim_stat(PrimaryAttributes::Stamina, 57);
  set_prim_stat(PrimaryAttributes::Intelligence, 21);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 32);
  set_sec_stat(SecondaryAttributes::SpellCritRating, 22);
  set_sec_stat(SecondaryAttributes::SpellPower, 34);
  set_slot(Slot::Head);
  set_name("Gladiator''s Lamellar Helm");
  set_red(1);
  set_meta(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 4);
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Plate);
}

HelmOfTheStalwartDefender::HelmOfTheStalwartDefender()
{
  set_prim_stat(PrimaryAttributes::Armor, 1366);
  set_prim_stat(PrimaryAttributes::Stamina, 47);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 23);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_slot(Slot::Head);
  set_name("Helm Of The Stalwart Defender");
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 4);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

GreathelmOfTheUnbreakable::GreathelmOfTheUnbreakable()
{
  set_prim_stat(PrimaryAttributes::Armor, 922);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_prim_stat(PrimaryAttributes::Strength, 36);
  set_sec_stat(SecondaryAttributes::DefenseRating, 30);
  set_slot(Slot::Head);
  set_name("Greathelm Of The Unbreakable");
  set_source(normaldungeon);
  set_dungeon(shattered_halls);
  set_ArmorClass(ArmorClass::Plate);
}

OathkeepersHelm::OathkeepersHelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1080);
  set_prim_stat(PrimaryAttributes::Stamina, 40);
  set_prim_stat(PrimaryAttributes::Intelligence, 22);
  set_sec_stat(SecondaryAttributes::SpellPower, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_sec_stat(SecondaryAttributes::MP5, 10);
  set_slot(Slot::Head);
  set_name("Oathkeeper''s Helm");
  set_red(1);
  set_blue(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::SpellhitRating, 4);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

DevilsharkCape::DevilsharkCape()
{
  set_prim_stat(PrimaryAttributes::Armor, 78);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::DodgeRating, 18);
  set_sec_stat(SecondaryAttributes::BlockValue, 30);
  set_slot(Slot::Back);
  set_name("Devilshark Cape");
  set_source(normaldungeon);
  set_dungeon(steamvault);
}

FarstriderDefendersCloak::FarstriderDefendersCloak()
{
  set_prim_stat(PrimaryAttributes::Armor, 267);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::BlockValue, 39);
  set_slot(Slot::Back);
  set_name("Farstrider Defender''s Cloak");
  set_source(boj);
  set_phase(1);
}

BurnooseOfShiftingAges::BurnooseOfShiftingAges()
{
  set_prim_stat(PrimaryAttributes::Armor, 216);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_sec_stat(SecondaryAttributes::BlockValue, 29);
  set_slot(Slot::Back);
  set_name("Burnoose Of Shifting Ages");
  set_source(normaldungeon);
  set_dungeon(black_morast);
}

BandOfImpenetrableDefenses::BandOfImpenetrableDefenses()
{
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_slot(Slot::Ring);
  set_name("Band of Impenetrable Defenses");
  set_source(randomdrop);
}

RingOfUnyieldingForce::RingOfUnyieldingForce()
{
  set_prim_stat(PrimaryAttributes::Armor, 294);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_slot(Slot::Ring);
  set_name("Ring of Unyielding Force");
  set_source(boj);
  set_phase(1);
}

YorsRevenge::YorsRevenge()
{
  set_prim_stat(PrimaryAttributes::Armor, 190);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_slot(Slot::Ring);
  set_name("Yor''s Revenge");
  set_source(heroicdungeon);
  set_dungeon(manatomb);
}

ElementiumBandOfTheSentry::ElementiumBandOfTheSentry()
{
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::DodgeRating, 19);
  set_slot(Slot::Ring);
  set_name("Elementium Band Of The Sentry");
  set_source(normaldungeon);
  set_dungeon(arcatraz);
}

LieutenantsSignetOfLordaeron::LieutenantsSignetOfLordaeron()
{
  set_prim_stat(PrimaryAttributes::Armor, 143);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::DodgeRating, 21);
  set_slot(Slot::Ring);
  set_name("Lieutenant’s Signet of Lordaeron");
  set_source(heroicdungeon);
  set_dungeon(ohf);
}

AndormusTear::AndormusTear()
{
  set_sec_stat(SecondaryAttributes::DefenseRating, 10);
  set_sec_stat(SecondaryAttributes::DodgeRating, 26);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 15);
  set_slot(Slot::Ring);
  set_name("Andormu’s Tear");
  set_source(groupquest);
}

NecklaceOfTheJuggernaut::NecklaceOfTheJuggernaut()
{
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Agility, 19);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_slot(Slot::Neck);
  set_name("Necklace of the Juggernaut");
  set_source(boj);
  set_phase(1);
}

StrengthOfTheUntamed::StrengthOfTheUntamed()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::DodgeRating, 18);
  set_slot(Slot::Neck);
  set_name("Strength of the Untamed");
  set_source(reputation);
  set_faction(cenarion_expedition);
}

MaladaarsBlessedChaplet::MaladaarsBlessedChaplet()
{
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::DodgeRating, 12);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_slot(Slot::Neck);
  set_name("Maladaar’s Blessed Chaplet");
  set_source(heroicdungeon);
  set_dungeon(auchenaicrypt);
}

SteamHingeChainOfValor::SteamHingeChainOfValor()
{
  set_prim_stat(PrimaryAttributes::Stamina, 26);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 19);
  set_sec_stat(SecondaryAttributes::BlockValue, 29);
  set_slot(Slot::Neck);
  set_name("Steam-Hinge Chain of Valor");
  set_source(normaldungeon);
  set_dungeon(steamvault);
}

DarkmoonCardVengeance::DarkmoonCardVengeance()
{
  set_prim_stat(PrimaryAttributes::Stamina, 51);
  set_slot(Slot::Trinket);
  set_name("Darkmoon Card: Vengeance");
  set_source(randomdrop);
}

FanbladePauldrons::FanbladePauldrons()
{
  set_prim_stat(PrimaryAttributes::Armor, 873);
  set_prim_stat(PrimaryAttributes::Strength, 16);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::ParryRating, 15);
  set_slot(Slot::Shoulders);
  set_name("Fanblade Pauldrons");
  set_blue(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::ParryRating, 3);
  set_source(heroicdungeon);
  set_dungeon(auchenaicrypt);
}

SpauldersOfDementia::SpauldersOfDementia()
{
  set_prim_stat(PrimaryAttributes::Armor, 1042);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_prim_stat(PrimaryAttributes::Strength, 25);
  set_prim_stat(PrimaryAttributes::Agility, 24);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_slot(Slot::Shoulders);
  set_name("Spaulders of Dementia");
  set_source(heroicdungeon);
  set_dungeon(sethekk_halls);
  set_ArmorClass(ArmorClass::Plate);
}

JadeSkullBreastplate::JadeSkullBreastplate()
{
  set_prim_stat(PrimaryAttributes::Armor, 1164);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Stamina, 50);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 23);
  set_slot(Slot::Chest);
  set_name("Jade-Skull Breastplate");
  set_source(normaldungeon);
  set_dungeon(mechanar);
}

VindicatorsHauberk::VindicatorsHauberk()
{
  set_prim_stat(PrimaryAttributes::Armor, 1164);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::DodgeRating, 19);
  set_sec_stat(SecondaryAttributes::DefenseRating, 46);
  set_slot(Slot::Chest);
  set_name("Vindicator’s Hauberk");
  set_source(reputation);
  set_faction(aldor);
}

BracersOfDignity::BracersOfDignity()
{
  set_prim_stat(PrimaryAttributes::Armor, 608);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 12);
  set_sec_stat(SecondaryAttributes::DefenseRating, 21);
  set_sec_stat(SecondaryAttributes::SpellPower, 20);
  set_slot(Slot::Bracers);
  set_name("Bracers of Dignity");
  set_source(heroicdungeon);
  set_dungeon(arcatraz);
}

AmberBandsOfTheAggressor::AmberBandsOfTheAggressor()
{
  set_prim_stat(PrimaryAttributes::Armor, 608);
  set_prim_stat(PrimaryAttributes::Strength, 22);
  set_prim_stat(PrimaryAttributes::Agility, 18);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_slot(Slot::Bracers);
  set_name("Amber Bands of the Aggressor");
  set_source(heroicdungeon);
  set_dungeon(steamvault);
  set_ArmorClass(ArmorClass::Plate);
}

GauntletsOfTheIronTower::GauntletsOfTheIronTower()
{
  set_prim_stat(PrimaryAttributes::Armor, 831);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 26);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_slot(Slot::Hands);
  set_name("Gauntlets of the Iron Tower");
  set_blue(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 3);
  set_source(crafting);
}

GauntletsOfDissension::GauntletsOfDissension()
{
  set_prim_stat(PrimaryAttributes::Armor, 868);
  set_prim_stat(PrimaryAttributes::Strength, 24);
  set_prim_stat(PrimaryAttributes::Agility, 23);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_slot(Slot::Hands);
  set_name("Gauntlets of Dissension");
  set_source(heroicdungeon);
  set_dungeon(botanika);
  set_ArmorClass(ArmorClass::Plate);
}

GauntletsOfTheRighteous::GauntletsOfTheRighteous()
{
  set_prim_stat(PrimaryAttributes::Armor, 728);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_sec_stat(SecondaryAttributes::SpellPower, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::MP5, 8);
  set_slot(Slot::Hands);
  set_name("Guantlets of the Righteous");
  set_source(normaldungeon);
  set_dungeon(shattered_halls);
  set_ArmorClass(ArmorClass::Plate);
}

GirdleOfValorousDeeds::GirdleOfValorousDeeds()
{
  set_prim_stat(PrimaryAttributes::Armor, 782);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_prim_stat(PrimaryAttributes::Intelligence, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 16);
  set_sec_stat(SecondaryAttributes::SpellPower, 21);
  set_slot(Slot::Belt);
  set_name("Girdle of Valorous Deeds");
  set_source(heroicdungeon);
  set_dungeon(black_morast);
  set_ArmorClass(ArmorClass::Plate);
}

LionsHeartGirdle::LionsHeartGirdle()
{
  set_prim_stat(PrimaryAttributes::Armor, 782);
  set_prim_stat(PrimaryAttributes::Strength, 26);
  set_prim_stat(PrimaryAttributes::Agility, 22);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_slot(Slot::Belt);
  set_name("Lion’s Heart Girdle");
  set_source(heroicdungeon);
  set_dungeon(ramparts);
  set_ArmorClass(ArmorClass::Plate);
}

GirdleOfTheImmovable::GirdleOfTheImmovable()
{
  set_prim_stat(PrimaryAttributes::Armor, 655);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 12);
  set_slot(Slot::Belt);
  set_name("Girdle of the Immovable");
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_source(heroicdungeon);
  set_dungeon(slave_pens);
}

FaceguardOfDetermination::FaceguardOfDetermination()
{
  set_prim_stat(PrimaryAttributes::Armor, 1129);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_sec_stat(SecondaryAttributes::DefenseRating, 32);
  set_sec_stat(SecondaryAttributes::DodgeRating, 24);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 24);
  set_slot(Slot::Head);
  set_name("Faceguard of Determination");
  set_meta(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 6);
  set_source(boj);
  set_phase(1);
}

TankatronicGoggles::TankatronicGoggles()
{
  set_prim_stat(PrimaryAttributes::Armor, 1296);
  set_prim_stat(PrimaryAttributes::Stamina, 67);
  set_sec_stat(SecondaryAttributes::DefenseRating, 38);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_sec_stat(SecondaryAttributes::DodgeRating, 22);
  set_slot(Slot::Head);
  set_name("Tankatronic Goggles");
  set_meta(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 6);
}

X52TechniciansHelm::X52TechniciansHelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 875);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_prim_stat(PrimaryAttributes::Strength, 38);
  set_prim_stat(PrimaryAttributes::Intelligence, 16);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_sec_stat(SecondaryAttributes::MP5, 7);
  set_slot(Slot::Head);
  set_name("X-52 Technician’s Helm");
  set_source(crafting);
}

MyrmidonsHeaddress::MyrmidonsHeaddress()
{
  set_prim_stat(PrimaryAttributes::Armor, 946);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_sec_stat(SecondaryAttributes::DefenseRating, 33);
  set_slot(Slot::Head);
  set_name("Myrmidon''s Headdress");
  set_meta(1);
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 4);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Plate);
}

HelmOfTheRighteous::HelmOfTheRighteous()
{
  set_prim_stat(PrimaryAttributes::Armor, 946);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_sec_stat(SecondaryAttributes::DefenseRating, 21);
  set_sec_stat(SecondaryAttributes::SpellPower, 23);
  set_sec_stat(SecondaryAttributes::MP5, 6);
  set_slot(Slot::Head);
  set_name("Helm of the Righteous");
  set_meta(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Intelligence, 4);
  set_source(normaldungeon);
  set_dungeon(mechanar);
}

ThalodiensCharm::ThalodiensCharm()
{
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_sec_stat(SecondaryAttributes::BlockValue, 15);
  set_slot(Slot::Neck);
  set_name("Thalodien''s Charm");
  set_source(groupquest);
}

MarkOfTheRavenguard::MarkOfTheRavenguard()
{
  set_prim_stat(PrimaryAttributes::Stamina, 40);
  set_sec_stat(SecondaryAttributes::DefenseRating, 17);
  set_slot(Slot::Neck);
  set_name("Mark of the Ravenguard");
  set_source(groupquest);
}

MedallionOfTheValiantGuardian::MedallionOfTheValiantGuardian()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_slot(Slot::Neck);
  set_name("Medallion of the Valiant Guardian");
  set_source(groupquest);
}

EnchantedThoriumTorque::EnchantedThoriumTorque()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DodgeRating, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 16);
  set_slot(Slot::Neck);
  set_name("Enchanted Thorium Torque");
  set_source(normaldungeon);
  set_dungeon(botanika);
}

EthereumTorqueOfTheKnight::EthereumTorqueOfTheKnight()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::SpellPower, 21);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_slot(Slot::Neck);
  set_name("Ethereum Torque of the Knight");
  set_source(randomdrop);
}

EthereumTorqueOfTheChampion::EthereumTorqueOfTheChampion()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_slot(Slot::Neck);
  set_name("Ethereum Torque of the Champion");
  set_source(randomdrop);
}

ChainOfTheTwilightOwl::ChainOfTheTwilightOwl()
{
  set_prim_stat(PrimaryAttributes::Intelligence, 19);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::SpellPower, 21);
  set_sec_stat(SecondaryAttributes::SpellCritRating, 45);
  set_slot(Slot::Neck);
  set_name("Chain of the Twilight Owl");
  set_source(crafting);
}

LibramOfSaintsDeparted::LibramOfSaintsDeparted()
{
  set_slot(Slot::Libram);
  set_name("Libram of Saints Departed");
  set_source(normaldungeon);
  set_dungeon(blood_furnace);
}

LibramOfTruth::LibramOfTruth()
{
  set_slot(Slot::Libram);
  set_name("Libram of Truth");
  set_source(normaldungeon);
  set_dungeon(blackrock);
}

DelicateEterniumRing::DelicateEterniumRing()
{
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_sec_stat(SecondaryAttributes::DodgeRating, 16);
  set_slot(Slot::Ring);
  set_name("Delicate Eternium Ring");
  set_source(crafting);
}

ProtectorsMarkOfTheRedemption::ProtectorsMarkOfTheRedemption()
{
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_sec_stat(SecondaryAttributes::BlockValue, 15);
  set_slot(Slot::Ring);
  set_name("Protector''s Mark of the Redemption");
  set_source(groupquest);
}

DathRemarsRingOfDefense::DathRemarsRingOfDefense()
{
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 15);
  set_sec_stat(SecondaryAttributes::BlockValue, 39);
  set_slot(Slot::Ring);
  set_name("Dath''Remar''s Ring of Defense");
  set_source(normaldungeon);
  set_dungeon(mechanar);
}

WarchiefsMantle::WarchiefsMantle()
{
  set_prim_stat(PrimaryAttributes::Armor, 786);
  set_prim_stat(PrimaryAttributes::Strength, 23);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::ParryRating, 18);
  set_slot(Slot::Shoulders);
  set_name("Warchief''s Mantle");
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::CritRating, 3);
  set_source(groupquest);
}

KaylaansSpaulders::KaylaansSpaulders()
{
  set_prim_stat(PrimaryAttributes::Armor, 787);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::SpellPower, 30);
  set_slot(Slot::Shoulders);
  set_name("Kaylaan''s Spaulders");
  set_source(groupquest);
}

BogstrokScaleCloak::BogstrokScaleCloak()
{
  set_prim_stat(PrimaryAttributes::Armor, 271);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_slot(Slot::Back);
  set_name("Bogstrok Scale Cloak");
  set_source(normaldungeon);
  set_dungeon(slave_pens);
}

ThoriumweaveCloak::ThoriumweaveCloak()
{
  set_prim_stat(PrimaryAttributes::Armor, 390);
  set_prim_stat(PrimaryAttributes::Stamina, 35);
  set_slot(Slot::Back);
  set_name("Thoriumweave Cloak");
  set_source(normaldungeon);
  set_dungeon(mechanar);
}

CloakOfTheValiantDefender::CloakOfTheValiantDefender()
{
  set_prim_stat(PrimaryAttributes::Armor, 262);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_slot(Slot::Back);
  set_name("Cloak of the Valiant Defender");
  set_source(soloquest);
}

BootsOfRighteousFortitude::BootsOfRighteousFortitude()
{
  set_prim_stat(PrimaryAttributes::Armor, 800);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_prim_stat(PrimaryAttributes::Intelligence, 14);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::SpellPower, 29);
  set_slot(Slot::Boots);
  set_name("Boots of Righteous Fortitude");
  set_source(normaldungeon);
  set_dungeon(sethekk_halls);
}

AscendantsBoots::AscendantsBoots()
{
  set_prim_stat(PrimaryAttributes::Armor, 722);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::DefenseRating, 21);
  set_sec_stat(SecondaryAttributes::BlockValue, 23);
  set_slot(Slot::Boots);
  set_name("Ascendant''s Boots");
  set_blue(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Plate);
}

BloodguardsGreaves::BloodguardsGreaves()
{
  set_prim_stat(PrimaryAttributes::Armor, 685);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_prim_stat(PrimaryAttributes::Strength, 11);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_slot(Slot::Boots);
  set_name("Bloodguard’s Greaves");
  set_source(soloquest);
}

StarcallersPlatedStompers::StarcallersPlatedStompers()
{
  set_prim_stat(PrimaryAttributes::Armor, 722);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_prim_stat(PrimaryAttributes::Intelligence, 14);
  set_sec_stat(SecondaryAttributes::DefenseRating, 13);
  set_sec_stat(SecondaryAttributes::SpellPower, 17);
  set_slot(Slot::Boots);
  set_name("Starcaller’s Plated Stompers");
  set_source(soloquest);
}

FelsteelLeggings::FelsteelLeggings()
{
  set_prim_stat(PrimaryAttributes::Armor, 1257);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::DefenseRating, 33);
  set_slot(Slot::Legs);
  set_name("Felsteel Leggings");
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

GreavesOfTheShatterer::GreavesOfTheShatterer()
{
  set_prim_stat(PrimaryAttributes::Armor, 1019);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_prim_stat(PrimaryAttributes::Strength, 25);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_slot(Slot::Legs);
  set_name("Greaves of the Shatterer");
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::BlockValue, 6);
  set_source(normaldungeon);
  set_dungeon(shattered_halls);
  set_ArmorClass(ArmorClass::Plate);
}

LegguardsOfTheResoluteDefender::LegguardsOfTheResoluteDefender()
{
  set_prim_stat(PrimaryAttributes::Armor, 942);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_prim_stat(PrimaryAttributes::Agility, 23);
  set_sec_stat(SecondaryAttributes::DefenseRating, 31);
  set_sec_stat(SecondaryAttributes::ParryRating, 21);
  set_slot(Slot::Legs);
  set_name("Legguards of the Resolute Defender");
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Plate);
}

LegplatesOfTheRighteous::LegplatesOfTheRighteous()
{
  set_prim_stat(PrimaryAttributes::Armor, 1019);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Intelligence, 24);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_sec_stat(SecondaryAttributes::SpellPower, 29);
  set_sec_stat(SecondaryAttributes::MP5, 11);
  set_slot(Slot::Legs);
  set_name("Legplates of the Righteous");
  set_source(normaldungeon);
  set_dungeon(black_morast);
  set_ArmorClass(ArmorClass::Plate);
}

KirinvarDefendersChausses::KirinvarDefendersChausses()
{
  set_prim_stat(PrimaryAttributes::Armor, 895);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::SpellPower, 31);
  set_sec_stat(SecondaryAttributes::MP5, 8);
  set_slot(Slot::Legs);
  set_name("Kirin’var Defender’s Chausses");
  set_source(soloquest);
}

BreastplateOfTheWarbringer::BreastplateOfTheWarbringer()
{
  set_prim_stat(PrimaryAttributes::Armor, 1048);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::HitRating, 30);
  set_sec_stat(SecondaryAttributes::DefenseRating, 31);
  set_slot(Slot::Chest);
  set_name("Breastplate of the Warbringer");
  set_source(groupquest);
}

BreastplateOfTheRighteous::BreastplateOfTheRighteous()
{
  set_prim_stat(PrimaryAttributes::Armor, 1164);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 28);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_sec_stat(SecondaryAttributes::SpellPower, 24);
  set_slot(Slot::Chest);
  set_name("Breastplate of the Righteous");
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::MP5, 2);
  set_source(normaldungeon);
  set_dungeon(steamvault);
  set_ArmorClass(ArmorClass::Plate);
}

ScavengedBreastplate::ScavengedBreastplate()
{
  set_prim_stat(PrimaryAttributes::Armor, 996);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_prim_stat(PrimaryAttributes::Strength, 14);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_sec_stat(SecondaryAttributes::HitRating, 14);
  set_slot(Slot::Chest);
  set_name("Scavenged Breastplate");
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Plate);
}

ShatariWroughtArmguards::ShatariWroughtArmguards()
{
  set_prim_stat(PrimaryAttributes::Armor, 509);
  set_prim_stat(PrimaryAttributes::Strength, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 12);
  set_slot(Slot::Bracers);
  set_name("Sha’tari Wrought Armguards");
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
}

VambracesOfDaring::VambracesOfDaring()
{
  set_prim_stat(PrimaryAttributes::Armor, 509);
  set_prim_stat(PrimaryAttributes::Stamina, 26);
  set_prim_stat(PrimaryAttributes::Strength, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 11);
  set_sec_stat(SecondaryAttributes::BlockValue, 23);
  set_slot(Slot::Bracers);
  set_name("Vambraces of Daring");
  set_source(heroicdungeon);
  set_dungeon(ramparts);
}

ThadellsBracers::ThadellsBracers()
{
  set_prim_stat(PrimaryAttributes::Armor, 448);
  set_prim_stat(PrimaryAttributes::Intelligence, 12);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::DefenseRating, 9);
  set_sec_stat(SecondaryAttributes::SpellPower, 17);
  set_slot(Slot::Bracers);
  set_name("Thadell’s Bracers");
  set_source(groupquest);
}

JuniorTechnician3rdGradeBracers::JuniorTechnician3rdGradeBracers()
{
  set_prim_stat(PrimaryAttributes::Armor, 436);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Agility, 10);
  set_sec_stat(SecondaryAttributes::DefenseRating, 11);
  set_sec_stat(SecondaryAttributes::HitRating, 11);
  set_slot(Slot::Bracers);
  set_name("Junior Technician 3rd Grade Bracers");
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Plate);
}

GreatswordOfHorridDreams::GreatswordOfHorridDreams()
{
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::Intelligence, 14);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 14);
  set_sec_stat(SecondaryAttributes::SpellPower, 131);
  set_slot(Slot::Mainhand);
  set_name("Greatsword Of Horrid Dreams");
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
}

ManaWrath::ManaWrath()
{
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_sec_stat(SecondaryAttributes::SpellPower, 127);
  set_slot(Slot::Mainhand);
  set_name("Mana Wrath");
  set_source(normaldungeon);
  set_dungeon(mechanar);
}

CrystalforgedSword::CrystalforgedSword()
{
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 8);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 11);
  set_sec_stat(SecondaryAttributes::SpellPower, 122);
  set_slot(Slot::Mainhand);
  set_name("Crystalforged Sword");
  set_source(randomdrop);
  set_ArmorClass(ArmorClass::OneHandSword);
}

GavelOfUnearthedSecrets::GavelOfUnearthedSecrets()
{
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Intelligence, 16);
  set_sec_stat(SecondaryAttributes::SpellCritRating, 15);
  set_sec_stat(SecondaryAttributes::SpellPower, 160);
  set_slot(Slot::Mainhand);
  set_name("Gavel of Unearthed Secrets");
  set_source(reputation);
  set_faction(lower_city);
  set_ArmorClass(ArmorClass::OneHandMace);
}

CrestOfTheShatar::CrestOfTheShatar()
{
  set_prim_stat(PrimaryAttributes::Armor, 4465);
  set_prim_stat(PrimaryAttributes::Stamina, 19);
  set_sec_stat(SecondaryAttributes::BlockValue, 108 + 25);
  set_sec_stat(SecondaryAttributes::DefenseRating, 13);
  set_slot(Slot::Offhand);
  set_name("Crest of the Sha’tar");
  set_blue(2);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_source(reputation);
  set_faction(shatar);
  set_ArmorClass(ArmorClass::Shield);
}

PlatinumShieldOfTheValorous::PlatinumShieldOfTheValorous()
{
  set_prim_stat(PrimaryAttributes::Armor, 3711);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::BlockValue, 83);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_slot(Slot::Offhand);
  set_name("Platinum Shield of the Valorous");
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
}

NetherwingDefendersShield::NetherwingDefendersShield()
{
  set_prim_stat(PrimaryAttributes::Armor, 3615);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_prim_stat(PrimaryAttributes::Intelligence, 13);
  set_sec_stat(SecondaryAttributes::DefenseRating, 13);
  set_sec_stat(SecondaryAttributes::BlockValue, 80 + 19);
  set_sec_stat(SecondaryAttributes::SpellPower, 15);
  set_slot(Slot::Offhand);
  set_name("Netherwing Defender''s Shield");
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Shield);
}

OgrilaAegis::OgrilaAegis()
{
  set_prim_stat(PrimaryAttributes::Armor, 3806);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::BlockValue, 86 + 23);
  set_slot(Slot::Offhand);
  set_name("Ogri''la Aegis");
  set_red(2);
  set_bonus_sec_stat(SecondaryAttributes::BlockChanceRating, 3);
  set_source(reputation);
  set_faction(ogrila);
  set_ArmorClass(ArmorClass::Shield);
}

ShieldOfTheWaywardFootman::ShieldOfTheWaywardFootman()
{
  set_prim_stat(PrimaryAttributes::Armor, 3329);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 18);
  set_sec_stat(SecondaryAttributes::BlockValue, 71);
  set_slot(Slot::Offhand);
  set_name("Shield of the Wayward Footman");
  set_source(randomdrop);
}

WarhelmOfTheBold::WarhelmOfTheBold()
{
  set_prim_stat(PrimaryAttributes::Armor, 946);
  set_prim_stat(PrimaryAttributes::Strength, 24);
  set_prim_stat(PrimaryAttributes::Agility, 22);
  set_prim_stat(PrimaryAttributes::Stamina, 23);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_blue(1);
  set_meta(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 4);
  set_name("Warhelm of the Bold");
  set_slot(Slot::Head);
  set_source(normaldungeon);
  set_dungeon(botanika);
  set_ArmorClass(ArmorClass::Plate);
}

ShoulderguardsOfTheBold::ShoulderguardsOfTheBold()
{
  set_prim_stat(PrimaryAttributes::Armor, 873);
  set_prim_stat(PrimaryAttributes::Strength, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::DefenseRating, 17);
  set_yellow(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_name("Shoulderguards of the Bold");
  set_slot(Slot::Shoulders);
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
  set_ArmorClass(ArmorClass::Plate);
}

BreastplateOfTheBold::BreastplateOfTheBold()
{
  set_prim_stat(PrimaryAttributes::Armor, 1164);
  set_prim_stat(PrimaryAttributes::Strength, 23);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_red(2);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 4);
  set_name("Breastplate of the Bold");
  set_slot(Slot::Chest);
  set_source(normaldungeon);
  set_dungeon(arcatraz);
  set_ArmorClass(ArmorClass::Plate);
}

GauntletsOfTheBold::GauntletsOfTheBold()
{
  set_name("Gauntlets of the Bold");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 728);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_prim_stat(PrimaryAttributes::Agility, 16);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::DefenseRating, 14);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ParryRating, 3);
  set_source(normaldungeon);
  set_dungeon(steamvault);
  set_ArmorClass(ArmorClass::Plate);
}

ThatiasSelfCorrectingGauntlets::ThatiasSelfCorrectingGauntlets()
{
  set_name("Thatia''s Self-Correcting Gauntlets");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 728);
  set_prim_stat(PrimaryAttributes::Strength, 16);
  set_prim_stat(PrimaryAttributes::Stamina, 35);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::BlockValue, 40);
  set_source(normaldungeon);
  set_dungeon(arcatraz);
}

GauntletsOfTheChosen::GauntletsOfTheChosen()
{
  set_name("Gauntlets of the Chosen");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 728);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_sec_stat(SecondaryAttributes::DefenseRating, 35);
  set_source(reputation);
  set_faction(scryers);
  set_ArmorClass(ArmorClass::Plate);
}

DauntlessHandguards::DauntlessHandguards()
{
  set_name("Dauntless Handguards");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 722);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 25);
  set_sec_stat(SecondaryAttributes::BlockValue, 39);
  set_source(groupquest);
}

LegplatesOfTheBold::LegplatesOfTheBold()
{
  set_name("Legplates of the Bold");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 1019);
  set_prim_stat(PrimaryAttributes::Strength, 31);
  set_prim_stat(PrimaryAttributes::Agility, 19);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_source(normaldungeon);
  set_dungeon(black_morast);
  set_ArmorClass(ArmorClass::Plate);
}

ShatariWroughtGreaves::ShatariWroughtGreaves()
{
  set_name("Sha''tari Wrought Greaves");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 800);
  set_prim_stat(PrimaryAttributes::Strength, 24);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_red(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 3);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Plate);
}

SabatonsOfTheRighteousDefender::SabatonsOfTheRighteousDefender()
{
  set_name("Sabatons of the Righteous Defender");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 1105);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_sec_stat(SecondaryAttributes::BlockValue, 30);
  set_sec_stat(SecondaryAttributes::SpellPower, 23);
  set_red(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_source(boj);
  set_ArmorClass(ArmorClass::Plate);
  set_phase(4);
}

AzureShieldOfColdarra::AzureShieldOfColdarra()
{
  set_prim_stat(PrimaryAttributes::Armor, 4668);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::BlockValue, 115 + 34);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_name("Azure-Shield of Coldarra");
  set_slot(Slot::Offhand);
  set_source(boj);
  set_phase(1);
  set_ArmorClass(ArmorClass::Shield);
}

BattlemastersAudacity::BattlemastersAudacity()
{
  set_name("Battlemaster''s Audacity");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::SpellPower, 48);
  set_uptime(15.0);
  set_cd(180.0);
  set_source(boj);
  set_phase(4);
}

void BattlemastersAudacity::activate()
{
  if (!is_active())
  {
    activate();
    set_prim_stat(PrimaryAttributes::Health, 1751);
  }
}

void BattlemastersAudacity::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_prim_stat(PrimaryAttributes::Health, 0);
  }
}

BonefistGauntlets::BonefistGauntlets()
{
  set_name("Bonefist Gauntlets");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 1005);
  set_prim_stat(PrimaryAttributes::Stamina, 51);
  set_sec_stat(SecondaryAttributes::ParryRating, 30);
  set_sec_stat(SecondaryAttributes::HitRating, 21);
  set_red(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_source(boj);
  set_phase(4);
  set_ArmorClass(ArmorClass::Plate);
}

BracersOfTheAncientPhalanx::BracersOfTheAncientPhalanx()
{
  set_name("Bracers of the Ancient Phalanx");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 703);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 22);
  set_source(boj);
  set_phase(4);
}

ChestguardOfTheStoicGuardian::ChestguardOfTheStoicGuardian()
{
  set_name("Chestguard of the Stoic Guardian");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 1607);
  set_prim_stat(PrimaryAttributes::Stamina, 60);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_sec_stat(SecondaryAttributes::DodgeRating, 38);
  set_sec_stat(SecondaryAttributes::SpellPower, 36);
  set_red(1);
  set_yellow(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 6);
  set_source(boj);
  set_phase(4);
  set_ArmorClass(ArmorClass::Plate);
}

GirdleOfTheProtector::GirdleOfTheProtector()
{
  set_prim_stat(PrimaryAttributes::Armor, 904);
  set_prim_stat(PrimaryAttributes::Stamina, 40);
  set_sec_stat(SecondaryAttributes::DodgeRating, 27);
  set_sec_stat(SecondaryAttributes::DefenseRating, 11);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 18);
  set_sec_stat(SecondaryAttributes::SpellPower, 24);
  set_blue(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_name("Girdle of the Protector");
  set_slot(Slot::Belt);
  set_source(boj);
  set_phase(4);
}

GnomereganAutoBlocker600::GnomereganAutoBlocker600()
{
  set_sec_stat(SecondaryAttributes::BlockValue, 59);
  set_name("Gnomeregan Auto-Blocker 600");
  set_slot(Slot::Trinket);
  set_uptime(20.0);
  set_cd(120.0);
  set_source(boj);
  set_phase(1);
}

void GnomereganAutoBlocker600::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::BlockValue, 259);
  }
}

void GnomereganAutoBlocker600::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::BlockValue, 59);
  }
}

LibramOfRepentance::LibramOfRepentance()
{
  set_name("Libram of Repentance");
  set_slot(Slot::Libram);
  set_source(boj);
  set_phase(1);
}

LibramOfDivinePurpose::LibramOfDivinePurpose()
{
  set_name("Libram of Divine Purpose");
  set_slot(Slot::Libram);
  set_source(boj);
  set_phase(4);
}

LibramOfTheEternalRest::LibramOfTheEternalRest()
{
  set_name("Libram of the Eternal Rest");
  set_slot(Slot::Libram);
  set_source(normaldungeon);
  set_dungeon(sethekk_halls);
  set_phase(1);
}

UnwaveringLegguards::UnwaveringLegguards()
{
  set_name("Unwavering Legguards");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 1406);
  set_prim_stat(PrimaryAttributes::Stamina, 73);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_sec_stat(SecondaryAttributes::BlockValue, 60);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 30);
  set_red(1);
  set_yellow(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 6);
  set_source(boj);
  set_phase(4);
  set_ArmorClass(ArmorClass::Plate);
}

CharmOfAlacrity::CharmOfAlacrity()
{
  set_name("Charm of Alacrity");
  set_slot(Slot::Trinket);
  set_uptime(10.0);
  set_cd(90.0);
  set_source(soloquest);
}

void CharmOfAlacrity::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::DodgeRating, 192);
  }
}

void CharmOfAlacrity::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::DodgeRating, 0);
  }
}

IdolOfTheRavenGoddess::IdolOfTheRavenGoddess()
{
  set_name("Idol of the Raven Goddess");
  set_slot(Slot::Relic);
  set_sec_stat(SecondaryAttributes::CritRating, 20);
  set_phase(3);
  set_source(groupquest);
}

FigurineOfTheColossus::FigurineOfTheColossus()
{
  set_name("Figurine of the Colossus");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 32);
  set_cd(120.0);
  set_uptime(20.0);
  set_source(normaldungeon);
  set_dungeon(shattered_halls);
}

void FigurineOfTheColossus::activate()
{
  if (!is_active())
  {
    activate();
  }
}

void FigurineOfTheColossus::deactivate()
{
  if (is_active())
  {
    deactivate();
  }
}

IronscaleWarCloak::IronscaleWarCloak()
{
  set_prim_stat(PrimaryAttributes::Stamina, 26);
  set_prim_stat(PrimaryAttributes::Armor, 78);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 19);
  set_sec_stat(SecondaryAttributes::BlockValue, 29);
  set_slot(Slot::Back);
  set_name("Ironscale War Cloak");
  set_source(heroicdungeon);
  set_dungeon(slave_pens);
}

SunguardLegplates::SunguardLegplates()
{
  set_prim_stat(PrimaryAttributes::Armor, 1544);
  set_prim_stat(PrimaryAttributes::Stamina, 78);
  set_sec_stat(SecondaryAttributes::DodgeRating, 35);
  set_sec_stat(SecondaryAttributes::DefenseRating, 43);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 23);
  set_slot(Slot::Legs);
  set_name("Sunguard Legplates");
  set_blue(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_source(boj);
  set_ArmorClass(ArmorClass::Plate);
  set_phase(3);
}

ChestplateOfStoicism::ChestplateOfStoicism()
{
  set_prim_stat(PrimaryAttributes::Armor, 1765);
  set_prim_stat(PrimaryAttributes::Stamina, 78);
  set_sec_stat(SecondaryAttributes::DodgeRating, 34);
  set_sec_stat(SecondaryAttributes::DefenseRating, 51);
  set_sec_stat(SecondaryAttributes::BlockValue, 39);
  set_slot(Slot::Chest);
  set_name("Chestplate of Stoicism");
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_source(boj);
  set_ArmorClass(ArmorClass::Plate);
  set_phase(3);
}

GirdleOfTheFearless::GirdleOfTheFearless()
{
  set_prim_stat(PrimaryAttributes::Armor, 993);
  set_prim_stat(PrimaryAttributes::Stamina, 58);
  set_sec_stat(SecondaryAttributes::HitRating, 23);
  set_sec_stat(SecondaryAttributes::DefenseRating, 34);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 22);
  set_slot(Slot::Belt);
  set_name("Girdle of the Fearless");
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_source(boj);
  set_phase(3);
}

InscribedLegplatesOfTheAldor::InscribedLegplatesOfTheAldor()
{
  set_prim_stat(PrimaryAttributes::Armor, 1544);
  set_prim_stat(PrimaryAttributes::Stamina, 78);
  set_sec_stat(SecondaryAttributes::DodgeRating, 43);
  set_sec_stat(SecondaryAttributes::DefenseRating, 25);
  set_sec_stat(SecondaryAttributes::SpellPower, 37);
  set_slot(Slot::Legs);
  set_name("Inscribed Legplates of the Aldor");
  set_red(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_source(boj);
  set_phase(3);
}

ShattrathProtectoratesBreastplate::ShattrathProtectoratesBreastplate()
{
  set_prim_stat(PrimaryAttributes::Armor, 1765);
  set_prim_stat(PrimaryAttributes::Stamina, 78);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 34);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_sec_stat(SecondaryAttributes::SpellPower, 60);
  set_slot(Slot::Chest);
  set_name("Shattrath Protectorate''s Breastplate");
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 2);
  set_source(boj);
  set_ArmorClass(ArmorClass::Plate);
  set_phase(3);
}

BluesGreavesOfTheRighteousGuardian::BluesGreavesOfTheRighteousGuardian()
{
  set_prim_stat(PrimaryAttributes::Armor, 1213);
  set_prim_stat(PrimaryAttributes::Stamina, 58);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 23);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 34);
  set_sec_stat(SecondaryAttributes::SpellPower, 26);
  set_slot(Slot::Boots);
  set_name("Blue''s Greaves of the Righteous Guardian");
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_source(boj);
  set_phase(3);
}

RingOfTheStalwartProtector::RingOfTheStalwartProtector()
{
  set_prim_stat(PrimaryAttributes::Armor, 392);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::DodgeRating, 28);
  set_slot(Slot::Ring);
  set_name("Ring of the Stalwart Protector");
  set_source(boj);
  set_phase(5);
}

RedHavocBoots::RedHavocBoots()
{
  set_prim_stat(PrimaryAttributes::Armor, 1105);
  set_prim_stat(PrimaryAttributes::Stamina, 49);
  set_sec_stat(SecondaryAttributes::DefenseRating, 32);
  set_sec_stat(SecondaryAttributes::BlockValue, 30);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 25);
  set_name("Red Havoc Boots");
  set_slot(Slot::Boots);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

MercilessGladiatorsGavel::MercilessGladiatorsGavel()
{
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::WeaponDamage, (18.0 + 113.0) / 2.0);
  set_prim_stat(PrimaryAttributes::AttackSpeed, 1.6);
  set_sec_stat(SecondaryAttributes::SpellPower, 225);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 15);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 18);
  set_slot(Slot::Mainhand);
  set_name("Merciless Gladiator''s Gavel");
  set_source(pvp);
  set_phase(2);
}

GladiatorsShieldWall::GladiatorsShieldWall()
{
  set_prim_stat(PrimaryAttributes::Armor, 5197);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::BlockValue, 134);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 29);
  set_name("Gladiator''s Shield Wall");
  set_slot(Slot::Offhand);
  set_source(pvp);
  set_phase(1);
}

BootsOfElusion::BootsOfElusion()
{
  set_prim_stat(PrimaryAttributes::Armor, 997);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::DodgeRating, 38);
  set_name("Boots of Elusion");
  set_slot(Slot::Boots);
  set_source(raid);
  set_raid(karazhan);
  set_ArmorClass(ArmorClass::Plate);
}

SpectralBandOfInnervation::SpectralBandOfInnervation()
{
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_prim_stat(PrimaryAttributes::Intelligence, 24);
  set_sec_stat(SecondaryAttributes::SpellPower, 29);
  set_name("Spectral Band of Innervation");
  set_slot(Slot::Ring);
  set_source(raid);
  set_raid(karazhan);
}

VambracesOfCourage::VambracesOfCourage()
{
  set_prim_stat(PrimaryAttributes::Armor, 634);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_sec_stat(SecondaryAttributes::BlockValue, 33);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 2);
  set_name("Vambraces of Courage");
  set_slot(Slot::Bracers);
  set_source(raid);
  set_raid(karazhan);
  set_ArmorClass(ArmorClass::Plate);
}

RoyalCloakOfArathiKings::RoyalCloakOfArathiKings()
{
  set_prim_stat(PrimaryAttributes::Armor, 97);
  set_prim_stat(PrimaryAttributes::Strength, 26);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::HitRating, 16);
  set_name("Royal Cloak of Arathi Kings");
  set_slot(Slot::Back);
  set_source(raid);
  set_raid(karazhan);
}

ShadowCloakOfDalaran::ShadowCloakOfDalaran()
{
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::Armor, 97);
  set_prim_stat(PrimaryAttributes::Stamina, 19);
  set_sec_stat(SecondaryAttributes::SpellPower, 36);
  set_name("Shadow Cloak of Dalaran");
  set_slot(Slot::Back);
  set_source(raid);
  set_raid(karazhan);
}

CrimsonGirdleOfTheIndomitable::CrimsonGirdleOfTheIndomitable()
{
  set_prim_stat(PrimaryAttributes::Armor, 816);
  set_prim_stat(PrimaryAttributes::Strength, 16);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ParryRating, 3);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 20);
  set_name("Crimson Girdle of the Indomitable");
  set_slot(Slot::Belt);
  set_source(raid);
  set_raid(karazhan);
}

BroochOfUnquenchableFury::BroochOfUnquenchableFury()
{
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Intelligence, 21);
  set_sec_stat(SecondaryAttributes::SpellhitRating, 15);
  set_sec_stat(SecondaryAttributes::SpellPower, 26);
  set_name("Brooch of Unquenchable Fury");
  set_slot(Slot::Neck);
  set_source(raid);
  set_raid(karazhan);
}

MoroesLuckyPocketWatch::MoroesLuckyPocketWatch()
{
  set_sec_stat(SecondaryAttributes::DodgeRating, 38);
  set_name("Moroes'' Lucky Pocket Watch");
  set_slot(Slot::Trinket);
  set_uptime(10.0);
  set_cd(120.0);
  set_source(raid);
  set_raid(karazhan);
}

void MoroesLuckyPocketWatch::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::DodgeRating, 338);
  }
}

void MoroesLuckyPocketWatch::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::DodgeRating, 38);
  }
}

IronGauntletsOfTheMaiden::IronGauntletsOfTheMaiden()
{
  set_prim_stat(PrimaryAttributes::Armor, 906);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::BlockChanceRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 17);
  set_sec_stat(SecondaryAttributes::BlockValue, 38);
  set_name("Iron Gauntlets of the Maiden");
  set_slot(Slot::Hands);
  set_source(raid);
  set_raid(karazhan);
  set_ArmorClass(ArmorClass::Plate);
}

BarbedChokerOfDiscipline::BarbedChokerOfDiscipline()
{
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::DodgeRating, 21);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_slot(Slot::Neck);
  set_name("Barbed Choker of Discipline");
  set_source(raid);
  set_raid(karazhan);
}

EterniumGreathelm::EterniumGreathelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1178);
  set_prim_stat(PrimaryAttributes::Strength, 31);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_red(1);
  set_yellow(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 34);
  set_name("Eternium Greathelm");
  set_slot(Slot::Head);
  set_source(raid);
  set_raid(karazhan);
}

WrynnDynastyGreaves::WrynnDynastyGreaves()
{
  set_prim_stat(PrimaryAttributes::Armor, 1269);
  set_prim_stat(PrimaryAttributes::Strength, 24);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_red(1);
  set_yellow(2);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 6);
  set_sec_stat(SecondaryAttributes::DefenseRating, 27);
  set_sec_stat(SecondaryAttributes::DodgeRating, 29);
  set_name("Wrynn Dynasty Greaves");
  set_slot(Slot::Legs);
  set_source(raid);
  set_raid(karazhan);
}

GildedThoriumCloak::GildedThoriumCloak()
{
  set_prim_stat(PrimaryAttributes::Armor, 385);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_name("Gilded Thorium Cloak");
  set_slot(Slot::Back);
  set_source(raid);
  set_raid(karazhan);
}

ShermanarGreatRing::ShermanarGreatRing()
{
  set_prim_stat(PrimaryAttributes::Armor, 223);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_name("Shermanar Great Ring");
  set_slot(Slot::Ring);
  set_source(raid);
  set_raid(karazhan);
}

MantleOfAbrahmis::MantleOfAbrahmis()
{
  set_prim_stat(PrimaryAttributes::Armor, 1087);
  set_prim_stat(PrimaryAttributes::Strength, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 43);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_name("Mantle of Abrahmis");
  set_slot(Slot::Shoulders);
  set_source(raid);
  set_raid(karazhan);
}

PanzarTharBreastplate::PanzarTharBreastplate()
{
  set_prim_stat(PrimaryAttributes::Armor, 1450);
  set_prim_stat(PrimaryAttributes::Stamina, 51);
  set_yellow(1);
  set_blue(2);
  set_bonus_sec_stat(SecondaryAttributes::BlockChanceRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 24);
  set_sec_stat(SecondaryAttributes::BlockValue, 39);
  set_name("Panzar''Thar Breastplate");
  set_slot(Slot::Chest);
  set_source(raid);
  set_raid(karazhan);
}

IronstridersOfUrgency::IronstridersOfUrgency()
{
  set_prim_stat(PrimaryAttributes::Armor, 997);
  set_prim_stat(PrimaryAttributes::Strength, 33);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_red(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 3);
  set_name("Ironstriders Of Urgency");
  set_slot(Slot::Boots);
  set_source(raid);
  set_raid(karazhan);
  set_ArmorClass(ArmorClass::Plate);
}

ShieldOfImpenetrableDarkness::ShieldOfImpenetrableDarkness()
{
  set_prim_stat(PrimaryAttributes::Armor, 4872);
  set_sec_stat(SecondaryAttributes::BlockValue, 122 + 33);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 22);
  set_slot(Slot::Offhand);
  set_name("Shield of Impenetrable Darkness");
  set_source(raid);
  set_raid(karazhan);
  set_ArmorClass(ArmorClass::Shield);
}

BattlescarBoots::BattlescarBoots()
{
  set_prim_stat(PrimaryAttributes::Armor, 997);
  set_prim_stat(PrimaryAttributes::Strength, 18);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_red(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::ParryRating, 3);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::ParryRating, 21);
  set_slot(Slot::Boots);
  set_name("Battlescar Boots");
  set_source(raid);
  set_raid(karazhan);
}

MithrilChainOfHeroism::MithrilChainOfHeroism()
{
  set_prim_stat(PrimaryAttributes::Strength, 28);
  set_prim_stat(PrimaryAttributes::Agility, 22);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_slot(Slot::Neck);
  set_name("Mithril Chain of Heroism");
  set_source(raid);
  set_raid(karazhan);
}

BandOfUrsol::BandOfUrsol()
{
  set_prim_stat(PrimaryAttributes::Strength, 23);
  set_prim_stat(PrimaryAttributes::Agility, 12);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_slot(Slot::Ring);
  set_name("Band Of Ursol");
  set_source(heroicdungeon);
  set_dungeon(slave_pens);
}

RingOfTheSilverHand::RingOfTheSilverHand()
{
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::MP5, 5);
  set_slot(Slot::Ring);
  set_name("Ring of the Silver Hand");
  set_source(normaldungeon);
  set_dungeon(steamvault);
}

RingOfTheStonebark::RingOfTheStonebark()
{
  set_prim_stat(PrimaryAttributes::Agility, 12);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_slot(Slot::Ring);
  set_name("Ring of the Stonebark");
  set_source(soloquest);
}

JusticarFaceguard::JusticarFaceguard()
{ // Karazhan
  set_prim_stat(PrimaryAttributes::Armor, 1227);
  set_prim_stat(PrimaryAttributes::Stamina, 43);
  set_prim_stat(PrimaryAttributes::Intelligence, 24);
  set_yellow(1);
  set_meta(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 29);
  set_sec_stat(SecondaryAttributes::DodgeRating, 24);
  set_sec_stat(SecondaryAttributes::SpellPower, 27);
  set_name("Justicar Faceguard");
  set_slot(Slot::Head);
  //(2):SoR,SoV, SoB +10%Dmg
  //(4):HS +15%Dmg
  set_source(raid);
  set_raid(karazhan);
  mark_as_set_piece();
}

JusticarShoulderguards::JusticarShoulderguards()
{ // Gruul
  set_prim_stat(PrimaryAttributes::Armor, 1133);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_prim_stat(PrimaryAttributes::Intelligence, 14);
  set_blue(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 15);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 17);
  set_sec_stat(SecondaryAttributes::SpellPower, 26);
  set_sec_stat(SecondaryAttributes::BlockValue, 27);
  set_name("Justicar Shoulderguards");
  set_slot(Slot::Shoulders);
  // Set
  set_source(raid);
  set_raid(gruuls_lair);
  mark_as_set_piece();
}

JusticarChestguard::JusticarChestguard()
{ // Magtheridon
  set_prim_stat(PrimaryAttributes::Armor, 1510);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_prim_stat(PrimaryAttributes::Intelligence, 30);
  set_red(1);
  set_blue(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::BlockChanceRating, 23);
  set_sec_stat(SecondaryAttributes::SpellPower, 27);
  set_name("Justicar Chestguard");
  set_slot(Slot::Chest);
  // Set
  set_source(raid);
  set_raid(magtheridon);
  mark_as_set_piece();
}

JusticarHandguard::JusticarHandguard()
{ // Karazhan
  set_prim_stat(PrimaryAttributes::Armor, 944);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_prim_stat(PrimaryAttributes::Intelligence, 24);
  set_sec_stat(SecondaryAttributes::DefenseRating, 23);
  set_sec_stat(SecondaryAttributes::SpellPower, 27);
  set_sec_stat(SecondaryAttributes::BlockValue, 35);
  set_name("Justicar Handguard");
  set_slot(Slot::Hands);
  // Set
  set_source(raid);
  set_raid(karazhan);
  mark_as_set_piece();
}

JusticarLegguards::JusticarLegguards()
{ // Gruul
  set_prim_stat(PrimaryAttributes::Armor, 1322);
  set_prim_stat(PrimaryAttributes::Stamina, 46);
  set_prim_stat(PrimaryAttributes::Intelligence, 31);
  set_sec_stat(SecondaryAttributes::DefenseRating, 31);
  set_sec_stat(SecondaryAttributes::ParryRating, 31);
  set_sec_stat(SecondaryAttributes::SpellPower, 36);
  set_name("Justicar Legguards");
  set_slot(Slot::Legs);
  // Set
  set_source(raid);
  set_raid(gruuls_lair);
  mark_as_set_piece();
}

AldoriLegacyDefender::AldoriLegacyDefender()
{ // Gruul
  set_prim_stat(PrimaryAttributes::Armor, 5279);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::BlockValue, 137);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DefenseRating, 2);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_sec_stat(SecondaryAttributes::HitRating, 15);
  set_name("Aldori Legacy Defender");
  set_slot(Slot::Offhand);
  set_source(raid);
  set_raid(gruuls_lair);
}

ThunderingGreathelm::ThunderingGreathelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1276);
  set_prim_stat(PrimaryAttributes::Strength, 50);
  set_prim_stat(PrimaryAttributes::Agility, 43);
  set_prim_stat(PrimaryAttributes::Stamina, 49);
  set_name("Thundering Greathelm");
  set_slot(Slot::Head);
  set_source(raid);
  set_raid(magtheridon);
  set_ArmorClass(ArmorClass::Plate);
}

AdalsSignetOfDefense::AdalsSignetOfDefense()
{ // Magtheridon
  set_prim_stat(PrimaryAttributes::Armor, 367);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_name("Adal''s Signet of Defense");
  set_slot(Slot::Ring);
  set_source(raid);
  set_raid(magtheridon);
}

VioletSignet::VioletSignet()
{
  set_name("Violet Signet");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Armor, 392);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_sec_stat(SecondaryAttributes::DefenseRating, 19);
  set_source(raid);
  set_raid(karazhan);
}

SlikksCloakOfPlacation::SlikksCloakOfPlacation()
{
  set_name("Slikk''s Cloak of Placation");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 346);
  set_prim_stat(PrimaryAttributes::Stamina, 37);
  set_sec_stat(SecondaryAttributes::DefenseRating, 16);
  set_sec_stat(SecondaryAttributes::DodgeRating, 25);
  set_source(boj);
  set_phase(4);
}

IrontuskGirdle::IrontuskGirdle()
{
  set_name("Iron-Tusk Girdle");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 904);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::DodgeRating, 33);
  set_sec_stat(SecondaryAttributes::DefenseRating, 21);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_blue(1);
  set_yellow(1);
  set_source(boj);
  set_phase(4);
  set_ArmorClass(ArmorClass::Plate);
}

IceguardBreastplate::IceguardBreastplate()
{
  set_prim_stat(PrimaryAttributes::Armor, 1450);
  set_prim_stat(PrimaryAttributes::Stamina, 49);
  set_prim_stat(PrimaryAttributes::FrostResistance, 60);
  set_sec_stat(SecondaryAttributes::DefenseRating, 10);
  set_name("Iceguard Breastplate");
  set_slot(Slot::Chest);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

IceguardHelm::IceguardHelm()
{
  set_prim_stat(PrimaryAttributes::Armor, 1030);
  set_prim_stat(PrimaryAttributes::Stamina, 64);
  set_prim_stat(PrimaryAttributes::FrostResistance, 50);
  set_sec_stat(SecondaryAttributes::DefenseRating, 20);
  set_slot(Slot::Head);
  set_name("Iceguard Helm");
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

IceguardLeggings::IceguardLeggings()
{
  set_prim_stat(PrimaryAttributes::Armor, 1110);
  set_prim_stat(PrimaryAttributes::Stamina, 55);
  set_prim_stat(PrimaryAttributes::FrostResistance, 60);
  set_slot(Slot::Legs);
  set_name("Iceguard Leggings");
  set_source(crafting);
  set_ArmorClass(ArmorClass::Plate);
}

PendantOfThawing::PendantOfThawing()
{
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_prim_stat(PrimaryAttributes::FrostResistance, 30);
  set_name("Pendant of Thawing");
  set_slot(Slot::Neck);
  set_source(crafting);
}

TheFrozenEye::TheFrozenEye()
{
  set_name("The Frozen Eye");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Stamina, 12);
  set_prim_stat(PrimaryAttributes::FrostResistance, 35);
  set_source(crafting);
}

MurkbloodCoverOfTheBandit::MurkbloodCoverOfTheBandit()
{
  set_name("Murkblood Cover of the Bandit");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 214);
  set_prim_stat(PrimaryAttributes::Agility, 27);
  set_prim_stat(PrimaryAttributes::Stamina, 41);
  set_sec_stat(SecondaryAttributes::AttackPower, 55);
  set_source(randomdrop);
  set_ArmorClass(ArmorClass::Leather);
}

SpauldersOfTheRing::SpauldersOfTheRing()
{
  set_name("Spaulders of the Ring");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 183);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_sec_stat(SecondaryAttributes::CritRating, 19);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_source(randomdrop);
}

PerfectlyBalancedCape::PerfectlyBalancedCape()
{
  set_name("Perfectly Balanced Cape");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 61);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::AttackPower, 30);
  set_source(randomdrop);
}

HeavyClefthoofVest::HeavyClefthoofVest()
{
  set_name("Heavy Clefthoof Vest");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 500);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_yellow(2);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 24);
  set_source(crafting);
  mark_as_set_piece();
}

UmberhowlsCollar::UmberhowlsCollar()
{
  set_name("Umberhowl''s Collar");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 281);
  set_prim_stat(PrimaryAttributes::Agility, 10);
  set_prim_stat(PrimaryAttributes::Strength, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Leather);
}

SmugglersMitts::SmugglersMitts()
{
  set_name("Smuggler''s Mitts");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 152);
  set_prim_stat(PrimaryAttributes::Agility, 19);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_source(randomdrop);
  set_ArmorClass(ArmorClass::Leather);
}

ManimalsCinch::ManimalsCinch()
{
  set_name("Manimal''s Cinch");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 348);
  set_prim_stat(PrimaryAttributes::Agility, 12);
  set_prim_stat(PrimaryAttributes::Strength, 23);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_source(randomdrop);
  set_ArmorClass(ArmorClass::Leather);
}

HeavyClefthoofLeggings::HeavyClefthoofLeggings()
{
  set_name("Heavy Clefthoof Leggings");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 503);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_blue(2);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::DefenseRating, 29);
  set_source(crafting);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

HeavyClefthoofBoots::HeavyClefthoofBoots()
{
  set_name("Heavy Clefthoof Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 394);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_yellow(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_sec_stat(SecondaryAttributes::DefenseRating, 21);
  set_source(crafting);
  mark_as_set_piece();
}

OgreSlayersBand::OgreSlayersBand()
{
  set_name("Ogre Slayer''s Band");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_prim_stat(PrimaryAttributes::Agility, 16);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_source(soloquest);
}

TerokkarTabletOfPrecision::TerokkarTabletOfPrecision()
{
  set_name("Terokkar Tablet of Precision");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::HitRating, 22);
  set_source(soloquest);
}

RegalProtectorate::RegalProtectorate()
{
  set_name("Regal Protectorate");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::DefenseRating, 26);
  set_source(groupquest);
}

StaffOfBeasts::StaffOfBeasts()
{
  set_name("Staff of Beasts");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Strength, 31);
  set_prim_stat(PrimaryAttributes::Agility, 30);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_sec_stat(SecondaryAttributes::AttackPower, 375);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Staff);
}

GladiatorsDragonhideHelm::GladiatorsDragonhideHelm()
{
  set_name("Gladiator''s Dragonhide Helm");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 356);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_prim_stat(PrimaryAttributes::Strength, 33);
  set_prim_stat(PrimaryAttributes::Intelligence, 19);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 24);
  set_sec_stat(SecondaryAttributes::Healing, 46);
  set_sec_stat(SecondaryAttributes::SpellPower, 16);
  set_meta(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 4);
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

DeathblowX11Goggles::DeathblowX11Goggles()
{
  set_name("Deathblow X11 Goggles");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 326);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_prim_stat(PrimaryAttributes::Agility, 48);
  set_meta(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 4);
  set_sec_stat(SecondaryAttributes::HitRating, 11);
  set_sec_stat(SecondaryAttributes::AttackPower, 76);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Leather);
}

HelmOfTheClaw::HelmOfTheClaw()
{
  set_name("Helm of the Claw");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 237);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_meta(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 4);
  set_sec_stat(SecondaryAttributes::HitRating, 14);
  set_sec_stat(SecondaryAttributes::AttackPower, 66);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

WastewalkerHelm::WastewalkerHelm()
{
  set_name("Wastewalker Helm");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 237);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_meta(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 8);
  set_sec_stat(SecondaryAttributes::CritRating, 22);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_source(heroicdungeon);
  set_dungeon(ohf);
  mark_as_set_piece();
}

CobrascaleHood::CobrascaleHood()
{
  set_name("Cobrascale Hood");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 271);
  set_prim_stat(PrimaryAttributes::Agility, 37);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 74);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Leather);
}

HelmOfAssassination::HelmOfAssassination()
{
  set_name("Helm of Assassination");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 237);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_yellow(1);
  set_meta(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::CritRating, 25);
  set_sec_stat(SecondaryAttributes::AttackPower, 66);
  set_source(normaldungeon);
  set_dungeon(arcatraz);
  mark_as_set_piece();
}

StealthersHelmetOfSecondSight::StealthersHelmetOfSecondSight()
{
  set_name("Stealther''s Helmet of Second Sight");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 226);
  set_prim_stat(PrimaryAttributes::Agility, 24);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_red(1);
  set_blue(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 8);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

ExorcistsLeatherHelm::ExorcistsLeatherHelm()
{
  set_name("Exorcist''s Leather Helm");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 208);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Agility, 27);
  set_meta(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 6);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 14);
  set_sec_stat(SecondaryAttributes::CritRating, 10);
  set_sec_stat(SecondaryAttributes::AttackPower, 20);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
}

StylinPurpleHat::StylinPurpleHat()
{
  set_name("Stylin'' Purple Hat");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 232);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_prim_stat(PrimaryAttributes::Agility, 48);
  set_source(crafting);
  set_ArmorClass(ArmorClass::Leather);
}

EnergizedHelm::EnergizedHelm()
{
  set_name("Energized Helm");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 203);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_prim_stat(PrimaryAttributes::Agility, 26);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 52);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Leather);
}

NecklaceOfTheDeep::NecklaceOfTheDeep()
{
  set_name("Necklace of the Deep");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 20);
  set_red(2);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 3);
  set_source(crafting);
}

PendantOfTriumph::PendantOfTriumph()
{
  set_name("Pendant of Triumph");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_sec_stat(SecondaryAttributes::CritRating, 10);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 2);
  set_source(pvp);
}

BoneChainNecklace::BoneChainNecklace()
{
  set_name("Bone Chain Necklace");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Agility, 19);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_source(heroicdungeon);
  set_dungeon(underbog);
}

ChokerOfVileIntent::ChokerOfVileIntent()
{
  set_name("Choker of Vile Intent");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 42);
  set_source(boj);
  set_phase(1);
}

MaimfistsChoker::MaimfistsChoker()
{
  set_name("Maimfist''s Choker");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 17);
  set_sec_stat(SecondaryAttributes::DefenseRating, 18);
  set_source(groupquest);
}

InsigniaOfTheMaghariHero::InsigniaOfTheMaghariHero()
{
  set_name("Insignia of the Mag''hari Hero");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 14);
  set_sec_stat(SecondaryAttributes::CritRating, 15);
  set_sec_stat(SecondaryAttributes::AttackPower, 30);
  set_source(soloquest);
}

GladiatorsDragonhideSpaulders::GladiatorsDragonhideSpaulders()
{
  set_name("Gladiator''s Dragonhide Spaulders");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 331);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Strength, 28);
  set_prim_stat(PrimaryAttributes::Intelligence, 12);
  set_prim_stat(PrimaryAttributes::Agility, 17);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 3);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 18);
  set_sec_stat(SecondaryAttributes::Healing, 29);
  set_sec_stat(SecondaryAttributes::SpellPower, 10);
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

ShoulderpadsOfAssassination::ShoulderpadsOfAssassination()
{
  set_name("Shoulderpads of Assassination");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 219);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::AttackPower, 42);
  set_yellow(2);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_source(normaldungeon);
  set_dungeon(sethekk_halls);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

WastewalkerShoulderpads::WastewalkerShoulderpads()
{
  set_name("Wastewalker Shoulderpads");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 219);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 13);
  set_sec_stat(SecondaryAttributes::HitRating, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 34);
  set_red(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::CritRating, 3);
  set_source(heroicdungeon);
  set_dungeon(auchenaicrypt);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

MantleOfPerenolde::MantleOfPerenolde()
{
  set_name("Mantle of Perenolde");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 197);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_red(2);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_sec_stat(SecondaryAttributes::CritRating, 23);
  set_sec_stat(SecondaryAttributes::HitRating, 23);
  set_sec_stat(SecondaryAttributes::AttackPower, 20);
  set_source(normaldungeon);
  set_dungeon(ohf);
}

MantleOfShadowyEmbrace::MantleOfShadowyEmbrace()
{
  set_name("Mantle of Shadowy Embrace");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 262);
  set_prim_stat(PrimaryAttributes::Agility, 39);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::AttackPower, 34);
  set_source(heroicdungeon);
  set_dungeon(blood_furnace);
  set_ArmorClass(ArmorClass::Leather);
}

MantleOfTheUnforgiven::MantleOfTheUnforgiven()
{
  set_name("Mantle of the Unforgiven");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 219);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::CritRating, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 12);
  set_sec_stat(SecondaryAttributes::AttackPower, 52);
  set_source(heroicdungeon);
  set_dungeon(manatomb);
}

TalbukHideSpaulders::TalbukHideSpaulders()
{
  set_name("Talbuk Hide Spaulders");
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 219);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_sec_stat(SecondaryAttributes::HitRating, 15);
  set_sec_stat(SecondaryAttributes::AttackPower, 70);
  set_source(reputation);
  set_faction(the_maghar);
  set_ArmorClass(ArmorClass::Leather);
}

SergeantsHeavyCloak::SergeantsHeavyCloak()
{
  set_name("Sergeant''s Heavy Cloak");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 104);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 19);
  set_sec_stat(SecondaryAttributes::CritRating, 19);
  set_sec_stat(SecondaryAttributes::AttackPower, 38);
  set_source(pvp);
}

BloodKnightWarCloak::BloodKnightWarCloak()
{
  set_name("Blood Knight War Cloak");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 93);
  set_prim_stat(PrimaryAttributes::Agility, 23);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_sec_stat(SecondaryAttributes::AttackPower, 48);
  set_source(boj);
  set_phase(1);
}

AuchenaiDeathShroud::AuchenaiDeathShroud()
{
  set_name("Auchenai Death Shroud");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 78);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_source(heroicdungeon);
  set_dungeon(auchenaicrypt);
}

DelicateGreenPoncho::DelicateGreenPoncho()
{
  set_name("Delicate Green Poncho");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 66);
  set_prim_stat(PrimaryAttributes::Stamina, 19);
  set_prim_stat(PrimaryAttributes::Agility, 14);
  set_sec_stat(SecondaryAttributes::HitRating, 14);
  set_sec_stat(SecondaryAttributes::AttackPower, 28);
  set_source(groupquest);
}

VengeanceWrap::VengeanceWrap()
{
  set_name("Vengeance Wrap");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 89);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 2);
  set_sec_stat(SecondaryAttributes::CritRating, 23);
  set_sec_stat(SecondaryAttributes::AttackPower, 52);
  set_source(crafting);
}

NomadsWovenCloak::NomadsWovenCloak()
{
  set_name("Nomad''s Woven Cloak");
  set_slot(Slot::Back);
  set_prim_stat(PrimaryAttributes::Armor, 66);
  set_prim_stat(PrimaryAttributes::Strength, 14);
  set_prim_stat(PrimaryAttributes::Agility, 14);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_source(groupquest);
}

GladiatorsDragonhideTunic::GladiatorsDragonhideTunic()
{
  set_name("Gladiator''s Dragonhide Tunic");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 429);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_prim_stat(PrimaryAttributes::Strength, 32);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_red(2);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::CritRating, 4);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 26);
  set_sec_stat(SecondaryAttributes::Healing, 29);
  set_sec_stat(SecondaryAttributes::SpellPower, 10);
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

WastewalkerTunic::WastewalkerTunic()
{
  set_name("Wastewalker Tunic");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 292);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_yellow(3);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 4);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_source(heroicdungeon);
  set_dungeon(blood_furnace);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

PrimalstrikeVest::PrimalstrikeVest()
{
  set_name("Primalstrike Vest");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 379);
  set_prim_stat(PrimaryAttributes::Agility, 38);
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::HitRating, 12);
  set_sec_stat(SecondaryAttributes::AttackPower, 108);
  set_source(crafting);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

TunicOfAssassination::TunicOfAssassination()
{
  set_name("Tunic of Assassination");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 292);
  set_prim_stat(PrimaryAttributes::Agility, 28);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::AttackPower, 54);
  set_red(2);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_source(normaldungeon);
  set_dungeon(mechanar);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

IllidariLordsTunic::IllidariLordsTunic()
{
  set_name("Illidari Lord''s Tunic");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 263);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_red(1);
  set_blue(2);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 4);
  set_sec_stat(SecondaryAttributes::AttackPower, 44);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Leather);
}

VestOfVengeance::VestOfVengeance()
{
  set_name("Vest of Vengeance");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 232);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_prim_stat(PrimaryAttributes::Agility, 27);
  set_red(1);
  set_yellow(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 4);
  set_sec_stat(SecondaryAttributes::HitRating, 11);
  set_sec_stat(SecondaryAttributes::AttackPower, 42);
  set_source(normaldungeon);
  set_dungeon(blood_furnace);
  set_ArmorClass(ArmorClass::Leather);
}

ChestguardOfTheProwler::ChestguardOfTheProwler()
{
  set_name("Chestguard of the Prowler");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 292);
  set_prim_stat(PrimaryAttributes::Agility, 31);
  set_prim_stat(PrimaryAttributes::Stamina, 26);
  set_sec_stat(SecondaryAttributes::ParryRating, 16);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 70);
  set_source(heroicdungeon);
  set_dungeon(ramparts);
  set_ArmorClass(ArmorClass::Leather);
}

AuchenaiMonksTunic::AuchenaiMonksTunic()
{
  set_name("Auchenai Monk''s Tunic");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 255);
  set_prim_stat(PrimaryAttributes::Agility, 24);
  set_red(2);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 6);
  set_sec_stat(SecondaryAttributes::HitRating, 19);
  set_sec_stat(SecondaryAttributes::DodgeRating, 24);
  set_sec_stat(SecondaryAttributes::AttackPower, 18);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

VindicatorsLeatherBracers::VindicatorsLeatherBracers()
{
  set_name("Vindicators''s Leather Bracers");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 194);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 2);
  set_sec_stat(SecondaryAttributes::CritRating, 12);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 15);
  set_sec_stat(SecondaryAttributes::AttackPower, 26);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

ShardboundBracers::ShardboundBracers()
{
  set_name("Shard-bound Bracers");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 146);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 4);
  set_sec_stat(SecondaryAttributes::AttackPower, 42);
  set_source(reputation);
  set_faction(ogrila);
  set_ArmorClass(ArmorClass::Leather);
}

NightfallWristguards::NightfallWristguards()
{
  set_name("Nightfall Wristguards");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 153);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_prim_stat(PrimaryAttributes::Agility, 24);
  set_sec_stat(SecondaryAttributes::AttackPower, 46);
  set_source(heroicdungeon);
  set_dungeon(ohf);
  set_ArmorClass(ArmorClass::Leather);
}

PrimalstrikeBracers::PrimalstrikeBracers()
{
  set_name("Primalstrike Bracers");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 159);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::AttackPower, 64);
  set_source(crafting);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

ShacklesOfQuagmirran::ShacklesOfQuagmirran()
{
  set_name("Shackles of Quagmirran");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 128);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 40);
  set_source(heroicdungeon);
  set_dungeon(slave_pens);
}

SpymistresssWristguards::SpymistresssWristguards()
{
  set_name("Spymistress''s Wristguards");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 128);
  set_prim_stat(PrimaryAttributes::Agility, 18);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 2);
  set_sec_stat(SecondaryAttributes::HitRating, 15);
  set_source(groupquest);
}

WastewalkerGloves::WastewalkerGloves()
{
  set_name("Wastewalker Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 183);
  set_prim_stat(PrimaryAttributes::Agility, 32);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::AttackPower, 16);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::DodgeRating, 3);
  set_source(normaldungeon);
  set_dungeon(shattered_halls);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

GlovesOfTheUnbound::GlovesOfTheUnbound()
{
  set_name("Gloves of the Unbound");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 183);
  set_prim_stat(PrimaryAttributes::Agility, 27);
  set_prim_stat(PrimaryAttributes::Stamina, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 38);
  set_red(1);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 3);
  set_source(normaldungeon);
  set_dungeon(arcatraz);
  set_ArmorClass(ArmorClass::Leather);
}

GladiatorsDragonhideGloves::GladiatorsDragonhideGloves()
{
  set_name("Gladiator''s Dragonhide Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 283);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 18);
  set_prim_stat(PrimaryAttributes::Agility, 19);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 20);
  set_sec_stat(SecondaryAttributes::Healing, 13);
  set_sec_stat(SecondaryAttributes::SpellPower, 5); // update tbcGear
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

VerdantGloves::VerdantGloves()
{
  set_name("Verdant Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 393);
  set_prim_stat(PrimaryAttributes::Agility, 14);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 26);
  set_source(groupquest);
}

CobrascaleGloves::CobrascaleGloves()
{
  set_name("Cobrascale Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 208);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::CritRating, 25);
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 50);
  set_source(crafting);
}

HandgripsOfAssassination::HandgripsOfAssassination()
{
  set_name("Handgrips of Assassination");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 183);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 50);
  set_source(normaldungeon);
  set_dungeon(black_morast);
  mark_as_set_piece();
}

FelLeatherGloves::FelLeatherGloves()
{
  set_name("Fel Leather Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 169);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::CritRating, 24);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_yellow(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 6);
  set_source(crafting);
  mark_as_set_piece();
}

GlovesOfTheNetherStalker::GlovesOfTheNetherStalker()
{
  set_name("Gloves of the Nether-Stalker");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 165);
  set_prim_stat(PrimaryAttributes::Stamina, 12);
  set_prim_stat(PrimaryAttributes::Agility, 16);
  set_sec_stat(SecondaryAttributes::HitRating, 8);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Leather);
}

PredatoryGloves::PredatoryGloves()
{
  set_name("Predatory Gloves");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 183);
  set_prim_stat(PrimaryAttributes::Stamina, 16);
  set_sec_stat(SecondaryAttributes::HitRating, 19);
  set_sec_stat(SecondaryAttributes::CritRating, 21);
  set_sec_stat(SecondaryAttributes::AttackPower, 48);
  set_source(heroicdungeon);
  set_dungeon(manatomb);
}

VindicatorsLeatherBelt::VindicatorsLeatherBelt()
{
  set_name("Vindicator''s Leather Belt");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 258);
  set_prim_stat(PrimaryAttributes::Stamina, 49);
  set_prim_stat(PrimaryAttributes::Agility, 33);
  set_sec_stat(SecondaryAttributes::CritRating, 19);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 40);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

DunewindSash::DunewindSash()
{
  set_name("Dunewind Sash");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 164);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 50);
  set_red(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 3);
  set_source(heroicdungeon);
  set_dungeon(underbog);
  set_ArmorClass(ArmorClass::Leather);
}

PrimalstrikeBelt::PrimalstrikeBelt()
{
  set_name("Primalstrike Belt");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 205);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 32);
  set_sec_stat(SecondaryAttributes::AttackPower, 84);
  set_source(crafting);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

GirdleOfTheDeathdealer::GirdleOfTheDeathdealer()
{
  set_name("Girdle of the Deathdealer");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 196);
  set_prim_stat(PrimaryAttributes::Agility, 28);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_source(heroicdungeon);
  set_dungeon(black_morast);
  set_ArmorClass(ArmorClass::Leather);
}

EpochsWhisperingCinch::EpochsWhisperingCinch()
{
  set_name("Epoch''s Whispering Cinch");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 164);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 40);
  set_source(heroicdungeon);
  set_dungeon(ohf);
  set_ArmorClass(ArmorClass::Leather);
}

SocretharsGirdle::SocretharsGirdle()
{
  set_name("Socrethar''s Girdle");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 156);
  set_prim_stat(PrimaryAttributes::Agility, 23);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 48);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

NaaruBeltOfPrecision::NaaruBeltOfPrecision()
{
  set_name("Naaru Belt of Precision");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 164);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_sec_stat(SecondaryAttributes::HitRating, 15);
  set_sec_stat(SecondaryAttributes::DodgeRating, 21);
  set_sec_stat(SecondaryAttributes::AttackPower, 44);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

TreeMendersBelt::TreeMendersBelt()
{
  set_name("Tree-Mender''s Belt");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 406);
  set_prim_stat(PrimaryAttributes::Agility, 27);
  set_prim_stat(PrimaryAttributes::Strength, 27);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_prim_stat(PrimaryAttributes::Intelligence, 21);
  set_source(heroicdungeon);
  set_dungeon(ramparts);
  set_ArmorClass(ArmorClass::Leather);
}

EvasStrap::EvasStrap()
{
  set_name("Eva''s Strap");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 148);
  set_sec_stat(SecondaryAttributes::HitRating, 12);
  set_sec_stat(SecondaryAttributes::CritRating, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_source(soloquest);
}

LeggingsOfTheUnrepentant::LeggingsOfTheUnrepentant()
{
  set_name("Leggings of the Unrepentant");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 256);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_red(1);
  set_yellow(1);
  set_blue(1);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 4);
  set_source(heroicdungeon);
  set_dungeon(blood_furnace);
  set_ArmorClass(ArmorClass::Leather);
}

WastewalkerLeggings::WastewalkerLeggings()
{
  set_name("Wastewalker Leggings");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 256);
  set_prim_stat(PrimaryAttributes::Agility, 31);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_red(2);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 4);
  set_sec_stat(SecondaryAttributes::HitRating, 19);
  set_sec_stat(SecondaryAttributes::AttackPower, 28);
  set_source(heroicdungeon);
  set_dungeon(manatomb);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

MidnightLegguards::MidnightLegguards()
{
  set_name("Midnight Legguards");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 305);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_red(2);
  set_blue(1);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 4);
  set_sec_stat(SecondaryAttributes::CritRating, 27);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 64);
  set_source(heroicdungeon);
  set_dungeon(slave_pens);
}

GladiatorsDragonhideLegguards::GladiatorsDragonhideLegguards()
{
  set_name("Gladiator''s Dragonhide Legguards");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 400);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_prim_stat(PrimaryAttributes::Strength, 40);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Intelligence, 25);
  set_sec_stat(SecondaryAttributes::Healing, 22);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 28);
  set_sec_stat(SecondaryAttributes::SpellPower, 8);
  set_source(pvp);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

LeggingsOfAssassination::LeggingsOfAssassination()
{
  set_name("Leggings of Assassination");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 256);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_prim_stat(PrimaryAttributes::Agility, 40);
  set_sec_stat(SecondaryAttributes::HitRating, 22);
  set_sec_stat(SecondaryAttributes::AttackPower, 44);
  set_source(normaldungeon);
  set_dungeon(shadow_lab);
  mark_as_set_piece();
  set_ArmorClass(ArmorClass::Leather);
}

FelLeatherLeggings::FelLeatherLeggings()
{
  set_name("Fel Leather Leggings");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 249);
  set_sec_stat(SecondaryAttributes::HitRating, 25);
  set_sec_stat(SecondaryAttributes::CritRating, 25);
  set_sec_stat(SecondaryAttributes::AttackPower, 52);
  set_red(1);
  set_yellow(2);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 8);
  set_source(crafting);
  mark_as_set_piece();
}

ForestwalkerKilt::ForestwalkerKilt()
{
  set_name("Forestwalker Kilt");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 459);
  set_prim_stat(PrimaryAttributes::Strength, 33);
  set_prim_stat(PrimaryAttributes::Agility, 26);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_prim_stat(PrimaryAttributes::Intelligence, 27);
  set_red(1);
  set_blue(2);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 4);
  set_source(heroicdungeon);
  set_dungeon(manatomb);
  set_ArmorClass(ArmorClass::Leather);
}

OilclothBreeches::OilclothBreeches()
{
  set_name("Oilcloth Breeches");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 243);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::HitRating, 25);
  set_sec_stat(SecondaryAttributes::CritRating, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_source(groupquest);
}

ClefthoofHideLeggings::ClefthoofHideLeggings()
{
  set_name("Clefthoof Hide Leggings");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 243);
  set_prim_stat(PrimaryAttributes::Agility, 30);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::HitRating, 17);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 18);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

VindicatorsDragonhideBoots::VindicatorsDragonhideBoots()
{
  set_name("Vindicator''s Dragonhide Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 357);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_sec_stat(SecondaryAttributes::CritRating, 21);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 26);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

ShadowstepStriders::ShadowstepStriders()
{
  set_name("Shadowstep Striders");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 240);
  set_prim_stat(PrimaryAttributes::Agility, 31);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 54);
  set_source(heroicdungeon);
  set_dungeon(arcatraz);
  set_ArmorClass(ArmorClass::Leather);
}

BootsOfTheUnjust::BootsOfTheUnjust()
{
  set_name("Boots of the Unjust");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 201);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::CritRating, 19);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_sec_stat(SecondaryAttributes::AttackPower, 64);
  set_source(heroicdungeon);
  set_dungeon(auchenaicrypt);
}

TheMastersTreads::TheMastersTreads()
{
  set_name("The Master''s Treads");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 191);
  set_prim_stat(PrimaryAttributes::Agility, 24);
  set_prim_stat(PrimaryAttributes::Stamina, 19);
  set_sec_stat(SecondaryAttributes::HitRating, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 48);
  set_source(randomdrop);
  set_ArmorClass(ArmorClass::Leather);
}

FelboarHideShoes::FelboarHideShoes()
{
  set_name("Felboar Hide Shoes");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 191);
  set_prim_stat(PrimaryAttributes::Agility, 18);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_sec_stat(SecondaryAttributes::HitRating, 9);
  set_sec_stat(SecondaryAttributes::AttackPower, 68);
  set_source(groupquest);
  set_ArmorClass(ArmorClass::Leather);
}

FelLeatherBoots::FelLeatherBoots()
{
  set_name("Fel Leather Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 196);
  set_yellow(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 6);
  set_sec_stat(SecondaryAttributes::HitRating, 25);
  set_sec_stat(SecondaryAttributes::CritRating, 17);
  set_sec_stat(SecondaryAttributes::AttackPower, 36);
  set_source(crafting);
  mark_as_set_piece();
}

FarahliteStuddedBoots::FarahliteStuddedBoots()
{
  set_name("Farahlite Studded Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 172);
  set_prim_stat(PrimaryAttributes::Agility, 16);
  set_sec_stat(SecondaryAttributes::CritRating, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_source(soloquest);
  set_ArmorClass(ArmorClass::Leather);
}

WindTradersBand::WindTradersBand()
{
  set_name("Wind Trader''s Band");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_prim_stat(PrimaryAttributes::Agility, 6);
  set_sec_stat(SecondaryAttributes::DefenseRating, 12);
  set_sec_stat(SecondaryAttributes::HitRating, 6);
  set_source(soloquest);
}

RingOfArathiWarlords::RingOfArathiWarlords()
{
  set_name("Ring of Arathi Warlords");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Stamina, 24);
  set_sec_stat(SecondaryAttributes::CritRating, 23);
  set_sec_stat(SecondaryAttributes::AttackPower, 46);
  set_source(boj);
  set_phase(1);
}

BandOfTriumph::BandOfTriumph()
{
  set_name("Band of Triumph");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_sec_stat(SecondaryAttributes::CritRating, 16);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 16);
  set_sec_stat(SecondaryAttributes::AttackPower, 32);
  set_source(pvp);
}

RavenclawBand::RavenclawBand()
{
  set_name("Ravenclaw Band");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_sec_stat(SecondaryAttributes::HitRating, 13);
  set_sec_stat(SecondaryAttributes::AttackPower, 30);
  set_source(normaldungeon);
  set_dungeon(sethekk_halls);
}

LongstridersLoop::LongstridersLoop()
{
  set_name("Longstrider''s Loop");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::Agility, 16);
  set_sec_stat(SecondaryAttributes::HitRating, 11);
  set_sec_stat(SecondaryAttributes::AttackPower, 32);
  set_source(normaldungeon);
  set_dungeon(manatomb);
}

ShapeshiftersSignet::ShapeshiftersSignet()
{
  set_name("Shapeshifter''s Signet");
  set_slot(Slot::Ring);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 18);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 20);
  set_source(reputation);
  set_faction(lower_city);
}

BroochOfTheImmortalKing::BroochOfTheImmortalKing()
{
  set_name("Brooch of the Immortal King");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::DefenseRating, 32);
  set_cd(60.0 * 2);
  set_uptime(15.0);
  set_source(groupquest);
}
void BroochOfTheImmortalKing::activate()
{
  if (!is_active())
  {
    activate();
    set_prim_stat(PrimaryAttributes::Health, 1250);
  }
}

void BroochOfTheImmortalKing::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_prim_stat(PrimaryAttributes::Health, 0);
  }
}

IdolOfUrsoc::IdolOfUrsoc()
{
  set_name("Idol of Ursoc");
  set_slot(Slot::Relic);
  set_source(heroicdungeon);
  set_dungeon(underbog);
}

IdolOfBrutality::IdolOfBrutality()
{
  set_name("Idol of Brutality");
  set_slot(Slot::Relic);
  set_source(normaldungeon);
  set_dungeon(stratholme);
}

IdolOfTheWild::IdolOfTheWild()
{
  set_name("Idol of the Wild");
  set_slot(Slot::Relic);
  set_source(groupquest);
}

GladiatorsMaul::GladiatorsMaul()
{
  set_name("Gladiator''s Maul");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_prim_stat(PrimaryAttributes::Strength, 32);
  set_sec_stat(SecondaryAttributes::CritRating, 35);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 28);
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 894);
  set_source(pvp);
}

Earthwarden::Earthwarden()
{
  set_name("Earthwarden");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Armor, 461); // update in tbcGear
  set_prim_stat(PrimaryAttributes::Stamina, 39);
  set_sec_stat(SecondaryAttributes::DefenseRating, 27);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 24);
  set_sec_stat(SecondaryAttributes::AttackPower, 712);
  set_source(reputation);
  set_faction(cenarion_expedition);
}

FeralStaffOfLashing::FeralStaffOfLashing()
{
  set_name("Feral Staff of Lashing");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Armor, 300);
  set_prim_stat(PrimaryAttributes::Strength, 36);
  set_prim_stat(PrimaryAttributes::Agility, 35);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_sec_stat(SecondaryAttributes::AttackPower, 754);
  set_source(heroicdungeon);
  set_dungeon(botanika);
  set_ArmorClass(ArmorClass::Staff);
}

StaffOfNaturalFury::StaffOfNaturalFury()
{
  set_name("Staff of Natural Fury");
  set_slot(Slot::Twohand);
  set_prim_stat(PrimaryAttributes::Armor, 320);
  set_prim_stat(PrimaryAttributes::Strength, 35);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::AttackPower, 712);
  set_source(randomdrop);
}

VindicatorsLeatherBoots::VindicatorsLeatherBoots()
{
  set_name("Vindicator''s Leather Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 315);
  set_prim_stat(PrimaryAttributes::Stamina, 49);
  set_prim_stat(PrimaryAttributes::Agility, 33);
  set_sec_stat(SecondaryAttributes::CritRating, 19);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 40);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

VindicatorsDragonhideBracers::VindicatorsDragonhideBracers()
{
  set_name("Vindicator''s Dragonhide Bracers");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 236);
  set_prim_stat(PrimaryAttributes::Stamina, 29);
  set_prim_stat(PrimaryAttributes::Strength, 22);
  set_prim_stat(PrimaryAttributes::Agility, 22);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::ResilienceRating, 2);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 17);
  set_sec_stat(SecondaryAttributes::CritRating, 21);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

VindicatorsDragonhideBelt::VindicatorsDragonhideBelt()
{
  set_name("Vindicator''s Dragonhide Belt");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 300);
  set_prim_stat(PrimaryAttributes::Stamina, 42);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 26);
  set_sec_stat(SecondaryAttributes::CritRating, 21);
  set_source(pvp);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

TalismanOfTheHorde::TalismanOfTheHorde()
{
  set_name("Talisman of the Horde");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 34);
  set_cd(120.0);
  set_source(pvp);
}

MaskOfTheDeceiver::MaskOfTheDeceiver()
{
  set_name("Mask of the Deceiver");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 283);
  set_prim_stat(PrimaryAttributes::Agility, 32);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_yellow(1);
  set_meta(1);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 4);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 64);
  set_source(boj);
  set_phase(1);
  set_ArmorClass(ArmorClass::Leather);
}

CowlOfBeastlyRage::CowlOfBeastlyRage()
{
  set_name("Cowl of Beastly Rage");
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 423);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_prim_stat(PrimaryAttributes::Strength, 29);
  set_prim_stat(PrimaryAttributes::Agility, 26);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_yellow(1);
  set_meta(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 4);
  set_source(boj);
  set_phase(1);
  set_ArmorClass(ArmorClass::Leather);
}

NynjahsTabiBoots::NynjahsTabiBoots()
{
  set_name("Nyn''jah''s Tabi Boots");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 278);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Stamina, 21);
  set_blue(1);
  set_red(1);
  set_bonus_sec_stat(SecondaryAttributes::HitRating, 3);
  set_sec_stat(SecondaryAttributes::HitRating, 22);
  set_sec_stat(SecondaryAttributes::AttackPower, 60);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

BroochOfDeftness::BroochOfDeftness()
{
  set_name("Brooch of Deftness");
  set_slot(Slot::Neck);
  set_prim_stat(PrimaryAttributes::Stamina, 48);
  set_sec_stat(SecondaryAttributes::HitRating, 22);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 21);
  set_source(boj);
  set_phase(4);
}

ShallowgraveTrousers::ShallowgraveTrousers()
{
  set_name("Shallow-grave Trousers");
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 353);
  set_prim_stat(PrimaryAttributes::Agility, 45);
  set_prim_stat(PrimaryAttributes::Stamina, 46);
  set_sec_stat(SecondaryAttributes::HasteRating, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 92);
  set_source(boj);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

TrickstersStickyfingers::TrickstersStickyfingers()
{
  set_name("Trickster''s Stickyfingers");
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 252);
  set_prim_stat(PrimaryAttributes::Agility, 30);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_sec_stat(SecondaryAttributes::HasteRating, 25);
  set_sec_stat(SecondaryAttributes::AttackPower, 68);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

MasterAssassinWristwraps::MasterAssassinWristwraps()
{
  set_name("Master Assassin Wristwraps");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 177);
  set_prim_stat(PrimaryAttributes::Agility, 17);
  set_prim_stat(PrimaryAttributes::Stamina, 22);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::CritRating, 2);
  set_sec_stat(SecondaryAttributes::CritRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 50);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

VestmentsOfHibernation::VestmentsOfHibernation()
{
  set_name("Vestments of Hibernation");
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 684);
  set_prim_stat(PrimaryAttributes::Strength, 46);
  set_prim_stat(PrimaryAttributes::Agility, 45);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_prim_stat(PrimaryAttributes::Intelligence, 13);
  set_sec_stat(SecondaryAttributes::ArmorPenetration, 150);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

BandOfTheSwiftPaw::BandOfTheSwiftPaw()
{
  set_name("Band of the Swift Paw");
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 317);
  set_prim_stat(PrimaryAttributes::Strength, 21);
  set_prim_stat(PrimaryAttributes::Agility, 22);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_prim_stat(PrimaryAttributes::Intelligence, 10);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 2);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

FootwrapsOfWildEncroachment::FootwrapsOfWildEncroachment()
{
  set_name("Footwraps of Wild Encroachment");
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 418);
  set_prim_stat(PrimaryAttributes::Strength, 29);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_prim_stat(PrimaryAttributes::Intelligence, 19);
  set_red(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 3);
  set_source(boj);
  set_ArmorClass(ArmorClass::Leather);
  set_phase(3);
}

WaistguardOfTheGreatBeast::WaistguardOfTheGreatBeast()
{
  set_name("Waistguard of the Great Beast");
  set_slot(Slot::Belt);
  set_prim_stat(PrimaryAttributes::Armor, 367);
  set_prim_stat(PrimaryAttributes::Strength, 29);
  set_prim_stat(PrimaryAttributes::Agility, 28);
  set_prim_stat(PrimaryAttributes::Stamina, 30);
  set_blue(1);
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Strength, 3);
  set_sec_stat(SecondaryAttributes::HitRating, 18);
  set_source(boj);
  set_phase(3);
  set_ArmorClass(ArmorClass::Leather);
}

IconOfUnyieldingCourage::IconOfUnyieldingCourage()
{
  set_name("Icon of Unyielding Courage");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::HitRating, 30);
  set_uptime(20);
  set_cd(2 * 60);
  set_source(Source::heroicdungeon);
  set_dungeon(Dungeon::blood_furnace);
}

void IconOfUnyieldingCourage::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::ArmorPenetration, 600);
  }
}

void IconOfUnyieldingCourage::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::ArmorPenetration, 0);
  }
}

BloodlustBrooch::BloodlustBrooch()
{
  set_name("Bloodlust Brooch");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::AttackPower, 72);
  set_uptime(20);
  set_cd(2 * 60);
  set_source(Source::boj);
}

void BloodlustBrooch::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::AttackPower, 287);
  }
}

void BloodlustBrooch::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::AttackPower, 0);
  }
}

BadgeOfTenacity::BadgeOfTenacity()
{
  set_name("Badge Of Tenacity");
  set_slot(Slot::Trinket);
  set_prim_stat(PrimaryAttributes::Armor, 308);
  set_uptime(20);
  set_cd(2 * 60);
  set_source(Source::reputation);
  set_phase(2);
}

void BadgeOfTenacity::activate()
{
  if (!is_active())
  {
    activate();
    set_prim_stat(PrimaryAttributes::Agility, 150);
  }
}

void BadgeOfTenacity::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_prim_stat(PrimaryAttributes::Agility, 0);
  }
}

AlchemistsStone::AlchemistsStone()
{
  set_name("Alchemist''s Stone");
  set_slot(Slot::Trinket);
  set_prim_stat(PrimaryAttributes::Strength, 15);
  set_prim_stat(PrimaryAttributes::Agility, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::Intelligence, 15);
  set_prim_stat(PrimaryAttributes::Spirit, 15);
  set_source(Source::crafting);
}

DrakeFangTalisman::DrakeFangTalisman()
{
  set_name("Drake Fang Talisman");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::HitRating, 20);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_sec_stat(SecondaryAttributes::DodgeRating, 12);
  set_source(Source::raid);
  set_phase(1);
  set_raid(Raid::blackwingLair);
}

AbacusOfViolentOdds::AbacusOfViolentOdds()
{
  set_name("Abacus of Violent Odds");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::AttackPower, 64);
  set_uptime(10);
  set_cd(2 * 60);
  set_source(Source::normaldungeon);
  set_dungeon(Dungeon::mechanar);
  set_phase(1);
}

void AbacusOfViolentOdds::activate()
{
  if (!is_active())
  {
    activate();
    set_sec_stat(SecondaryAttributes::HasteRating, 260);
  }
}

void AbacusOfViolentOdds::deactivate()
{
  if (is_active())
  {
    deactivate();
    set_sec_stat(SecondaryAttributes::HasteRating, 0);
  }
}

MarkOfTyranny::MarkOfTyranny()
{
  set_name("Mark Of Tyranny");
  set_slot(Slot::Trinket);
  set_prim_stat(PrimaryAttributes::Armor, 180);
  set_prim_stat(PrimaryAttributes::ArcaneResistance, 10);
  set_sec_stat(SecondaryAttributes::DodgeRating, 12);
  set_source(Source::groupquest);
  set_phase(1);
}

TimelapseShard::TimelapseShard()
{
  set_name("Timelapse Shard");
  set_slot(Slot::Trinket);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::ResilienceRating, 24);
  set_source(Source::reputation);
  set_faction(Faction::keepers_of_time);
  set_phase(1);
}

FleshHandlersGauntlets::FleshHandlersGauntlets()
{ // update tbcGear
  set_name("Flesh Hanlder''s Gauntlets");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 165);
  set_prim_stat(PrimaryAttributes::Strength, 18);
  set_prim_stat(PrimaryAttributes::Agility, 17);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 18);
  set_source(Source::soloquest);
}

ShattrathLeggings::ShattrathLeggings()
{ // update tbcGear
  set_name("Shattrath Leggings");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 243);
  set_prim_stat(PrimaryAttributes::Strength, 35);
  set_prim_stat(PrimaryAttributes::Agility, 25);
  set_prim_stat(PrimaryAttributes::Stamina, 27);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 22);
  set_source(Source::groupquest);
  set_phase(1);
}

TamelessBreeches::TamelessBreeches()
{ // update tbcGear
  set_name("Tameless Breeches");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 654);
  set_prim_stat(PrimaryAttributes::Strength, 39);
  set_prim_stat(PrimaryAttributes::Agility, 45);
  set_prim_stat(PrimaryAttributes::Stamina, 52);
  set_prim_stat(PrimaryAttributes::Intelligence, 20);
  set_sec_stat(SecondaryAttributes::HasteRating, 17);
  set_red(1);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 4);
  set_phase(5);
  set_source(Source::boj);
}

LeggingsOfTheBetrayed::LeggingsOfTheBetrayed()
{ // update tbcGear
  set_name("Leggings of the Betrayed");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 256);
  set_prim_stat(PrimaryAttributes::Agility, 26);
  set_prim_stat(PrimaryAttributes::Stamina, 25);
  set_sec_stat(SecondaryAttributes::HasteRating, 18);
  set_sec_stat(SecondaryAttributes::AttackPower, 66);
  set_blue(1);
  set_red(1);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::HasteRating, 4);
  set_phase(5);
  set_source(Source::normaldungeon);
  set_dungeon(Dungeon::magisters_terrace);
}

WarpscaleLeggings::WarpscaleLeggings()
{ // update tbcGear
  set_name("Warpscale Leggings");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Legs);
  set_prim_stat(PrimaryAttributes::Armor, 256);
  set_prim_stat(PrimaryAttributes::Agility, 32);
  set_prim_stat(PrimaryAttributes::Stamina, 31);
  set_sec_stat(SecondaryAttributes::DodgeRating, 21);
  set_sec_stat(SecondaryAttributes::HitRating, 14);
  set_sec_stat(SecondaryAttributes::AttackPower, 56);
  set_phase(1);
  set_source(Source::heroicdungeon);
  set_dungeon(Dungeon::botanika);
}

GlovesOfImmortalDusk::GlovesOfImmortalDusk()
{ // update tbcGear
  set_name("Gloves of Immortal Dusk");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 312);
  set_prim_stat(PrimaryAttributes::Agility, 30);
  set_prim_stat(PrimaryAttributes::Stamina, 33);
  set_sec_stat(SecondaryAttributes::CritRating, 30);
  set_sec_stat(SecondaryAttributes::AttackPower, 90);
  set_sec_stat(SecondaryAttributes::ArmorPenetration, 154);
  set_red(2);
  set_bonus_sec_stat(SecondaryAttributes::CritRating, 3);
  set_phase(5);
  set_source(Source::crafting);
}

SunrageTreads::SunrageTreads()
{ // update tbcGear
  set_name("Sunrage Treads");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Boots);
  set_prim_stat(PrimaryAttributes::Armor, 240);
  set_prim_stat(PrimaryAttributes::Agility, 28);
  set_prim_stat(PrimaryAttributes::Stamina, 28);
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_sec_stat(SecondaryAttributes::AttackPower, 58);
  set_sec_stat(SecondaryAttributes::ArmorPenetration, 126);
  set_phase(5);
  set_source(Source::normaldungeon);
  set_dungeon(Dungeon::magisters_terrace);
}

CircletOfRestlessDreams::CircletOfRestlessDreams()
{ // update tbcGear
  set_name("Circlet of Restless Dreams");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Head);
  set_prim_stat(PrimaryAttributes::Armor, 199);
  set_prim_stat(PrimaryAttributes::Agility, 21);
  set_prim_stat(PrimaryAttributes::Stamina, 38);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 14);
  set_phase(1);
  set_source(Source::raid);
  set_raid(Raid::emeriss);
}

AgedCoreLeatherGloves::AgedCoreLeatherGloves()
{ // update tbcGear
  set_name("Aged Core Leather Gloves");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 148);
  set_prim_stat(PrimaryAttributes::Strength, 15);
  set_prim_stat(PrimaryAttributes::Stamina, 15);
  set_prim_stat(PrimaryAttributes::FireResistance, 8);
  set_prim_stat(PrimaryAttributes::ShadowResistance, 5);
  set_source(Source::raid);
  set_raid(Raid::molten_core);
  set_phase(1);
}

CarapaceOfSunAndShadow::CarapaceOfSunAndShadow()
{ // update tbcGear
  set_name("Carapace of Sun and Shadow");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 499);
  set_prim_stat(PrimaryAttributes::Stamina, 45);
  set_prim_stat(PrimaryAttributes::Agility, 42);
  set_sec_stat(SecondaryAttributes::HitRating, 30);
  set_sec_stat(SecondaryAttributes::HasteRating, 38);
  set_sec_stat(SecondaryAttributes::AttackPower, 120);
  set_red(2);
  set_yellow(1);
  set_bonus_sec_stat(SecondaryAttributes::AttackPower, 8);
  set_phase(5);
  set_source(Source::crafting);
}

SwiftstrikeShoulders::SwiftstrikeShoulders()
{ // update tbcGear
  set_name("Swiftstrike Shoulders");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Shoulders);
  set_prim_stat(PrimaryAttributes::Armor, 333);
  set_prim_stat(PrimaryAttributes::Agility, 29);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_sec_stat(SecondaryAttributes::HasteRating, 38);
  set_sec_stat(SecondaryAttributes::AttackPower, 74);
  set_phase(3);
  set_source(Source::crafting);
}

SwiftstrikeBracers::SwiftstrikeBracers()
{ // update tbcGear
  set_name("Swiftstrike Bracers");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Bracers);
  set_prim_stat(PrimaryAttributes::Armor, 194);
  set_prim_stat(PrimaryAttributes::Agility, 20);
  set_prim_stat(PrimaryAttributes::Stamina, 34);
  set_sec_stat(SecondaryAttributes::HasteRating, 27);
  set_sec_stat(SecondaryAttributes::AttackPower, 50);
  set_phase(3);
  set_source(Source::crafting);
}

HandwrapsOfTheAggressor::HandwrapsOfTheAggressor()
{
  // update tbcGear
  set_name("Handwraps of the Aggressor");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Hands);
  set_prim_stat(PrimaryAttributes::Armor, 473);
  set_prim_stat(PrimaryAttributes::Strength, 30);
  set_prim_stat(PrimaryAttributes::Agility, 35);
  set_prim_stat(PrimaryAttributes::Stamina, 36);
  set_prim_stat(PrimaryAttributes::Intelligence, 19);
  set_sec_stat(SecondaryAttributes::HasteRating, 13);
  set_yellow(1);
  set_bonus_prim_stat(PrimaryAttributes::Agility, 2);
  set_phase(5);
  set_source(Source::boj);
}

EmbraceOfEverlastingProwess::EmbraceOfEverlastingProwess()
{
  // update tbcGear
  set_name("Embrace of Everlasting Prowess");
  set_ArmorClass(ArmorClass::Leather);
  set_slot(Slot::Chest);
  set_prim_stat(PrimaryAttributes::Armor, 696);
  set_prim_stat(PrimaryAttributes::Strength, 40);
  set_prim_stat(PrimaryAttributes::Agility, 49);
  set_prim_stat(PrimaryAttributes::Stamina, 52);
  set_prim_stat(PrimaryAttributes::Intelligence, 23);
  set_red(1);
  set_bonus_prim_stat(PrimaryAttributes::Stamina, 3);
  set_sec_stat(SecondaryAttributes::HasteRating, 20);
  set_phase(5);
  set_source(Source::boj);
}

ShardOfContempt::ShardOfContempt()
{
  // update tbcGear
  set_name("Shard of Contempt");
  set_slot(Slot::Trinket);
  set_sec_stat(SecondaryAttributes::ExpertiseRating, 44);
  set_phase(5);
  set_source(Source::heroicdungeon);
  set_dungeon(Dungeon::magisters_terrace);
}