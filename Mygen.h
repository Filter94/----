#pragma once
void Q_matrix(double **Q, int n, int schema);
void matr_mul(double **a, double **b, double **c, int n);
double matr_inf_norm(double **a, int n);
void mygen(double **a, double **a_inv, int n, double alpha, double beta, int sign_law, int lambda_law, int variant, int schema);
