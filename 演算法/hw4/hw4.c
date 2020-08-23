#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int m, n;

int check(int x, int y, int pass[m][n], int count, bool v[m][n], bool dec){
    v[x][y] = true, count++;
    if((x!=0)&&(pass[x-1][y]==dec)&&!v[x-1][y]){
        count = check(x - 1, y, pass, count, v, dec);
    }
    if((x!=m-1)&&(pass[x+1][y]==dec)&&!v[x+1][y]){
        count = check(x + 1, y, pass, count, v, dec);
    }
    if((y!=0)&&(pass[x][y-1]==dec)&&!v[x][y-1]){
        count = check(x, y - 1, pass, count, v, dec);
    }
    if((y!=n-1)&&(pass[x][y+1]==dec)&&!v[x][y+1]){
        count = check(x, y + 1, pass, count, v, dec);
    }
    return count;
}

int main(void){
    int total=0, ans=0;
    scanf("%d %d", &m, &n);
    int graph[m][n];
    bool visited[m][n], dec;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &graph[i][j]);
            visited[i][j] = 0;
        }
    }
    for (int X = 0; X < m; X++){
        for (int Y = 0; Y < n; Y++){
            dec = graph[X][Y];
            total = check(X, Y, graph, 0, visited, dec);
            if (total > ans){
                ans = total;
            }
        }
    }
    printf("%d", ans);
    return 0;
}