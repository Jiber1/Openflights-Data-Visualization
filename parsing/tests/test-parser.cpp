#include "catch2/catch.hpp"
#include "../include/parser_header.h"

TEST_CASE("Parsing test_airport.dat") {
    // TODO: Redo testing to reflect new changes.
    SECTION("Size of airports vector is accurate") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();

        std::vector<Airport*> result = reader.GetAirportList();
        REQUIRE(result.size() == 10);
    }

    SECTION("All airport data is parsed") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();

        std::vector<Airport*> result = reader.GetAirportList();

        std::vector<std::string> expectedName = {"Goroka Airport",
                                                "Madang Airport",
                                                "Mount Hagen Kagamuga Airport",
                                                "Nadzab Airport",
                                                "Port Moresby Jacksons International Airport",
                                                "Wewak International Airport",
                                                "Narsarsuaq Airport",
                                                "Godthaab / Nuuk Airport",
                                                "Kangerlussuaq Airport",
                                                "Thule Air Base"};

        std::vector<std::string> expectedIATA = {"GKA",
                                                 "MAG",
                                                 "HGU",
                                                 "LAE",
                                                 "POM",
                                                 "WWK",
                                                 "UAK",
                                                 "GOH",
                                                 "SFJ",
                                                 "THU"};

        std::vector<std::string> expectedICAO = {"AYGA",
                                                 "AYMD",
                                                 "AYMH",
                                                 "AYNZ",
                                                 "AYPY",
                                                 "AYWK",
                                                 "BGBW",
                                                 "BGGH",
                                                 "BGSF",
                                                 "BGTL"};

        std::vector<float> expectedLat = {-6.081689834590001,
                                          -5.20707988739,
                                          -5.826789855957031,
                                          -6.569803,
                                          -9.443380355834961,
                                          -3.58383011818,
                                          61.1604995728,
                                          64.19090271,
                                          67.0122218992,
                                          76.5311965942};
   
        std::vector<float> expectedLong = {145.391998291,
                                          145.789001465,
                                          144.29600524902344,
                                          146.725977,
                                          147.22000122070312,
                                          143.669006348,
                                          -45.4259986877,
                                          -51.6781005859,
                                          -50.7116031647,
                                          -68.7032012939};
                                    
        std::vector<float> expectedAlt = {5282,
                                          20,
                                          5388,
                                          239,
                                          146,
                                          19,
                                          112,
                                          283,
                                          165,
                                          251};
        

        REQUIRE(result.size() == expectedName.size());
        for (size_t i = 0; i < result.size(); i++) {
            //std::cout << result[i]->getName() << ", " << result[i]->getID() << ", " << result[i]->getIATA() << ", " << result[i]->getICAO() << ", " << result[i]->getLatitude() << ", " << result[i]->getLongitude() << ", " << result[i]->getAltitude() << std::endl;
            REQUIRE(result[i]->getName() == expectedName[i]);
            REQUIRE(result[i]->getID() == i + 1); // ID begins at 1
            REQUIRE(result[i]->getIATA() == expectedIATA[i]);
            REQUIRE(result[i]->getICAO() == expectedICAO[i]);
            REQUIRE(result[i]->getLatitude() == expectedLat[i]);
            REQUIRE(result[i]->getLongitude() == expectedLong[i]);
            REQUIRE(result[i]->getAltitude() == expectedAlt[i]);
        }
        
    }
}

TEST_CASE("Parsing airport.dat") {
    // TODO: Redo testing to reflect new changes.
    SECTION("All airports are parsed corrected") {
        CSVReader reader("../data/airports.dat", "tests/test_data/test_route.dat");
        reader.parse();

        std::vector<Airport*> result = reader.GetAirportList();
        REQUIRE(result.size() == 7698);
    }
}

TEST_CASE("Parsing route.dat") {
    // TODO: Redo testing to reflect new changes.
    SECTION("All routes are parsed corrected") {

        CSVReader reader("../data/airports.dat", "../data/routes.dat");
        reader.parse();

        std::vector<Route*> result = reader.GetRoutes();
        REQUIRE(result.size() == 67221);
        REQUIRE(result[0]->getSource() == 2965);
    }
}