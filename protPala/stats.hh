#ifndef _STATS_HH_
#define _STATS_HH_

#include "enums.hh"
#include <algorithm>
#include <iostream>
#include <vector>

class AbstractStats{
  public:
  AbstractStats(uint);
  virtual ~AbstractStats()=0;

  uint getNumberOfVars() const {return stats_.size();}
  double getStat(uint in) const {return stats_[in];}
  void setStat(uint inIndex, double inValue){stats_[inIndex]=inValue;}
  void addStat(uint inIndex, double inValue){stats_[inIndex]+=inValue;}
  void reset();

  private:
  std::vector<double> stats_;
};

template <class T>
class Stats : public AbstractStats
{
  public:
  Stats(uint);
  Stats(const Stats&);
  ~Stats();

  double get_stat(T inIndex) const { return getStat((uint)inIndex); }
  void set_stat(T inIndex, double inValue) { setStat((uint)inIndex, inValue); }
  void add_stat(T inIndex, double inValue){ addStat((uint)inIndex,inValue); }
  void set_stats(const Stats<T>);
  void setStatsRef(const Stats<T>&);

  Stats<T> operator+(const Stats<T>) const;
  Stats<T> operator-(const Stats<T>) const;
  void operator=(Stats<T>);
  bool operator==(const Stats<T>) const;
  bool operator<=(const Stats<T>) const;
  bool operator>=(const Stats<T>) const;

  friend std::ostream &operator<<(std::ostream &out, const Stats<T> &stats)
  {
    for (uint i=0;i<stats.getNumberOfVars()-1;i++)
    {
      out << stats.get_stat((T)i) << "\t";
    }
    out << stats.get_stat((T)(stats.getNumberOfVars()-1));
    return out;
  };
};

class PrimaryStats : public Stats<PrimaryAttributes>
{
public:
  PrimaryStats();
  PrimaryStats(const PrimaryStats&);
  PrimaryStats(const Stats&);
  ~PrimaryStats() = default;
  
  void print() const;
  bool operator<=(const PrimaryStats) const;
  bool operator>=(const PrimaryStats) const;
  // friend istream &operator>>(istream &in, PrimaryStats &prim_stats)
  // {
  //   in >> prim_stats.strength >> prim_stats.agility >> prim_stats.stamina >> prim_stats.intelligence >> prim_stats.spirit >> prim_stats.armor >> prim_stats.arcane_resistance >> prim_stats.fire_resistance >> prim_stats.frost_resistance >> prim_stats.shadow_resistance >> prim_stats.nature_resistance >> prim_stats.weapondamage >> prim_stats.attack_speed >> prim_stats.health >> prim_stats.mana;
  //   return in;
  // };
};

class SecondaryStats : public Stats<SecondaryAttributes>
{
public:
  SecondaryStats();
  SecondaryStats(const SecondaryStats&);
  SecondaryStats(const Stats&);
  ~SecondaryStats() = default;

  void print() const;
  // friend std::ostream &operator<<(std::ostream &out, const SecondaryStats &sec_stats)
  // {
  //   for (uint i=(uint)SecondaryAttributes::FirstSecondary;i<(uint)SecondaryAttributes::LastSecondary;i++)
  //   {
  //     out << sec_stats.get_stat((SecondaryAttributes)i) << "\t";
  //   }
  //   out << sec_stats.get_stat(SecondaryAttributes::LastSecondary);
  //   return out;
  // };
  // friend istream &operator>>(istream &in, SecondaryStats &sec_stats)
  // {
  //   in >> sec_stats.armor >> sec_stats.dodge_rating >> sec_stats.parry_rating >> sec_stats.block_chance_rating >> sec_stats.block_value >> sec_stats.defense_rating >> sec_stats.hit_rating >> sec_stats.spellpower >> sec_stats.spellhit_rating >> sec_stats.crit_rating >> sec_stats.spellcrit_rating >> sec_stats.healing >> sec_stats.mp5 >> sec_stats.haste_rating >> sec_stats.spell_haste_rating >> sec_stats.attackpower >> sec_stats.resilience_rating >> sec_stats.expertise_rating >> sec_stats.armor_penetration >> sec_stats.arcane_spellpower >> sec_stats.fire_spellpower >> sec_stats.frost_spellpower >> sec_stats.shadow_spellpower >> sec_stats.nature_spellpower >> sec_stats.holy_spellpower;
  //   return in;
  // };
};

#endif
