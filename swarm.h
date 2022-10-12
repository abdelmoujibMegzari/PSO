//
// Created by heisenberg on 04/10/22.
//

//TODO why does the system converge so fast

#ifndef PSO2_SWARM_H
#define PSO2_SWARM_H
#define K 50
#define numberOfSwarms 500
#define numberOfNodes 235
#define numberOfEdges 350
#define maxNumberOfIterations 100
typedef struct swarm_t
{
    int* position;
    float cognitiveValue;
    int* cognitivePosition;
    //TODO make position float and round when calculating goal function
    double* inertia;

} swarm;


void updateInertia(swarm *swarm1,float w, float c1, float c2, float r1, float r2, int *socialPosition );

void updatePosition(swarm *swarm1);

void updateCognitive(swarm *swarm1,float (*goalFunction)(int* position));

void updateSocial(swarm **swarms, int* socialPosition,float* socialValue);

#endif //PSO2_SWARM_H
