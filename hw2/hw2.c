#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int *output_list = NULL;
int left_size = 0, right_size = 0;
int input_list_size = 0;

// merge function for merging two parts
void merge(int low, int mid, int high)
{
    int* left = (int *)malloc((mid - low + 1) * sizeof(int));
    int* right = (int *)malloc((high - mid) * sizeof(int));

    // s1 is size of left part and s2 is size
    // of right part
    int s1 = mid - low + 1, s2 = high - mid, i, j;
 
    // storing values in left part
    for (i = 0; i < s1; i++) left[i] = output_list[i + low];
    // storing values in right part
    for (i = 0; i < s2; i++) right[i] = output_list[i + mid + 1];

    int k = low;
    i = j = 0;
 
    // merge left and right in ascending order
    while (i < s1 && j < s2) {
        if (left[i] <= right[j])
            output_list[k++] = left[i++];
        else
            output_list[k++] = right[j++];
    }
 
    // insert remaining values from left
    while (i < s1) {
        output_list[k++] = left[i++];
    }
 
    // insert remaining values from right
    while (j < s2) {
        output_list[k++] = right[j++];
    }
}

// merge sort function
void merge_sort(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {
 
        // calling first half
        merge_sort(low, mid);
 
        // calling second half
        merge_sort(mid + 1, high);
 
        // merging the two halves
        merge(low, mid, high);
    }
}

void *left_sorting_thread()
{
	int i;
    merge_sort(0, input_list_size/2 - 1);
}

void *right_sorting_thread()
{
	int i;
    merge_sort(input_list_size/2, input_list_size-1);
}


void *merge_thread()
{
    merge(0, input_list_size/2 -1, input_list_size-1);
}

int main(int argc, char **argv)
{
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    int input_list[10000] = {0};
    int input_single_number = 0;
    char parser;
    int i, j;
    clock_t t1, t2;

    pthread_t id[3];

    for(j = 0; j < 9; j++){

        fscanf(input_file, "%d", &input_single_number);
        fscanf(input_file, "%c", &parser);

        for(i = 0;  parser != '\n' && parser != '\r'; i++){
            input_list[i] = input_single_number;
            input_list_size = i + 1;
            fscanf(input_file, "%d", &input_single_number);
            fscanf(input_file, "%c", &parser);
        }

        input_list[i] = input_single_number;
        input_list_size = i + 1;
        
        t1 = clock();
       
        output_list = (int *)malloc(sizeof(int) * input_list_size);
        for(i = 0; i < input_list_size; i++){
            output_list[i] = input_list[i];
        }       

    	pthread_create(&id[0],NULL,(void *) left_sorting_thread,NULL);
        pthread_create(&id[1],NULL,(void *) right_sorting_thread,NULL);
    	
        pthread_join(id[0],NULL);//等待線程（pthread）結束
        pthread_join(id[1],NULL);
    	
        pthread_create(&id[2],NULL,(void *) merge_thread,NULL);
       
        pthread_join(id[2],NULL);

        t2 = clock();
        printf("Line %d takes :%.3fs\n", j+1, t2-t1);

        for(i = 0;  i < input_list_size; i++){
            fprintf(output_file, "%d ", output_list[i]);
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

	return 0;
}
