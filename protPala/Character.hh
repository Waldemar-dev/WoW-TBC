#ifndef _CHARACTER_HH_
#define _CHARACTER_HH_

class Boss;
#include "NPCs.hh"
#include "buffs.hh"
#include "equipment.hh"
#include "stats.hh"
// #include "enums.hh"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cfloat>
#include <functional>
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "Math/Minimizer.h"
#include "Math/MinimizerOptions.h"

class Character
{
public:
  Character(CharacterClass, Race, const unsigned int, Boss *const);
  Character(const Character &);
  ~Character() = default;

  void set_encounter(unsigned int);
  // void set_boss(Boss *in) { boss_ = in; }
  void set_n_ally_dd(unsigned int in) { nDDs_ = in; }
  void get_raid_buffed();
  void print_buffs();
  double get_time_of_encounter() const
  {
    if (timeNeeded_ == 0)
    {
      std::cout << "return 0 sec" << std::endl;
      abort();
    }
    return timeNeeded_;
  }
  double get_eff_hp(double time_in_seconds_ = 0.0);
  double get_avoidance(bool dual_wield = false); // in %
  double get_crush(bool dual_wield = false);     // in decimals
  void set_talent(std::string, unsigned int);
  double get_dodge_chance();         // in %
  double get_dodge_chance_with_dr(); // in %
  unsigned int get_armor(unsigned int debuff = 0);
  const unsigned int getLevel() const { return level_; }
  double get_armor_reduction(unsigned int debuff = 0); // in decimals
  double get_parry();                                  // in %
  double get_missed(bool dual_wield = false);          // in %
  double get_block(bool dual_wield = false);           // in decimals
  void equip(Gear);
  double red_chance_to_get_crit();
  double get_tps();
  double getSavedTps() const { return savedTps_; }
  double get_bear_tps(bool simplify = true);
  double simple_bear_tps();
  double calc_bear_tps(double, double, double, double);
  double get_bear_dps();
  double calc_bear_dps(double, double, double, double);
  double get_paladin_tps();
  void print_gear();
  double get_hit_chance(bool yellow_damage = false); // decimal
  double getBaseHit() const { return hit_; }
  double getBaseSpellHit() const { return spellHit_; }
  double get_spell_hit_chance();
  double get_effective_redoubt_chance();
  double check_block_chance(double, bool dual_wield = false);
  double get_spell_crit_chance();
  double get_melee_crit_chance(); // decimal
  double get_hp();
  double get_mp();
  unsigned int get_defense();
  unsigned int getBaseDefense() const { return defense_; }
  unsigned int getBaseExpertise() const { return expertise_; }
  double getBaseDodge() const { return dodge_; }
  double getBaseParry() const { return parry_; }
  double getBaseBlockChance() const { return blockChance_; }
  double getBaseCrit() const { return crit_; }
  double getBaseSpellCrit() const { return spellCrit_; }
  unsigned int get_block_value();
  void print_base_stats();
  void print_all_stats();
  std::vector<Elixir> get_elixirs() const { return elixirs_; }
  void add_elixir(Elixir);
  void print_elixirs();
  double get_hps(); // to do
  void reset_boni();
  double average_resistance(MagicSchool);
  bool survives_worst_case_szenario(unsigned int *out = 0);
  double total_damage_taken(double time_in_seconds_ = 0.0);
  double metric(double time_in_seconds_ = 0.0);
  double getSavedMetric() const { return savedMetric_; }
  Boss *get_encounter() const { return boss_; }
  unsigned int get_n_dds() const { return nDDs_; }
  void add_buff(Buff);
  void add_bufffood(BuffFood in) { buffFood_ = in; }
  BuffFood get_buff_food() const { return buffFood_; }
  void operator=(Character);
  double get_miss_chance(); // decimal
  double get_parried_chance();
  double get_dodged_chance();  // decimal
  double get_blocked_chance(); // decimal
  double get_seal_of_blood_damage();
  double get_judgement_of_blood_damage();
  double get_seal_of_blood_recoil() { return 0.1 * get_seal_of_blood_damage(); }
  double get_judgement_of_blood_recoil() { return 0.33 * get_judgement_of_blood_damage(); }
  double get_passive_rage_generation();
  double get_active_rage_generation();
  double get_total_rage_generation() { return get_passive_rage_generation() + get_active_rage_generation(); }
  double get_white_damage();
  double get_glancing_blow_chance(); // decimal
  double get_glancing_blow_damage();
  double get_global_cd();
  double get_haste();
  double get_attackpower();
  double get_spellpower(SecondaryAttributes);
  double get_tot_prim_stat(PrimaryAttributes in) { return basePrimStats_.get_stat(in) + primaryStats_.get_stat(in) + bonusPrimStats_.get_stat(in); }
  double get_tot_sec_stat(SecondaryAttributes in) { return baseSecStats_.get_stat(in) + secondaryStats_.get_stat(in) + bonusSecStats_.get_stat(in); }
  void set_bear(bool in) { bearForm_ = in; }
  void set_cat(bool in) { catForm_ = in; }
  bool is_bear() { return bearForm_; }
  bool is_cat() { return catForm_; }
  void compute_set_boni();
  double get_critted_chance(); // in decimals
  void set_source(Source in) { src_ = in; }
  Source get_source() { return src_; }
  void exclude_source(Source in);
  bool is_excluded(Source in);
  bool is_excluded(Gear *in);
  void set_phase(uint in) { maxPhase_ = in; }
  uint get_max_phase() { return maxPhase_; }
  void set_base_prim_stat(PrimaryAttributes inIndex, double inValue) { basePrimStats_.set_stat(inIndex, inValue); }
  void set_base_prim_stats(PrimaryStats in) { basePrimStats_.set_stats(in); }
  void set_base_sec_stat(SecondaryAttributes inIndex, double inValue) { baseSecStats_.set_stat(inIndex, inValue); }
  void set_base_sec_stats(SecondaryStats in) { baseSecStats_.set_stats(in); }
  void set_bonus_prim_stats(PrimaryStats in) { bonusPrimStats_.set_stats(in); }
  void set_bonus_sec_stats(SecondaryStats in) { bonusSecStats_.set_stats(in); }
  std::map<std::string, unsigned int> talents;
  CharacterClass get_class() const { return charClass_; }
  Race get_race() const { return charRace_; }
  std::string getSeal() const { return seal_; }
  std::unordered_map<Slot, Gear, std::hash<uint>> gear;
  unsigned int number_of_rings = 0;
  unsigned int number_of_trinkets = 0;
  // precalc
  void compute_stats();
  void parry_haste_sim();
  void set_prim_stat(PrimaryAttributes inIndex, double inValue) { primaryStats_.set_stat(inIndex, inValue); }
  void set_sec_stat(SecondaryAttributes inIndex, double inValue) { secondaryStats_.set_stat(inIndex, inValue); }
  double get_prim_stat(PrimaryAttributes inIndex) const { return primaryStats_.get_stat(inIndex); }
  double get_bonus_prim_stat(PrimaryAttributes inIndex) const { return bonusPrimStats_.get_stat(inIndex); }
  double get_base_prim_stat(PrimaryAttributes in) const { return basePrimStats_.get_stat(in); }
  double get_base_sec_stat(SecondaryAttributes in) const { return baseSecStats_.get_stat(in); }
  double get_sec_stat(SecondaryAttributes inIndex) const { return secondaryStats_.get_stat(inIndex); }
  double get_bonus_sec_stat(SecondaryAttributes inIndex) const { return bonusSecStats_.get_stat(inIndex); }
  double calc_average_raid_damage(double, double);
  double calc_average_raid_dps(double);
  void set_prim_stats(PrimaryStats in) { primaryStats_.set_stats(in); }
  PrimaryStats get_prim_stats() const { return primaryStats_; }
  PrimaryStats get_bonus_prim_stats() const { return bonusPrimStats_; }
  PrimaryStats get_base_prim_stats() const { return basePrimStats_; }
  void set_bonus_prim_stat(PrimaryAttributes inIndex, double inValue) { bonusPrimStats_.set_stat(inIndex, inValue); }
  void set_bonus_sec_stat(SecondaryAttributes inIndex, double inValue) { bonusSecStats_.set_stat(inIndex, inValue); }
  void set_sec_stats(SecondaryStats in) { secondaryStats_.set_stats(in); }
  SecondaryStats get_sec_stats() const { return secondaryStats_; }
  SecondaryStats get_bonus_sec_stats() const { return bonusSecStats_; }
  SecondaryStats get_base_sec_stats() const { return baseSecStats_; }
  void use_trinkets_parallel() { trinketsParallel_ = true; }
  bool how_use_trinkets() const { return trinketsParallel_; }
  bool use_lacerate_over_swipe() const { return isLacerateFiller_; }
  bool calculatedParryHaste() const { return parryHaste_; }
  bool saveMetric() const { return saveMetric_; }
  bool saveTps() const { return saveTps_; }
  bool saveHps() const { return saveHps_; }
  bool saveWorstCase() const { return saveWorstCase_; }
  bool saveDps() const { return saveDps_; }
  bool savedWorstCase() const { return savedWorstCase_; }
  std::vector<Buff> get_buffs() const { return buffs_; }
  double getH() const { return h_; }
  double getSavedDps() const { return savedDps_; }
  int getRecursions() const { return recursions_; }
  unsigned int getSavedWorstCaseN() const { return savedWorstCaseN_; }

