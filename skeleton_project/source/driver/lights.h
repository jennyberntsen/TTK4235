#pragma once

#include "elevator.h"
#include "queue.h"
#include "elevio.h"


void lights_on(NewOrder o);

void lights_off(int floor, ButtonType button);

void floorLight();
