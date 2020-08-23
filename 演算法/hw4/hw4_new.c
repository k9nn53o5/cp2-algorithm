#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int m, n;

bool check(int pass[m][n], int r, int c, bool visit[m][n]){
    return (r >= 0) && (r < m) && (c >= 0) && (c < n) && (pass[r][c] && !visit[r][c]);
}

int DFS(int x, int y, int pass[m][n], bool v[m][n], int count){
    v[x][y] = true;
    int row[4] = {-1, 0, 0, 1};
    int col[4] = {0, -1, 1, 0};
    for (int a = 0; a < 4; a++){
        if (check(pass, x+row[a], y+col[a], v)){
            count++;
            count = DFS(x + row[a], y + col[a], pass, v, count);
        }
    }
    return count;
}

int main(void){
    int count=0, ans=0;
    scanf("%d %d", &m, &n);
    int graph[m][n];
    bool visited[m][n];
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &graph[i][j]);
            visited[i][j] = 0;
        }
    }
    for (int c = 0; c < m; c++){
        for (int d = 0; d < n; d++){
            if(graph[c][d]==0){
                count = DFS(c, d, graph, visited, 0);
            }
            if(count > ans){
                ans = count;
            }
        }
    }
    printf("%d", ans);
    return 0;
}