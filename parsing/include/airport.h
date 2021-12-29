#pragma once

#include <string>

class Airport {
    public:
        Airport();
        Airport(std::string _name, int _ID, std::string _IATA, std::string _ICAO, 
        float _latitude, float _longitude, float _altitude);
        std::string getName() const;
        int getID() const;
        std::string getIATA() const;
        std::string getICAO() const;
        float getLatitude() const;
        float getLongitude() const;
        float getAltitude() const;

    private:
        std::string name;
        int ID;
        std::string IATA;
        std::string ICAO;
        float latitude;
        float longitude;
        float altitude;
};