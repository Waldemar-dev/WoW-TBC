#include "gems.hh"

Socket::Socket(Color inColor) : active(false), phase_(1), unique_(false), src_(Source::crafting), dng_(Dungeon::noDungeon), rep_(Faction::noFaction), name_("No Name"), color_(std::vector<Color>(1,inColor))
{
  switch (inColor){
    case (Color::Green):
      add_color(Color::Blue);
      add_color(Color::Yellow);
      break;
    case (Color::Purple):
      add_color(Color::Blue);
      add_color(Color::Red);
      break;
    case (Color::Orange):
      add_color(Color::Red);
      add_color(Color::Yellow);
      break;
    default:
      color_.shrink_to_fit();
      break;
  }
  color_.shrink_to_fit();
}

void Socket::operator=(Socket b)
{
  color_ = b.get_color();
  for (uint i=(uint)PrimaryAttributes::FirstPrimary; i<=(uint)PrimaryAttributes::LastPrimary;i++){
    set_prim_stat((PrimaryAttributes)i,b.get_prim_stat((PrimaryAttributes)i));
  }
  for (uint index=(uint)SecondaryAttributes::FirstSecondary; index<=(uint)SecondaryAttributes::LastSecondary;index++){
    set_sec_stat((SecondaryAttributes)index,b.get_sec_stat((SecondaryAttributes)index));
  }
  set_name(b.get_name());
  active = b.active;
}

bool Socket::operator==(Socket b) const
{
  if (get_sec_stats()==b.get_sec_stats() && get_prim_stats()==b.get_prim_stats() && get_name()==b.get_name()){
    return true;
  }
  return false;
}

