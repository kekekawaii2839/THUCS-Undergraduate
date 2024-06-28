#include <cstdio>

int matrix[2000][2000];
int matrixsum[2001][2001];

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            matrixsum[i][j] = matrixsum[i][j - 1] + matrixsum[i - 1][j] - matrixsum[i - 1][j - 1] + matrix[i - 1][j - 1];
        }
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        x -= 1; //输入为1~n，而数组下标为0~n-1
        y -= 1;
        printf("%d\n", matrixsum[x + a][y + b] - matrixsum[x + a][y] - matrixsum[x][y + b] + matrixsum[x][y]);
    }
    return 0;
}