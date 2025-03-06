#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "door.h"

void doorOpen(){
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    for(int i = 0; i < 150; i++){
        if(elevio_stopButton()){
            stop();
        }
        if(elevio_obstruction()){
            if(checkIfButtonPressed() == 1){
                addToQueue(newOrder);
            }
            obstruction();
            doorOpen();
        } 
        if(checkIfButtonPressed()){
            addToQueue(newOrder);
        }  
        nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    }
}



void obstruction(){
    while(elevio_obstruction()){
        if(checkIfButtonPressed() == 1){
            addToQueue(newOrder);
        }
        if(elevio_stopButton()){
            stop();
        }

    }
}