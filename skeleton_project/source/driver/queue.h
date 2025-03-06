#pragma once

#include "elevator.h"
#include "elevio.h"
#include "con_load.h"


//Queue system that will be used to store orders
typedef struct {
    int queue[N_FLOORS][N_BUTTONS];
} Queue;

typedef struct {
    int floor;
    ButtonType button;
} NewOrder;

//Creating an instance of the Queue struct
extern Queue q;

//Creating an instance of the NewOrder struct
extern NewOrder newOrder;


void addToQueue(NewOrder o);

void removeOrder();

void deleteQueue();

void orderExecute();


//LIGHTS
void lights_on(NewOrder o);

void lights_off(int floor, ButtonType button);

void floorLight();






