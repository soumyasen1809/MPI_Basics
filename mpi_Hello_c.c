#include<stdio.h>
#include"mpi.h"

int main(int argc, char **argv){
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Size is %d: ", size);
    }
    else
    {
        printf("Rank is %d: ", rank);
    }
    

    MPI_Finalize();

    return 0;
}
