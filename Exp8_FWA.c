#include <stdio.h>
#define INF 99999
#define V 5

// Function to print the solution matrix
void printSolution(int dist[V][V]) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Floyd-Warshall Algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize the solution matrix same as the input graph matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Update the solution matrix
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distances
    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 4, 2, INF, INF},
        {INF, 0, INF, INF, 6},
        {1, INF, 0, 3, INF},
        {INF, INF, INF, 0, 2},
        {INF, INF, INF, INF, 0},
    };

    floydWarshall(graph);
    return 0;
}

