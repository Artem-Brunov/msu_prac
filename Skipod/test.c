#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//-----------Функции вывода вспомогательные
void printMatrix(int count, double** A, int N)
{
    for(int i = 0; i < count; i++){
        for(int j = 0; j < N;j++)
            printf("A[%d][%d] = %5.2f\t",i,j,A[i][j]);
        printf("\n");
    }
}
 
void vyvod1(double **matrix, int Strok, int Stolb)
{FILE *f;f = fopen("out1.txt","w");
for (int i=0; i<Strok; i++)
{
 
for (int j=0; j<Stolb; j++)
fprintf(f,"%9.2f\t",matrix[i][j]);
 
fprintf(f,"\n");
}
 
fclose(f);
}
 
 
void vyvod2(double **matrix, int Strok, int Stolb)
{
FILE *f;
f = fopen("out2.txt","w");
for (int i=0; i<Strok; i++)
{
 
for (int j=0; j<Stolb; j++)
fprintf(f,"%9.2f\t",matrix[i][j]);
 
fprintf(f,"\n");
}
 
fclose(f);
}
 
void vyvod3(double **matrix, int Strok, int Stolb)
{
FILE *f;
f = fopen("out3.txt","w");
for (int i=0; i<Strok; i++)
{
 
for (int j=0; j<Stolb; j++)
fprintf(f,"%9.2f\t",matrix[i][j]);
 
fprintf(f,"\n");
}
 
fclose(f);
}
 
void vyvod4(double **matrix, int Strok, int Stolb)
{
FILE *f;
f = fopen("out4.txt","w");
for (int i=0; i<Strok; i++)
{
 
for (int j=0; j<Stolb; j++)
fprintf(f,"%9.2f\t",matrix[i][j]);
 
fprintf(f,"\n");
}
 
fclose(f);
}
void printVector(int count, double *L)
    {
        for(int i = 0; i < count; i++)
            printf("L[%d] = %5.2f\n",i,L[i]);
        printf("\n");
    }
 
void printVector1(int count, int *L)
    {
        for(int i = 0; i < count; i++)
            printf("L[%d] = %5d\n",i,L[i]);
        printf("\n");
    }
