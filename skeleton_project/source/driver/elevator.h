#pragma once

#include "elevio.h"
#include "con_load.h"

typedef enum {
    START,
    MOVING,
    WAITING,
    STOP
} elevator_states;

typedef struct {
    int current_floor;
    int next_floor;
    int queue[N_FLOORS][N_BUTTONS];
    elevator_states state;
    MotorDirection direction;
} elevator;

