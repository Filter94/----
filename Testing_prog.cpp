#include<fstream>
#include<iostream>
#include<windows.h>
#include"Mygen.h"

#define SIZE 50

using namespace std;

void matrix_output(double ** A, int N, int M){
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void LU_fun_OBR(int N, double **&LU)		//нахождение обратной матрицы
{
	int i, j, k, t;
	double sum;
	int p;

	for (i = N - 1; i >= 0; i--)
	{
		for (j = N - 1; j >= i; j--)
		{
			sum = 0;
			if (i == j)
			{
				LU[i][j] = 1 / LU[i][j];
			}
			else if (i < j)
			{
				for (p = i + 1; p <= j; p++)
					sum += LU[i][p] * LU[p][j];
				LU[i][j] = -sum / LU[i][i];

			}
		}
	}
	for (i = 1; i < N; i++)
	{
		for (j = 0; j < i; j++)
		{
			sum = 0;
			for (p = j + 1; p < i; p++)
				sum += LU[i][p] * LU[p][j];
			sum += LU[p][j];
			LU[i][j] = -sum;
		}
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			sum = 0;
			for (int k = (i<j) ? j : i; k < N; k++)
			if (k != j)
				sum += LU[i][k] * LU[k][j];
			else
				sum += LU[i][k];
			LU[i][j] = sum;
		}
	}
}

void LU_dec(int N, double **&LU)
{
	int i, j, k;
	double sum;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			sum = 0;
			if (i <= j)
			{
				for (k = 0; k < i; k++)
					sum += LU[i][k] * LU[k][j];
				LU[i][j] = LU[i][j] - sum;
			}
			else
			{
				for (k = 0; k < j; k++)
					sum += LU[i][k] * LU[k][j];
				LU[i][j] = (LU[i][j] - sum) / LU[j][j];
			}
		}
	}
}

void findRev(double** A, int N){
	LU_dec(N, A);
	LU_fun_OBR(N, A);
}

double** multiplicate(double** A, double** B, int n, int m, int q){			//n*m m*q		Multiplies. Result in A
	int i, j, k;
	double ** C = new double *[n];
	for (i = 0; i < n; i++){
		C[i] = new double[q];
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < q; j++){
			C[i][j] = 0;
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	return C;
}

double ** Add(double** A, double** B, int N, int M, bool minus = false){	//Adds. Result in A
	int i, j;
	double **C = new double *[N];
	for (i = 0; i < N; i++){
		C[i] = new double[M];
	}
		for (i = 0; i < N; ++i){
			for (j = 0; j < M; ++j){
				if (minus == false){
					C[i][j] = A[i][j] + B[i][j];
				}
				else
				{
					C[i][j] = A[i][j] - B[i][j];
				}
			}
		}
	return C;
}

double matrix_norm(double ** A, int N, int M){		//Counts infinite norm of A
	double max = 0, sum = 0;
	int i, j;
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = 0; j < M; j++)
			sum += A[i][j];
		if (max < sum)
			max = sum;
	}
	return max;
}

void vector_gen(double ** A, int N){		//Counts infinite norm of A
	for (int i = 0; i < N; i++){
		A[i][0] = (rand() / static_cast <double> (RAND_MAX));
	}
}

void ouptut(double a){
	cout << trunc(a / pow(10, trunc(log10(a))))<< ".*10^";
	cout << trunc(log10(a));
}