bool Socket::is_active(std::vector<Socket> gems)
{
  if (name_ == "Tenacious Earthstorm Diamond")
  {
    unsigned int blue = 0;
    for (uint i = 0; i < gems.size(); i++)
    {
      for (uint j = 0; j < gems[i].get_color().size(); j++)
      {
        if (gems[i].get_color()[j] == Color::Blue)
        {
          blue++;
          if (blue >= 5 && !active)
          {
            set_sec_stat(SecondaryAttributes::DefenseRating,12);
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 5)
    {
      active = false;
    }
  }
  else if (name_ == "Powerful Earthstorm Diamond")
  {
    unsigned int blue = 0;
    for (uint i = 0; i < gems.size(); i++)
    {
      for (uint j = 0; j < gems[i].get_color().size(); j++)
      {
        if (gems[i].get_color()[j] == Color::Blue)
        {
          blue++;
          if (blue >= 3 && !active)
          {
            set_prim_stat(PrimaryAttributes::Stamina,get_prim_stat(PrimaryAttributes::Stamina)+18);
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 3)
    {
      active = false;
    }
  }
  else if (name_ == "Eternal Earthstorm Diamond")
  {
    unsigned int blue = 0;
    unsigned int yellow = 0;
    for (uint i = 0; i < gems.size(); i++)
    {
      for (uint j = 0; j < gems[i].get_color().size(); j++)
      {
        if (gems[i].get_color()[j] == Color::Blue)
        {
          blue++;
          if (blue >= 2 && yellow >= 1 && !active)
          {
            set_sec_stat(SecondaryAttributes::DefenseRating,get_sec_stat(SecondaryAttributes::DefenseRating)+12);
            active = true;
            return active;
          }
        }
        else if (gems[i].get_color()[j] == Color::Yellow)
        {
          yellow++;
          if (blue >= 2 && yellow >= 1 && !active)
          {
            set_sec_stat(SecondaryAttributes::DefenseRating,get_sec_stat(SecondaryAttributes::DefenseRating)+12);
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 2 || yellow < 1)
    {
      active = false;
    }
  }
  return active;
}

bool Socket::is_meta() const
{
  if (color_[0] == Color::Meta)
  {
    return true;
  }
  return false;
}

void Socket::set_prim_stats(PrimaryStats *in)
{
  for (uint i=(uint)PrimaryAttributes::FirstPrimary; i<=(uint)PrimaryAttributes::LastPrimary;i++){
    set_prim_stat((PrimaryAttributes)i,in->get_stat((PrimaryAttributes)i));
  }
}

void Socket::set_sec_stats(SecondaryStats *in){
  for (uint i=(uint)SecondaryAttributes::FirstSecondary; i<=(uint)SecondaryAttributes::LastSecondary;i++){
    set_sec_stat((SecondaryAttributes)i,in->get_stat((SecondaryAttributes)i));
  }
}

std::vector<std::string> Socket::get_names(uint nGem=1) const {
  std::vector<std::string> result={"Gem"+std::to_string(nGem)+"Name TEXT","Gem"+std::to_string(nGem)+"Color INT"};
  std::vector<std::string> temp={"Gem"+std::to_string(nGem)+"Phase INT", "Gem"+std::to_string(nGem)+"Source INT", "Gem"+std::to_string(nGem)+"Dungeon INT", "Gem"+std::to_string(nGem)+"Faction INT"};
  result.reserve(result.size()+Names::primaryAttributesNames.size()+Names::secondaryAttributesNames.size()+temp.size());
  for (uint i=0;i<Names::primaryAttributesNames.size();i++){
    std::string temp_name="Gem"+std::to_string(nGem) + Names::primaryAttributesNames[i];
    result.push_back(temp_name);
  }
  for (uint i=0;i<Names::secondaryAttributesNames.size();i++){
    std::string temp_name="Gem"+std::to_string(nGem) + Names::secondaryAttributesNames[i];
    result.push_back(temp_name);
  }
  result.insert(result.end(),temp.begin(),temp.end());
  result.shrink_to_fit();
  return result;
}

std::string Socket::get_values() const{
  std::stringstream result;
  result<<"'"<<get_name()<<"', ";
  if (get_color().size()==1){
    result<<(uint)get_color()[0]<<", ";
  } else {
    if (std::find(color_.begin(), color_.end(), Color::Blue)!=color_.end() && std::find(color_.begin(),color_.end(),Color::Red)!=color_.end()){
      result<<(uint)Color::Purple<<", ";
    } else if (std::find(color_.begin(), color_.end(), Color::Blue)!=color_.end() && std::find(color_.begin(),color_.end(),Color::Yellow)!=color_.end()){
      result<<(uint)Color::Green<<", ";
    } else if (std::find(color_.begin(), color_.end(), Color::Yellow)!=color_.end() && std::find(color_.begin(),color_.end(),Color::Red)!=color_.end()){
      result<<(uint)Color::Orange<<", ";
    } else {
      std::cout<<"Not defined color combination."<<std::endl;
      abort();
    }
  }
  for (uint i=(uint)PrimaryAttributes::FirstPrimary; i<=(uint)PrimaryAttributes::LastPrimary;i++){
    result<<get_prim_stat((PrimaryAttributes)i)<<", ";
  }
  for (uint i=(uint)SecondaryAttributes::FirstSecondary; i<=(uint)SecondaryAttributes::LastSecondary;i++){
    result<<get_sec_stat((SecondaryAttributes)i)<<", ";
  }
  result<<(uint)get_phase()<<", "<<(uint)get_source()<<", "<<(uint)get_dungeon()<<", "<<(uint)get_faction();
  return result.str();
}

DummyGem::DummyGem()
{
  set_name("Dummy Gem");
  add_color(Color::Dummy);
  set_source(noSource);
  set_dungeon(noDungeon);
  set_faction(noFaction);
  set_sources(noSource,noDungeon,noFaction,1);
}

DelicateLivingRuby::DelicateLivingRuby()
{
  set_prim_stat(PrimaryAttributes::Agility,8);
  set_name("Delicate Living Ruby");
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,1);
}

RunedLivingRuby::RunedLivingRuby()
{
  set_sec_stat(SecondaryAttributes::SpellPower,9);
  set_sec_stat(SecondaryAttributes::Healing,9);
  set_name("Runed Living Ruby");
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,1);
}

BoldLivingRuby::BoldLivingRuby()
{
  set_prim_stat(PrimaryAttributes::Strength,8);
  set_name("Bold Living Ruby");
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,1);
}

SubtleLivingRuby::SubtleLivingRuby()
{
  set_sec_stat(SecondaryAttributes::DodgeRating,8);
  set_name("Subtle Living Ruby");
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,1);
}

ThickDawnstone::ThickDawnstone()
{
  set_sec_stat(SecondaryAttributes::DefenseRating,8);
  set_name("Thick Dawnstone");
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,1);
}

SolidStarOfElune::SolidStarOfElune()
{
  set_prim_stat(PrimaryAttributes::Stamina,12);
  set_name("Solid Star of Elune");
  add_color(Color::Blue);
  set_sources(crafting,noDungeon,noFaction,1);
}

StalwartFireOpal::StalwartFireOpal()
{
  set_sec_stat(SecondaryAttributes::DodgeRating,4);
  set_sec_stat(SecondaryAttributes::DefenseRating,5);
  set_name("Stalwart Fire Opal");
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,sethekk_halls,noFaction,1);
  set_unique();
}

EnduringTalasit::EnduringTalasit()
{
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::DefenseRating,4);
  set_name("Enduring Talasit");
  add_color(Color::Blue);
  add_color(Color::Yellow);
  add_color(Color::Green);
  set_sources(crafting,noDungeon,noFaction,1);
}

SovereignNightseye::SovereignNightseye()
{
  set_prim_stat(PrimaryAttributes::Strength,4);
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_name("Sovereign Nightseye");
  add_color(Color::Blue);
  add_color(Color::Red);
  add_color(Color::Purple);
  set_sources(crafting,noDungeon,noFaction,1);
}

ShiftingNightseye::ShiftingNightseye()
{
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_prim_stat(PrimaryAttributes::Agility,4);
  set_name("Shifting Nightseye");
  add_color(Color::Blue);
  add_color(Color::Red);
  add_color(Color::Purple);
  set_sources(crafting,noDungeon,noFaction,1);
}

RegalNightseye::RegalNightseye()
{
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::DodgeRating,4);
  set_name("Regal Nightseye");
  add_color(Color::Blue);
  add_color(Color::Red);
  add_color(Color::Purple);
  set_sources(crafting,noDungeon,noFaction,1);
}

GlisteringFireOpal::GlisteringFireOpal()
{
  set_prim_stat(PrimaryAttributes::Agility,4);
  set_sec_stat(SecondaryAttributes::DefenseRating,5);
  set_name("Glistering Fire Opal");
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,manatomb,noFaction,1);
  set_unique();
}

