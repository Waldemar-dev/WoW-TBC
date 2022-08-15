#ifndef GEMS_HH_
#define GEMS_HH_

#include "stats.hh"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
// #include "enums.hh"

class Socket
{ // TO DO: meta socket
public:
  Socket() = default;
  Socket(Color);
  ~Socket() = default;

  void set_source(Source in) { src_ = in; }
  void set_dungeon(Dungeon in) { dng_ = in; }
  void set_faction(Faction in) { rep_ = in; }
  void set_sources(Source in_s, Dungeon in_d, Faction in_f, uint in_p)
  {
    set_source(in_s);
    set_dungeon(in_d);
    set_faction(in_f);
    set_phase(in_p);
  }
  void set_phase(unsigned int in) { phase_ = in; }
  void set_name(std::string in){name_=in;}
  void set_prim_stats(PrimaryStats*);
  void set_sec_stats(SecondaryStats*);
  void set_prim_stat(PrimaryAttributes inIndex, double inValue) { primaryStats_.set_stat(inIndex, inValue); }
  void set_sec_stat(SecondaryAttributes inIndex, double inValue) { secondaryStats_.set_stat(inIndex, inValue); }
  unsigned int get_phase() const { return phase_; }
  Source get_source() const { return src_; }
  Dungeon get_dungeon() const { return dng_; }
  Faction get_faction() const { return rep_; }
  std::vector<Color> get_color() const {return color_;}
  void add_color(Color in){color_.push_back(in);}
  bool active; // just for metasockets. default state
  bool is_active(std::vector<Socket>);
  bool is_meta() const;
  bool is_unique() const { return unique_; }
  void set_unique() { unique_ = true; }
  // uint get_number_of_vars() const { return primary_stats.get_number_of_vars() + secondary_stats.get_number_of_vars() + 7; }
  std::string get_name() const {return name_;}
  std::vector<std::string> get_names(uint) const;
  std::string get_values() const;
  double get_prim_stat(PrimaryAttributes in) const {return primaryStats_.get_stat(in);}
  double get_sec_stat(SecondaryAttributes in) const {return secondaryStats_.get_stat(in);}
  PrimaryStats get_prim_stats() const {return primaryStats_;}
  SecondaryStats get_sec_stats() const {return secondaryStats_;}
  void operator=(Socket);
  bool operator==(Socket) const;
  friend std::ostream &operator<<(std::ostream &out, const Socket &gem)
  {
    out << gem.get_name() << "\t" << (uint)gem.get_color()[0] << "\t" << gem.get_prim_stats() << "\t" << gem.get_sec_stats() << "\t" << gem.get_phase() << "\t" << (uint)gem.get_source() << "\t" << (uint)gem.get_dungeon() << "\t" << (uint)gem.get_faction();
    return out;
  }
  // friend istream &operator>>(istream &in, Socket &gem)
  // {
  //   std::string in_colors, in_active, in_phase;
  //   uint in_src, in_dng, in_fac;
  //   cout << __LINE__ << endl;
  //   in >> in_colors >> gem.primary_stats >> gem.secondary_stats >> gem.name >> in_active >> in_phase >> in_src >> in_dng >> in_fac;
  //   istringstream(in_active) >> gem.active;
  //   std::stringstream ss(in_colors);
  //   std::stringstream temp_ss;
  //   for (std::string i; ss >> i;)
  //   {
  //     if (i != ",")
  //     {
  //       temp_ss << i;
  //     }
  //     else
  //     {
  //       gem.color.push_back(temp_ss.str());
  //       temp_ss.str("");
  //     }
  //   }
  //   if (in_phase == "")
  //   {
  //     in_phase = "1";
  //   }
  //   else
  //   {
  //     cout << "gem phase=" << in_phase << endl;
  //   }
  //   gem.set_phase((uint)stoi(in_phase));
  //   gem.set_source((Source)in_src);
  //   gem.set_dungeon((Dungeon)in_dng);
  //   gem.set_faction((Faction)in_fac);
  //   cout << "read gem" << endl;
  //   return in;
  // }

private:
  unsigned int phase_;
  bool unique_;
  Source src_;
  Dungeon dng_;
  Faction rep_;
  std::string name_;
  std::vector<Color> color_;
  PrimaryStats primaryStats_;
  SecondaryStats secondaryStats_;
};

