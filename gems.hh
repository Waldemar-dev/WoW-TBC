#ifndef GEMS_HH_
#define GEMS_HH_

#include "stats.hh"
#include <string>
#include <vector>

using namespace std;

class Socket { // TO DO: meta socket
public:
  Socket() = default;
  Socket(string);
  ~Socket() = default;

  vector<string> color;
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
  string name;
  bool active = false; // just for metasockets default state
  bool is_active(vector<Socket>);
  void operator=(Socket);
};

class DelicateLivingRuby : public Socket {
public:
  DelicateLivingRuby();
};

class RunedLivingRuby : public Socket {
public:
  RunedLivingRuby();
};

class BoldLivingRuby : public Socket {
public:
  BoldLivingRuby();
};

class SubtleLivingRuby : public Socket {
public:
  SubtleLivingRuby();
};

class ThickDawnstone : public Socket {
public:
  ThickDawnstone();
};

class SolidStarOfElune : public Socket {
public:
  SolidStarOfElune();
};

class StalwartFireOpal : public Socket {
public:
  StalwartFireOpal();
};

class EnduringTalasit : public Socket {
public:
  EnduringTalasit();
};

class SovereignNightseye : public Socket {
public:
  SovereignNightseye();
};

class ShiftingNightseye : public Socket {
public:
  ShiftingNightseye();
};

class RegalNightseye : public Socket {
public:
  RegalNightseye();
};

class GlisteringFireOpal : public Socket {
public:
  GlisteringFireOpal();
};

class ChampionsFireOpal : public Socket {
public:
  ChampionsFireOpal();
};

class TenaciousEarthstormDiamond : public Socket {
public:
  TenaciousEarthstormDiamond();
};

class PowerfulEarthstormDiamond : public Socket {
public:
  PowerfulEarthstormDiamond();
};

class EternalEarthstormDiamond : public Socket {
public:
  EternalEarthstormDiamond();
};

class RigidDawnstone : public Socket {
public:
  RigidDawnstone();
};

class FlashingLivingRuby : public Socket {
public:
  FlashingLivingRuby();
};

class GlowingNightseye : public Socket {
public:
  GlowingNightseye();
};

class EffulgentChrysoprase : public Socket {
public:
  EffulgentChrysoprase();
};

class ThickLionseye : public Socket {
public:
  ThickLionseye();
};

class SubtleCrimsonSpinel : public Socket {
public:
  SubtleCrimsonSpinel();
};

class SolidEmpyreanSapphire : public Socket {
public:
  SolidEmpyreanSapphire();
};

class GlimmeringFireOpal : public Socket {
public:
  GlimmeringFireOpal();
};

class RegalTanzanite : public Socket {
public:
  RegalTanzanite();
};

class EnduringChrysoprase : public Socket {
public:
  EnduringChrysoprase();
};

class GlowingTanzanite : public Socket {
public:
  GlowingTanzanite();
};

class VividChrysoprase : public Socket {
public:
  VividChrysoprase();
};

class SplendidFireOpal : public Socket {
public:
  SplendidFireOpal();
};

class ShiftingTanzanite : public Socket {
public:
  ShiftingTanzanite();
};

class SteadyChrysoprase : public Socket {
public:
  SteadyChrysoprase();
};

class BeamingFireOpal : public Socket {
public:
  BeamingFireOpal();
};

class DefendersTanzanite : public Socket {
public:
  DefendersTanzanite();
};

#endif
