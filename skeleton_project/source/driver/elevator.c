#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevator.h"
#include "elevio.h"


Elevator_states s = START; //Initializing the elevator state
int lastFloor;

//Initializing the elevator to start at a legal floor. 
//Setting the lamps to zero
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


//Stop-function 
//If the stop button is pressed, the elevator must stop immediately
void stop(){
    if(elevio_stopButton() == 1 && elevio_floorSensor() != -1){ //Stop butten is pressed while at a floor
        elevio_motorDirection(DIRN_STOP);
        deleteQueue();
        elevio_stopLamp(1);
        while(elevio_stopButton() == 1){
            elevio_doorOpenLamp(1);
            elevio_motorDirection(DIRN_STOP);
            deleteQueue();
        }
        elevio_stopLamp(0);
        elevio_doorOpenLamp(1);
        doorOpen();

    }else if(elevio_stopButton()){ //Stop button is pressed and inbetween floors
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

//Updates the lastFloor variable to the most reasent visited floor
void lastFloorFunc(){
    if(elevio_floorSensor() != -1){
        lastFloor = elevio_floorSensor();
    }
}


//Checks if a button is pressed.
//If so, this is a new order.
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
                    stop();
                    floorLight();

                    if(f < lastFloor){ //Checking if there is a placed order on the way down
                        elevio_motorDirection(DIRN_DOWN);

                        for(int i = initFloor - 1; i > f; i--){
                            if((q.queue[i][1] == 1 || q.queue[i][2] == 1) && lastFloor == i){
                                orderExecute();
                            }
                        }
                    }
                    else if(f > lastFloor){ //Checking if there is a placed order on the way up
                        elevio_motorDirection(DIRN_UP);

                        for(int i = initFloor + 1; i < f; i++){
                            if((q.queue[i][0] == 1 || q.queue[i][2] == 1) && lastFloor == i){
                                orderExecute();
                            }
                        }
                    }
                }
                orderExecute();
                break;      
            } 
        }
    }
}