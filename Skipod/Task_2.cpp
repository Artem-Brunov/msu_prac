#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <mpi.h>
using namespace std;
double **swap(double **a, int i, int j, int N, int M, double *count)
{
	int iMax = 0;
	unsigned int start_time =  clock();
        unsigned int end_time;
	double k = a[i][j], minus;
	int p = i+1, s = j;
	for(j = j; j < M; j++)
        {
        	a[i][j] = a[i][j]/k;
       
        } 
	j = s; 
	for(l = 0; l < size; l++)
	{
		for(p = p; p < N; p++)
		{
			if(rank == l)
			{
				minus = a[p][j];
				for(s = 0; s < M; s++)
				{
					a[p][s] = a[p][s] - a[i][s]*minus;
				}
				t1 = MPI_Wtime();
				for(m = l+1; m < size; m++)
					MPI_Send(&a[])
			}
		}
	}
	*count = *count * k;
	return a;
}
int main(int argc, char** argv)
{
	float start_time = clock();
	float end_time;
	double count = 1.0;
	int N = atoi(argv[1]);
	int M = N;
	double **a = new double *[N];
	int op = 0, ot = 0;
	int errCode, size, rank, time;
	MPI_Status stat;
	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for(int i = 0; i < N; i++)
	{
		a[i] = new double[M];
		for(int j = 0; j < M; j++)
		{
			if((N*rank + i) ==j)
			{
				a[i][j] = 2 + rend() % 5;
				if(a[i][j] == 0)
                                        a[i][j]++;
			}
			else
			{
    				a[i][j] = 3 + rand() % 7;
				if(a[i][j] == 0)
					a[i][j]++;
			}
		}
		timm = MPI_Wtime();
	}
	for(op = op; op < N; op++)
        {
		a = swap(a, op, op, N, M, &count);
	}
	end_time = clock();
	cout << (end_time-start_time)/1000000<<"size = " <<size<<endl;	
	MPI_Finalize();
	return 0;
}
