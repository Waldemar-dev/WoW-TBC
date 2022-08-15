#include <mysql/mysql.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
// #include "enchantments.hh"
#include "equipment.hh"
// #include "gems.hh"
#include "support_functions.hh"

using namespace std;

bool check_gear_vec(double size_before, std::vector<Gear> *in)
{
    if (size_before > in->size())
    {
        for (uint i = 0; i < in->size(); i++)
        {
            cout << in->at(i).get_name() << endl;
        }
        return false;
    }
    return true;
}

int main()
{
    CharacterClass char_class = CharacterClass::Druid;
    vector<Gear> heads = {CircletOfRestlessDreams(), GladiatorsDragonhideHelm(), DeathblowX11Goggles(), HelmOfTheClaw(), WastewalkerHelm(), CobrascaleHood(), HelmOfAssassination(), StealthersHelmetOfSecondSight(), StealthersHelmetOfSecondSight(), ExorcistsLeatherHelm(), StylinPurpleHat(), EnergizedHelm(), MaskOfTheDeceiver(), CowlOfBeastlyRage()}; // Druid
    vector<Gear> necks = {NecklaceOfTheJuggernaut(), MaladaarsBlessedChaplet(), MarkOfTheRavenguard(), EnchantedThoriumTorque(), StrengthOfTheUntamed(), NecklaceOfTheDeep(), PendantOfTriumph(), BoneChainNecklace(), ChokerOfVileIntent(), MaimfistsChoker(), InsigniaOfTheMaghariHero(), BroochOfDeftness()};
    vector<Gear> shoulders = {SwiftstrikeShoulders(), SpauldersOfTheRing(), GladiatorsDragonhideSpaulders(), ShoulderpadsOfAssassination(), WastewalkerShoulderpads(), MantleOfPerenolde(), MantleOfShadowyEmbrace(), MantleOfTheUnforgiven(), TalbukHideSpaulders()};                                                     // Druid
    vector<Gear> backs = {CloakOfEternity(), ThoriumweaveCloak(), SlikksCloakOfPlacation(), PerfectlyBalancedCape(), NomadsWovenCloak(), DelicateGreenPoncho(), SergeantsHeavyCloak(), BloodKnightWarCloak(), AuchenaiDeathShroud(), VengeanceWrap()};                                                                     // Druid
    vector<Gear> chests = {CarapaceOfSunAndShadow(), EmbraceOfEverlastingProwess(), HeavyClefthoofVest(), GladiatorsDragonhideTunic(), WastewalkerTunic(), PrimalstrikeVest(), TunicOfAssassination(), IllidariLordsTunic(), VestOfVengeance(), ChestguardOfTheProwler(), AuchenaiMonksTunic(), VestmentsOfHibernation()}; // Druid
    vector<Gear> bracers = {SwiftstrikeBracers(), UmberhowlsCollar(), VindicatorsLeatherBracers(), ShardboundBracers(), NightfallWristguards(), ShacklesOfQuagmirran(), VindicatorsDragonhideBracers(), MasterAssassinWristwraps(), BandOfTheSwiftPaw()};                                                                  // Druid
    vector<Gear> hands = {GladiatorsDragonhideGloves(), FleshHandlersGauntlets(), GlovesOfImmortalDusk(), AgedCoreLeatherGloves(), HandwrapsOfTheAggressor(), SmugglersMitts(), WastewalkerGloves(), GlovesOfTheUnbound(), VerdantGloves(), CobrascaleGloves(), HandgripsOfAssassination(), FelLeatherGloves(), GlovesOfTheNetherStalker(), PredatoryGloves(), TrickstersStickyfingers()};
    vector<Gear> belts = {ManimalsCinch(), VindicatorsLeatherBelt(), DunewindSash(), PrimalstrikeBelt(), GirdleOfTheDeathdealer(), EpochsWhisperingCinch(), SocretharsGirdle(), NaaruBeltOfPrecision(), TreeMendersBelt(), EvasStrap(), VindicatorsDragonhideBelt(), WaistguardOfTheGreatBeast()};
    vector<Gear> legs = {ShattrathLeggings(), TamelessBreeches(), LeggingsOfTheBetrayed(), WarpscaleLeggings(), HeavyClefthoofLeggings(), LeggingsOfTheUnrepentant(), WastewalkerLeggings(), MidnightLegguards(), GladiatorsDragonhideLegguards(), LeggingsOfAssassination(), FelLeatherLeggings(), ForestwalkerKilt(), OilclothBreeches(), ClefthoofHideLeggings(), ShallowgraveTrousers()};                                                                                                 // Druid
    vector<Gear> boots = {VindicatorsLeatherBoots(), SunrageTreads(), HeavyClefthoofBoots(), VindicatorsDragonhideBoots(), ShadowstepStriders(), BootsOfTheUnjust(), TheMastersTreads(), FelboarHideShoes(), FelLeatherBoots(), FarahliteStuddedBoots(), NynjahsTabiBoots(), FootwrapsOfWildEncroachment()};                                                                                                                                                                                                             // Druid
    vector<Gear> rings = {LieutenantsSignetOfLordaeron(), RingOfTheStalwartProtector(), ShapeshiftersSignet(), LongstridersLoop(), RavenclawBand(), BandOfTriumph(), RingOfArathiWarlords(), WindTradersBand(), OgreSlayersBand(), RingOfTheStonebark(), DelicateEterniumRing(), ElementiumBandOfTheSentry(), YorsRevenge(), RingOfUnyieldingForce(), BandOfImpenetrableDefenses(), IronBandOfTheUnbreakable(), BandOfUrsol(), TheFrozenEye(), AdalsSignetOfDefense(), ShermanarGreatRing()}; // Druid
    vector<Gear> twohands = {StaffOfBeasts(), GladiatorsMaul(), Earthwarden(), FeralStaffOfLashing(), StaffOfNaturalFury()};                                                                                                                                                                                                                                                                                                                                                                  // Druid
    vector<Gear> trinkets = {ShardOfContempt(), AdamantineFigurine(), DarkmoonCardVengeance(), CharmOfAlacrity(), TerokkarTabletOfPrecision(), RegalProtectorate(), BroochOfTheImmortalKing(), TalismanOfTheHorde(), MoroesLuckyPocketWatch(), IconOfUnyieldingCourage(), BloodlustBrooch(), BadgeOfTenacity(), AlchemistsStone(), DrakeFangTalisman(), AbacusOfViolentOdds(), MarkOfTyranny(), TimelapseShard()};                                                                            // Druid
    vector<Gear> mainhands = {
        ContinuumBlade(),
        GreatswordOfHorridDreams(),
        ManaWrath(),
        CrystalforgedSword(),
        GavelOfUnearthedSecrets(),
        MercilessGladiatorsGavel(),
    };                                                                                                                                                                                                                                                                                  // Paladin
    vector<Gear> offhands = {AegisOfTheSunbird(), CrestOfTheShatar(), PlatinumShieldOfTheValorous(), NetherwingDefendersShield(), OgrilaAegis(), ShieldOfTheWaywardFootman(), AzureShieldOfColdarra(), GladiatorsShieldWall(), ShieldOfImpenetrableDarkness(), AldoriLegacyDefender()}; // Paladin
    vector<Gear> range_slot;
    vector<vector<Gear> *> all_gear = {&heads, &necks, &shoulders, &backs, &chests, &bracers, &hands, &belts, &legs, &boots, &rings, &trinkets, &range_slot};
    if (char_class != CharacterClass::Druid)
    {
        all_gear.push_back(&offhands);
        all_gear.push_back(&mainhands);
    }
    else
    {
        vector<Gear> idols = {IdolOfTheRavenGoddess(), IdolOfUrsoc(), IdolOfBrutality(), IdolOfTheWild()};
        range_slot = idols;
        all_gear.push_back(&twohands);
    }

    // if (char_class == CharacterClass::Paladin)
    // {
    //     vector<Gear> librams = {LibramOfTruth(), LibramOfSaintsDeparted(), LibramOfRepentance(), LibramOfDivinePurpose(), LibramOfTheEternalRest()};
    //     range_slot = librams;
    // }
    for (uint i = 0; i < all_gear.size(); i++)
    {
        uint size_before = all_gear[i]->size();
        cout << i << "/" << all_gear.size() - 1 << ") size before:" << size_before << endl;
        (*all_gear[i]) = sort_out_gear(all_gear[i], 1);
        (*all_gear[i]) = enchant_gear(all_gear[i], char_class);
        (*all_gear[i]) = add_gems(all_gear[i], char_class);
        cout << i << "/" << all_gear.size() - 1 << ") size after:" << all_gear[i]->size() << endl;
        cout << endl;
    }
    vector<string> firstRow = heads[0].get_names();
    stringstream command;
    command << "CREATE TABLE TEMPphase1PreRaidDruid(";
    stringstream varTypes;
    varTypes << "(";
    stringstream varNames;
    varNames << "(";
    stringstream questionMarks;
    questionMarks << "(";
    vector<string> delimiter = {"INT", "DOUBLE", "TEXT"};
    for (uint i = 0; i < firstRow.size() - 1; i++)
    {
        questionMarks << "?,";
        command << firstRow[i] << ", ";
        for (uint j = 0; j < delimiter.size(); j++)
        {
            if (firstRow[i].substr(0, firstRow[i].find(delimiter[j])) != firstRow[i])
            {
                varTypes << delimiter[j] << ", ";
                varNames << firstRow[i].substr(0, firstRow[i].find(delimiter[j]) - 1) << ", ";
            }
        }
    }
    command << firstRow.back() << ")";
    questionMarks << "?)";
    for (uint j = 0; j < delimiter.size(); j++)
    {
        if (firstRow.back().substr(0, firstRow.back().find(delimiter[j])) != firstRow.back())
        {
            varTypes << delimiter[j] << ")";
            varNames << firstRow.back().substr(0, firstRow.back().find(delimiter[j]) - 1) << ")";
        }
    }

    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = "tcp://127.0.0.1:3306";
        connection_properties["userName"] = "wow";
        connection_properties["password"] = "$herlock_H0lmes#";
        connection_properties["OPT_RECONNECT"] = true;
        connection_properties["OPT_CONNECT_TIMEOUT"] = 2147483647;
        sql::Statement *stmt;
        // sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(connection_properties);
        /* Connect to the MySQL database */
        con->setSchema("tbcGear");
        stmt = con->createStatement();
        stmt->execute(command.str().c_str());
        delete stmt;
        uint start_point = 0;
        for (uint i = 0; i < all_gear.size(); i++)
        {
            cout << "Writing all_gear[" << i << "]" << endl;
            for (uint j = start_point; j < std::min((uint)all_gear[i]->size(), start_point + 35000); j++)
            {
                command.str("");
                command << "INSERT INTO TEMPphase1PreRaidDruid" << varNames.str() << " VALUES " + all_gear[i]->at(j).get_values();
                if (!con->isValid())
                {
                    cout << __LINE__ << endl;
                    con->reconnect();
                    con->setSchema("tbcGear");
                }
                pstmt = con->prepareStatement(command.str().c_str());
                pstmt->execute();
            }
        }
        command.str("");
        command << "show tables";
        pstmt = con->prepareStatement(command.str().c_str());
        pstmt->execute();
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return 0;
}