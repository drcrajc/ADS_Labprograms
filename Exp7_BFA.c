#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford algorithm
void BellmanFord(int V, int E, struct Edge edges[], int src) {
    int distance[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        distance[i] = INF;
    distance[src] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INF && distance[u] + weight < distance[v])
                distance[v] = distance[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    // Print the distance array
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, distance[i]);
}

int main() {
    int V = 5; // Number of vertices
    int E = 5; // Number of edges

    struct Edge edges[] = {
        {0, 1, 5},
        {1, 3, 2},
        {4, 3, -1},
        {2, 4, 1},
        {1, 2, 1},
    };

    int src = 0; // Source vertex
    BellmanFord(V, E, edges, src);

    return 0;
}
