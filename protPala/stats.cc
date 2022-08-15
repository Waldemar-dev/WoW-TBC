#include "stats.hh"

AbstractStats::AbstractStats(uint in): stats_(std::vector<double>(in,0)){}

AbstractStats::~AbstractStats(){}

template<typename T>
Stats<T>::Stats(uint number_of_vars): AbstractStats(number_of_vars){
}

template<typename T>
Stats<T>::Stats(const Stats<T> &in): AbstractStats(in.getNumberOfVars()){
  // setStatsRef(in);
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    set_stat((T)i, in.get_stat((T)i));
  }
}

void AbstractStats::reset()
{
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    stats_[i]=0;
  }
}

template<typename T>
Stats<T>::~Stats<T>(){}

template<typename T>
void Stats<T>::set_stats(const Stats<T> in)
{
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    set_stat((T)i, in.get_stat((T)i));
  }
}

template<typename T>
void Stats<T>::setStatsRef(const Stats<T> &in)
{
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    set_stat((T)i, in.get_stat((T)i));
  }
}

// void PrimaryStats::set_stats(const PrimaryStats in)
// {
//   for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
//   {
//     set_stat((PrimaryAttributes)i, in.get_stat((PrimaryAttributes)i));
//   }
// }
template<typename T>
Stats<T> Stats<T>::operator+(const Stats<T> in) const
{
  Stats<T> result(getNumberOfVars());
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    result.set_stat((T)i, get_stat((T)i) + in.get_stat((T)i));
  }
  return result;
}

template<typename T>
Stats<T> Stats<T>::operator-(const Stats<T> in) const
{
  Stats<T> result(getNumberOfVars());
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    result.set_stat((T)i, get_stat((T)i) - in.get_stat((T)i));
  }
  return result;
}

template<typename T>
void Stats<T>::operator=(Stats<T> in)
{
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    set_stat((T)i, in.get_stat((T)i));
  }
}

template<typename T>
bool Stats<T>::operator==(const Stats<T> in) const
{
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    if (get_stat((T)i) != in.get_stat((T)i))
    {
      return false;
    }
  }
  return true;
}

PrimaryStats::PrimaryStats() : Stats((uint)PrimaryAttributes::PrimAttCount)
{
}

PrimaryStats::PrimaryStats(const PrimaryStats &in):Stats((uint)PrimaryAttributes::PrimAttCount){
  setStatsRef(in);
}

PrimaryStats::PrimaryStats(const Stats &in):Stats((uint)PrimaryAttributes::PrimAttCount){
  setStatsRef(in);
}

void PrimaryStats::print() const
{
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    std::cout << Names::primaryAttributesNames[i] << " = " << get_stat((PrimaryAttributes)i) << std::endl;
  }
}

bool PrimaryStats::operator<=(PrimaryStats b) const
{
  bool is_weapon = (get_stat(PrimaryAttributes::AttackSpeed) > 0) && (b.get_stat(PrimaryAttributes::AttackSpeed) > 0);
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    if (i == (uint)PrimaryAttributes::WeaponDamage || i == (uint)PrimaryAttributes::AttackSpeed)
    {
      continue;
    }
    if (!(get_stat((PrimaryAttributes)i) <= b.get_stat((PrimaryAttributes)i)))
    {
      return false;
    }
  }
  if (is_weapon && !(get_stat(PrimaryAttributes::AttackSpeed) <= b.get_stat(PrimaryAttributes::AttackSpeed) && get_stat(PrimaryAttributes::WeaponDamage) <= b.get_stat(PrimaryAttributes::WeaponDamage)))
  {
    return false;
  }
  return true;
}

bool PrimaryStats::operator>=(PrimaryStats b) const
{
  for (uint i = (uint)PrimaryAttributes::FirstPrimary; i <= (uint)PrimaryAttributes::LastPrimary; i++)
  {
    if (i == (uint)PrimaryAttributes::WeaponDamage || i == (uint)PrimaryAttributes::AttackSpeed)
    {
      continue;
    }
    if (!(get_stat((PrimaryAttributes)i) >= b.get_stat((PrimaryAttributes)i)))
    {
      return false;
    }
  }
  return true;
}

SecondaryStats::SecondaryStats() : Stats((uint)SecondaryAttributes::SecAttCount)
{
}

SecondaryStats::SecondaryStats(const SecondaryStats& in): Stats((uint)SecondaryAttributes::SecAttCount){
  setStatsRef(in);
}

SecondaryStats::SecondaryStats(const Stats& in): Stats((uint)SecondaryAttributes::SecAttCount){
  setStatsRef(in);
}

void SecondaryStats::print() const
{
  for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
  {
    std::cout << Names::secondaryAttributesNames[i] << " = " << get_stat((SecondaryAttributes)i) << std::endl;
  }
}

template<typename T>
bool Stats<T>::operator<=(const Stats<T> in) const {
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    if (!(get_stat((T)i) <= in.get_stat((T)i)))
    {
      return false;
    }
  }
  return true;
}

template<typename T>
bool Stats<T>::operator>=(const Stats<T> in) const {
  for (uint i = 0; i < getNumberOfVars(); i++)
  {
    if (!(get_stat((T)i) >= in.get_stat((T)i)))
    {
      return false;
    }
  }
  return true;
}

// template<typename T>
// bool Stats<T>::operator==(const Stats<T> in) const {
//   for (uint i = 0; i < getNumberOfVars(); i++)
//   {
//     if (get_stat((T)i) != in.get_stat((T)i))
//     {
//       return false;
//     }
//   }
//   return true;
// }

// template<typename T>
// void Stats<T>::operator=(const Stats<T> in)
// {
//   for (uint i = 0; i < getNumberOfVars(); i++)
//   {
//     set_stat((T)i, in.get_stat((T)i));
//   }
// }

// SecondaryStats SecondaryStats::operator+(SecondaryStats in) const
// {
//   SecondaryStats result;
//   for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
//   {
//     result.set_stat((SecondaryAttributes)i, get_stat((SecondaryAttributes)i) + in.get_stat((SecondaryAttributes)i));
//   }
//   return result;
// }

// void SecondaryStats::set_stats(const SecondaryStats in)
// {
//   for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
//   {
//     set_stat((SecondaryAttributes)i, in.get_stat((SecondaryAttributes)i));
//   }
// }

// SecondaryStats SecondaryStats::operator-(SecondaryStats in) const
// {
//   SecondaryStats result;
//   for (uint i = (uint)SecondaryAttributes::FirstSecondary; i <= (uint)SecondaryAttributes::LastSecondary; i++)
//   {
//     result.set_stat((SecondaryAttributes)i, get_stat((SecondaryAttributes)i) - in.get_stat((SecondaryAttributes)i));
//   }
//   return result;
// }

template class Stats<PrimaryAttributes>;
template class Stats<SecondaryAttributes>;