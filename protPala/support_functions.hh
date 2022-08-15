#ifndef _SUPPORT_FUNCTIONS_HH_
#define _SUPPORT_FUNCTIONS_HH_

#include "Character.hh"
#include "equipment.hh"
#include "enchantments.hh"
#include <functional>
// #include "enums.hh"
#include <vector>
#include <map>
#include <cfloat>
#include <time.h>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "Math/Minimizer.h"
#include "Math/MinimizerOptions.h"

void remove(std::vector<uint> &v)
{
  auto end = v.end();
  for (auto it = v.begin(); it != end; ++it)
  {
    end = std::remove(it + 1, end, *it);
  }
  v.erase(end, v.end());
}

Character char_with_best_consumables(Character *character)
{
  std::vector<Elixir> flasks = {FlaskOfBlindingLight(), FlaskOfFortification(), FlaskOfRelentlessAssault(), FlaskOfChromaticWonder()};
  std::vector<Elixir> battle_e = {ElixirOfMastery(), ElixirOfMajorAgility(), ElixirOfMajorStrength(), FelStrengthElixir()};
  std::vector<Elixir> guardian_e = {ElixirOfIronskin(), ElixirOfMajorDefense(), ElixirOfMajorFortitude()};
  std::vector<BuffFood> cooking = {FishermensFeast(), GrilledMudfish(), BroiledBloodfin(), RoastedClefthoof(), SpicyHotTalbulk()};
  std::vector<Character> chars;
  for (uint i = 0; i < flasks.size(); i++)
  {
    for (uint j = 0; j < cooking.size(); j++)
    {
      Character temp(*character);
      temp.add_elixir(flasks[i]);
      temp.add_bufffood(cooking[j]);
      temp.compute_stats();
      chars.push_back(temp);
    }
  }
  for (uint i = 0; i < guardian_e.size(); i++)
  {
    for (uint j = 0; j < battle_e.size(); j++)
    {
      for (uint k = 0; k < cooking.size(); k++)
      {
        Character temp(*character);
        temp.add_elixir(guardian_e[i]);
        temp.add_elixir(battle_e[j]);
        temp.add_bufffood(cooking[k]);
        temp.compute_stats();
        chars.push_back(temp);
      }
    }
  }
  double max_metric = DBL_MAX;
  unsigned int max_i=0;
  for (uint i = 0; i < chars.size(); i++)
  {
    double temp_metric = chars[i].metric();
    if (temp_metric < max_metric)
    {
      max_metric = temp_metric;
      max_i = i;
    }
  }
  return chars[max_i];
}

