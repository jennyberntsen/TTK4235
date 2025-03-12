#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "queue.h"

//Creating an instance of Queue
Queue q = {
    .queue = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

NewOrder newOrder;

//Adds new order to the queue
void addToQueue(NewOrder o){
    lights_on(o);
    q.queue[o.floor][o.button] = 1;
}

//Removes order from the queue
void removeOrder(){
    lastFloorFunc();
    for(int f = 0; f < N_FLOORS; f++){
        if (f == lastFloor){
            for(int b = 0; b < N_BUTTONS; b++){
                q.queue[f][b] = 0;
                lights_off(f, b);
            }
        }
    }
}

//The deletes the entire queue
void deleteQueue(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            q.queue[f][b] = 0;
            lights_off(f, b);
        }
    }
}

void orderExecute(){
    removeOrder();
    doorOpen();
}

//LIGHTS

void lights_on(NewOrder o){
    int floor = o.floor;
    ButtonType button = o.button;
    elevio_buttonLamp(floor, button, 1);
}

void lights_off(int floor, ButtonType button){
    elevio_buttonLamp(floor, button, 0);
}


void floorLight(){
    int floor = elevio_floorSensor();
    if(floor >=0 && floor < N_FLOORS){
        elevio_floorIndicator(floor);
    }
}