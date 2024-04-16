/*Q.2 Write an MPI program to calculate sum of randomly generated 1000 numbers 
(stored in array) on a cluster */


#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define ARRAY_SIZE 1000
int main(int argc , char *argv[])
{
    int rank , size;
    int local_array[ARRAY_SIZE];

    int global_sum =0, local_sum =0 ;

    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank);
    for(int i =0; i<ARRAY_SIZE; i++){
        local_array[i] = rand() %100;
        local_sum += local_array[i];
    }

    MPI_Reduce(&local_sum , &global_sum , 1 , MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    printf("Process %d local sum: %d\n" , rank , local_sum);

    if(rank == 0){
        printf("Total sum: %d\n" , global_sum);
    }

    MPI_Finalize();

    return 0;
}
