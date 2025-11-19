#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 9999

void dijkstra(int graph[MAX][MAX], int n, int start) {
    int dist[MAX], visited[MAX];
    
    // Initialize distances
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[start] = 0;   // Distance of start node is 0

    // Dijkstra's main logic
    for (int i = 0; i < n - 1; i++) {
        int min = INF, u;

        // Pick the unvisited vertex with minimum distance
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = 1;

        // Update distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print result
    printf("\nShortest distances from source %d:\n", start);
    for (int i = 0; i < n; i++) {
        printf("To %d = %d\n", i, dist[i]);
    }
}

int main() {
    int graph[MAX][MAX], n, start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    dijkstra(graph, n, start);

    return 0;
}