//---------------------------
int main(int argv,char* argc[]){
    int rank,size;
    int count = 1080;
    double t1,t2;
    MPI_Status status;
    MPI_Init(&argv,&argc);
    
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 
    MPI_Bcast(&count,1,MPI_INT,0,MPI_COMM_WORLD);
    double temp;
    int maxCol;
    double maxValue;
    double *trX = new double[count];    
    int numb;
    int* ind = new int[count];
    for(int i =0; i < count; i++)
        ind[i] = i;
    int N = count/size;
    double** A = new double*[count];
    for(int i = 0; i < count; i++)
        A[i] = new double[N];
    
    double*B = new double [count];
    for(int i = 0; i < count; i++) B[i] = rand()%100+1;
    srand(time(NULL) + rank);   
    for(int i = 0; i < count; i++)      
        for(int j = 0; j < N;j++)
            A[i][j] = rand()%400+1;
    int recv = 0;
    double* L = new double[count];
    double* cfs = new double[count];
    double orB = B[0];
        //if(rank == 0) printf("%f",orB);
 
 
//MPI_Bcast(B,count,MPI_DOUBLE,size - 1,MPI_COMM_WORLD);
//printVector(count,B);
//if(rank == 0)vyvod1(A, count, N);
//if(rank == 1)vyvod2(A, count, N);
//-------------------------
    t1 = MPI_Wtime();
for(int p = 0; p < size; p++)
{
    if(p == rank)
    {       
    
        for(int k = 0;k<N;k++)
        {       maxValue = A[N*p+k][k];
                maxCol = N*p + k;
                //поиск главного элемента
                for(int i = N*p + k + 1; i < count; i ++)
                    if(abs(A[i][k]) > abs(maxValue)) {maxValue = A[i][k]; maxCol = i;}
                for(int i = 0; i < N; i++)
                {
                    temp = A[N*p+k][i];
                    A[N*p+k][i] = A[maxCol][i];
                    A[maxCol][i] = temp;
                }
                
                if(maxCol!=N*p+k){
                temp = ind[N*p+k];
                ind[N*p+k] =ind[maxCol];
                ind[maxCol] = temp;
                temp = B[N*p+k];
                B[N*p+k] = B[maxCol];
                B[maxCol] = temp;}
                
                //
                for(int j = N*p + k; j < count - 1; j++){
                    L[j] = A[j+1][k]/A[p*N+k][k];
                }
                for(int proc = p + 1;proc < size; proc++)
                {            
                    MPI_Send(L,count,MPI_DOUBLE,proc,1,MPI_COMM_WORLD);
                    MPI_Send(&k,1,MPI_DOUBLE,proc,2,MPI_COMM_WORLD);
                    MPI_Send(&maxCol,1,MPI_INT,proc,22,MPI_COMM_WORLD);
                    MPI_Send(ind,count,MPI_INT,proc,33,MPI_COMM_WORLD);
            
                }
        for(int i = N*p + k + 1; i < count; i++)
        {
            for(int j = k; j < N; j++){
                A[i][j] = A[i][j] - A[N*p + k][j] * L[i - 1];
            if(abs(A[i][j]) < 0.00001) A[i][j] = 0;
                        }
            B[i] = B[i] - B[N*p + k]*L[i - 1];
        }
        
        if(p != size - 1){
            for(int proc = p + 1;proc < size; proc++)            
                MPI_Send(B,count,MPI_DOUBLE,proc,3,MPI_COMM_WORLD);
        }
        
            
    }
    }
    if(rank > p)
    {       for(int k = 0;k<N;k++) {     
                MPI_Recv(&numb,1,MPI_DOUBLE,p,2,MPI_COMM_WORLD,&status);
                MPI_Recv(L,count,MPI_DOUBLE,p,1,MPI_COMM_WORLD,&status);
                MPI_Recv(B,count,MPI_DOUBLE,p,3,MPI_COMM_WORLD,&status);
                MPI_Recv(ind,count,MPI_INT,p,33,MPI_COMM_WORLD,&status);
                MPI_Recv(&maxCol,1,MPI_INT,p,22,MPI_COMM_WORLD,&status);
                for(int i = 0; i < N; i++){
                    temp = A[maxCol][i];
                    A[maxCol][i] = A[N*p + numb][i];
                    A[N*p + numb][i] = temp;}
                    for(int i = numb + 1; i < count; i++)
                        {
                            for(int j = numb; j < N; j++)
                                A[i][j] = A[i][j] - A[k][j] * L[i - 1];//к потому что по диагонали
                            //B[i] = B[i] - B[k]*L[i - 1];
                        }
            }
    
    }
 
}
 
//-------так как последний свободный вектор, верный
MPI_Bcast(B,count,MPI_DOUBLE,size - 1,MPI_COMM_WORLD);
 
MPI_Bcast(ind,count,MPI_INT,size - 1, MPI_COMM_WORLD);
double* X = new double[count];
orB = B[0];
//-----обратный ход
for(int p = size - 1; p >=0; p--)
{
    if(p == rank) 
        {
 
            X[N*p + N - 1] = B[N*p + N - 1]/ A[N*p + N-1][N-1];
            
                for(int i = N - 2; i>=0; i--){
                    for(int j = i + 1; j < N; j++)
                        B[N*p + i] = B[N*p + i] - A[N*p + i][j] * X[N*p+j];
                    
                    X[N*p + i] = B[N*p + i]/A[N*p + i][i];
                }
                for(int i = 0; i < N*p; i++)
                    for(int j = 0; j < N;j++)
                        B[i] = B[i] - A[i][j] * X[N*p + j]; 
                if(p>0){
                MPI_Send(B,count,MPI_DOUBLE,p-1,4,MPI_COMM_WORLD);
                MPI_Send(X,count,MPI_DOUBLE,p-1,5,MPI_COMM_WORLD);}         
                
        }
    if(rank == p - 1)
    {       
            MPI_Recv(B,count,MPI_DOUBLE,p,4,MPI_COMM_WORLD,&status);
            MPI_Recv(X,count,MPI_DOUBLE,p,5,MPI_COMM_WORLD,&status);                
        
    }
}
t2 = MPI_Wtime();
printf("time = %f\n",t2 - t1);                  
double ch = 0;
    
MPI_Bcast(X,count,MPI_DOUBLE,0,MPI_COMM_WORLD);
 
//printVector(count,X);
for(int p = 0; p < size; p++){
    if(rank == p) {
        for(int i = 0; i < N; i++)
            ch = ch +  A[0][i] * X[N*p + i];
        if(p != size - 1) MPI_Send(&ch,1,MPI_DOUBLE,p + 1,223,MPI_COMM_WORLD);
        if(p == size - 1) printf("pogreshnost = %2.16f\n",orB - ch);
    }
    if(rank == p + 1) 
        MPI_Recv(&ch,1,MPI_DOUBLE,p,223,MPI_COMM_WORLD,&status);        
        
    }
 
//проверка 
 
//if(rank == 0)vyvod1(A, count, N);
//if(rank == 1)vyvod2(A, count, N);
//if(rank == 2)vyvod3(A, count, N);
//if(rank == 3)vyvod4(A, count, N);
MPI_Finalize();
}
