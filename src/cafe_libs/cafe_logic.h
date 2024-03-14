#ifndef CAFE_LOGIC_H
#define CAFE_LOGIC_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/errors.h"

#define BUFFER 100
#define MAX_ORDER_LEN 256
#define MAX_RECORDS 100

typedef enum { KITCHEN, BAR } Queue_type_t;

typedef struct {
    char order[MAX_ORDER_LEN];
    int cost;
} Order_t;

typedef struct {
    int current_order_index;
    int last_order_index;
    Order_t orders[MAX_RECORDS];
} Orders_queue_t;

typedef struct {
    int kitchen_orders_amount;
    int kitchen_income;
    int bar_orders_amount;
    int bar_income;
} Cafe_stats_t;

ErrorCode is_valid_command(char *command);
void init_queue(Orders_queue_t *queue);
ErrorCode main_menu_loop(Orders_queue_t *kitchen_queue, Orders_queue_t *bar_queue, Cafe_stats_t *cafe_stats);
ErrorCode get_command(char *command);
void print_stats(Cafe_stats_t *cafe_stats);
ErrorCode get_order(Orders_queue_t *queue);
ErrorCode add_order(Orders_queue_t *queue, char *order, int cost);
ErrorCode process_order(Orders_queue_t *queue, Queue_type_t type, Cafe_stats_t *cafe_stats);
#endif