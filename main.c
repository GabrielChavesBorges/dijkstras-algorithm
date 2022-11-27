#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define GRAPH_FILE_PATH "./graphs/a.dat"

struct edge
{
    int vertex;
    int weight;
};

struct vertex
{
    bool was_visited;
    int weight;
    struct edge *edges;
    int n_edges;
    int previous;
};

int main()
{
    struct vertex *vertices;
    FILE *file_pointer;
    int origin_vertex;
    int destination_vertex;
    int n_vertices;
    int n_edges;
    int i;

    // Create Graph -----------------------------------------------------------

    file_pointer = fopen(GRAPH_FILE_PATH, "r");
    fscanf(file_pointer, "%d %d\n", &n_vertices, &n_edges);

    // Initialize vertices
    vertices = malloc(n_vertices * (sizeof(struct vertex)));
    for (i = 0; i < n_vertices; i++)
    {
        vertices[i].was_visited = false;
        vertices[i].weight = INT_MAX;
        vertices[i].n_edges = 0;
        vertices[i].edges = malloc(0);
        vertices[i].previous = -1;
    }

    // Map edges
    for (i = 0; i < n_edges; i++)
    {
        // Read next edge
        int vertex_a, vertex_b, weight;
        fscanf(file_pointer, "%d %d %d\n", &vertex_a, &vertex_b, &weight);
        // offset vertices to use 0 base index.
        vertex_a--;
        vertex_b--;
        // Incorporate edge into map
        // From vertex A to B
        struct vertex *origin = &vertices[vertex_a];
        int lastIndex = origin->n_edges;
        origin->n_edges++;
        origin->edges = realloc(
            origin->edges,
            origin->n_edges * sizeof(struct edge));
        origin->edges[lastIndex].vertex = vertex_b;
        origin->edges[lastIndex].weight = weight;
        // From vertex B to A
        origin = &vertices[vertex_b];
        lastIndex = origin->n_edges;
        origin->n_edges++;
        origin->edges = realloc(
            origin->edges,
            origin->n_edges * sizeof(struct edge));
        origin->edges[lastIndex].vertex = vertex_a;
        origin->edges[lastIndex].weight = weight;
    }

    // Get starting and end vertices
    fscanf(file_pointer, "%d %d\n", &origin_vertex, &destination_vertex);
    origin_vertex--;
    destination_vertex--;
    vertices[origin_vertex].weight = 0;

    fclose(file_pointer);

    // Calculate shortest path ------------------------------------------------

    // initialize next vertex, closest distance variables
    int next_visit = origin_vertex;
    int current_visit = next_visit;
    while (current_visit != destination_vertex)
    {
        int shortest_distance = INT_MAX;
        int n_neighbors = vertices[current_visit].n_edges;
        for (i = 0; i < n_neighbors; i++)
        {
            // Check if neighbor was visited before:
            struct edge *neighbor = &(vertices[current_visit].edges[i]);
            bool was_neighbor_visited = vertices[neighbor->vertex].was_visited;
            if (was_neighbor_visited)
            {
                continue;
            }
            // Check if this edge is closer than current closest:
            int new_distance = vertices[current_visit].weight + neighbor->weight;
            if (new_distance < vertices[neighbor->vertex].weight)
            {
                vertices[neighbor->vertex].weight = new_distance;
                vertices[neighbor->vertex].previous = current_visit;
            }
            // Check if this is the closest neighbor to current vertex:
            if (neighbor->weight < shortest_distance)
            {
                shortest_distance = neighbor->weight;
                next_visit = neighbor->vertex;
            }
        }
        vertices[current_visit].was_visited = true;
        current_visit = next_visit;
        next_visit = -1;
    }
    // retrace steps to get best path
    int best_path_length = 1;
    int *best_path = malloc(best_path_length * sizeof(int));
    best_path[0] = current_visit;
    while (current_visit != origin_vertex)
    {
        current_visit = vertices[current_visit].previous;
        best_path_length++;
        best_path = realloc(best_path, best_path_length * sizeof(int));
        best_path[best_path_length - 1] = current_visit;
    }

    // Free vertices and edges from memory:
    for (i = 0; i < n_vertices; i++)
    {
        free(vertices[i].edges);
    }
    free(vertices);

    // print answer
    printf("Best path:\n");
    for (i = best_path_length; i > 0; i--)
    {
        if (i != 1)
        {
            printf("%d --> ", best_path[i - 1] + 1);
        }
        else
        {
            printf("%d\n", best_path[0] + 1);
        }
    };
    free(best_path);
    return 0;
}