ChampionsFireOpal::ChampionsFireOpal()
{
  set_prim_stat(PrimaryAttributes::Strength,5);
  set_sec_stat(SecondaryAttributes::DefenseRating,4);
  set_name("Champions Fire Opal");
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,auchenaicrypt,noFaction,1);
  set_unique();
}

RigidDawnstone::RigidDawnstone()
{
  set_sec_stat(SecondaryAttributes::HitRating,8);
  set_name("Rigid Dawnstone");
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,1);
}

FlashingLivingRuby::FlashingLivingRuby()
{
  set_name("Flashing Living Ruby");
  set_sec_stat(SecondaryAttributes::ParryRating,8);
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,1);
}

GlowingNightseye::GlowingNightseye()
{
  set_name("Glowing Nightseye");
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::SpellPower,5);
  add_color(Color::Blue);
  add_color(Color::Red);
  add_color(Color::Purple);
  set_sources(crafting,noDungeon,noFaction,1);
}

TenaciousEarthstormDiamond::TenaciousEarthstormDiamond()
{
  set_name("Tenacious Earthstorm Diamond");
  add_color(Color::Meta);
  set_sources(crafting,noDungeon,noFaction,1);
}

PowerfulEarthstormDiamond::PowerfulEarthstormDiamond()
{
  set_name("Powerful Earthstorm Diamond");
  add_color(Color::Meta);
  set_sources(crafting,noDungeon,noFaction,1);
}

