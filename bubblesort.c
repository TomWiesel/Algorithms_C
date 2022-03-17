#include <stdio.h>
#include <stdlib.h>

int main(){
    int size = 8;
    int values[] = {3,5,1,2,0,-1,4,8};
    int tmp;
    for(int i = 0; i < size; i++){
        for(int o = 0; o < size-i-1;o++){
            if(values[o] > values[o+1]){
                tmp = values[o];
                values[o] = values[o+1];
                values[o+1] = tmp;
            }
        }
    }

    for(int i = 0; i < size; i++){
        printf("%d, ", values[i]);
    }

    return EXIT_SUCCESS;
}
