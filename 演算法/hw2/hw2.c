#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int *value;

void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void quicksort(int array[], int a, int b){
    if(a < b){
        //let pivot = mid;
        int pivot = (a+b)/2;
        int p = array[pivot];
        swap(&array[a], &array[pivot]);
        int front = a+1;
        int end = b;
        while(front <= end){
            while((front <= b)&&(array[front] <= p)){
                front++;
            }
            while((end >= a)&&(array[end] > p)){
                end--;
            }
            if(front < end){
                swap(&array[front], &array[end]);
            }
        }
        swap(&array[a], &array[end]);
        quicksort(array, a, end-1);
        quicksort(array, end+1, b);
    }
}

void clean(int *array, int size, int value){
    for (int i = 0; i < size; i++){
        array[i] = value;
    }
}

bool ismore(int *arrA, int *arrB, int size){
    for (int i = 0; i < size; i++){
        if(arrA[i] <= arrB[i]){
            return false;
        }
    }
    return true;
}

int calculate(int **mate, int loop, int size, int *pre, int*deny, int z){
    int max=0;
    if(z == loop){
        return 0;
    }
    for (int i = 0; i < loop; i++){
        for (int j = 0; j < z; j++){
            if(deny[j]==i){
                continue;
            }
        }
        if(ismore(mate[i], pre, size)){
            if(value[i] == 0){
                deny[z] = i;
                value[i] = calculate(mate, loop, size, mate[i], deny, z+1);
            }
            if((value[i]+1)>max){
                max = value[i]+1;
            }
        }
    }
    return max;
}

int main(void){
    int M, N;
    scanf("%d %d", &M, &N);

    int *pre_row = (int*)malloc(N * sizeof(int));
    int *deny_row = (int*)malloc(N * sizeof(int));
    value = (int*)malloc(M * sizeof(int));

    clean(pre_row, N, 0);
    clean(deny_row, N, 0);
    clean(value, M, 0);

    /////make 2d array/////
    int **mate = (int**)malloc(M*sizeof(int*));
    for (int i = 0; i < M;i++){
        mate[i] = (int *)malloc(N * sizeof(int));
    }

    /////get all value/////
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &mate[i][j]);
        }
    }

    /////qsort/////
    for (int z = 0; z < M; z++){
        quicksort(mate[z], 0, N - 1);
    }

    printf("%d\n", calculate(mate, M, N, pre_row, deny_row, 0));

    /////free malloc/////
    for (int i = 0; i < M; i++){
        free(mate[i]);
    }
    free(mate);
    free(deny_row);
    free(pre_row);
    free(value);
    return 0;
}