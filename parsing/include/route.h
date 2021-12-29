#pragma once

#include <string>

class Route {
    public:
        Route();
        Route(std::string _Airline, std::string _Airline_ID, std::string _Source_airport, float _Source_airport_ID, std::string _Destination_airport, float _Destination_airport_ID, float _stops);
        std::string getAirline() const;
        int getSource() const;
        int getDestination() const;
        double getStops() const;
    private:
        std::string Airline;
        std::string Airline_ID;
        std::string Source_airport;
        float Source_airport_ID;
        std::string Destination_airport;
        float Destination_airport_ID;
        float Stops;
};