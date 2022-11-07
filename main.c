#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

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
    int start_vertex;
    int end_vertex;
    int n_vertices;
    int n_edges;
    int i;

    // Create Graph ------------------------------------------

    file_pointer = fopen("./input.dat", "r");
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
    fscanf(file_pointer, "%d %d\n", &start_vertex, &end_vertex);
    start_vertex--;
    end_vertex--;

    fclose(file_pointer);

    // Calculate shortest path ------------------------------------------

    return 0;
}