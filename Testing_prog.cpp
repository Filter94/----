#include<fstream>
#include<iostream>
#include<windows.h>
#include<cmath>

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
	}		// Нашли верхнетреугольную обратную
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
	}		// Нижнюю тоже
	for (i = 0; i < N; i++){		//		Перемножаем матрицы 
		for (j = 0; j < N; j++){
			sum = 0;
			for (int k = (i<j)?j:i; k < N; k++)
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
				LU[i][j] = LU[i][j] - sum;//вычисляем элементы верхней треугольной матрицы
			}
			else
			{
				for (k = 0; k < j; k++)
					sum += LU[i][k] * LU[k][j];
				LU[i][j] = (LU[i][j] - sum) / LU[j][j];//вычисляем элементы нижней треугольной матрицы
			}
		}
	}
}

void findRev(double** A, int N){
	LU_dec(N, A);
	matrix_output(A, N, N);
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
	double ** C = new double *[N];
	for (i = 0; i < N; i++){
		C[i] = new double[M];
	}
	if (minus == false)
		for (i = 0; i < N; ++i)
			for (j = 0; M < N; ++j)
				C[i][j] = A[i][j]+B[i][j];
	else
		for (i = 0; i < N; ++i)
			for (j = 0; j < M; ++j)
				C[i][j] = A[i][j] - B[i][j];
			return C;
}

double matrix_norm(double ** A, int N){		//Counts infinite norm of A
	double max = 0, sum = 0;
	int i, j;
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = 0; j < 1; j++)
		if (max < abs(A[i][j]))
			max = abs(A[i][j]);
	}
	return max;
}


using namespace std;

void main(){

	double ** A, ** Arev, ** R, ** Z, ** E, ** X, ** B, **Xapr, buf, znorm, xnorm, rnorm, bnorm, ksi, ro;

	int N = 0, i = 0, j = 0;

	ifstream fin("MatrixA.in");

	fin >> N;

	A = new double *[N];
	B = new double *[N];//	AX=B
	X = new double *[N];
	Xapr = new double *[N];//	X aproximated solution
	R = new double *[N];//	discrepancy
	Z = new double *[N];//	inaccuracy
	Arev = new double *[N];//	A^-1 aproximated

	for (i = 0; i < N; i++){
		A[i] = new double[N];
		R[i] = new double[1];
		Z[i] = new double[1];
		Arev[i] = new double[N];
		B[i] = new double[1];
		X[i] = new double[1];
		Xapr[i] = new double[1];
	}

	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++){
		fin >> buf;
		A[i][j] = buf;
		Arev[i][j] = A[i][j];
	}

	for (i = 0; i < N; i++){
		fin >> buf;
		B[i][0] = buf;
	}

	for (i = 0; i < N; i++){
		fin >> buf;
		X[i][0] = buf;
	}
	fin.close();
	cout << "A = " << '\n';
	matrix_output(A, N, N);
	system("pause");
	cout << "X = "<< '\n';
	matrix_output(X, N, 1);
	cout << "B = " << '\n';
	matrix_output(B, N, 1);

	findRev(Arev, N);	//	Approximated reverted matrix
	cout << "A reversed = " << '\n';
	matrix_output(Arev, N, N);
	Xapr = multiplicate(Arev, B, N, N, N);
	cout << "X aproximated = " << '\n';
	matrix_output(Xapr, N, 1);
	cout << "X norm = " << matrix_norm(X, N) << '\n';

	Z = Add(Xapr, X, N, 1, true);	//	Z = X - Xapr
	cout << "Z = " << '\n';
	matrix_output(Z, N, 1);
	ksi = matrix_norm(Z, N);
	ksi /= matrix_norm(X, N);	//	ksi = ||X||/||(X - Xapr)||
	cout << "Z norm = " << matrix_norm(Z, N) << '\n';
	cout << "Ksi = " << ksi << '\n';

	R = multiplicate(A, Xapr, N, N, 1);	
	R = Add(R, B, N, 1, true);	// R = A * Xapr - B
	cout << "R = " << '\n';
	matrix_output(R, N, 1);
	ro = matrix_norm(R, N);
	ro /= matrix_norm(B, N);	// ro = ||A * Xapr - B||/||B||
	cout << "R norm = " << matrix_norm(R, N) << '\n';
	cout << "B norm = " << matrix_norm(B, N) << '\n';
	cout << "Ro = " << ro << '\n';
	
	system("pause");

	for (i = 0; i < N; i++){
		delete [] A[i];
		delete[] R[i];
		delete[] Z[i];
		delete[] Arev[i];
	}
	delete[] A;
	delete[] R;
	delete[] Z;
	delete[] Arev;
}