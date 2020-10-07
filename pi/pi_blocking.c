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
    
    // Initialize MPI processes
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);
    
    // Start MPI wall timing
    start_time = MPI_Wtime();
    
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);

    // Save process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Multiply SEED by "rank" when you introduce MPI!
    srand(time(NULL) + 123456789 + rank*100);
    
    int flip = total/num_ranks;
    
    // Process 0 receives values from all other processes
    if(rank == 0) {
    	int counts[num_ranks - 1];
    	int global_count = 0;
    	
    	// Receive from other processes
    	for(i = 1; i < num_ranks; i++) {
    		// MPI_Recv(data, count, datatype, source, tag, communicator, status
    		// printf("Receiving local_count from rank %d\n", i);
    		MPI_Recv(&counts[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    		// printf("Received local_count %d from rank %d\n", counts[i-1], i);
    	}
    	
    	// Calculate local count for process 0 itself
    	for(iter = 0; iter < flip; iter ++) {
    		x = (double)random()/(double)RAND_MAX;
    		y = (double)random()/(double)RAND_MAX;
    		z = sqrt(x*x + y*y);
    		
    		if (z <= 1.0)
    			local_count++;
		}
	
	global_count += local_count;
	
	for(i = 0; i < num_ranks - 1; i++) {
		global_count += counts[i];
	}
	
	// Calculate PI with final global count from Process 0
	pi = ((double) global_count / (double) (total)) * 4.0;
    } else {
    	// Calculate local count for other processes
    	for(iter = 0; iter < flip; iter ++){
    		x = (double)random()/(double)RAND_MAX;
    		y = (double)random()/(double)RAND_MAX;
    		z = sqrt(x*x + y*y);
    		
    		if (z <= 1.0)
    			local_count++;
	}
	
	// MPI blocking send local count to process 0
	// MPI_send(data, count, datatype, dest, tag, communicator)
	// printf("Sending local_count %d from rank %d\n", local_count, rank);
	MPI_Send(&local_count, 1, MPI_INT, 0 , 0, MPI_COMM_WORLD);
	// printf("Sent local_count %d from rank %d\n", local_count, rank);
    }
    
    // Stop MPI wall timing
    stop_time = MPI_Wtime();
    elapsed_time = stop_time - start_time;
    
    if(rank == 0){
    	printf("pi: %f\n", pi);
    	printf("Execution Time: %f\n", elapsed_time);
    }
    
    // End MPI processes
    MPI_Finalize();
    return 0;
}

