#include <cstdio>

int matrix[2000][2000];

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        x -= 1;
        y -= 1;
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < b; ++k) {
                sum += matrix[x + j][y + k];
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}