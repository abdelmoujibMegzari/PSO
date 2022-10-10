//
// Created by heisenberg on 08/10/22.
//

#ifndef PSO2_GRAPH_H
#define PSO2_GRAPH_H

typedef struct graph_t{
    int size;
    int **matrix;
} graph;

graph *createGraph(int size);

void addEdge(graph* graph1,int vertex1, int vertex2);

graph* deleteVerteces(graph *graph1,int numberOfVertecies,int *vertecies);

int pairwiseConnectivity(graph *graph1);

graph *generateRandomGraph(int size, int numberOfEdge);

graph* generateGraphFromFile(char *fileName);
#endif //PSO2_GRAPH_H
