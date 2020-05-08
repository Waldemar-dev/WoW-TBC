#include "gems.hh"

Socket::Socket(string color_) {
  if (color_ == "green") {
    color.push_back("blue");
    color.push_back("yellow");
  } else if (color_ == "purple") {
    color.push_back("blue");
    color.push_back("red");
  } else if (color_ == "orange") {
    color.push_back("red");
    color.push_back("yellow");
  } else {
    color.push_back(color_);
  }
}

void Socket::operator=(Socket b) {
  color = b.color;
  primary_stats = b.primary_stats;
  secondary_stats = b.secondary_stats;
  name = b.name;
  active = b.active;
}

bool Socket::is_active(vector<Socket> gems) {
  if (name == "Tenacious Earthstorm Diamond") {
    unsigned int blue = 0;
    for (uint i = 0; i < gems.size(); i++) {
      for (uint j = 0; j < gems[i].color.size(); j++) {
        if (gems[i].color[j] == "blue") {
          blue++;
          if (blue >= 5 && !active) {
            secondary_stats.defense_rating = 12;
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 5) {
      active = false;
    }
  } else if (name == "Powerful Earthstorm Diamond") {
    unsigned int blue = 0;
    for (uint i = 0; i < gems.size(); i++) {
      for (uint j = 0; j < gems[i].color.size(); j++) {
        if (gems[i].color[j] == "blue") {
          blue++;
          if (blue >= 3 && !active) {
            primary_stats.stamina += 18;
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 3) {
      active = false;
    }
  } else if (name == "Eternal Earthstorm Diamond") {
    unsigned int blue = 0;
    unsigned int yellow = 0;
    for (uint i = 0; i < gems.size(); i++) {
      for (uint j = 0; j < gems[i].color.size(); j++) {
        if (gems[i].color[j] == "blue") {
          blue++;
          if (blue >= 2 && yellow >= 1 && !active) {
            secondary_stats.defense_rating += 12;
            active = true;
            return active;
          }
        } else if (gems[i].color[j] == "yellow") {
          yellow++;
          if (blue >= 2 && yellow >= 1 && !active) {
            secondary_stats.defense_rating += 12;
            active = true;
            return active;
          }
        }
      }
    }
    if (blue < 2 || yellow < 1) {
      active = false;
    }
  }
  return active;
}

DelicateLivingRuby::DelicateLivingRuby() {
  primary_stats.agility = 8;
  name = "Delicate Living Ruby";
  color.push_back("red");
}

RunedLivingRuby::RunedLivingRuby() {
  secondary_stats.spellpower = 9;
  secondary_stats.healing = 9;
  name = "Runed Living Ruby";
  color.push_back("red");
}

BoldLivingRuby::BoldLivingRuby() {
  primary_stats.strength = 8;
  name = "Bold Living Ruby";
  color.push_back("red");
}

SubtleLivingRuby::SubtleLivingRuby() {
  secondary_stats.dodge_rating = 8;
  name = "Subtle Living Ruby";
  color.push_back("red");
}

ThickDawnstone::ThickDawnstone() {
  secondary_stats.defense_rating = 8;
  name = "Thick Dawnstone";
  color.push_back("yellow");
}

SolidStarOfElune::SolidStarOfElune() {
  primary_stats.stamina = 12;
  name = "Solid Star of Elune";
  color.push_back("blue");
}

StalwartFireOpal::StalwartFireOpal() {
  secondary_stats.dodge_rating = 4;
  secondary_stats.defense_rating = 5;
  name = "Stalwart Fire Opal";
  color.push_back("red");
  color.push_back("yellow");
}

EnduringTalasit::EnduringTalasit() {
  primary_stats.stamina = 6;
  secondary_stats.defense_rating = 4;
  name = "Enduring Talasit";
  color.push_back("blue");
  color.push_back("yellow");
}

SovereignNightseye::SovereignNightseye() {
  primary_stats.strength = 4;
  primary_stats.stamina = 6;
  name = "Sovereign Nightseye";
  color.push_back("blue");
  color.push_back("red");
}

ShiftingNightseye::ShiftingNightseye() {
  primary_stats.stamina = 6;
  primary_stats.agility = 4;
  name = "Shifting Nightseye";
  color.push_back("blue");
  color.push_back("red");
}

RegalNightseye::RegalNightseye() {
  primary_stats.stamina = 6;
  secondary_stats.dodge_rating = 4;
  name = "Regal Nightseye";
  color.push_back("blue");
  color.push_back("red");
}

GlisteringFireOpal::GlisteringFireOpal() {
  primary_stats.agility = 4;
  secondary_stats.defense_rating = 5;
  name = "Glistering Fire Opal";
  color.push_back("red");
  color.push_back("yellow");
}

ChampionsFireOpal::ChampionsFireOpal() {
  primary_stats.strength = 5;
  secondary_stats.defense_rating = 4;
  name = "Champions Fire Opal";
  color.push_back("red");
  color.push_back("yellow");
}

RigidDawnstone::RigidDawnstone() {
  secondary_stats.spellhit_rating = 8;
  name = "Rigid Dawnstone";
  color.push_back("yellow");
}

FlashingLivingRuby::FlashingLivingRuby() {
  name = "Flashing Living Ruby";
  secondary_stats.parry_rating = 8;
  color.push_back("red");
}

GlowingNightseye::GlowingNightseye() {
  name = "Glowing Nightseye";
  primary_stats.stamina = 6;
  secondary_stats.spellpower = 5;
  color.push_back("blue");
  color.push_back("red");
}

TenaciousEarthstormDiamond::TenaciousEarthstormDiamond() {
  name = "Tenacious Earthstorm Diamond";
  color.push_back("meta");
}

PowerfulEarthstormDiamond::PowerfulEarthstormDiamond() {
  name = "Powerful Earthstorm Diamond";
  color.push_back("meta");
}

EternalEarthstormDiamond::EternalEarthstormDiamond() {
  name = "Eternal Earthstorm Diamond";
  color.push_back("meta");
}

EffulgentChrysoprase::EffulgentChrysoprase() {
  name = "Effulgent Chrysoprase";
  secondary_stats.defense_rating = 5;
  secondary_stats.mp5 = 2;
  color.push_back("yellow");
  color.push_back("blue");
}

ThickLionseye::ThickLionseye() {
  name = "Thick Lionseye";
  secondary_stats.defense_rating = 10;
  color.push_back("yellow");
}

SubtleCrimsonSpinel::SubtleCrimsonSpinel() {
  name = "Subtle Crimson Spinel";
  secondary_stats.dodge_rating = 10;
  color.push_back("red");
}

SolidEmpyreanSapphire::SolidEmpyreanSapphire() {
  name = "Solid Empyrean Sapphire";
  primary_stats.stamina = 15;
  color.push_back("blue");
}

GlimmeringFireOpal::GlimmeringFireOpal() {
  name = "Glimmering Fire Opal";
  secondary_stats.parry_rating = 5;
  secondary_stats.defense_rating = 4;
  color.push_back("red");
  color.push_back("yellow");
}

RegalTanzanite::RegalTanzanite() {
  name = "Regal Tanzanite";
  secondary_stats.dodge_rating = 5;
  primary_stats.stamina = 6;
  color.push_back("red");
  color.push_back("blue");
}

EnduringChrysoprase::EnduringChrysoprase() {
  name = "Enduring Chrysoprase";
  primary_stats.stamina = 6;
  secondary_stats.defense_rating = 5;
  color.push_back("yellow");
  color.push_back("blue");
}

GlowingTanzanite::GlowingTanzanite() {
  name = "Glowing Tanzanite";
  primary_stats.stamina = 6;
  secondary_stats.spellpower = 6;
  color.push_back("red");
  color.push_back("blue");
}

VividChrysoprase::VividChrysoprase() {
  name = "Vivid Chrysoprase";
  secondary_stats.spellhit_rating = 5;
  primary_stats.stamina = 6;
  color.push_back("yellow");
  color.push_back("blue");
}

SplendidFireOpal::SplendidFireOpal() {
  name = "Splendid Fire Opal";
  secondary_stats.parry_rating = 5;
  secondary_stats.resilience_rating = 4;
  color.push_back("red");
  color.push_back("yellow");
}

ShiftingTanzanite::ShiftingTanzanite() {
  name = "Shifting Tanzanite";
  primary_stats.agility = 5;
  primary_stats.stamina = 6;
  color.push_back("red");
  color.push_back("blue");
}

SteadyChrysoprase::SteadyChrysoprase() {
  name = "Steady Chrysoprase";
  primary_stats.stamina = 6;
  secondary_stats.resilience_rating = 5;
  color.push_back("yellow");
  color.push_back("blue");
}

BeamingFireOpal::BeamingFireOpal() {
  name = "Beaming Fire Opal";
  secondary_stats.dodge_rating = 5;
  secondary_stats.resilience_rating = 4;
  color.push_back("red");
  color.push_back("yellow");
}

DefendersTanzanite::DefendersTanzanite() {
  name = "Defenders Tanzanite";
  primary_stats.stamina = 6;
  secondary_stats.parry_rating = 5;
  color.push_back("blue");
  color.push_back("red");
}
