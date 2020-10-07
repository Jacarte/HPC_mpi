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
	int counts[num_ranks];

	for(iter = 0; iter < flip; iter ++){
		x = (double)random()/(double)RAND_MAX;
		y = (double)random()/(double)RAND_MAX;
		z = sqrt(x*x + y*y);

		if (z <= 1.0)
			local_count++;
	}

	MPI_Gather(&local_count, 1, MPI_INT, &counts,1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
		for(int i= 0;i < num_ranks; i++)
			global_count += counts[i];

	pi = (double)global_count/((double)total)*4;
	stop_time = MPI_Wtime();
	elapsed_time = stop_time - start_time;

	if(rank == 0){
		printf("pi: %f\n", pi);
		printf("Execution Time: %f\n", elapsed_time);
	}

	MPI_Finalize();
	return 0;
}