#ifndef _STATS_HH_
#define _STATS_HH_

using namespace std;

class PrimaryStats {
public:
  PrimaryStats();
  ~PrimaryStats() = default;
  int armor;
  double strength, agility, stamina, intelligence, spirit, arcane_resistance, fire_resistance, frost_resistance, shadow_resistance, nature_resistance, health, mana;
  double attack_speed, weapondamage;
  PrimaryStats operator+(PrimaryStats);
  PrimaryStats operator-(PrimaryStats);
  void operator=(PrimaryStats);
};

class SecondaryStats {
public:
  SecondaryStats();
  ~SecondaryStats() = default;
  double dodge_rating, parry_rating, block_chance_rating, block_value, defense_rating, hit_rating, spellhit_rating, spellpower, crit_rating, spellcrit_rating, healing, mp5, haste_rating,
      spell_haste_rating, attackpower, resilience_rating, expertise_rating;
  SecondaryStats operator+(SecondaryStats);
  SecondaryStats operator-(SecondaryStats);
  void operator=(SecondaryStats);
};

#endif
