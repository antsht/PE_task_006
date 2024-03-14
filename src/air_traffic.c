#include "air_traffic.h"

int main(void) {
    air_traffic_t air_traffic = {.lower_bound = 0, .upper_bound = 0, .planes_count = 0};
    try(air_traffic_init(&air_traffic));
    check_air_traffic(&air_traffic);
    return 0;
}

ErrorCode air_traffic_init(air_traffic_t *air_traffic) {
    if (scanf("%d %d %d", &air_traffic->lower_bound, &air_traffic->upper_bound, &air_traffic->planes_count) !=
        3)
        return INVALID_INPUT;
    if (air_traffic->lower_bound < 300 || air_traffic->upper_bound > 15000 ||
        air_traffic->upper_bound < air_traffic->lower_bound || air_traffic->planes_count < 1)
        return INVALID_DATA;
    return OK;
}

void check_air_traffic(air_traffic_t *air_traffic) {
    int max_planes = 0;
    max_planes = (air_traffic->upper_bound - air_traffic->lower_bound) / MIN_PLANE_TO_PLANE_DISTANCE + 1;
    if (air_traffic->planes_count <= max_planes)
        printf("SAFELY");
    else
        printf("DANGEROUS\a");
}