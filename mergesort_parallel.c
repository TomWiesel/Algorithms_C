#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

struct list{
    size_t size;
    int* values;
};

inline double timedifference(struct timeval start, struct timeval end){
    return (end.tv_sec-start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec)/1000.0f;
}

void* mergesort_parallel(void*);
void print_list(struct list);

int main(){
    int unsorted_values[] = {5,4,2,1,0,9,4,56,4,23,1,3,45,-1,-3,-4,-6,2,4,6,123,35};    
    size_t size = sizeof(unsorted_values)/sizeof(int);
    struct list unsorted_list = {size, unsorted_values}; 
    

    size_t size_steroids =2000000;
    int* un_values = calloc(size_steroids, sizeof(int));
    for(int i = size_steroids-1; i > -1; i--){
        un_values[i] = i;
    }
    struct list un_list = {size_steroids, un_values};

    struct timeval start, end;
    gettimeofday(&start,NULL);
    pthread_t t_id;
    pthread_create(&t_id, NULL, mergesort_parallel, &un_list);
    pthread_join(t_id, NULL);
    gettimeofday(&end,NULL);
    printf("%lf \n", timedifference(start, end));
    return EXIT_SUCCESS;
}

void print_list(struct list local_list){
    for(size_t i = 0; i < local_list.size; i++){
        printf("%d, ", local_list.values[i]);
    }
    printf("\n");
}

void* mergesort_parallel(void* args){
    struct list* local_list = args;
    if(local_list->size > 1){
        bool sorted = true;
        for(size_t i = 0; i < local_list->size-1; i++){
            if(local_list->values[i] > local_list->values[i+1]){
                sorted = false;
                break;
            }
        }
        if(!sorted){
            size_t size = local_list->size/2;
            int* list1_values = calloc(size, sizeof(int));
            int* list2_values = calloc(local_list->size-size, sizeof(int));
            struct list list1 = {size, list1_values};
            struct list list2 = {local_list->size-size, list2_values};
            memcpy(list1_values, &local_list->values[0], size*sizeof(int));
            memcpy(list2_values, &local_list->values[size], (local_list->size-size)*sizeof(int));
            
            pthread_t t_id1, t_id2;
            pthread_create(&t_id1, NULL, mergesort_parallel, &list1);
            pthread_create(&t_id2, NULL, mergesort_parallel, &list2);

            size_t index1 = 0;
            size_t index2 = 0;
            size_t result_index = 0;

            pthread_join(t_id1, NULL);
            pthread_join(t_id2, NULL);

            while(local_list->size != result_index){
                if(index1 == list1.size){
                    memcpy(&local_list->values[result_index], &list2_values[index2], (list2.size-index2)<<2);
                    return NULL;
                }else if(index2 == list2.size){
                    memcpy(&local_list->values[result_index], &list1_values[index1], (list1.size-index1)<<2);
                    return NULL;
                }
                if(list1_values[index1] < list2_values[index2]){
                    local_list->values[result_index++] = list1_values[index1++];
                }else{
                    local_list->values[result_index++] = list2_values[index2++];
                }
            }
            free(list1_values);
            free(list2_values);
            return NULL;    
        }

    }
    return NULL;
}
