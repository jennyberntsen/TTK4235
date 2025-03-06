#pragma once

typedef enum {
    START,
    MOVING,
    WAITING,
    STOP
} Elevator_states;

#include "elevio.h"
#include "con_load.h"
#include "queue.h"
#include "door.h"



//extern int floor;

extern int lastFloor;

//Creating an instance of the Elevator_states enum
extern Elevator_states s;


void start();

void stop();

void lastFloorFunc();

//Checks if a button is pressed
int checkIfButtonPressed();

void elevator();

