#include <stdio.h>
#define INF 99999
#define N 5

void floydWarshall(int graph[N][N]) {
    int dist[N][N], i, j, k;

    // Initialize distance matrix
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            dist[i][j] = graph[i][j];

    // Floyd's algorithm
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the distance matrix
    printf("Shortest distances between pairs of cities:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int graph[N][N] = {
        {0, 4, INF, INF, INF},
        {4, 0, 8, INF, INF},
        {INF, 8, 0, 2, INF},
        {INF, INF, 2, 0, 6},
        {INF, INF, INF, 6, 0}
    };

    floydWarshall(graph);

    return 0;
}
