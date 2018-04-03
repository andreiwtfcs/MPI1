#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#define MASTER 0
#define MAXSIZE 10
int main(int argc, char *argv[])
{

	int numprocs, procid, data[] = { 1,2,3,4,5,6,7,8,9,10 }, sum = 0, sum1 = 0, s1[4], s2 = 0;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	//printf("My rank is: %d", procid);
	if (procid == MASTER) {

		//printf("Master starting");
		for (int i = MAXSIZE / 2 + 1; i < MAXSIZE;i++)
		{
			s1[i - (MAXSIZE / 2 + 1)] = data[i];
		}
		//for (int i = 0;i < 4;i++) { printf("suma1este: %d", s1[i]); } 
		fflush(stdout);
		MPI_Send(s1, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);

		for (int i = 0;i <= MAXSIZE / 2;i++)
		{
			sum1 += data[i];
		}


		MPI_Recv(&sum, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);


	}
	else if (procid == 1) {
		MPI_Recv(s1, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		for (int i = MAXSIZE / 2 + 1;i < MAXSIZE;i++)
		{
			sum += s1[i - (MAXSIZE / 2 + 1)];
			//printf("s1 este: %d", s1[i - (MAXSIZE / 2 + 1)]);
		}
		//printf("Suma1 este %d ", sum);


		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	if (procid == MASTER) {
		printf("Suma este: %d", sum + sum1);
	}

	MPI_Finalize();


}