class DummyGem : public Socket
{
public:
  DummyGem();
};

class DelicateLivingRuby : public Socket
{
public:
  DelicateLivingRuby();
};

class RunedLivingRuby : public Socket
{
public:
  RunedLivingRuby();
};

class BoldLivingRuby : public Socket
{
public:
  BoldLivingRuby();
};

class SubtleLivingRuby : public Socket
{
public:
  SubtleLivingRuby();
};

class ThickDawnstone : public Socket
{
public:
  ThickDawnstone();
};

class SolidStarOfElune : public Socket
{
public:
  SolidStarOfElune();
};

class StalwartFireOpal : public Socket
{
public:
  StalwartFireOpal();
};

class EnduringTalasit : public Socket
{
public:
  EnduringTalasit();
};

class SovereignNightseye : public Socket
{
public:
  SovereignNightseye();
};

class ShiftingNightseye : public Socket
{
public:
  ShiftingNightseye();
};

class RegalNightseye : public Socket
{
public:
  RegalNightseye();
};

class GlisteringFireOpal : public Socket
{
public:
  GlisteringFireOpal();
};

class ChampionsFireOpal : public Socket
{
public:
  ChampionsFireOpal();
};

class TenaciousEarthstormDiamond : public Socket
{
public:
  TenaciousEarthstormDiamond();
};

class PowerfulEarthstormDiamond : public Socket
{
public:
  PowerfulEarthstormDiamond();
};

class EternalEarthstormDiamond : public Socket
{
public:
  EternalEarthstormDiamond();
};

class RigidDawnstone : public Socket
{
public:
  RigidDawnstone();
};

class FlashingLivingRuby : public Socket
{
public:
  FlashingLivingRuby();
};

class GlowingNightseye : public Socket
{
public:
  GlowingNightseye();
};

class EffulgentChrysoprase : public Socket
{
public:
  EffulgentChrysoprase();
};

class ThickLionseye : public Socket
{
public:
  ThickLionseye();
};

class SubtleCrimsonSpinel : public Socket
{
public:
  SubtleCrimsonSpinel();
};

class SolidEmpyreanSapphire : public Socket
{
public:
  SolidEmpyreanSapphire();
};

class GlimmeringFireOpal : public Socket
{
public:
  GlimmeringFireOpal();
};

class RegalTanzanite : public Socket
{
public:
  RegalTanzanite();
};

class EnduringChrysoprase : public Socket
{
public:
  EnduringChrysoprase();
};

class GlowingTanzanite : public Socket
{
public:
  GlowingTanzanite();
};

class VividChrysoprase : public Socket
{
public:
  VividChrysoprase();
};

class SplendidFireOpal : public Socket
{
public:
  SplendidFireOpal();
};

class ShiftingTanzanite : public Socket
{
public:
  ShiftingTanzanite();
};

class SteadyChrysoprase : public Socket
{
public:
  SteadyChrysoprase();
};

class BeamingFireOpal : public Socket
{
public:
  BeamingFireOpal();
};

class DefendersTanzanite : public Socket
{
public:
  DefendersTanzanite();
};

class GleamingDawnstone : public Socket
{
public:
  GleamingDawnstone();
};

class GreatDawnstone : public Socket
{
public:
  GreatDawnstone();
};

class MysticDawnstone : public Socket
{
public:
  MysticDawnstone();
};

class DelicateCrimsonSpinel : public Socket
{
public:
  DelicateCrimsonSpinel();
};

class GlintingNobleTopaz : public Socket
{
public:
  GlintingNobleTopaz();
};

class NimbleFireOpal : public Socket
{
public:
  NimbleFireOpal();
};

class PristineFireOpal : public Socket
{
public:
  PristineFireOpal();
};

class QuickDawnstone : public Socket
{
public:
  QuickDawnstone();
};

class VeiledNobleTopaz : public Socket
{
public:
  VeiledNobleTopaz();
};

#endif
