#pragma once

#include "elevio.h"
#include "con_load.h"
#include "queue.h"

typedef enum {
    START,
    MOVING,
    WAITING,
    STOP
} Elevator_states;


//extern int floor;

extern int lastFloor;

//Creating an instance of the Elevator_states enum
extern Elevator_states s;


void start();

void stop();

void lastFloorFunc();


