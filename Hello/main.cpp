#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib> 


#define MAXSIZE 10

int randInt(int a, int b)
{
	int randValue;
	randValue = (rand() % (b - a + 1)) + a;
	return randValue;
}

int main(int argc, char *argv[])
{

	int numprocs, procid, s1[4], s2[4], xRan;
	int MASTER = 0;
	int SECOND=1;

	srand((int)time(NULL));

	for (int i = 0;i < 4;i++) s1[i] = 0;
	for (int i = 0;i < 4;i++) s2[i] = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	//printf("My rank is: %d", procid);
	while (s2[MASTER]==0 || s2[SECOND]==0) {
		if (procid == MASTER) {
			
			xRan = randInt(1, 100);
			//printf("Procesul lider %d a generat: %d  \n", procid, xRan);
			
			s1[procid] = xRan;
			

			fflush(stdout);

			MPI_Send(s1, 4, MPI_INT, SECOND, 1, MPI_COMM_WORLD);


			MPI_Recv(s1, 4, MPI_INT, SECOND, 1, MPI_COMM_WORLD, &status);
		}
	
	
		else if (procid == SECOND) {
			MPI_Recv(s1, 4, MPI_INT, MASTER, 1, MPI_COMM_WORLD, &status);

			
			srand(100);
			xRan = randInt(1, 100);
			//printf("Procesul %d a generat: %d  \n", procid, xRan);
			
			s1[procid] = xRan;
			fflush(stdout);

			MPI_Send(s1, 4, MPI_INT, MASTER, 1, MPI_COMM_WORLD);
		}

		if (procid == MASTER) {
			if (s1[MASTER] > s1[SECOND]) {
				printf("Procesul %d este leaderul procesului %d\n", MASTER, SECOND);
				printf("Leaderul a generat %d iar celalalt %d\n", s1[MASTER], s1[SECOND]);
				s2[MASTER] = 1;
				
			}
			else
			{
				printf("Procesul %d este leaderul procesului %d\n", SECOND, MASTER);
				printf("Leaderul a generat %d iar celalalt %d\n", s1[SECOND],s1[MASTER]);
				s2[SECOND] = 1;
			}
			fflush(stdout);
			

		}
	}
	
	MPI_Finalize();
	
	
}