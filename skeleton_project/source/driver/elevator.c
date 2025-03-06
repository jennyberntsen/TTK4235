#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevator.h"
#include "elevio.h"


Elevator_states s = START;
int lastFloor;

void start(){
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);

}

void stop(){
    if(elevio_stopButton() == 1 && elevio_floorSensor() != -1){
        elevio_motorDirection(DIRN_STOP);
        deleteQueue();
        elevio_stopLamp(1);
        while(elevio_stopButton() == 1){
            elevio_d
            void oorOpenLamp(1);
            elevio_motorDirection(DIRN_STOP);
            deleteQueue();
        }
        elevio_stopLamp(0);
        elevio_doorOpenLamp(1);
        doorOpen();

    }else if(elevio_stopButton()){
        elevio_motorDirection(DIRN_STOP);
        deleteQueue();
        elevio_stopLamp(1);
        
        while(elevio_stopButton() == 1){
            elevio_motorDirection(DIRN_STOP);
            deleteQueue();
        }
        elevio_stopLamp(0);
        if(checkIfButtonPressed()){
            addToQueue(newOrder);

        } else{
            elevio_motorDirection(DIRN_STOP);
        }
    }
}

void lastFloorFunc(){
    if(elevio_floorSensor() != -1){
        lastFloor = elevio_floorSensor();
    }
}


int checkIfButtonPressed(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(elevio_callButton(f, b) == 1){
                newOrder.floor = f;
                newOrder.button = b;
                return 1;
            }
        }   
    }
    return 0;   
}

void elevator(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){

            if(q.queue[f][b] == 1){ //Checks if there is a placed order
                int initFloor = lastFloor;
                while(f != lastFloor){
                    if(checkIfButtonPressed() == 1){
                        addToQueue(newOrder);
                    }
                    lastFloorFunc();

                }
            } 

        }
    }
}