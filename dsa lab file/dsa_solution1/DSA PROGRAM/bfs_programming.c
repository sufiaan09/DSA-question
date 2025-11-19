#include <stdio.h>

int main() {
    int n, adj[20][20], visited[20] = {0};
    int queue[20], front = 0, rear = -1;
    int start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    visited[start] = 1;
    queue[++rear] = start;

    printf("BFS Traversal: ");

    while (front <= rear) {
        int node = queue[front++];
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }

    return 0;
}
