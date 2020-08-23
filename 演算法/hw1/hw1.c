#include<stdio.h>
#include<stdlib.h>
int main(void){
    int sum=0, max=0, *array, seat=0, num=0, judge=0;
    array = (int*) calloc(100000, sizeof(int));
    while (scanf("%d", &num)==1){
        *(array + seat) = num;
        seat++;
        if(num >= 0){
            judge = 1;
        }
    }
    if(judge != 1){
        goto execption;
    }
    for (int loop = 0; loop < seat; loop++){
        sum = 0;
        for (int i = 0; i < seat; i++)
        {
            if (sum > 0)
            {
                sum += *(array + i);
            }
            else if (sum <= 0)
            {
                sum = *(array + i);
            }
            if (sum > max)
            {
                max = sum;
            }
        }
        int first = *(array);
        for (int j = 0; j < seat-1; j++){
            *(array + j) = *(array + j + 1);
        }
        *(array + seat - 1) = first;
    }
execption:    printf("%d", max);
    free(array);
    return 0;
}