#ifndef BUFFS_HH_
#define BUFFS_HH_

#include "stats.hh"
#include <string>

class Buff
{
public:
  Buff(bool inBuffFood=false);
  Buff(const Buff&);
  ~Buff() = default;
  void operator=(Buff);
  bool operator==(Buff);
  void set_prim_stat(PrimaryAttributes inIndex, double inValue) { primaryStats_.set_stat(inIndex, inValue); }
  void set_sec_stat(SecondaryAttributes inIndex, double inValue) { secondaryStats_.set_stat(inIndex, inValue); }
  void set_name(std::string in) { name_ = in; }
  double get_prim_stat(PrimaryAttributes in) const { return primaryStats_.get_stat(in); }
  PrimaryStats get_prim_stats() const { return primaryStats_; }
  double get_sec_stat(SecondaryAttributes in) { return secondaryStats_.get_stat(in); }
  SecondaryStats get_sec_stats() const { return secondaryStats_; }
  std::string get_name() const { return name_; }
  bool is_buffFood() const { return buffFood_; }
  void set_buffFood(){buffFood_=true;}

private:
  PrimaryStats primaryStats_;
  SecondaryStats secondaryStats_;
  std::string name_;
  bool buffFood_;
};

class BuffFood : public Buff
{
public:
  BuffFood();
  ~BuffFood() = default;
};

class Elixir : public Buff
{
public:
  Elixir() = default;
  ~Elixir() = default;
  void set_battle_elixir() { battle_elixir = true; }
  void set_guardian_elixir() { guardian_elixir = true; }
  bool is_battle_elixir() const { return battle_elixir; }
  bool is_guardian_elixir() const { return guardian_elixir; }

private:
  bool battle_elixir = false;
  bool guardian_elixir = false;
};

// Buff food:
class BlackenedBasilisk : public BuffFood
{
public:
  BlackenedBasilisk();
};

class BlackenedSporefish : public BuffFood
{
public:
  BlackenedSporefish();
};

class BroiledBloodfin : public BuffFood
{
public:
  BroiledBloodfin();
};

class BuzzardBites : public BuffFood
{
public:
  BuzzardBites();
};

class DirgesKickinChimaerokChops : public BuffFood
{
  DirgesKickinChimaerokChops();
};

class GrilledMudfish : public BuffFood
{
public:
  GrilledMudfish();
};

class RoastedClefthoof : public BuffFood
{
public:
  RoastedClefthoof();
};

class Stormchops : public BuffFood
{
public:
  Stormchops();
};

class FishermensFeast : public BuffFood
{
public:
  FishermensFeast();
};

class SkullfishSoup : public BuffFood
{
public:
  SkullfishSoup();
};

class SpicyHotTalbulk : public BuffFood
{
public:
  SpicyHotTalbulk();
};

// Buffs

class BlessingOfSanctuary : public Buff
{
public:
  BlessingOfSanctuary();
};

class BlessingOfKings : public Buff
{
public:
  BlessingOfKings();
};

class MarkOfTheWild : public Buff
{
public:
  MarkOfTheWild();
};

class BlessingOfWisdom : public Buff
{
public:
  BlessingOfWisdom();
};

class ArcaneIntellect : public Buff
{
public:
  ArcaneIntellect();
};

class PowerWordFortitude : public Buff
{
public:
  PowerWordFortitude();
};

// Elixirs:
class FlaskOfFortification : public Elixir
{
public:
  FlaskOfFortification();
};

class FlaskOfBlindingLight : public Elixir
{
public:
  FlaskOfBlindingLight();
};

class FlaskOfRelentlessAssault : public Elixir
{
public:
  FlaskOfRelentlessAssault();
};

class FlaskOfChromaticWonder : public Elixir
{
public:
  FlaskOfChromaticWonder();
};

class ElixirOfMajorDefense : public Elixir
{
public:
  ElixirOfMajorDefense();
};

class ElixirOfMajorAgility : public Elixir
{
public:
  ElixirOfMajorAgility();
};

class ElixirOfMastery : public Elixir
{
public:
  ElixirOfMastery();
};

class ElixirOfMajorStrength : public Elixir
{
public:
  ElixirOfMajorStrength();
};

class ElixirOfMajorFortitude : public Elixir
{
public:
  ElixirOfMajorFortitude();
};

class EarthernElixir : public Elixir
{
public:
  EarthernElixir();
};

class ElixirOfIronskin : public Elixir
{
public:
  ElixirOfIronskin();
};

class FelStrengthElixir : public Elixir
{
public:
  FelStrengthElixir();
};
#endif
