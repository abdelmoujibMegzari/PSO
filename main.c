#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "swarm.h"
#include "malloc.h"
#include "graph.h"

float randomGoalFunctionJustForTest(int* position);
float goalFunction(int* position);
//TODO read more about binary PSO
//TODO look more on how to apply the sailsman PSO solution to our situation

graph * graph2;
int main() {
    //Problem Constants
    int seed=1256854;
    float w=0.5f;
    float c1=0.2f;
    float c2=0.2f;
    // initializing the swarms
    srand(seed);

    //graph2=generateRandomGraph(numberOfNodes,numberOfEdges);
    graph2 = generateGraphFromFile("graphDataSet/ErdosRenyi_n250.txt");
    printf("pairwize connectivity in the begining: %d\n", pairwiseConnectivity(graph2));
    swarm ** swarms = malloc(sizeof(swarm*)*numberOfSwarms);
    for(int i=0;i<numberOfSwarms;i++){
        swarms[i] = malloc((sizeof(swarm)));
        swarms[i]->position= malloc(K*sizeof(int));
        for(int j=0; j<K; j++){
            swarms[i]->position[j] = rand()%numberOfNodes;
        }
        swarms[i]->cognitiveValue=-FLT_MAX;
        swarms[i]->cognitivePosition= calloc(K,sizeof(int));
        swarms[i]->inertia= calloc(K, sizeof(double ));
        for(int j=0; j<K; j++){
            swarms[i]->inertia[j] = rand()%10;
        }
    }

    //problem Social Variables
    float socialValue = -FLT_MAX;
    int* socialPosition = calloc(K, sizeof(int));

    //starting optimisation
    for(int iteration=0; iteration<maxNumberOfIterations;iteration++) {
        printf("%d:%f\n",iteration,socialValue);
        //printf("%d:%f\n%f:(",iteration,socialValue, goalFunction(swarms[0]->position));
        //for(int i=0;i<K;i++) {
        //    printf("%d,", swarms[0]->position[i]);
        //}
        //printf(")\n");
        for (int i=0; i < numberOfSwarms; i++) {
            updateCognitive(swarms[i], goalFunction);
        }
        updateSocial(swarms, socialPosition, &socialValue);
        for (int i = 0; i < numberOfSwarms; i++) {
            updateInertia(swarms[i], w, c1, c2, 1.0f/(rand()%10+1), 1.0f/(rand()%10+1), socialPosition);
            updatePosition(swarms[i]);
        }
    }
    printf("the best value for the function is: %f : %d", socialValue,socialPosition[1]);



}

float randomGoalFunctionJustForTest(int* position){
    float s =0;
    for(int i=0; i<K;i++){
        s+= pow(-1,i)*position[i];
    }
    return s;
}

float goalFunction(int* position){
    graph *newGraph = deleteVerteces(graph2,K,position);
    return -pairwiseConnectivity(newGraph);
}

