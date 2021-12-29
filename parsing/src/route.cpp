#include "../include/route.h"

#include <string>

Route::Route() {

}

Route::Route(std::string _Airline, std::string _Airline_ID, std::string _Source_airport, float _Source_airport_ID, std::string _Destination_airport, float _Destination_airport_ID, float _Stops) {
    Airline = _Airline;
    Airline_ID = _Airline_ID;
    Source_airport = _Source_airport;
    Source_airport_ID = _Source_airport_ID;
    Destination_airport = _Destination_airport;
    Destination_airport_ID = _Destination_airport_ID;
    Stops = _Stops;
}

std::string Route::getAirline() const {
    return Airline;
}
int Route::getSource() const {
    return Source_airport_ID;
}

int Route::getDestination() const {
    return Destination_airport_ID;
}

double Route::getStops() const {
    return Stops;
}