#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define SIZE 10
int unsorted_array[SIZE];
int sorted_array[SIZE];


typedef struct {
    int *arr;
    int left;
    int right;
} merge_sort_arguments ;


typedef struct{
    int *sorted_arr;
    int *sorted_first;
    int *sorted_second;
} merge_first_and_second_of_main_arguments;


void merge_for_merge_sort(int *arr, int left, int middle, int right){    // Used for merge sort
    
    
    int number_of_elements_in_left = middle - left + 1;
    int number_of_elements_in_right = right - middle;
    
    int left_arr[number_of_elements_in_left], right_arr[number_of_elements_in_right];
    
    for (int i = 0; i < number_of_elements_in_left; ++i)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < number_of_elements_in_right; ++j)
        right_arr[j] = arr[middle + 1 + j] ;
    
    int i = 0 ;
    int j = 0 ;
    int k = left;
    
    while(i < number_of_elements_in_left && j < number_of_elements_in_right){
        
        if(left_arr[i] < right_arr[j]){
            arr[k++] = left_arr[i++];
        }
        else{
            arr[k++] = right_arr[j++];
        }
    }
    
    while(i < number_of_elements_in_left){
        arr[k++] = left_arr[i++];
    }
    
    while(j < number_of_elements_in_right){
        arr[k++] = right_arr[j++];
    }
}



void *merge_sort(void *args){    // Sorting the first half and second half of array using merge sort
     
    merge_sort_arguments *arguments = (merge_sort_arguments *)args;

    int left = arguments->left;
    int right = arguments->right;
    int *array = arguments->arr;
    
    if(left < right){   // Still we can divide the array
        int mid = (right + left)/2;
        merge_sort_arguments *first_args = malloc(sizeof(merge_sort_arguments));
        first_args->arr = array;
        first_args->left = left;
        first_args->right = mid;
        
        merge_sort_arguments *second_args = malloc(sizeof(merge_sort_arguments));
        second_args->arr = array;
        second_args->left = mid + 1;
        second_args->right = right;
        
        merge_sort(first_args);
        merge_sort(second_args);
        
        merge_for_merge_sort(array, left, mid, right);
        
        free(first_args);
        free(second_args);
    }
    
    return NULL;
}


void *merge_first_and_second_half_of_main_array(void *args){
    
    merge_first_and_second_of_main_arguments *arguments = (merge_first_and_second_of_main_arguments *)args;
    
    int *sorted_arr = arguments->sorted_arr;
    int *sorted_first = arguments->sorted_first;
    int *sorted_second = arguments->sorted_second;
    
    int i = 0 ;
    int j = 0 ;
    int k = 0 ;
    
    while(i < SIZE/2 && j < SIZE/2){
        if(sorted_first[i] < sorted_second[j]){
            sorted_arr[k] = sorted_first[i];
            ++i;
        }
        else{
            sorted_arr[k] = sorted_second[j];
            ++j;
        }
        ++k;
    }

    while(i<SIZE/2){
        sorted_arr[k++] = sorted_first[i++];
    }
    while(j<SIZE/2){
        sorted_arr[k++] = sorted_second[j++];
    }
    
    free(arguments);
    return NULL;
}


int main(void){
    
    printf("Enter %d numbers\n", SIZE);
    
    for (int i = 0; i < SIZE; ++i) {
        scanf("%d", &unsorted_array[i]);
    }
    
    int first_half_array[SIZE/2];
    int second_half_array[SIZE/2];
    
    for (int i = 0; i < SIZE/2; ++i) {
        first_half_array[i] = unsorted_array[i];
    }
    for (int i = SIZE/2; i < SIZE; ++i) {
        second_half_array[i - (SIZE/2)] = unsorted_array[i];
    }
    
    merge_sort_arguments *first_args = malloc(sizeof(merge_sort_arguments));
    first_args->arr = first_half_array;
    first_args->left = 0;
    first_args->right = (SIZE/2) - 1;
    
    merge_sort_arguments *second_args = malloc(sizeof(merge_sort_arguments));
    second_args->arr = second_half_array;
    second_args->left = 0;
    second_args->right = (SIZE/2) - 1;
    
    
    // Create 2 threads for sorting first and second part
    pthread_t sort_first_half_thread,sort_second_half_thread;
    
    
    pthread_create(&sort_first_half_thread, NULL, merge_sort, (void *)first_args);
    pthread_create(&sort_second_half_thread, NULL, merge_sort, (void *)second_args);
    
    pthread_join(sort_first_half_thread, NULL);
    pthread_join(sort_second_half_thread, NULL);
    
    
    merge_first_and_second_of_main_arguments *merge_first_second = malloc(sizeof(merge_first_and_second_of_main_arguments));
    merge_first_second->sorted_arr = sorted_array;
    merge_first_second->sorted_first = first_half_array;
    merge_first_second->sorted_second = second_half_array;
    
    
    
    // Create a thread to merge these 2 sorted parts
    pthread_t merge_first_and_second_half;
    
    pthread_create(&merge_first_and_second_half, NULL, merge_first_and_second_half_of_main_array, (void *)merge_first_second);
    
    pthread_join(merge_first_and_second_half, NULL);
    
    
    // Print sorted array in parent thread( main thread) which is in main()
    printf("Sorted array:\n");
    
    for (int i = 0; i < SIZE; ++i) {
        printf("%d   ", sorted_array[i]);
    }
}
