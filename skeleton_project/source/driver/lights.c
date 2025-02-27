#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "lights.h"


void lights_on(NewOrder o){
    int floor = o.floor;
    ButtonType button = o.button;
    elevio_buttonLamp(floor, button, 1);
}

void lights_off(int floor, ButtonType button){
    elevio_buttonLamp(floor, button, 0);
}

void floorLight(){ }