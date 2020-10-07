#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[]){

	int rank, num_ranks, i, iter, provided;
	int local_count = 0, global_count = 0, total = 1 << 24;
	double x, y, z, pi;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

	double start_time, stop_time, elapsed_time;

	start_time = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);

	srand(time(NULL) + 123456789 + rank*100);

	int flip = total/num_ranks;


	MPI_Bcast(&flip, 1, MPI_INT, 0, MPI_COMM_WORLD);


	for(iter = 0; iter < flip; iter ++){
		x = (double)random()/(double)RAND_MAX;
		y = (double)random()/(double)RAND_MAX;
		z = sqrt(x*x + y*y);

		if (z <= 1.0)
			local_count++;
	}

	MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM,  0, MPI_COMM_WORLD);

	stop_time = MPI_Wtime();
	elapsed_time = stop_time - start_time;

	pi = 4*(double)global_count/((double)total);

	if(rank == 0){
		printf("pi: %f\n", pi);
		printf("Execution Time: %f\n", elapsed_time);
	}

	MPI_Finalize();
	return 0;
}