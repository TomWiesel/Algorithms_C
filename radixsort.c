#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_list_element str_list_element;

typedef struct str_list_element{
    char* message;
    str_list_element* next;
}str_list_element;

typedef struct{
    str_list_element* start;
    str_list_element* end;
}str_list;

void empty_array(str_list*, int);
void radix_sort(str_list*);
void add_message(str_list*, char*);
void add(str_list*, str_list_element*);
void addAll(str_list*, str_list*);
void clear_lists(str_list*, int);
void print_list(str_list*);

int main(){
        str_list* unsorted_strings = malloc(sizeof(str_list));
        empty_array(unsorted_strings, 1);
        add_message(unsorted_strings,"Zerba");
        add_message(unsorted_strings,"Zug");
        add_message(unsorted_strings, "zaubern");
        add_message(unsorted_strings, "Ameise");
        add_message(unsorted_strings, "Belag");
        add_message(unsorted_strings, "Clown");
        add_message(unsorted_strings, "Aermel");
        add_message(unsorted_strings, "1+1=2");
        
        print_list(unsorted_strings);
        radix_sort(unsorted_strings);
        print_list(unsorted_strings);
        
        clear_lists(unsorted_strings, 1);
        free(unsorted_strings);
        return EXIT_SUCCESS;
    }

void radix_sort(str_list* local_list){
    size_t longest = 0;
    str_list_element* string = local_list->start;
    while(string->next != NULL){
        if(strlen(string->message) > longest){
            longest = strlen(string->message);
        }
        string = string->next;
    } 
    longest--;

    str_list* buckets = calloc(255, sizeof(str_list));
    empty_array(buckets, 255);

    string = local_list->start;
    for(size_t i = 0; i <= longest; i++){
        while(string->next != NULL){
            short index = string->message[longest-i];
            add(&buckets[index], string);
            string = string->next;
            local_list->start = string;
        }
        local_list->end = local_list->start; 
        for(int o = 0; o < 255; o++){
            addAll(local_list, &buckets[o]);
        }
        clear_lists(buckets, 255);
        empty_array(buckets, 255);
    }
    free(buckets);
}

void add_message(str_list* local_list, char* msg){
   if(local_list->start->next == NULL){
        local_list->end->message = msg;
        local_list->end->next = malloc(sizeof(str_list_element));
        local_list->end->next->next = NULL;
        return;
    }
    local_list->end->next->message = msg;
    local_list->end->next->next = malloc(sizeof(str_list_element));
    local_list->end = local_list->end->next;
    local_list->end->next->next = NULL;
}

void add(str_list* dest, str_list_element* src){
    if(dest->start->next == NULL){
        memcpy(dest->end, src, sizeof(str_list_element));
        dest->end->next = malloc(sizeof(str_list_element));
        dest->end->next->next = NULL;
        return;
    }
    memcpy(dest->end->next, src, sizeof(str_list_element));
    dest->end = dest->end->next;
    dest->end->next = malloc(sizeof(str_list_element));
    dest->end->next->next = NULL;
}

void addAll(str_list* dest, str_list* src){
    str_list_element* element_dest = dest->end;
    str_list_element* element_src = src->start;
    if(element_src->next != NULL){
        if(element_dest->next == NULL){
            memcpy(element_dest, element_src,sizeof(str_list_element));
            element_dest->next = malloc(sizeof(str_list_element));
            element_dest->next->next = NULL;
            element_src = element_src->next;
        }
        element_dest = element_dest->next;
        while(element_src->next != NULL){
            memcpy(element_dest, element_src,sizeof(str_list_element));
            element_dest->next = malloc(sizeof(str_list_element));
            element_dest->next->next = NULL;
            dest->end = element_dest;
            element_src = element_src->next;
            element_dest = element_dest->next;
        }
    }
}

void clear_lists(str_list* array, int amount){
    str_list_element* element, *tmp;
    for(int i = 0; i < amount; i++){
        element = array[i].start;
        while(element != NULL){
            tmp = element;
            element = element->next;
            free(tmp);
        }  
    }
}

void empty_array(str_list* array,int amount){
    for(int i = 0; i < amount; i++){
        array[i].start = malloc(sizeof(str_list_element));
        array[i].end = array[i].start;
        array[i].start->next = NULL;
    }
}

void print_list(str_list* array){
    str_list_element* element = array->start;
    while(element->next != NULL) {
        printf("%s, ", element->message);
        element = element->next;
    }
    printf("\n");
}
