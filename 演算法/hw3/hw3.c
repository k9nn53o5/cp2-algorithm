#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>

struct keroro{
    int x, y;
};

bool connect(struct keroro a, struct keroro b){
    if((a.x<=b.x)&&(a.y>b.x))return true;        
    if((a.x>=b.x)&&(b.y>a.x))return true;
    return false;
}

int check(int N, int pass[][N], int head, int count){
    if(head == N-1){
        return count;
    }
    for (int i = N-1; i > 0; i--){
        if(pass[head][i]==1){
            int temp[N][N];
            for (int c = 0; c < N; c++){
                for (int d = 0; d < N; d++){
                    temp[c][d] = pass[c][d];
                }
            }
            temp[head][i]--;
            temp[i][head]--;
            printf("pass[%d][%d]==1, count=%d\n", head, i, count+1);
            count = check(N, temp, i, count+1);
            return count;
        }
    }
    return count;
}

int main(void){
    int N, ANS=INT_MAX, total=0;
    scanf("%d", &N);

    /////make 2d array and clean it/////
    int graph[N][N], temp[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            graph[i][j] = 0;
        }
    }

    struct keroro wood[N];

    /////make graph/////
    for (int i = 0; i < N; i++){
        scanf("%d %d", &wood[i].x, &wood[i].y);
        if(i>0){
            for (int j = i; j > 0; j--){
                for (int k = j - 1; k >= 0; k--){
                    if (connect(wood[k], wood[j])){
                        graph[k][j] = 1;
                        graph[j][k] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++){
        if(graph[0][i] == 1){
            for (int c = 0; c < N; c++){
                for (int d = 0; d < N; d++){
                    temp[c][d] = graph[c][d];
                }
            }
            temp[0][i]--;
            temp[i][0]--;
            total = check(N, temp, i, 1);
            printf("total[%d] = %d\n", i, total);
            if(total < ANS){
                ANS = total;
            }
        }
    }
    if(ANS == INT_MAX){
        printf("1");
    }else{
        printf("%d", ANS);
    }
    return 0;
}