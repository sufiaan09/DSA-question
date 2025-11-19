#include <stdio.h>

#define INF 9999
#define MAX 20

int main() {
    int n, cost[MAX][MAX];
    int visited[MAX] = {0};
    int i, j, ne = 0;
    int min, a, b, total = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INF;  // replace 0 with INF
        }

    visited[0] = 1;  // start from vertex 0

    printf("\nEdges in Minimum Spanning Tree (Prim's):\n");

    while (ne < n - 1) {
        min = INF;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        visited[b] = 1;
        printf("Edge %d: (%d - %d)  Cost = %d\n", ne + 1, a, b, min);
        total += min;
        ne++;
    }

    printf("\nMinimum Cost = %d\n", total);
    return 0;
}
