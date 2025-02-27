#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevator.h"
#include "elevio.h"

Elevator_states s;
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
            elevio_doorOpenLamp(1);
            doorOpen();
            //Hvordan implementere at heisen skal ignorere alle forsøk på bestillinger mens stoppknappen er trykket inn?
        }
        elevio_stopLamp(0);
        elevio_doorOpenLamp(1);
        doorOpen();

    }else if(elevio_stopButton() == 1){
        elevio_motorDirection(DIRN_STOP);
        deleteQueue();
        elevio_stopLamp(1);
        while(elevio_stopButton() == 1){
            
            
        }
    }

   
}

void lastFloorFunc(){
    lastFloor = elevio_floorSensor();
    if(lastFloor != -1){
        s = WAITING;
    }
}

