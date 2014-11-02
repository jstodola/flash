#include "common.h"
#include <math.h>

double log2(double x) {
    return log(x)/log(2);
}

double shutter_index_to_seconds(int8_t speed_index, const uint16_t *shutter_speeds) {
    uint16_t speed;
    speed = shutter_speeds[abs(speed_index)];
    if(speed_index >= 0) {
        return speed / 10.0 ;
    } else {
        return 10.0 / speed;
    }
}
