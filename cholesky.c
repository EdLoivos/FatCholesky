#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 4
#define WIDTH 5

float **a;
float **g;
float **mat;

int fatoracaoCholesky (float **a, int rows, int lb) {
	//acumulador para calculo dos somatórios.
	float gk;
	// iteradores.
	int i, j, k;

	/*for (i = 0; i < rows; i++){
		for (j = 0; j <= lb; j++){
			g[i][j] = 0;
		}
	}*/

	//calcula g0,0

	a[0][lb] = (float) sqrt(a[0][lb]);

	//calcula termos das primeiras lb linhas (completa a primeira coluna da matriz original)
	for (i = 1; i <= lb; i++){
		for (j = lb-i; j <= lb; j++){
			if (i+j == lb){//calcula valores da primeira coluna da matriz original
				a[i][j] = a[i][j]/a[0][lb];
				a[j+i-lb][2*lb-j] = a[i][j];
			}
			else if (j != lb) {//calcula g[i][j]
				gk = 0;
				for (k = 0; k < j; k++){
					gk += a[i][k]*a[j+i-lb][k-j+lb];
				}
				a[i][j] = (a[i][j] - gk)/a[j+i-lb][lb];
				a[j+i-lb][2*lb-j] = a[i][j];
			}
			else {//calcula valores da diagonal (g[i][i])
				gk = 0;
				for (k = lb-i; k < lb; k++){
					gk += a[i][k]*a[i][k];
				}
				a[i][lb] = (float) sqrt (a[i][lb] - gk);
			}
		}
	}

	for (i = lb+1; i < rows; i++){
		for (j = 0; j <= lb; j++){
			if (j != lb) {//calcula g[i][j]
				gk = 0;
				for (k = 0; k < j; k++){
					gk += a[i][k]*a[j+i-lb][k-j+lb];
				}
				a[i][j] = (a[i][j] - gk)/a[j+i-lb][lb];
				a[j+i-lb][2*lb-j] = a[i][j];
			} else {//calcula valores da diagonal (g[i][i])
				gk = 0;
				for (k = 0; k < j; k++){
					gk += a[i][k]*a[i][k];
				}
				a[i][lb] = (float) sqrt (a[i][lb] - gk);
			}
		}
	}
	return 0;
}

int resolucaoSistema (float** a, int rows, int lb, float* b, float* x){

	int i, j = 0;
	float aj = 0;
	float y[rows];

	for (i = 0; i < rows; i++){
		x[i] = 0;
		y[i] = 0;
	}

	for (i = 0; i < rows; i++){
		aj = 0;
		for (j = 0; j < lb; j++){
			if(i-lb+j >= 0){
				aj += a[i][j]*y[i-lb+j];
			}
		}
		y[i] = (b[i] - aj)/a[i][lb];
	}

	for (i = rows-1; i >= 0; i--){
		aj = 0;
		for (j = lb; j > 0; j--){
			if(i+j < rows){
				aj += a[i][j+lb]*x[i+j];
			}
		}
		x[i] = (y[i] - aj)/a[i][lb];
	}

	return 0;
}

int main (int argc, char**argv){
	char* inputF = argv[1];
	int lin, col;

	FILE *ent  = fopen(argv[1], "r");

	fscanf(ent, "%d", &lin);
	fscanf(ent, "%d", &col);

	float **a;
	float b[lin];
	float *x = malloc (sizeof (float) * lin);
	int i, j;


	/*float g[HEIGHT][WIDTH] = {	{0,0,4,1,-1},
						{0,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,-1},
						{-1,1,4,1,0},
						{-1,1,4,0,0}
	};*/

	//float g[HEIGHT][WIDTH] = {{0,0,4},{0,12,37},{-16,-43,98}};
	//float g[HEIGHT][WIDTH] = {{0,0,5,-4,1},{0,-4,6,-4,1},{1,-4,6,-4,0},{1,-4,5,0,0}};

	//float b[HEIGHT] = {4,5,4,4,4,4,4,4,5,4};
	//float b[HEIGHT] = {1,2,3};
	//float b[HEIGHT] = {0,1,0,0};

	a = malloc(sizeof (float *) * lin);

	for (i = 0; i < lin; i++){
		a[i] = malloc (sizeof (float) * col);
	}

	for (i = 0; i < lin; i++){
		for (j = 0; j < col; j++){
			fscanf(ent, "%d", &a[i][j]);
		}
	}
	for (i = 0; i< lin;i++){
		fscanf(ent, "%d", &b[i]);
	}

	fatoracaoCholesky(a, lin, (col-1)/2);
	resolucaoSistema(a, lin, (col-1)/2, b, x);

	for (i = 0; i < lin; i++){
		printf("%f\n", x[i]);
	}

	for (i = 0; i < lin; i++){
		free(a[i]);
	}
	free(a);
	free(x);

	return 0;
}
