#include "extras.h"
#include <utility>
#include <math.h>

//https://stackoverflow.com/questions/4953150/convert-lat-longs-to-x-y-co-ordinates
/**
 * Transforms the given position (latitude, longitude) to map to the Mercator projection of the provided width and height.
 * @param position The position as a pair of floats, (latitude, longitude)
 * @param width The width of the Mercator projection map PNG in pixels
 * @param height The height of the Mercator projection map PNG in pixels
 */
std::pair<int,int> airportgrapher(std::pair<float,float> position, int width, int height) {
    const float PI = 3.14159265359;

    float x = floor(std::fmod((width * (180 + position.second) / 360), (width + (width / 2))));

    float latRad = position.first * PI / 180;
    float mercN = log(tan((PI / 4) + (latRad / 2)));
    float y = (height / 2) - (width * mercN / (2 * PI));
    
    return std::pair<int,int>(x, y);
}