EternalEarthstormDiamond::EternalEarthstormDiamond()
{
  set_name("Eternal Earthstorm Diamond");
  add_color(Color::Meta);
  set_sources(crafting,noDungeon,noFaction,5);
}

EffulgentChrysoprase::EffulgentChrysoprase()
{
  set_name("Effulgent Chrysoprase");
  set_sec_stat(SecondaryAttributes::DefenseRating,5);
  set_sec_stat(SecondaryAttributes::MP5,2);
  add_color(Color::Yellow);
  add_color(Color::Blue);
  add_color(Color::Green);
  set_sources(heroicdungeon,ramparts,noFaction,1);
  set_unique();
}

ThickLionseye::ThickLionseye()
{
  set_name("Thick Lionseye");
  set_sec_stat(SecondaryAttributes::DefenseRating,10);
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,3);
}

SubtleCrimsonSpinel::SubtleCrimsonSpinel()
{
  set_name("Subtle Crimson Spinel");
  set_sec_stat(SecondaryAttributes::DodgeRating,10);
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,3);
}

SolidEmpyreanSapphire::SolidEmpyreanSapphire()
{
  set_name("Solid Empyrean Sapphire");
  set_prim_stat(PrimaryAttributes::Stamina,15);
  add_color(Color::Blue);
  set_sources(crafting,noDungeon,noFaction,3);
}

GlimmeringFireOpal::GlimmeringFireOpal()
{
  set_name("Glimmering Fire Opal");
  set_sec_stat(SecondaryAttributes::ParryRating,5);
  set_sec_stat(SecondaryAttributes::DefenseRating,4);
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,black_morast,noFaction,1);
  set_unique();
}

RegalTanzanite::RegalTanzanite()
{
  set_name("Regal Tanzanite");
  set_sec_stat(SecondaryAttributes::DodgeRating,5);
  set_prim_stat(PrimaryAttributes::Stamina,6);
  add_color(Color::Red);
  add_color(Color::Blue);
  add_color(Color::Purple);
  set_sources(heroicdungeon,shadow_lab,noFaction,1);
  set_unique();
}

EnduringChrysoprase::EnduringChrysoprase()
{
  set_name("Enduring Chrysoprase");
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::DefenseRating,5);
  add_color(Color::Yellow);
  add_color(Color::Blue);
  add_color(Color::Green);
  set_sources(heroicdungeon,ohf,noFaction,1);
  set_unique();
}

GlowingTanzanite::GlowingTanzanite()
{
  set_name("Glowing Tanzanite");
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::SpellPower,6);
  add_color(Color::Red);
  add_color(Color::Blue);
  add_color(Color::Purple);
  set_sources(heroicdungeon,black_morast,noFaction,1);
  set_unique();
}

VividChrysoprase::VividChrysoprase()
{
  set_name("Vivid Chrysoprase");
  set_sec_stat(SecondaryAttributes::SpellhitRating,5);
  set_prim_stat(PrimaryAttributes::Stamina,6);
  add_color(Color::Yellow);
  add_color(Color::Blue);
  add_color(Color::Green);
  set_sources(heroicdungeon,slave_pens,noFaction,1);
  set_unique();
}

SplendidFireOpal::SplendidFireOpal()
{
  set_name("Splendid Fire Opal");
  set_sec_stat(SecondaryAttributes::ParryRating,5);
  set_sec_stat(SecondaryAttributes::ResilienceRating,4);
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,underbog,noFaction,1);
  set_unique();
}

ShiftingTanzanite::ShiftingTanzanite()
{
  set_name("Shifting Tanzanite");
  set_prim_stat(PrimaryAttributes::Agility,5);
  set_prim_stat(PrimaryAttributes::Stamina,6);
  add_color(Color::Red);
  add_color(Color::Blue);
  add_color(Color::Purple);
  set_sources(heroicdungeon,steamvault,noFaction,1);
  set_unique();
}

