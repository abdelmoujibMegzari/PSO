//
// Created by heisenberg on 08/10/22.
//
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "malloc.h"
#include <string.h>

void trimTrailing(char *string1);

graph *createGraph(int size){
    graph *graph1= malloc(sizeof(graph));
    graph1->size=size;
    graph1->matrix= calloc(size,sizeof(int*));
    for(int i=0;i<size;i++){
        graph1->matrix[i] = calloc(size,sizeof(int));
    }
    return graph1;
}

void addEdge(graph* graph1,int vertex1, int vertex2){
    graph1->matrix[vertex1][vertex2]=1;
    graph1->matrix[vertex2][vertex1]=1;
}

int pairwiseConnectivity(graph *graph1){
    //TODO store the connected components for efficiency when adding back some nodes not sure it 's feasible

    int *marked= calloc(graph1->size,sizeof(int));
    int groupNumber=0;
    int* count= calloc(graph1->size, sizeof(int));
    for(int i=0;i<graph1->size;i++){
        int* newlyMarked= calloc(graph1->size, sizeof(int));
        newlyMarked[i] =!marked[i];
        int justMarked =!marked[i];
        marked[i]=1;
        if(justMarked){
            groupNumber++;
            count[groupNumber]+=1;
        }
        while(justMarked){
            justMarked=0;
            for(int k=0; k<graph1->size;k++) {
                if(newlyMarked[k]) {
                    for (int j = 0; j < graph1->size; j++) {
                        if (graph1->matrix[k][j] == 1) {
                            if (!marked[j]){
                                marked[j]=1;
                                count[groupNumber]++;
                                justMarked=1;
                                newlyMarked[j]=1;
                            }
                        }
                    }
                    newlyMarked[k]=0;
                }
            }

        }
    }
    int pairwizeConnectivity=0;
    for(int i=0;i<graph1->size;i++){
        pairwizeConnectivity+=count[i]*(count[i]-1)/2;
    }
    return pairwizeConnectivity;
}

int  removeDuplicates(int size,int* vertecies){
    /**
     * modifies the table and returns the new size
     * */
    for (int i = 0; i < size; i ++)
    {
        for (int j = i + 1; j < size; j++)
        {
            // use if statement to check duplicate element
            if ( vertecies[i] == vertecies[j])
            {
                // delete the current position of the duplicate element
                for (int k = j; k < size - 1; k++)
                {
                    vertecies[k] = vertecies [k + 1];
                }
                // decrease the size of array after removing duplicate element
                size--;

                // if the position of the elements is changes, don't increase the index j
                j--;
            }
        }
    }
    return size;
}
graph* deleteVerteces(graph *graph1,int numberOfVertecies,int *vertecies){
    //TODO  by given a sorted vertecies and avoiding to loop to check if it's inside
    //TODO other wise use a set maybe switch to c++
    // this optimization is important if the number of vertecies to delete is very big

    //remove doubles
    numberOfVertecies = removeDuplicates(numberOfVertecies,vertecies);
    graph *newGraph= createGraph( graph1->size-numberOfVertecies);
    int l=0;
    for(int i=0;i<graph1->size;i++){
        int skip=0;
        for(int j=0;j<numberOfVertecies;j++){
            if(i==vertecies[j]){
                skip=1;
                break;
            }
        }
        if(!skip){
            int m=0;
            for(int k=0;k<graph1->size;k++){
                int skip2=0;
                for(int j=0;j<numberOfVertecies;j++){
                    if(k==vertecies[j]){
                        skip2=1;
                        break;
                    }
                }
                if(!skip2){
                    newGraph->matrix[l][m]=graph1->matrix[i][k];
                    m++;
                }
            }
            l++;
        }
    }
    return newGraph;
}

graph *generateRandomGraph(int size, int numberOfEdges){
    graph* graph1=createGraph(size);
    int node1=rand()%size;
    int node2=rand()%size;
    for(int i=0;i<numberOfEdges;i++){
        while(node1 == node2 || graph1->matrix[node1][node2]==1){
            node1=rand()%size;
            node2=rand()%size;
        }
        addEdge(graph1,node1,node2);
    }
    return graph1;
}

graph* generateGraphFromFile(char *fileName){
    FILE *f =fopen(fileName,"r");
    if(!f){
        printf("file can't be opened\n");
    }
    char sizeStr[10];
    int size;
    fgets(sizeStr,10,f);
    trimTrailing(sizeStr);
    size = atoi(sizeStr);
    graph *graph1 = createGraph(size);
    //Reading Line By Line
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) {
        char* node1;
        char* node2;
        node1 = strtok(line,":");
        node2 = strtok(NULL, " ");
        while( node2 != NULL ) {
            addEdge(graph1, atoi(node1),atoi(node2));
            node2 = strtok(NULL, " ");
        }
    }
    fclose(f);
    return graph1;
}

void trimTrailing(char *string1) {
    int i =0;
    int index=0;
    while(string1[i] != '\0'){
        if(string1[i] != ' ' && string1[i] != '\t' && string1[i] != '\n')
        {
            index= i;
        }
        i++;
    }
    string1[index + 1] = '\0';
}