void make_experiment(bool alpha_var, bool simple_cell){
	double ** A, ** Arev, ** R, ** Z, ** E, ** X, ** B, **Xapr, buf, znorm, xnorm, rnorm, bnorm, ksi, ro;
	int i;

	double alpha = 1, beta = 1;

	A = new double *[SIZE];
	B = new double *[SIZE];//	AX=B
	X = new double *[SIZE];
	Xapr = new double *[SIZE];//	X aproximated solution
	R = new double *[SIZE];//	discrepancy
	Z = new double *[SIZE];//	inaccuracy
	Arev = new double *[SIZE];//	A^-1 aproximated

	for (int k = 0; k < SIZE; k++){
		A[k] = new double[SIZE];
		R[k] = new double[1];
		Z[k] = new double[1];
		Arev[k] = new double[SIZE];
		B[k] = new double[1];
		X[k] = new double[1];
		Xapr[k] = new double[1];
	}

	do{
		if (alpha_var){
			alpha /= 10;
			cout << "Alpha =" << alpha;
		}
		else{
			beta *= 10;
			cout << "Beta =" << beta;
		}

		if (simple_cell)
			mygen(A, Arev, SIZE, alpha, beta, 0, 0, 1, 1);
		else
			mygen(A, Arev, SIZE, alpha, beta, 0, 0, 2, 1);
		cout << " // ";
		cout << "||A||= ";
		ouptut(matrix_norm(A, SIZE, SIZE));
		cout<< " // ";
		cout << "Nu(A) = ";
		ouptut(matrix_norm(A, SIZE, SIZE) * matrix_norm(Arev, SIZE, SIZE));
		cout << " // ";
		//cout << "Arev = " << '\n';
		//matrix_output(Arev, SIZE, SIZE);
		vector_gen(B, SIZE);
		X = multiplicate(Arev, B, SIZE, SIZE, 1);

		for (int g = 0; g < SIZE; g++){
			for (int h = 0; h < SIZE; h++){
				Arev[g][h] = A[g][h];
			}
		}

		findRev(A, SIZE);	//	Approximated reverted matrix
		cout << "||Arev|| = ";
		ouptut(matrix_norm(Arev, SIZE, SIZE));
		cout << " // ";
		//cout << "Arev = " << '\n';
		//matrix_output(A, SIZE, SIZE);
		Xapr = multiplicate(A, B, SIZE, SIZE, 1);
		//cout << "Xapr = " << '\n';
		//matrix_output(Xapr, SIZE, 1);
		//cout << "X norm = " << matrix_norm(X, SIZE, 1) << '\n';

		Z = Add(Xapr, X, SIZE, 1, true);	//	Z = X - Xapr
		//cout << "Z = " << '\n';
		//matrix_output(Z, SIZE, 1);
		ksi = matrix_norm(Z, SIZE, 1);
		ksi /= matrix_norm(X, SIZE, 1);	//	ksi = ||X||/||(X - Xapr)||
		cout << "||Z|| = ";
		ouptut(matrix_norm(Z, SIZE, 1));
		cout << " // ";
		cout << "Ksi = ";
		ouptut(ksi);
		cout << " // ";
		R = multiplicate(Arev, Xapr, SIZE, SIZE, 1);
		R = Add(R, B, SIZE, 1, true);	// R = A * Xapr - B
		//cout << "R = " << '\n';
		//matrix_output(R, SIZE, 1);
		ro = matrix_norm(R, SIZE, 1);
		ro /= matrix_norm(B, SIZE, 1);	// ro = ||A * Xapr - B||/||B||
		cout << "Ro = ";
		ouptut(ro);
		cout << '\n';
	} while (ksi < 1);
	for (i = 0; i < SIZE; i++){
		delete[] A[i];
		delete[] R[i];
		delete[] Z[i];
		delete[] Arev[i];
		delete[] X[i];
		delete[] B[i];
	}
	delete[] A;
	delete[] R;
	delete[] Z;
	delete[] Arev;
}

using namespace std;

void main(){
	cout << "Beta is variant and matrix isn't simple.\n";
	make_experiment(0, 0);
	cout << "Alpha is variant and matrix isn't simple.\n";
	make_experiment(1, 0);
	cout << "Beta is variant and matrix is simple.\n";
	make_experiment(0, 1);
	cout << "Alpha is variant and matrix is simple.\n";
	make_experiment(1, 1);
	system("pause");
}