SteadyChrysoprase::SteadyChrysoprase()
{
  set_name("Steady Chrysoprase");
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::ResilienceRating,5);
  add_color(Color::Yellow);
  add_color(Color::Blue);
  add_color(Color::Green);
  set_sources(heroicdungeon,ramparts,noFaction,1);
  set_unique();
}

BeamingFireOpal::BeamingFireOpal()
{
  set_name("Beaming Fire Opal");
  set_sec_stat(SecondaryAttributes::DodgeRating,5);
  set_sec_stat(SecondaryAttributes::ResilienceRating,4);
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(heroicdungeon,blood_furnace,noFaction,1);
  set_unique();
}

DefendersTanzanite::DefendersTanzanite()
{
  set_name("Defenders Tanzanite");
  set_prim_stat(PrimaryAttributes::Stamina,6);
  set_sec_stat(SecondaryAttributes::ParryRating,5);
  add_color(Color::Blue);
  add_color(Color::Red);
  add_color(Color::Purple);
  set_sources(heroicdungeon,mechanar,noFaction,1);
  set_unique();
}

GleamingDawnstone::GleamingDawnstone()
{
  set_name("Gleaming Dawnstone");
  set_sec_stat(SecondaryAttributes::CritRating,8);
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,1);
}

GreatDawnstone::GreatDawnstone()
{
  set_name("Great Dawnstone");
  set_sec_stat(SecondaryAttributes::SpellhitRating,8);
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,1);
}

MysticDawnstone::MysticDawnstone()
{
  set_name("Mystic Dawnstone");
  set_sec_stat(SecondaryAttributes::ResilienceRating,8);
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,1);
}

DelicateCrimsonSpinel::DelicateCrimsonSpinel()
{
  set_name("Delicate Crimson Spinel");
  set_prim_stat(PrimaryAttributes::Agility,10);
  add_color(Color::Red);
  set_sources(crafting,noDungeon,noFaction,3);
}

GlintingNobleTopaz::GlintingNobleTopaz()
{
  set_name("Glinting Noble Topaz");
  set_prim_stat(PrimaryAttributes::Agility,4);
  set_sec_stat(SecondaryAttributes::HitRating,4);
  add_color(Color::Yellow);
  add_color(Color::Red);
  add_color(Color::Orange);
  set_sources(crafting,noDungeon,noFaction,1);
}

NimbleFireOpal::NimbleFireOpal()
{
  set_name("Nimble Fire Opal");
  set_sec_stat(SecondaryAttributes::HitRating,4);
  set_sec_stat(SecondaryAttributes::DodgeRating,5);
  add_color(Color::Yellow);
  add_color(Color::Red);
  add_color(Color::Orange);
  set_sources(heroicdungeon,arcatraz,noFaction,1);
  set_unique();
}

PristineFireOpal::PristineFireOpal()
{
  set_name("Pristine Fire Opal");
  set_sec_stat(SecondaryAttributes::AttackPower,10);
  set_sec_stat(SecondaryAttributes::HitRating,4);
  add_color(Color::Yellow);
  add_color(Color::Red);
  add_color(Color::Orange);
  set_sources(heroicdungeon,sethekk_halls,noFaction,1);
  set_unique();
}

QuickDawnstone::QuickDawnstone()
{
  set_name("Quick Dawnstone");
  set_sec_stat(SecondaryAttributes::SpellHasteRating,8);
  add_color(Color::Yellow);
  set_sources(crafting,noDungeon,noFaction,5);
}

VeiledNobleTopaz::VeiledNobleTopaz()
{
  set_name("Veiled Noble Topaz");
  set_sec_stat(SecondaryAttributes::SpellPower,5);
  set_sec_stat(SecondaryAttributes::SpellhitRating,4);
  add_color(Color::Red);
  add_color(Color::Yellow);
  add_color(Color::Orange);
  set_sources(crafting,noDungeon,noFaction,1);
}
