#ifndef _SUPPORT_FUNCTIONS_HH_
#define _SUPPORT_FUNCTIONS_HH_

#include "Character.hh"
#include <vector>

using namespace std;

unsigned int factorial(unsigned int n) {
  if (n == 0) {
    return 1;
  }
  unsigned int result = 1;
  for (uint i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

unsigned int binomial(unsigned int n, unsigned int k) { return (factorial(n) / (factorial(k) * factorial(n - k))); }

Character char_with_best_consumables(Character character) {
  FlaskOfBlindingLight flask1;
  FlaskOfFortification flask2;
  ElixirOfMastery battle1;
  ElixirOfMajorAgility battle2;
  ElixirOfMajorStrength battle3;
  ElixirOfIronskin guardian1;
  ElixirOfMajorDefense guardian2;
  ElixirOfMajorFortitude guardian3;
  vector<Elixir> flasks = {flask1, flask2};
  vector<Elixir> battle_e = {battle1, battle2, battle3};
  vector<Elixir> guardian_e = {guardian1, guardian2, guardian3};
  vector<Character> chars;
  for (uint i = 0; i < flasks.size(); i++) {
    Character temp = character;
    temp.add_elixir(flasks[i]);
    temp.compute_stats();
    chars.push_back(temp);
  }
  for (uint i = 0; i < guardian_e.size(); i++) {
    for (uint j = 0; j < battle_e.size(); j++) {
      Character temp = character;
      temp.add_elixir(guardian_e[i]);
      temp.add_elixir(battle_e[j]);
      temp.compute_stats();
      chars.push_back(temp);
    }
  }
  double max_hp = 0;
  unsigned int max_i;
  for (uint i = 0; i < chars.size(); i++) {
    if (chars[i].get_eff_hp() > max_hp) {
      max_hp = chars[i].get_eff_hp();
      max_i = i;
    }
  }
  return chars[max_i];
}

vector<Gear> enchant_gear(vector<Gear> *in) {
  vector<Gear> result;
  for (uint i = 0; i < in->size(); i++) {
    if (in->at(i).slot == "Head") {
      Gear temp = in->at(i);
      GlyphOfTheDefender head_ench1;
      temp.set_enchantment(head_ench1);
      result.push_back(temp);
      Gear temp2 = in->at(i);
      ArcanumOfPower head_ench2;
      temp2.set_enchantment(head_ench2);
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      ArcanumOfTheGladiator head_ench3;
      temp3.set_enchantment(head_ench3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      LesserArcanumOfTenacity head_ench4;
      temp4.set_enchantment(head_ench4);
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      SyncretistsSigil head_ench5;
      temp5.set_enchantment(head_ench5);
      result.push_back(temp5);
      Gear temp6 = in->at(i);
      ArcanumOfFrostWarding head_ench6;
      temp6.set_enchantment(head_ench6);
      result.push_back(temp6);
    } else if (in->at(i).slot == "Shoulder") {
      Gear temp = in->at(i);
      GreaterInscriptionOfWarding shoulder_ench1;
      temp.set_enchantment(shoulder_ench1);
      result.push_back(temp);
      Gear temp2 = in->at(i);
      GreaterInscriptionOfTheKnight shoulder_ench2;
      temp2.set_enchantment(shoulder_ench2);
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      HeavyKnothideArmorKit shoulder_ench3;
      temp3.set_enchantment(shoulder_ench3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      FortitudeOfTheScourge shoulder_ench4;
      temp4.set_enchantment(shoulder_ench4);
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      InscriptionOfEndurance shoulder_ench5;
      temp5.set_enchantment(shoulder_ench5);
      result.push_back(temp5);
    } else if (in->at(i).slot == "Back") {
      Gear temp = in->at(i);
      Steelweave back_enchant1;
      temp.set_enchantment(back_enchant1);
      result.push_back(temp);
      Gear temp2 = in->at(i);
      MajorArmor back_enchant2;
      temp2.set_enchantment(back_enchant2);
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      BackGreaterAgility back_enchant3;
      temp3.set_enchantment(back_enchant3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      Dodge back_enchant4;
      temp4.set_enchantment(back_enchant4);
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      BackMajorResistance back_enchant5;
      temp5.set_enchantment(back_enchant5);
      result.push_back(temp5);
    } else if (in->at(i).slot == "Chest") {
      Gear temp = in->at(i);
      ExceptionalHealth chest_ench1;
      temp.set_enchantment(chest_ench1);
      result.push_back(temp);
      Gear temp2 = in->at(i);
      ExceptionalStats chest_enchantment2;
      temp2.set_enchantment(chest_enchantment2);
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      temp3.primary_stats.armor += 40;
      temp3.name += "+40 Armor"; // Rugged Armor Kit
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      temp4.secondary_stats.dodge_rating += 8;
      temp4.name += "+8 DodgeR"; // Vindicator's Armor Kit
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      temp5.secondary_stats.resilience_rating += 15;
      temp5.name += "+15 Resilience";
      result.push_back(temp5);
      Gear temp6 = in->at(i);
      temp6.primary_stats.stamina += 10;
      temp6.name += "+10 Sta"; // Heavy Knothide Armor Kit
      result.push_back(temp6);
      Gear temp7 = in->at(i);
      ChestDefense chest_ench7;
      temp7.set_enchantment(chest_ench7);
      result.push_back(temp7);
      Gear temp8 = in->at(i);
      ChestFrostArmorKit chest_ench8;
      temp8.set_enchantment(chest_ench8);
      result.push_back(temp8);
    } else if (in->at(i).slot == "Wrist") {
      Gear temp = in->at(i);
      temp.primary_stats.stamina += 12;
      temp.name += "+12 Sta"; // Fortitude
      result.push_back(temp);
      Gear temp2 = in->at(i);
      temp2.secondary_stats.defense_rating += 12;
      temp2.name += "+12 DefR";
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      temp3.secondary_stats.spellpower += 15;
      temp3.name += "+15 SP"; // Spellpower
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      temp4.primary_stats.strength += 4;
      temp4.primary_stats.agility += 4;
      temp4.primary_stats.stamina += 4;
      temp4.primary_stats.intelligence += 4;
      temp4.primary_stats.spirit += 4;
      temp4.name += "+4 all stats"; // Stats
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      Brawn wrist_ench5;
      temp5.set_enchantment(wrist_ench5);
      result.push_back(temp5);
    } else if (in->at(i).slot == "Hands") {
      Gear temp = in->at(i);
      HeavyKnothideArmorKitHands hands_ench1;
      temp.set_enchantment(hands_ench1);
      result.push_back(temp);
      Gear temp2 = in->at(i);
      HandsSuperiorAgility hands_enchantment2;
      temp2.set_enchantment(hands_enchantment2);
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      temp3.secondary_stats.spellpower += 20;
      temp3.name += "+20 SP"; // Major Spellpower
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      temp4.primary_stats.armor += 240;
      temp4.name += "+240 Armor"; // Glove Reinforcements
      result.push_back(temp4);
      Gear temp5 = in->at(i);
      temp5.secondary_stats.dodge_rating += 8;
      temp5.name += "+8 DodgeR"; // Vindicator's Armor Kit
      result.push_back(temp5);
      Gear temp6 = in->at(i);
      HandsMajorStrength hands_enchantment6;
      temp6.set_enchantment(hands_enchantment6);
      result.push_back(temp6);
      //+2% threat
      Gear temp7 = in->at(i);
      HandsFrostArmorKit hands_ench7;
      temp7.set_enchantment(hands_ench7);
      result.push_back(temp7);
    } else if (in->at(i).slot == "Legs") {
      Gear temp1 = in->at(i);
      temp1.primary_stats.armor += 40;
      temp1.name += "+40 Armor";
      result.push_back(temp1);
      Gear temp2 = in->at(i);
      temp2.primary_stats.stamina += 20;
      temp2.secondary_stats.spellpower += 35;
      temp2.name += "+Runic Spellthread";
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      NethercleftLegArmor leg_enchantment3;
      temp3.set_enchantment(leg_enchantment3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      LegsFrostArmorKit leg_enchantment4;
      temp4.set_enchantment(leg_enchantment4);
      result.push_back(temp4);
    } else if (in->at(i).slot == "Feet") {
      Gear temp = in->at(i);
      temp.primary_stats.stamina += 12;
      temp.name += "+12 Sta";
      result.push_back(temp);
      Gear temp2 = in->at(i);
      temp2.primary_stats.armor += 40;
      temp2.name += "+40 Armor";
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      BootsDexterity feet_ench3;
      temp3.set_enchantment(feet_ench3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      FeetFrostArmorKit feet_ench4;
      temp4.set_enchantment(feet_ench4);
      result.push_back(temp4);
    } else if (in->at(i).slot == "Mainhand") {
      Gear temp = in->at(i);
      WeaponMajorSpellpower mainhand_enchantment1;
      temp.set_enchantment(mainhand_enchantment1);
      result.push_back(temp);
    } else if (in->at(i).slot == "Offhand") {
      Gear temp = in->at(i);
      temp.secondary_stats.block_chance_rating += 15;
      temp.name += "+15 BlockR";
      result.push_back(temp);
      Gear temp2 = in->at(i);
      temp2.primary_stats.stamina += 18;
      temp2.name += "+18 Sta";
      result.push_back(temp2);
      Gear temp3 = in->at(i);
      ToughShield shield_enchantment3;
      temp3.set_enchantment(shield_enchantment3);
      result.push_back(temp3);
      Gear temp4 = in->at(i);
      ShieldResistance shield_enchantment4;
      temp4.set_enchantment(shield_enchantment4);
      result.push_back(temp4);
    }
  }
  return result;
}

void convergent_gearing(Character *character, vector<vector<Gear>> *all_gear, unsigned int cycle = 0) {
  cout << "Iteration = " << cycle << endl;
  cout << "Starting with " << character->get_eff_hp() << " effective HP." << endl;
  if (cycle > 50) {
    cout << "aborting condition reached" << endl;
    cout << character->get_eff_hp() << endl;
    character->print_gear();
    character->print_elixirs();
    abort();
  }
  DelicateLivingRuby rare_red_agi_gem;
  FlashingLivingRuby rare_red_parry_gem;
  RunedLivingRuby rare_red_sp_gem;
  SubtleLivingRuby rare_red_dodge_gem;
  SubtleCrimsonSpinel epic_red_dodge_gem;
  ThickDawnstone rare_yellow_def_gem;
  ThickLionseye epic_yellow_def_gem;
  RigidDawnstone rare_yellow_spellhit_gem;
  SolidStarOfElune rare_blue_sta_gem;
  SolidEmpyreanSapphire epic_blue_sta_gem;
  StalwartFireOpal epic_orange_dodge_def_gem;
  GlisteringFireOpal epic_orange_agi_def_gem;
  GlimmeringFireOpal epic_orange_parry_def_gem;
  EnduringTalasit rare_green_sta_def_gem;
  ShiftingNightseye rare_purple_sta_agi_gem;
  RegalNightseye rare_purple_sta_dodge_gem;
  GlowingNightseye rare_purple_sta_sp_gem;
  RegalTanzanite epic_purple_dodge_sta_gem;
  EnduringChrysoprase epic_green_sta_def_gem;
  GlowingTanzanite epic_purple_sp_sta_gem;
  VividChrysoprase epic_green_sphit_sta_gem;
  SplendidFireOpal epic_orange_parry_resilience_gem;
  ShiftingTanzanite epic_purple_agi_sta_gem;
  SteadyChrysoprase epic_green_sta_resilience_gem;
  BeamingFireOpal epic_orange_dodge_resilience_gem;
  DefendersTanzanite epic_purple_parry_sta_gem;

  TenaciousEarthstormDiamond meta1;
  PowerfulEarthstormDiamond meta2;
  EternalEarthstormDiamond meta3;
  vector<Socket> gems = {rare_red_agi_gem, rare_red_parry_gem, rare_red_sp_gem, rare_red_dodge_gem, rare_yellow_def_gem, rare_yellow_spellhit_gem, rare_blue_sta_gem, epic_orange_dodge_def_gem,
                         epic_orange_agi_def_gem, epic_orange_parry_def_gem, epic_purple_dodge_sta_gem, epic_green_sta_def_gem, epic_purple_sp_sta_gem, epic_green_sphit_sta_gem,
                         epic_orange_parry_resilience_gem, epic_purple_agi_sta_gem, epic_green_sta_resilience_gem, epic_orange_dodge_resilience_gem, epic_purple_parry_sta_gem,
                         // epic_blue_sta_gem,
                         // epic_red_dodge_gem,
                         // epic_yellow_def_gem,
                         rare_green_sta_def_gem, rare_purple_sta_agi_gem, rare_purple_sta_dodge_gem, rare_purple_sta_sp_gem, meta1, meta2, meta3};
  double max_hp = character->get_eff_hp();
  double max_tps = character->get_tps();
  unsigned int max_i, max_j;
  for (uint i = 0; i < all_gear->size(); i++) {
    for (uint j = 0; j < all_gear->at(i).size(); j++) {
      /*if (i == 14) {
        cout << i << "\t" << j << endl;
        cout << all_gear->at(i)[j].get_name() << endl;
        cout << all_gear->at(i)[j].slot << endl;
      }*/
      if (all_gear->at(i)[j].name == character->gear["Ring0"].name || all_gear->at(i)[j].name == character->gear["Ring1"].name || all_gear->at(i)[j].name == character->gear["Trinket0"].name ||
          all_gear->at(i)[j].name == character->gear["Trinket1"].name || character->gear[(*all_gear)[i][j].slot].get_name() == all_gear->at(i)[j].get_name()) {
        continue;
      }
      if (all_gear->at(i)[j].slot == "Mainhand") {
        cout << i << "\t" << j << "\t" << all_gear->at(i)[j].get_name() << endl;
        // is skipping gladiator weapon
      }
      Character temp = (*character);

      if (all_gear->at(i)[j].get_sockets() > 0) {
        if (all_gear->at(i)[j].gems.size() < all_gear->at(i)[j].get_sockets()) {
          Gear temp_gear = all_gear->at(i)[j];
          temp.find_best_gems(&temp_gear, &gems);
          temp.equip(temp_gear);
        }
      } else {
        temp.equip(all_gear->at(i)[j]);
      }
      temp.compute_stats();
      double temp_eff_hp = temp.get_eff_hp();
      double temp_tps = temp.get_tps();
      double temp_crit_immunity = temp.red_chance_to_get_crit();
      if (temp_eff_hp > max_hp && temp_crit_immunity >= 5.6 && !temp.survives_worst_case_szenario()) {
        max_i = i;
        max_j = j;
        max_hp = temp_eff_hp;
        max_tps = temp_tps;
      } else if (temp_eff_hp == max_hp && temp_tps > max_tps && temp_crit_immunity >= 5.6) {
        max_i = i;
        max_j = j;
        max_tps = temp_tps;
      } else if (temp_crit_immunity >= 5.6 && temp.survives_worst_case_szenario() && temp_tps > max_tps) {
        max_i = i;
        max_j = j;
        max_tps = temp_tps;
      }
    }
  }

  if (max_hp == character->get_eff_hp() && max_tps == character->get_tps()) {
    (*character) = char_with_best_consumables((*character));
    cout << "converged after " << cycle << " iterations." << endl;
    cout << "Effective HP = " << character->get_eff_hp() << endl;
    cout << "Approximated time of encounter = " << character->get_time_of_encounter() << " seconds" << endl;
    cout << "HP = " << character->get_hp() << endl;
    cout << "Armor = " << character->get_armor() << endl;
    cout << "Damage reduction from armor against level " << character->get_encounter().get_lvl() << " = " << character->get_armor_reduction() * 100.0 << "%" << endl;
    cout << "Defense = " << character->get_defense() << endl;
    cout << "Dodge against level " << character->get_encounter().get_lvl() << " = " << character->get_dodge_chance() << "%" << endl;
    cout << "Parry against level " << character->get_encounter().get_lvl() << " = " << character->get_parry() << "%" << endl;
    cout << "Chance to get missed against level " << character->get_encounter().get_lvl() << " = " << character->get_missed() << "%" << endl;
    cout << "Total avoidance against level" << character->get_encounter().get_lvl() << " = " << character->get_avoidance() << "%" << endl;
    cout << "Effective block chance against level" << character->get_encounter().get_lvl() << " = " << character->get_block() << "%" << endl;
    cout << "Block value = " << character->get_block_value() << endl;
    cout << "Reduced chance to get critical hits = " << character->red_chance_to_get_crit() << "%" << endl;
    cout << "TPS = " << character->get_tps() << endl;
    cout << "Frost resistance = " << character->primary_stats.frost_resistance + character->bonus_prim_stats.frost_resistance << endl;
    cout << "Survives worst case szenario against " << character->get_encounter().get_name() << ": " << character->survives_worst_case_szenario() << endl;
    cout << "Gear:" << endl;
    character->print_gear();
    character->print_elixirs();
    character->print_buffs();
  } else {
    Character temp = (*character);
    if (all_gear->at(max_i)[max_j].get_sockets() > 0) {
      if (all_gear->at(max_i)[max_j].gems.size() < all_gear->at(max_i)[max_j].get_sockets()) {
        Gear temp_gear = all_gear->at(max_i)[max_j];
        temp.find_best_gems(&temp_gear, &gems);
        temp.equip(temp_gear);
      }
    } else {
      temp.equip(all_gear->at(max_i)[max_j]);
    }
    temp.compute_stats();
    convergent_gearing(&temp, all_gear, cycle + 1);
  }
}

void iterative_gearing(Character *character, vector<vector<Gear>> *all_gear, double tps_cut = 650, unsigned int index = 0, unsigned int cycles = 0) {
  if (index > all_gear->size() - 1) {
    index = 0;
    cycles++;
  }
  if (cycles > 4) {
    cout << endl;
    if (character->red_chance_to_get_crit() < 5.6) {
      abort();
    }
    cout << "eff hp=" << character->get_eff_hp() << endl;
    cout << "tps=" << character->get_tps() << endl;
    cout << "hp=" << character->get_hp() << endl;
    cout << "dodge=" << character->get_dodge_chance() << endl;
    cout << "parry=" << character->get_parry() << endl;
    cout << "missed=" << character->get_missed() << endl;
    cout << "block chance=" << character->get_block() << endl;
    cout << "red chance to get critted=" << character->red_chance_to_get_crit() << endl;
    character->print_gear();
  } else {
    Character temp = (*character);
    unsigned int max_hp = 0;
    unsigned int max_tps = 0;
    double max_red_crit = 0;
    int max_i = -1;
    int max_i_tps = -1;
    int max_i_crit = -1;
    for (uint i = 0; i < all_gear->at(index).size(); i++) {
      if (all_gear->at(index)[i].slot == "Ring1") {
        if (temp.gear["Ring0"].name == all_gear->at(index)[i].name) {
          continue;
        }
      } else if (all_gear->at(index)[i].slot == "Trinket1") {
        if (temp.gear["Trinket0"].name == all_gear->at(index)[i].name) {
          continue;
        }
      }
      temp.equip(all_gear->at(index)[i]);
      temp.compute_stats();
      cout << "eff hp=" << temp.get_eff_hp() << endl;
      cout << "red chance to get critted=" << temp.red_chance_to_get_crit() << endl;
      if (temp.get_eff_hp() > max_hp && temp.get_tps() >= tps_cut && temp.red_chance_to_get_crit() >= 5.6) {
        max_hp = temp.get_eff_hp();
        max_i = i;
      } else if (temp.get_tps() > max_tps && temp.red_chance_to_get_crit() >= 5.6) {
        max_tps = temp.get_tps();
        max_i_tps = i;
      } else if (temp.red_chance_to_get_crit() > max_red_crit) {
        max_red_crit = temp.red_chance_to_get_crit();
        max_i_crit = i;
      }
    }
    if (max_i != -1) {
      temp.equip(all_gear->at(index)[max_i]);
      temp.compute_stats();
      iterative_gearing(&temp, all_gear, tps_cut, index + 1, cycles);
    } else if (max_tps < tps_cut) {
      temp.equip(all_gear->at(index)[max_i_tps]);
      temp.compute_stats();
      if (temp.red_chance_to_get_crit() < 5.6 && max_red_crit > 0) {
        temp.equip(all_gear->at(index)[max_i_crit]);
        temp.compute_stats();
      }
      iterative_gearing(&temp, all_gear, tps_cut, index + 1, cycles);
    } else if (max_red_crit < 5.6) {
      temp.equip(all_gear->at(index)[max_i_crit]);
      temp.compute_stats();
      iterative_gearing(&temp, all_gear, tps_cut, index + 1, cycles);
    } else {
      iterative_gearing(character, all_gear, tps_cut, index + 1, cycles);
    }
  }
}

void gear(vector<vector<Gear>> *all_gear, vector<Character> *characters, vector<unsigned int> *all_gear_indices, unsigned int index) {
  if (index < all_gear->size() - 1) {
    if ((*all_gear)[index].size() > 0) {
      for (uint i = 0; i < (*all_gear)[index].size(); i++) {
        if (index > 0) {
          if ((*all_gear)[index][i].name == (*all_gear)[index - 1][i].name) {
            if (i == (*all_gear)[index].size() - 1) {
              (*all_gear_indices)[index] = i;
            } else {
              (*all_gear_indices)[index] = i + 1;
            }
          } else {
            (*all_gear_indices)[index] = i;
          }
        } else {
          (*all_gear_indices)[index] = i;
        }
        gear(all_gear, characters, all_gear_indices, index + 1);
      }
    } else {
      gear(all_gear, characters, all_gear_indices, index + 1);
    }

  } else {
    Character temp("Paladin", "Draenei");
    temp.set_talent("Redoubt", 5);
    temp.set_talent("Toughness", 5);
    temp.set_talent("Precision", 3);
    temp.set_talent("Improved Righteous Fury", 3);
    temp.set_talent("Shield Specialization", 3);
    temp.set_talent("Anticipation", 5);
    temp.set_talent("Spell Warding", 2);
    temp.set_talent("Sacred Duty", 2);
    temp.set_talent("One-Handed Weapon Specialization", 5);
    temp.set_talent("Ardent Defender", 5);
    temp.set_talent("Combat Expertise", 5);
    temp.set_talent("Blessing of Sanctuary", 1);
    temp.set_talent("Holy Shield", 1);
    temp.set_talent("Improved Holy Shield", 2);
    temp.set_talent("Improved Judgement", 2);
    temp.set_talent("Deflection", 5);
    for (uint i = 0; i < all_gear->size() - 1; i++) {
      if ((*all_gear)[i][all_gear_indices->at(i)].name == (*all_gear)[i + 1][all_gear_indices->at(i + 1)].name) {
        return;
      }
    }
    for (uint i = 0; i < all_gear->size(); i++) {
      temp.equip((*all_gear)[i][all_gear_indices->at(i)]);
    }
    temp.compute_stats();
    // if (temp.red_chance_to_get_crit() >= 5.6) {
    characters->push_back(temp);
    //}
  }
}

#endif