  // friend std::ostream &operator<<(std::ostream &out, const Character &playerChar)
  // {
  //   out<<playerChar.get_race()<<"\t"<<playerChar.get_class()<<"\t";
  //   for (std::map<Slot, Gear>::iterator it=playerChar.gear.begin();it!=playerChar.gear.end();it++){
  //     out<<it->second<<"\t";
  //   }
  //   for (uint i=0;i<playerChar.get_elixirs().size();i++){
  //     out<<playerChar.get_elixirs()[i]<<"\t";
  //   }
  //   out<<playerChar.metric();
  // }
private:
  const CharacterClass charClass_;
  const Race charRace_;
  const unsigned int level_;
  Boss *const boss_;
  double h_;
  unsigned int defense_, expertise_;
  double dodge_, parry_, blockChance_, crit_, spellCrit_, hit_, spellHit_;
  bool trinketsParallel_;
  double timeNeeded_;
  static const double myH_, fExpertise_, fDef_, fDodge_, fParry_, fBlock_, fHit_, fSpellHit_, fCrit_, fHaste_, fArmorPen_, fDefAvoidance_, fResilience_;
  static const double rExpertise_, rHit_, rSpellHit_, rCrit_, rHaste_, rArmorPen_, rDef_, rDefAvoidance_, rDodge_, rParry_, rBlock_, rResilience_, cD_, cP_, cM_, k_, myRDodge_;
  static const double lacerateDirectBonusThreat_, lacerateDirectThreatMultiplier_, swipeBonusThreat_, swipeThreatMultiplier_, maulBonusThreat_, maulThreatMultiplier_, mangleBonusThreat_, mangleThreatMultiplier_;
  static bool kings_, sanctuary_, bearForm_, catForm_; // static only for comparing same character with different gear
  static const uint tpsFitAttempts_;
  static unsigned int nDDs_; // DDs in group/raid
  static unsigned int maxPhase_;
  PrimaryStats basePrimStats_;
  SecondaryStats baseSecStats_;
  PrimaryStats primaryStats_;
  PrimaryStats bonusPrimStats_;
  SecondaryStats secondaryStats_;
  SecondaryStats bonusSecStats_;
  std::vector<Elixir> elixirs_;
  std::vector<Buff> buffs_;
  BuffFood buffFood_;
  Source src_;
  std::vector<Source> excludedSrcs_;
  std::string seal_;
  double n_auto = 0, n_maul = 0, n_mangle = 0, n_swipe = 0, n_lacerate = 0, n_min_lacerate = 0, n_filler = 0; // to do: naming convention
  bool isLacerateFiller_;
  int recursions_;
  // precalc switches
  bool parryHaste_;
  bool saveMetric_;
  bool saveTps_;
  bool saveHps_;
  bool saveWorstCase_;
  bool saveDps_;
  // precalc saves
  double savedTps_;
  double savedMetric_;
  double savedDps_;
  bool savedWorstCase_;
  unsigned int savedWorstCaseN_;
  // functions
  double get_leader_of_the_pack_hps();
  double get_hps(double);
};

#endif
