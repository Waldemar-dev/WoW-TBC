#ifndef BUFFS_HH_
#define BUFFS_HH_

#include "stats.hh"
#include <string>

class Buff {
public:
  Buff() = default;
  ~Buff() = default;
  PrimaryStats primary_stats;
  SecondaryStats secondary_stats;
  string name;
  void operator=(Buff);
  bool operator==(Buff);
};

class BuffFood : public Buff {
public:
  BuffFood() = default;
  ~BuffFood() = default;
};

class Elixir : public Buff {
public:
  Elixir() = default;
  ~Elixir() = default;

  bool battle_elixir = false;
  bool guardian_elixir = false;
};

// Bufffood:
class BlackenedBasilisk : public BuffFood {
public:
  BlackenedBasilisk();
};

class BlackenedSporefish : public BuffFood {
public:
  BlackenedSporefish();
};

class BroiledBloodfin : public BuffFood {
public:
  BroiledBloodfin();
};

class BuzzardBites : public BuffFood {
public:
  BuzzardBites();
};

class DirgesKickinChimaerokChops : public BuffFood {
  DirgesKickinChimaerokChops();
};

class GrilledMudfish : public BuffFood {
public:
  GrilledMudfish();
};

class RoastedClefthoof : public BuffFood {
  RoastedClefthoof();
};

class Stormchops : public BuffFood {
public:
  Stormchops();
};

class FishermensFeast : public BuffFood {
public:
  FishermensFeast();
};

class SkullfishSoup : public BuffFood {
public:
  SkullfishSoup();
};

class SpicyHotTalbulk : public BuffFood {
public:
  SpicyHotTalbulk();
};

// Buffs

class BlessingOfSanctuary : public Buff {
public:
  BlessingOfSanctuary();
};

class BlessingOfKings : public Buff {
public:
  BlessingOfKings();
};

class MarkOfTheWild : public Buff {
public:
  MarkOfTheWild();
};

class BlessingOfWisdom : public Buff {
public:
  BlessingOfWisdom();
};

class ArcaneIntellect : public Buff {
public:
  ArcaneIntellect();
};

class PowerWordFortitude : public Buff {
public:
  PowerWordFortitude();
};

// Elixirs:
class FlaskOfFortification : public Elixir {
public:
  FlaskOfFortification();
};

class FlaskOfBlindingLight : public Elixir {
public:
  FlaskOfBlindingLight();
};

class ElixirOfMajorDefense : public Elixir {
public:
  ElixirOfMajorDefense();
};

class ElixirOfMajorAgility : public Elixir {
public:
  ElixirOfMajorAgility();
};

class ElixirOfMastery : public Elixir {
public:
  ElixirOfMastery();
};

class ElixirOfMajorStrength : public Elixir {
public:
  ElixirOfMajorStrength();
};

class ElixirOfMajorFortitude : public Elixir {
public:
  ElixirOfMajorFortitude();
};

class EarthernElixir : public Elixir {
public:
  EarthernElixir();
};

class ElixirOfIronskin : public Elixir {
public:
  ElixirOfIronskin();
};

#endif
