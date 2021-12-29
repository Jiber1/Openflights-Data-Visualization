#include "../include/airport.h"

Airport::Airport() {
    //empty constructor
};

Airport::Airport(std::string _name, int _ID, std::string _IATA, std::string _ICAO, float _latitude, float _longitude, float _altitude) {
    name = _name;
    ID = _ID;
    IATA = _IATA;
    ICAO = _ICAO;
    latitude = _latitude;
    longitude = _longitude;
    altitude = _altitude;
}

std::string Airport::getName() const {
    return name;
}

int Airport::getID() const {
    return ID;
}

std::string Airport::getIATA() const {
    return IATA;
}

std::string Airport::getICAO() const {
    return ICAO;
}

float Airport::getLatitude() const {
    return latitude;
}

float Airport::getLongitude() const {
    return longitude;
}

float Airport::getAltitude() const {
    return altitude;
}