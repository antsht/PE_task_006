#ifndef AIR_TRAFFIC_H
#define AIR_TRAFFIC_H

#include <stdio.h>

#include "common/errors.h"

#define MIN_PLANE_TO_PLANE_DISTANCE 300

typedef struct {
    int lower_bound;
    int upper_bound;
    int planes_count;
} air_traffic_t;

ErrorCode air_traffic_init(air_traffic_t *air_traffic);
void check_air_traffic(air_traffic_t *air_traffic);
#endif