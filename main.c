#include <stdio.h>
#include <stdbool.h>
// #include "graph.h"

typedef struct Node_type
{
    int id;
    bool was_visited;
    int tentative_distance;
    int *neighbor_nodes;
} Node;

int main()
{
    // read a file with inputs
    FILE *file_pointer;
    int n_nodes;
    int n_edges;
    int i;

    file_pointer = fopen("./input.dat", "r");
    fscanf(file_pointer, "%d %d\n", &n_nodes, &n_edges);

    for (i = 0; i < n_edges; i++) {
        // get edges
    }
    printf("%d %d", n_nodes, n_edges);
    fclose(file_pointer);
    return 0;
}