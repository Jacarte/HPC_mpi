// Blocking MPI_Send(), MPI_Recv()

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, num_ranks, i, iter, provided;
    int local_count = 0, total = 1 << 24;
    double x, y, z, pi;
    double start_time, stop_time, elapsed_time;
    
    printf("Starting\n");
    // Initialize MPI processes
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);
    
    // Start MPI wall timing
    start_time = MPI_Wtime();
    
    printf("Starting\n");
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);

    // Save process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Multiply SEED by "rank" when you introduce MPI!
    srand(time(NULL) + 123456789 + rank*100);
    
    int flip = total/num_ranks;
    
    for(iter = 0; iter < flip; iter ++) {
        x = (double)random()/(double)RAND_MAX;
        y = (double)random()/(double)RAND_MAX;
        z = sqrt(x*x + y*y);
        
        if (z <= 1.0)
            local_count++;
    }

    printf("I am %d, this is my count %d\n", rank, local_count);
    int parentRank = -1, leftChild = -1, rightChild = -1;

    if(rank != 0)
        parentRank = (int)floor((rank - 1)/2);
    if(2*rank + 1 < num_ranks)
        leftChild = 2*rank + 1;
    if(2*rank + 2 < num_ranks)
        rightChild = 2*rank + 2;
        
    int childrenCount = 0;

    if(leftChild >= 0) // Wait for the first child
    {    	
        printf("I am %d, waiting for %d\n", rank, leftChild);

        MPI_Recv(&childrenCount, 1, MPI_INT, leftChild, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        local_count += childrenCount;
        childrenCount = 0;
    }

    if(rightChild >= 0) // Wait for the second child
    {

        printf("I am %d, waiting for %d\n", rank, rightChild);
        MPI_Recv(&childrenCount, 1, MPI_INT, rightChild, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        local_count += childrenCount;
        childrenCount = 0;
    }



    if(rank != 0 && parentRank >= 0){
        printf("I am %d, sending to my parent %d\n", rank, parentRank);
        MPI_Send(&local_count, 1, MPI_INT, parentRank , 0, MPI_COMM_WORLD);
    }
    // Process 0 receives values from all other processes
    
    // Stop MPI wall timing
    stop_time = MPI_Wtime();
    elapsed_time = stop_time - start_time;
    
    if(rank == 0){
    	pi = ((double) local_count / (double) (total)) * 4.0;
    	printf("pi: %f\n", pi);
    	printf("Execution Time: %f\n", elapsed_time);
    }
    
    // End MPI processes
    MPI_Finalize();
    return 0;
}

