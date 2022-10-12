//
// Created by heisenberg on 04/10/22.
//
#include <stdlib.h>
#include "swarm.h"
#include <math.h>
#include <stdio.h>

void updateInertia(swarm *swarm1,float w, float c1, float c2, float r1, float r2, int *socialPosition ){
    //TODO if r1 r2 are random just pick them here
    for(int i=0;i<K;i++) {
        swarm1->inertia[i] =
                w * swarm1->inertia[i] //Inertia
                +c1*r1*(swarm1->cognitivePosition[i]-swarm1->position[i]) //Cognitive Component
                +c2*r2*(socialPosition[i]-swarm1->position[i]);//Social COmponent

    }
}
//TODO limit the values
void updatePosition(swarm *swarm1){
    for(int i=0;i<K;i++) {
        swarm1->position[i]=round(swarm1->position[i]+swarm1->inertia[i])<numberOfNodes?round(swarm1->position[i]+swarm1->inertia[i]):numberOfNodes-1 ;//limiting the max value
        swarm1->position[i]=swarm1->position[i]<0?0:swarm1->position[i];
    }
}

void updateCognitive(swarm *swarm1,float (*goalFunction)(int* position)){
    float curentValue = goalFunction(swarm1->position);
    if(swarm1->cognitiveValue< curentValue){
        swarm1->cognitiveValue=curentValue;
        swarm1->cognitivePosition=swarm1->position;
    }
}

void updateSocial(swarm **swarms, int* socialPosition,float* socialValue){
    for(int i=0;i<numberOfSwarms;i++){
        if( *socialValue < swarms[i]->cognitiveValue){
            *socialValue=swarms[i]->cognitiveValue;
            for(int j=0;j<K;j++){
                socialPosition[j]=swarms[i]->position[j];
            }
        }
    }
}