std::vector<Gear> enchant_gear(std::vector<Gear> *in, CharacterClass character_class)
{
  std::vector<Gear> result;
  result.reserve(11 * in->size());
  // std::unordered_map<MagicSchool, double> magic_dps = character->get_encounter()->get_magic_dps();
  for (uint i = 0; i < in->size(); i++)
  {
    std::vector<Gear> temp_result;
    if (in->at(i).get_slot() == Slot::Head)
    {
      Gear temp = in->at(i);
      GlyphOfTheDefender head_ench1;
      temp.set_enchantment(head_ench1);
      temp_result.push_back(temp);
      if (character_class == CharacterClass::Paladin)
      {
        Gear temp2 = in->at(i);
        ArcanumOfPower head_ench2;
        temp2.set_enchantment(head_ench2);
        temp_result.push_back(temp2);
        Gear temp5 = in->at(i);
        SyncretistsSigil head_ench5;
        temp5.set_enchantment(head_ench5);
        temp_result.push_back(temp5);
      }
      Gear temp3 = in->at(i);
      ArcanumOfTheGladiator head_ench3;
      temp3.set_enchantment(head_ench3);
      temp_result.push_back(temp3);
      Gear temp4 = in->at(i);
      LesserArcanumOfTenacity head_ench4;
      temp4.set_enchantment(head_ench4);
      temp_result.push_back(temp4);
      // if (magic_dps.find(MagicSchool::Frost) != magic_dps.end())
      // if (character->get_encounter()->get_name() == "Hydros")
      // {
      Gear temp6 = in->at(i);
      ArcanumOfFrostWarding head_ench6;
      temp6.set_enchantment(head_ench6);
      temp_result.push_back(temp6);
      // }
      // if (magic_dps.find(MagicSchool::Shadow) != magic_dps.end()) //(character->get_encounter()->get_name() == "Prince Malchezaar")
      // {
      Gear temp10 = in->at(i);
      GlyphOfShadowWarding head_ench10;
      temp10.set_enchantment(head_ench10);
      temp_result.push_back(temp10);
      // }
      // if (magic_dps.find(MagicSchool::Fire) != magic_dps.end())
      // {
      Gear temp11 = in->at(i);
      GlyphOfFireWarding head_ench11;
      temp11.set_enchantment(head_ench11);
      temp_result.push_back(temp11);
      // }
      Gear temp7 = in->at(i);
      ArcanumOfFerocity head_ench7;
      temp7.set_enchantment(head_ench7);
      temp_result.push_back(temp7);
      Gear temp8 = in->at(i);
      HeavyKnothideArmorKitHead head_ench8;
      temp8.set_enchantment(head_ench8);
      temp_result.push_back(temp8);
      Gear temp9 = in->at(i);
      ArcanumOfProtection head_ench9;
      temp9.set_enchantment(head_ench9);
      temp_result.push_back(temp9);
    }
    else if (in->at(i).get_slot() == Slot::Shoulders)
    {
      Gear temp = in->at(i);
      GreaterInscriptionOfWarding shoulder_ench1;
      temp.set_enchantment(shoulder_ench1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      GreaterInscriptionOfTheKnight shoulder_ench2;
      temp2.set_enchantment(shoulder_ench2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      HeavyKnothideArmorKit shoulder_ench3;
      temp3.set_enchantment(shoulder_ench3);
      temp_result.push_back(temp3);
      Gear temp4 = in->at(i);
      FortitudeOfTheScourge shoulder_ench4;
      temp4.set_enchantment(shoulder_ench4);
      temp_result.push_back(temp4);
      Gear temp5 = in->at(i);
      InscriptionOfEndurance shoulder_ench5;
      temp5.set_enchantment(shoulder_ench5);
      temp_result.push_back(temp5);
    }
    else if (in->at(i).get_slot() == Slot::Back)
    {
      Gear temp = in->at(i);
      Steelweave back_enchant1;
      temp.set_enchantment(back_enchant1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      MajorArmor back_enchant2;
      temp2.set_enchantment(back_enchant2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      BackGreaterAgility back_enchant3;
      temp3.set_enchantment(back_enchant3);
      temp_result.push_back(temp3);
      Gear temp4 = in->at(i);
      Dodge back_enchant4;
      temp4.set_enchantment(back_enchant4);
      temp_result.push_back(temp4);
      Gear temp5 = in->at(i);
      BackMajorResistance back_enchant5;
      temp5.set_enchantment(back_enchant5);
      temp_result.push_back(temp5);
      // if (magic_dps.find(MagicSchool::Shadow) != magic_dps.end()) //(character->get_encounter()->get_name() == "Prince Malchezaar")
      // {
      Gear temp7 = in->at(i);
      CloakGreaterShadowResistance back_enchant7;
      temp7.set_enchantment(back_enchant7);
      temp_result.push_back(temp7);
      // }
      // if (magic_dps.find(MagicSchool::Fire) != magic_dps.end())
      // {
      Gear temp6 = in->at(i);
      CloakGreaterFireResistance back_enchant6;
      temp6.set_enchantment(back_enchant6);
      temp_result.push_back(temp6);
      // }
    }
    else if (in->at(i).get_slot() == Slot::Chest)
    {
      Gear temp = in->at(i);
      ExceptionalHealth chest_ench1;
      temp.set_enchantment(chest_ench1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      ExceptionalStats chest_enchantment2;
      temp2.set_enchantment(chest_enchantment2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      RuggedArmorKitChest chest_ench3;
      temp3.set_enchantment(chest_ench3);
      temp_result.push_back(temp3);
      Gear temp4 = in->at(i);
      VindicatorsArmorKit chest_ench4;
      temp4.set_enchantment(chest_ench4);
      temp_result.push_back(temp4);
      Gear temp5 = in->at(i);
      MajorResilience chest_ench5;
      temp5.set_enchantment(chest_ench5);
      temp_result.push_back(temp5);
      Gear temp6 = in->at(i);
      HeavyKnothideArmorKitChest chest_ench6;
      temp6.set_enchantment(chest_ench6);
      temp_result.push_back(temp6);
      Gear temp7 = in->at(i);
      ChestDefense chest_ench7;
      temp7.set_enchantment(chest_ench7);
      temp_result.push_back(temp7);
      // if (magic_dps.find(MagicSchool::Frost) != magic_dps.end()) //(character->get_encounter()->get_name() == "Hydros")
      // {
      Gear temp8 = in->at(i);
      ChestFrostArmorKit chest_ench8;
      temp8.set_enchantment(chest_ench8);
      temp_result.push_back(temp8);
      // }
      // if (magic_dps.find(MagicSchool::Fire) != magic_dps.end()) //(character->get_encounter()->get_name() == "Prince Malchezaar")
      // {
      Gear temp9 = in->at(i);
      ChestFlameArmorKit chest_ench9;
      temp9.set_enchantment(chest_ench9);
      temp_result.push_back(temp9);
      // }
      // if (magic_dps.find(MagicSchool::Shadow) != magic_dps.end())
      // {
      Gear temp10 = in->at(i);
      ChestShadowArmorKit chest_ench10;
      temp10.set_enchantment(chest_ench10);
      temp_result.push_back(temp10);
      // }
    }
    else if (in->at(i).get_slot() == Slot::Bracers)
    {
      Gear temp = in->at(i);
      WristsFortitude wrist_ench1;
      temp.set_enchantment(wrist_ench1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      WristsMajorDefense wrist_ench2;
      temp2.set_enchantment(wrist_ench2);
      temp_result.push_back(temp2);
      if (character_class == CharacterClass::Paladin)
      {
        Gear temp3 = in->at(i);
        WristsSpellpower wrist_ench3;
        temp3.set_enchantment(wrist_ench3);
        temp_result.push_back(temp3);
      }
      Gear temp4 = in->at(i);
      WristsStats wrist_ench4;
      temp4.set_enchantment(wrist_ench4);
      temp_result.push_back(temp4);
      Gear temp5 = in->at(i);
      Brawn wrist_ench5;
      temp5.set_enchantment(wrist_ench5);
      temp_result.push_back(temp5);
    }
    else if (in->at(i).get_slot() == Slot::Hands)
    {
      Gear temp = in->at(i);
      HeavyKnothideArmorKitHands hands_ench1;
      temp.set_enchantment(hands_ench1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      HandsSuperiorAgility hands_enchantment2;
      temp2.set_enchantment(hands_enchantment2);
      temp_result.push_back(temp2);
      if (character_class == CharacterClass::Paladin)
      {
        Gear temp3 = in->at(i);
        HandsMajorSpellpower hands_enchantment3;
        temp3.set_enchantment(hands_enchantment3);
        temp_result.push_back(temp3);
      }
      Gear temp4 = in->at(i);
      GloveReinforcements hands_enchantment4;
      temp4.set_enchantment(hands_enchantment4);
      temp_result.push_back(temp4);
      Gear temp5 = in->at(i);
      VindicatorsArmorKitHands hands_enchantment5;
      temp5.set_enchantment(hands_enchantment5);
      temp_result.push_back(temp5);
      Gear temp6 = in->at(i);
      HandsMajorStrength hands_enchantment6;
      temp6.set_enchantment(hands_enchantment6);
      temp_result.push_back(temp6);
      // if (magic_dps.find(MagicSchool::Frost) != magic_dps.end()) //(character->get_encounter()->get_name() == "Hydros")
      // {
      Gear temp7 = in->at(i);
      HandsFrostArmorKit hands_ench7;
      temp7.set_enchantment(hands_ench7);
      temp_result.push_back(temp7);
      // }
      // if (magic_dps.find(MagicSchool::Fire) != magic_dps.end()) //(character->get_encounter()->get_name() == "Prince Malchezaar")
      // {
      Gear temp9 = in->at(i);
      GlovesFlameArmorKit hands_ench9;
      temp9.set_enchantment(hands_ench9);
      temp_result.push_back(temp9);
      // }
      // if (magic_dps.find(MagicSchool::Shadow) != magic_dps.end())
      // {
      Gear temp10 = in->at(i);
      GlovesShadowArmorKit hands_ench10;
      temp10.set_enchantment(hands_ench10);
      temp_result.push_back(temp10);
      // }

      Gear temp8 = in->at(i);
      GlovesThreat hands_enchantment8;
      temp8.set_enchantment(hands_enchantment8);
      temp_result.push_back(temp8);
    }
    else if (in->at(i).get_slot() == Slot::Legs)
    {
      Gear temp1 = in->at(i);
      RuggedArmorKitLegs leg_enchantment1;
      temp1.set_enchantment(leg_enchantment1);
      temp_result.push_back(temp1);
      if (character_class == CharacterClass::Paladin)
      {
        Gear temp2 = in->at(i);
        RunicSpellthread leg_enchantment2;
        temp2.set_enchantment(leg_enchantment2);
        temp_result.push_back(temp2);
      }
      Gear temp3 = in->at(i);
      NethercleftLegArmor leg_enchantment3;
      temp3.set_enchantment(leg_enchantment3);
      temp_result.push_back(temp3);
      // if (magic_dps.find(MagicSchool::Frost) != magic_dps.end()) //(character->get_encounter()->get_name() == "Hydros")
      // {
      Gear temp4 = in->at(i);
      LegsFrostArmorKit leg_enchantment4;
      temp4.set_enchantment(leg_enchantment4);
      temp_result.push_back(temp4);
      // }
    }
    else if (in->at(i).get_slot() == Slot::Boots)
    {
      Gear temp = in->at(i);
      BootsFortitude feet_ench1;
      temp.set_enchantment(feet_ench1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      RuggedArmorKitFeet feet_ench2;
      temp2.set_enchantment(feet_ench2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      BootsDexterity feet_ench3;
      temp3.set_enchantment(feet_ench3);
      temp_result.push_back(temp3);
      // if (magic_dps.find(MagicSchool::Frost) != magic_dps.end()) //(character->get_encounter()->get_name() == "Hydros")
      // {
      Gear temp4 = in->at(i);
      FeetFrostArmorKit feet_ench4;
      temp4.set_enchantment(feet_ench4);
      temp_result.push_back(temp4);
      // }
      // if (magic_dps.find(MagicSchool::Fire) != magic_dps.end()) //(character->get_encounter()->get_name() == "Prince Malchezaar")
      // {
      Gear temp5 = in->at(i);
      FeetFlameArmorKit feet_ench5;
      temp5.set_enchantment(feet_ench5);
      temp_result.push_back(temp5);
      // }
      // if (magic_dps.find(MagicSchool::Shadow) != magic_dps.end())
      // {
      Gear temp6 = in->at(i);
      FeetShadowArmorKit feet_ench6;
      temp6.set_enchantment(feet_ench6);
      temp_result.push_back(temp6);
      // }
    }
    else if (in->at(i).get_slot() == Slot::Mainhand)
    {
      Gear temp = in->at(i);
      WeaponMajorSpellpower mainhand_enchantment1;
      temp.set_enchantment(mainhand_enchantment1);
      temp_result.push_back(temp);
    }
    else if (in->at(i).get_slot() == Slot::Offhand)
    {
      Gear temp = in->at(i);
      ShieldBlock shieldEnchantment1;
      temp.set_enchantment(shieldEnchantment1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      MajorStamina shieldEnchantment2;
      temp2.set_enchantment(shieldEnchantment2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      ToughShield shieldEnchantment3;
      temp3.set_enchantment(shieldEnchantment3);
      temp_result.push_back(temp3);
      Gear temp4 = in->at(i);
      ShieldResistance shieldEnchantment4;
      temp4.set_enchantment(shieldEnchantment4);
      temp_result.push_back(temp4);
    }
    else if (in->at(i).get_slot() == Slot::Ring1 || in->at(i).get_slot() == Slot::Ring2 || in->at(i).get_slot() == Slot::Ring)
    {
      Gear temp = in->at(i);
      RingSpellpower ringEnchantment1;
      temp.set_enchantment(ringEnchantment1);
      temp_result.push_back(temp);
      Gear temp2 = in->at(i);
      RingStats ringEnchantment2;
      temp2.set_enchantment(ringEnchantment2);
      temp_result.push_back(temp2);
      Gear temp3 = in->at(i);
      RingStriking ringEnchantment3;
      temp3.set_enchantment(ringEnchantment3);
      temp_result.push_back(temp3);
    }
    else if (in->at(i).get_slot() == Slot::Twohand)
    {
      Gear temp1 = in->at(i);
      TwoHandSavagery twohand_enchantment1;
      temp1.set_enchantment(twohand_enchantment1);
      temp_result.push_back(temp1);
      Gear temp2 = in->at(i);
      TwoHandMajorAgility twohand_enchantment2;
      temp2.set_enchantment(twohand_enchantment2);
      temp_result.push_back(temp2);
    }
    std::vector<unsigned int> delete_indices;
    delete_indices.reserve(result.size());
    for (uint j = 0; j < temp_result.size(); j++)
    {
      bool add_item = true;
      tbb::parallel_for(tbb::blocked_range<uint>(0, result.size()), [&](tbb::blocked_range<uint> a)
                        {
                          for (uint k = a.begin(); k < a.end(); k++)
                          {
                            if (result[k] >= temp_result[j])
                            {
                              add_item = false;
                              break;
                            }
                            else if (result[k] <= temp_result[j])
                            {
                              delete_indices.push_back(k);
                            }
                          } });
      delete_indices.shrink_to_fit();
      sort(delete_indices.begin(), delete_indices.end());
      remove(delete_indices);
      for (uint k = delete_indices.size(); k >= 1; k--)
      {
        if (delete_indices[k] != 0)
        {
          result.erase(result.begin() + delete_indices[k]);
        }
        else
        {
          result.erase(result.begin());
        }
      }
      if (add_item)
      {
        result.push_back(temp_result[j]);
      }
    }
  }
  result.shrink_to_fit();
  if (result.size() == 0)
  {
    return (*in);
  }
  return result;
}

Character convergent_gearing(Character *character, std::vector<std::vector<Gear> *> *all_gear, unsigned int cycle = 0, Slot last_slot = Slot::NoSlot)
{
  unsigned int fails_phases = 0;
  std::cout << std::endl;
  std::cout << "Iteration = " << cycle << std::endl;
  double metric = character->metric();
  std::cout << "Starting with metric = " << metric << std::endl;
  double tps = character->get_tps();
  std::cout << "Starting with tps = " << tps << std::endl;
  // std::cout << "Starting with " << character->get_eff_hp() << " effective HP and " <<  << " TPS and " << character->total_damage_taken() << " damage taken." << std::endl;
  if (character->survives_worst_case_szenario(&fails_phases))
  {
    std::cout << "Survives the worst case szenario." << std::endl;
  }
  else
  {
    std::cout << "Cannot survive the worst case szenario." << std::endl;
  }
  if (cycle > 50)
  {
    std::cout << "aborting condition reached" << std::endl;
    std::cout << metric << std::endl;
    character->print_gear();
    character->print_elixirs();
    abort();
  }
  double max_tps = tps;
  unsigned int max_i = 0, max_j = 0;
  bool survives = false;
  std::string my_case = "no case";
  float progress = 0.0;
  int barWidth = 70;
  for (uint i = 0; i < all_gear->size(); i++)
  {
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
      if (i < pos)
        std::cout << "=";
      else if (i == pos)
        std::cout << ">";
      else
        std::cout << " ";
    }
    std::cout << "] " << round(progress * 100.0 * 100.0) / 100.0 << " %\t\r";
    std::cout.flush();

    progress = i / ((double)all_gear->size() - 2.0);
    if (all_gear->at(i)->size() == 0 || (all_gear->at(i)->at(0).get_slot() == last_slot))
    {
      continue;
    }
    tbb::parallel_for(tbb::blocked_range<uint>(0, all_gear->at(i)->size()), [&](tbb::blocked_range<uint> a)
                      {
    for (uint j = a.begin(); j < a.end(); j++)
    {
      std::string ring0Name = character->gear[Slot::Ring1].get_name().substr(0, character->gear[Slot::Ring1].get_name().find("+"));
      std::string ring1Name = character->gear[Slot::Ring2].get_name().substr(0, character->gear[Slot::Ring2].get_name().find("+"));
      std::string all_gear_substr = all_gear->at(i)->at(j).get_name().substr(0, all_gear->at(i)->at(j).get_name().find("+"));
      std::string trinket0Name = character->gear[Slot::Trinket1].get_name().substr(0, character->gear[Slot::Trinket1].get_name().find("+"));
      std::string trinket1Name = character->gear[Slot::Trinket2].get_name().substr(0, character->gear[Slot::Trinket2].get_name().find("+"));
      std::string all_gear_trinket_substr = all_gear->at(i)->at(j).get_name().substr(0, all_gear->at(i)->at(j).get_name().find("+"));
      if (all_gear_substr == ring0Name || all_gear_substr == ring1Name || all_gear_trinket_substr == trinket0Name ||
          all_gear_trinket_substr == trinket1Name || character->gear[(*all_gear->at(i))[j].get_slot()].get_name() == (*all_gear->at(i))[j].get_name())
      {
        continue;
      }
      if ((character->get_source() < (*all_gear->at(i))[j].get_src()) || character->is_excluded(&all_gear->at(i)->at(j)))
      {
        continue;
      }
      Character temp(*character);
      if ((*all_gear->at(i))[j].get_sockets() > 0)
      {
        if ((*all_gear->at(i))[j].gems.size() < (*all_gear->at(i))[j].get_sockets())
        {
          Gear temp_gear = (*all_gear->at(i))[j];
          temp.equip(temp_gear);
        }
      }
      else
      {
        temp.equip((*all_gear->at(i))[j]);
      }
      temp.compute_stats();
      double temp_metric = temp.metric();
      double temp_tps = temp.get_tps();
      unsigned int temp_fails_phases = 0;
      bool case1 = (!temp.survives_worst_case_szenario(&temp_fails_phases) && !character->survives_worst_case_szenario(&fails_phases) && !survives);
      bool case2 = (temp.survives_worst_case_szenario(&temp_fails_phases) && !character->survives_worst_case_szenario(&fails_phases));
      bool case3 = (temp.survives_worst_case_szenario(&temp_fails_phases) && character->survives_worst_case_szenario(&fails_phases));
      bool case4 = (temp_fails_phases < fails_phases);
      // bool caseA=(temp_damage_taken < min_dmg_taken);
      bool caseA = (temp_metric < metric);
      // bool caseB=(temp_damage_taken == min_dmg_taken);
      bool caseB = (temp_metric == metric);
      // bool caseC=(temp_damage_taken == min_dmg_taken && temp_tps > max_tps);
      bool caseC = (temp_metric == metric && temp_tps > max_tps);
      bool save = false;
      
      if ((case1 || case4) && (caseA || caseC))
      {
        save = true;
      }
      else if (case2)
      {
        if (survives)
        {
          if (caseA || caseB || caseC)
          {
            save = true;
          }
        }
        else
        {
          save = true;
          survives = true;
        }
      }
      else if (case3)
      {
        if (caseA || caseB || caseC)
        {
          save = true;
        }
      }
      if (save)
      {
        max_i = i;
        max_j = j;
        max_tps = temp_tps;
        metric = temp_metric;
      }
    } });
  }
  Character *result = character;
  if (metric == character->metric() && max_tps == character->get_tps())
  {
    (*character) = char_with_best_consumables(character);
    // std::cout << std::endl;
    // std::cout << "converged after " << cycle << " iterations." << std::endl;
    // std::cout << "Approximated time of encounter = " << character->get_time_of_encounter() << " seconds" << std::endl;
    // std::cout << "HP = " << character->get_hp() << std::endl;
    // std::cout << "Armor = " << character->get_armor() << std::endl;
    // character->print_all_stats();
    // std::cout << "Damage reduction from armor against level " << character->get_encounter()->get_lvl() << " = " << character->get_armor_reduction() * 100.0 << "%" << std::endl;
    // std::cout << "Defense = " << character->get_defense() << std::endl;
    // std::cout << "Dodge against level " << character->get_encounter()->get_lvl() << " = " << character->get_dodge_chance() << "%" << std::endl;
    // if (character->get_class() != CharacterClass::Druid)
    // {
    //   std::cout << "Parry against level " << character->get_encounter()->get_lvl() << " = " << character->get_parry() << "%" << std::endl;
    //   std::cout << "Effective block chance against level " << character->get_encounter()->get_lvl() << " = " << character->get_block() << "%" << std::endl;
    //   std::cout << "Block value = " << character->get_block_value() << std::endl;
    // }
    // std::cout << "Chance to get missed against level " << character->get_encounter()->get_lvl() << " = " << character->get_missed() << "%" << std::endl;
    // std::cout << "Total avoidance against level " << character->get_encounter()->get_lvl() << " = " << character->get_avoidance() << "%" << std::endl;
    // std::cout << "Reduced chance to get critical hits = " << character->red_chance_to_get_crit() * 100 << "%" << std::endl;
    // std::cout << "Hit chance = " << character->get_hit_chance() << std::endl;
    // std::cout << "TPS = " << character->get_tps() << std::endl;
    // std::cout << "Frost resistance = " << character->get_tot_prim_stat(PrimaryAttributes::FrostResistance) << std::endl;
    // std::cout << "Nature resistance = " << character->get_tot_prim_stat(PrimaryAttributes::NatureResistance) << std::endl;
    // unsigned int temp_n;
    // std::cout << "Survives worst case szenario against " << character->get_encounter()->get_name() << ": " << character->survives_worst_case_szenario(&temp_n) << std::endl;
    // std::cout << "Metric = " << metric << std::endl;
    // std::cout << "Gear:" << std::endl;
    // character->print_gear();
    // character->print_elixirs();
    // character->print_buffs();
    return (*character);
  }
  else
  {
    // if ((*all_gear->at(max_i))[max_j].get_sockets() > 0)
    // {
    //   if ((*all_gear->at(max_i))[max_j].gems.size() < (*all_gear->at(max_i))[max_j].get_sockets())
    //   {
    //     Gear temp_gear = (*all_gear->at(max_i))[max_j];
    //     temp->equip(temp_gear);
    //   }
    // }
    // else
    // {
    result->equip((*all_gear->at(max_i))[max_j]);
    // }
    result->compute_stats();
    // std::cout << "case = " << my_case << std::endl;
    (*result) = convergent_gearing(result, all_gear, cycle + 1, all_gear->at(max_i)->at(max_j).get_slot());
  }
  return (*result);
}

// void gear(std::vector<std::vector<Gear> *> *all_gear, std::vector<Character> *characters, std::vector<unsigned int> *all_gear_indices, unsigned int index)
// {
//   if (index < all_gear->size() - 1)
//   {
//     if (all_gear->at(index)->size() > 0)
//     {
//       for (uint i = 0; i < all_gear->at(index)->size(); i++)
//       {
//         if (index > 0)
//         {
//           if (all_gear->at(index)->at(i).name == all_gear->at(index - 1)->at(i).name)
//           {
//             if (i == all_gear->at(index)->size() - 1)
//             {
//               (*all_gear_indices)[index] = i;
//             }
//             else
//             {
//               (*all_gear_indices)[index] = i + 1;
//             }
//           }
//           else
//           {
//             (*all_gear_indices)[index] = i;
//           }
//         }
//         else
//         {
//           (*all_gear_indices)[index] = i;
//         }
//         gear(all_gear, characters, all_gear_indices, index + 1);
//       }
//     }
//     else
//     {
//       gear(all_gear, characters, all_gear_indices, index + 1);
//     }
//   }
//   else
//   {
//     Character temp(CharacterClass::Paladin, Race::Draenei);
//     temp.set_talent("Redoubt", 5);
//     temp.set_talent("Toughness", 5);
//     temp.set_talent("Precision", 3);
//     temp.set_talent("Improved Righteous Fury", 3);
//     temp.set_talent("Shield Specialization", 3);
//     temp.set_talent("Anticipation", 5);
//     temp.set_talent("Spell Warding", 2);
//     temp.set_talent("Sacred Duty", 2);
//     temp.set_talent("One-Handed Weapon Specialization", 5);
//     temp.set_talent("Ardent Defender", 5);
//     temp.set_talent("Combat Expertise", 5);
//     temp.set_talent("Blessing of Sanctuary", 1);
//     temp.set_talent("Holy Shield", 1);
//     temp.set_talent("Improved Holy Shield", 2);
//     temp.set_talent("Improved Judgement", 2);
//     temp.set_talent("Deflection", 5);
//     for (uint i = 0; i < all_gear->size() - 1; i++)
//     {
//       if ((*all_gear->at(i))[all_gear_indices->at(i)].name == (*all_gear->at(i + 1))[all_gear_indices->at(i + 1)].name)
//       {
//         return;
//       }
//     }
//     for (uint i = 0; i < all_gear->size(); i++)
//     {
//       temp.equip((*all_gear->at(i))[all_gear_indices->at(i)]);
//     }
//     temp.compute_stats();
//     // if (temp.red_chance_to_get_crit() >= 5.6) {
//     characters->push_back(temp);
//     //}
//   }
// }

std::vector<Gear> sort_out_gear(std::vector<Gear> *in, uint phase = 5)
{
  std::vector<Gear> out;
  out.reserve(in->size());
  for (uint i = 0; i < in->size(); i++)
  {
    if (in->at(i).get_phase() > phase)
    {
      continue;
    }
    bool add_item = true;
    if (!in->at(i).is_set_piece())
    {
      tbb::parallel_for(tbb::blocked_range<uint>(i + 1, in->size()), [&](tbb::blocked_range<uint> a)
                        {
                        
                          for (uint j = a.begin(); j < a.end(); j++)
                        {
                          if (in->at(i) <= in->at(j))
                          {
                            add_item = false;
                            break;
                          }
                        } });
    }
    if (add_item)
    {
      out.push_back(in->at(i));
    }
  }
  out.shrink_to_fit();
  return out;
}

void filter_gems(std::vector<Socket> *in)
{
  for (uint i = 0; i < in->size() - 1; i++)
  {
    for (uint j = i + 1; j < in->size(); j++)
    {
      if (in->at(i).get_prim_stats() <= in->at(j).get_prim_stats() && in->at(i).get_sec_stats() <= in->at(j).get_sec_stats())
      {
        if (i == 0)
        {
          in->erase(in->begin());
        }
        else
        {
          in->erase(in->begin() + i);
        }
        i--;
        break;
      }
    }
  }
  in->shrink_to_fit();
}

std::vector<Gear> add_gems(std::vector<Gear> *in, CharacterClass character_class)
{
  std::vector<Gear> out;
  std::vector<Socket> gems = {GleamingDawnstone(), RigidDawnstone(), MysticDawnstone(), DelicateLivingRuby(), SubtleLivingRuby(), ThickDawnstone(), SolidStarOfElune(), StalwartFireOpal(),
                              GlisteringFireOpal(), RegalTanzanite(), EnduringChrysoprase(),
                              ShiftingTanzanite(), SteadyChrysoprase(), BeamingFireOpal(),
                              // DelicateCrimsonSpinel(), SolidEmpyreanSapphire(), SubtleCrimsonSpinel(), ThickLionseye(),
                              EnduringTalasit(), ShiftingNightseye(), RegalNightseye()};
  std::vector<Socket> meta_gems = {TenaciousEarthstormDiamond(), PowerfulEarthstormDiamond()};
  if ((uint)character_class != (uint)CharacterClass::Druid)
  {
    std::vector<Socket> temp = {FlashingLivingRuby(), GlimmeringFireOpal(), SplendidFireOpal(), DefendersTanzanite()};
    gems.insert(gems.end(), temp.begin(), temp.end());
  }
  else
  {
    gems.push_back(PristineFireOpal());
  }
  if ((uint)character_class == (uint)CharacterClass::Paladin)
  {
    std::vector<Socket> temp = {GreatDawnstone(), RunedLivingRuby(), VeiledNobleTopaz(), GlowingTanzanite(), GlowingNightseye(), VividChrysoprase()};
    gems.insert(gems.end(), temp.begin(), temp.end());
    EternalEarthstormDiamond meta3;
    meta_gems.push_back(meta3);
  }
  else
  {
    std::vector<Socket> temp = {GlintingNobleTopaz(), NimbleFireOpal()};
    gems.insert(gems.end(), temp.begin(), temp.end());
  }
  if ((uint)character_class != (uint)CharacterClass::Druid && (uint)character_class != (uint)CharacterClass::Paladin && (uint)character_class != (uint)CharacterClass::Rogue && (uint)character_class != (uint)CharacterClass::Warrior && (uint)character_class != (uint)CharacterClass::Hunter)
  {
    QuickDawnstone rare_spell_haste_gem;
    gems.push_back(rare_spell_haste_gem);
  }
  gems.shrink_to_fit();
  filter_gems(&gems);
  std::vector<Socket> *pointer_to_gems;
  for (uint i = 0; i < in->size(); i++)
  {
    std::vector<Gear> finished_gear;
    if (in->at(i).get_sockets() == 0 || in->at(i).gems.size() == in->at(i).get_sockets())
    {
      finished_gear.push_back(in->at(i));
      finished_gear.shrink_to_fit();
    }
    else
    {
      if (in->at(i).has_free_meta_place())
      {
        pointer_to_gems = &meta_gems;
      }
      else
      {
        pointer_to_gems = &gems;
      }
      for (uint j = 0; j < pointer_to_gems->size(); j++)
      {
        Gear temp_gear = in->at(i);
        temp_gear.add_gem(pointer_to_gems->at(j));
        std::vector<Gear> temp_vec = {temp_gear};
        std::vector<Gear> temp_vec2 = add_gems(&temp_vec, character_class);
        finished_gear.insert(finished_gear.end(), temp_vec2.begin(), temp_vec2.end());
      }
    }
    for (uint j = 0; j < finished_gear.size(); j++)
    {
      bool add = true;
      std::vector<unsigned int> delete_indices;
      delete_indices.reserve(out.size());
      if (!finished_gear[j].is_set_piece())
      {
        tbb::parallel_for(tbb::blocked_range<uint>(0, out.size()), [&](tbb::blocked_range<uint> a)
                          {
                          for (uint k = a.begin(); k < a.end(); k++)
                          {
                            if (out[k].is_set_piece()){continue;}
                            if (out[k] >= finished_gear[j])
                            {
                              add = false;
                              break;
                            }
                            else if (out[k] <= finished_gear[j])
                            {
                              delete_indices.push_back(k);
                            }
                          } });
      }
      delete_indices.shrink_to_fit();
      sort(delete_indices.begin(), delete_indices.end());
      remove(delete_indices);
      for (uint k = delete_indices.size(); k >= 1; k--)
      {
        if (delete_indices[k - 1] != 0)
        {
          out.erase(out.begin() + delete_indices[k - 1]);
        }
        else
        {
          out.erase(out.begin());
        }
      }
      if (add)
      {
        out.push_back(finished_gear[j]);
      }
    }
  }
  out.shrink_to_fit();
  if (out.size() == 0)
  {
    return *in;
  }
  return out;
}

std::vector<Gear *> filter_set_pieces(std::vector<Gear> *in)
{
  std::vector<Gear *> result;
  result.reserve(in->size());
  tbb::parallel_for(tbb::blocked_range<uint>(0, in->size()), [&](tbb::blocked_range<uint> a)
                    {
    for (uint i = a.begin(); i < a.end(); i++)
    {
      if (in->at(i).is_set_piece())
      {
        result.push_back(&in->at(i));
      }
    } });
  result.shrink_to_fit();
  return result;
}

void equip_random_set_pieces(Character *playerChar, std::vector<std::vector<Gear> *> *all_gear)
{
  std::map<Slot, std::vector<Gear *>> set_pieces;
  for (uint i = 0; i < all_gear->size(); i++)
  {
    for (uint j = 0; j < all_gear->at(i)->size(); j++)
    {
      if (all_gear->at(i)->at(j).is_set_piece())
      {
        if (set_pieces.find(all_gear->at(i)->at(j).get_slot()) != set_pieces.end())
        {
          set_pieces[all_gear->at(i)->at(j).get_slot()].push_back(&all_gear->at(i)->at(j));
        }
        else
        {
          std::vector<Gear *> temp = {&all_gear->at(i)->at(j)};
          set_pieces.insert(std::pair<Slot, std::vector<Gear *>>(all_gear->at(i)->at(j).get_slot(), temp));
        }
      }
    }
  }
  srand(time(NULL));
  for (std::map<Slot, std::vector<Gear *>>::iterator it = set_pieces.begin(); it != set_pieces.end(); it++)
  {
    uint random_index = rand() % it->second.size();
    playerChar->equip((*it->second[random_index]));
  }
}

#endif
