#include "../include/utilities.h"

#include <math.h>
#include <utility>
#include <cmath>

#define PI 3.14159265358979323846 
#define radiusEarthkilometers 6371
//http://edwilliams.org/avform147.htm
//https://www.movable-type.co.uk/scripts/latlong.html


double distance(std::pair<double, double> airport1_coords, std::pair<double, double> airport2_coords) {

    double airport_latitude_1_Radians = airport1_coords.first * PI/180;
    double airport_latitude_2_Radians = airport2_coords.first * PI/180;
    double latitude_difference_Radians = (airport2_coords.first - airport1_coords.first) * PI/180;
    double longitude_difference_Radians = (airport2_coords.second - airport1_coords.second) * PI/180;

    double alpha = pow(sin(latitude_difference_Radians/2), 2) + 
        cos(airport_latitude_1_Radians) * cos(airport_latitude_2_Radians) * 
        pow(sin(longitude_difference_Radians/2), 2);
    double kappa = 2 * atan2(sqrt(alpha), sqrt(1 - alpha)); //arctan on all quadrants
    return radiusEarthkilometers * kappa;
}

