#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "queue.h"

Queue q = {
    .queue = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

void addToQueue(NewOrder o){
    lights_on(o);
    q.queue[o.floor][o.button] = 1;
}

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

void deleteQueue(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            q.queue[f][b] = 0;
            lights_off(f, b);
        }
    }
}