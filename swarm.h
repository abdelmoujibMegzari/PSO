//
// Created by heisenberg on 04/10/22.
//

#ifndef PSO2_SWARM_H
#define PSO2_SWARM_H
#define K 25
#define numberOfSwarms 50
#define numberOfNodes 100
#define numberOfEdges 194
#define maxNumberOfIterations 500
typedef struct swarm_t
{
    int* position;
    float cognitiveValue;
    int* cognitivePosition;
    int* inertia;

} swarm;


void updateInertia(swarm *swarm1,float w, float c1, float c2, float r1, float r2, int *socialPosition );

void updatePosition(swarm *swarm1);

void updateCognitive(swarm *swarm1,float (*goalFunction)(int* position));

void updateSocial(swarm **swarms, int* socialPosition,float* socialValue);

#endif //PSO2_SWARM_H
