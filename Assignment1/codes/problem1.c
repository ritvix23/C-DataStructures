#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int debug = 0;


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int randint (int lo, int hi){
    return (rand() % (hi - lo + 1)) + lo;
}

void swap(int i, int j, int * arr){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void free_mem(int ** matrix){
    for(int i =0 ; i<sizeof(matrix)/sizeof(matrix[0]); i++){
        free(matrix[i]);
    }
    free(matrix);
}



int ** generate_rand_matrix(int n){
    int **matrix = (int **)malloc(n* sizeof(int *));
    for (int i=0; i<n; i++)
         matrix[i] = (int *)malloc(n * sizeof(int));  
         
    for(int i = 0; i< n; i++){
        for(int j = 0; j< n ; j++){
            matrix[i][j] = randint(1, 1000);
        }
    }

    if(debug){
        for(int i = 0; i< n; i++){
            for(int j = 0; j< n ; j++){
                printf("%d", matrix[i][j]);
                printf(" ");
            }
            printf("\n");
        }
    }    
    return matrix;
}


int qselect(int i, int j, int k, int * arr){
    int p = randint(i, j);
    
    swap(p, j, arr);
    
    int ind = i;
    
    for(int l  =i ;l < j; l++){
        if(arr[j] > arr[l]){
            swap(ind, l, arr);
            ind++;
        }
    }
    swap(ind, j, arr);
    
    if(ind == k) return arr[ind];
    else if(ind > k) return qselect(i, ind -1, k, arr);
    else return qselect(ind + 1, j , k, arr);
}


int median_efficient(int * arr, int n){
    return qselect(0, n-1, n/2, arr); 
}


int median_of_median_efficient(int ** matrix, int n){
    int * medians = (int *)malloc(n * sizeof(int));  

    for(int i = 0; i < n; i++){
        medians[i] = median_efficient(matrix[i], n); 
    }
    
    return median_efficient(medians, n);
}

int median_naive(int *arr, int n){
    qsort(arr, n, sizeof(int), cmpfunc);
    return arr[n/2];
}


int median_of_median_naive(int ** matrix, int n){
    int * medians = (int *)malloc(n * sizeof(int));  

    for(int i = 0; i < n; i++){
        medians[i] = median_naive(matrix[i], n); 
    }
    
    return median_naive(medians, n);
}

int** copy_arr(int** src, int n){
    int ** dest = malloc(n*sizeof(int*));

    for (int i = 0; i < n; i++){
        dest[i] = malloc(n*sizeof(int));
        memcpy(dest[i], src[i], sizeof(int) * n);
    }

    return dest;

}


int main(int argc, char *argv[]){
    srand(time(0));
    int  n;
    if(argc <= 1) {
        printf("Taking default array size to be 9 \n");
        n = 1;
    }else{
        n = atoi(argv[1]);
        if(n&2==0){
            printf("size should be odd number, incrementing the input by 1");
            n++;
        }
    }

    clock_t timer;

    int ** matrix = generate_rand_matrix(n);
    int ** matrix_copy = copy_arr(matrix, n);
    

    timer = clock();

    int eff_med = median_of_median_efficient(matrix, n);
    timer = clock() - timer;
    double time_taken1 = ((double)timer)/CLOCKS_PER_SEC;

    int naive_med = median_of_median_naive(matrix_copy, n);    
    timer  = clock() - timer;
    double time_taken2 = ((double)timer)/CLOCKS_PER_SEC;

    FILE * fptr;

    fptr = fopen("./runtimes.txt", "a");
    fprintf(fptr, "%.8f", time_taken1);
    fprintf(fptr, " ");
    fprintf(fptr, "%.8f", time_taken2);
    fprintf(fptr, "\n");


    fclose(fptr);



    // printf("%d", naive_med);
    // printf("\n");
    // printf("%d", eff_med);
    // printf("\n");
    // printf("%f", time_taken1);
    // printf("\n");
    // printf("%f", time_taken2);

    
    free_mem(matrix);
    free_mem(matrix_copy);
    return 0;
}
