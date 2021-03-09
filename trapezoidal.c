#include<stdio.h>
#include<mpi.h>

double foo(double x){return x*x+2*x+1;}

double Trapezoidal_function(double a, double b, int n, double h){
	double area = 0;
	area = (foo(a)+foo(b))/2;
	for(int i = 1; i < n; i++){
		area += foo(a+i*h);
	}
	return h*area;

}


int main(void){
	double a = 0;
	double b = 1;
	int n = 1024;
	double h = (b-a)/n;

	int rank, size;
	double local_a, local_b;
	int local_n;
	double local_integral, global_integral = 0;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	local_n = n/size;
	local_a = a + rank*local_n*h;
	local_b = local_a + local_n*h;
	local_integral = Trapezoidal_function(local_a, local_b, local_n, h);

	if(rank != 0){
		printf("Sending from rank %d\n", rank);
		MPI_Send(&local_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else{
		printf("Receiving in rank %d\n", rank);
		global_integral = local_integral;
		for(int i = 1; i < size; i++){
			MPI_Recv(&local_integral, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			global_integral += local_integral;
		}
	}

	if(rank == 0){
		printf("Global integral is: %f\n", global_integral);
	}

	MPI_Finalize();

	return 0;
}
