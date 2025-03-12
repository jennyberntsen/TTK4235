#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator.h"
#include "driver/con_load.h"
#include "driver/queue.h"
#include "driver/door.h"



int main(){

    elevio_init();
    while(1){
        switch (s) //s = state
        {
        case START:
            start();
            floorLight();
            s = WAITING;
            break;

        case MOVING:
            stop();
            elevator();
            s = WAITING;
            break;
        
        case WAITING:
            floorLight();
            stop();
            if(checkIfButtonPressed()){
                addToQueue(newOrder);
                s = MOVING;
            }
            break;
        
        case STOP:
            stop();
            s = WAITING;
            break;
        
        default:
            break;
        }
    }
    return 0;
}
