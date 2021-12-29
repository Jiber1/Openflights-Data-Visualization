#pragma once

#include <math.h>
#include <utility> 

/**
* This function computes the distance between two airports given their latitude and longitude
*/
double distance(std::pair<double, double> airport1_coords, std::pair<double, double> airport2_coords);
