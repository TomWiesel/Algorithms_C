#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

inline double timedifference(struct timeval start, struct timeval end){
    return (end.tv_sec-start.tv_sec)*1000.0f + (end.tv_usec-start.tv_usec)/1000.0f;
}

struct list{
    size_t size;
    int* values;
};

void mergesort(struct list);

int main (){
    int values[] = {3,2,1,73,5,6,2,8,-34,-341,4,6,5}; 
    struct list unsorted_list = {sizeof(values)/sizeof(int), values};
    
    size_t size = 2000000;
    int un_values[size];
    for(int i = size-1; i > -1; i--){
        un_values[i] = i; 
    }
    struct list un_list = {size, un_values};
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergesort(un_list);
    gettimeofday(&end, NULL);
    printf("%lf \n", timedifference(start, end));
    return EXIT_SUCCESS;
}

void print_list(struct list local_list){
    for(size_t i = 0; i < local_list.size; i++){
         printf("%d, ", *(local_list.values+i));
     }
}

void mergesort(struct list list_local){
    if(list_local.size > 1){ 

    bool sorted = true;
    for(size_t i = 0; i < list_local.size-1; i++){
        if(*(list_local.values+i) > *(list_local.values+i+1)){
            sorted = false;
            break;
        }
    }
    if(!sorted){ 
    
        struct list list1 = {list_local.size>>1,list_local.values};
        struct list list2 = {list_local.size-list1.size, list_local.values+list1.size};
    
        mergesort(list1);
        mergesort(list2);
        
        int result_values[list_local.size];
        struct list result = {0,result_values};
        
        size_t index1 = 0;
        size_t index2 = 0;

        while(list_local.size != result.size){
            if(index1 >= list1.size){
                memcpy(result.values+result.size, list2.values+index2, (list2.size-index2)*sizeof(int));
                memcpy(list_local.values, result.values, sizeof(int)*list_local.size);
                break;
            }else if(index2 >= list2.size){
                memcpy(result.values+result.size, list1.values+index1, (list1.size-index1)*sizeof(int));
                memcpy(list_local.values, result.values, sizeof(int)*list_local.size);
                break;
            }
            if(*(list1.values+index1) < *(list2.values+index2)){
                *(result.values+result.size++) = *(list1.values+index1++); 
            }else{
                *(result.values+result.size++) = *(list2.values+index2++);
                }
            }
        }
    }
}
