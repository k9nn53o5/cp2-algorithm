#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void swap(int *x, int *y);
void swap_list(int **arrC, int c, int d);
void quicksort(int *array, int a, int b);
void sort_2D(int arrA[], int **arrB, int size);

void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void swap_list(int **arrC, int c, int d){
    int *temp;
    temp = arrC[c];
    arrC[c] = arrC[d];
    arrC[d] = temp;
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

void sort_2D(int arrA[], int **arrB, int size){
    for (int i = 1; i < size; i++){
        for (int j = 0; j < (size - i); j++){
            if(arrA[j]>arrA[j+1]){
                swap(&arrA[j], &arrA[j+1]);
                swap_list(arrB, j, j+1);
            }
        }
    }
}

int main(void){
    int M, N, total=0, count=0;
    bool error=false;
    scanf("%d %d", &M, &N);
    int **mate = (int**)malloc(M*sizeof(int*));
    for (int i = 0; i < M;i++){
        mate[i] = (int *)malloc(N * sizeof(int));
    }
    int list[M];
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &mate[i][j]);
        }
    }
    for (int z = 0; z < M; z++){
        quicksort(mate[z], 0, N - 1);
    }
    for (int z = 0; z < M; z++){
        list[z] = *mate[z];
    }
    sort_2D(list, mate, M);
    for (int i = 0; i < M; i++){
        for (int j = i; j < M; j++){
            if (error != true){
                for (int loop = 0; loop < N; loop++){
                    list[loop] = mate[j][loop];
                }
            }
            else{
                error = false;
            }
            if (i == 0){
                for (int loop = 0; loop < N; loop++){
                    list[loop] = 0;
                }
            }
            for (int k = 0; k < N; k++){
                if (list[k] > mate[j][k]){
                    error = true;
                    break;
                }
            }
            count++;
        }
        if(count>total){
            total = count;
        }
        count = 0;
    }
    printf("%d", total);
    for (int i = 0; i < M; i++){
        free(mate[i]);
    }
    free(mate);
    return 0;
}