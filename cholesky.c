#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//[a11,a21,a22,a31,a32,33]
//[0,0,1,0,1,2]
//[0,1,3]

float** fatoracaoCholesky (float **a, int rows, int lb) {
	// caa => vetor de dados, cja => vetor de colunas, cia => vetor de linhas.
	float g[rows][rows];
	//acumulador para calculo dos somatórios.
	float gk;
	// iteradores.
	int i, j, k;

	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			g[i][j] = 0;
		}
	}

	//calcula g0,0

	g[0][lb] = (float) sqrt(a[0][lb]);
	printf("%f\n", g[0][lb]);

	//calcula termos das primeiras lb linhas (completa a primeira coluna da matriz original)
	for (i = 1; i <= lb; i++){
		for (j = lb-i; j <= lb; j++){
			if (i+j == lb){//calcula valores da primeira coluna da matriz original
				g[i][j] = a[i][j]/g[0][lb];
				printf("(%d)(%d) ~ (%d)(%d)\n", i,j,i,j);
				printf("%f = %f/%f\n\n", g[i][j],a[i][j],g[0][lb]);
			}
			else if (j != lb) {//calcula g[i][j]
				gk = 0;
				for (k = 0; k < j; k++){
					gk += g[i][k]*g[j+i-lb][k-j+lb];
					printf("[%f] += (%d)(%d) ~ (%d)(%d) ~~ (%d)\n", gk,i,j,j+i-lb,k-j+lb, lb);
					//printf("gx = %f/%f\n\n", g[i][j],a[i][j],g[0][lb]);
					printf("%f = %f*%f\n", gk,g[i][k],g[j+i-lb][k-j+lb]);
				}
				g[i][j] = (a[i][j] - gk)/g[j+i-lb][lb];
				//printf("%f = %f/%f\n", g[i][j],a[i][j],g[j+i-lb][lb]);
			}
			else {//calcula valores da diagonal (g[i][i])
				gk = 0;
				for (k = lb-i; k < lb; k++){
					gk += g[i][k]*g[i][k];
				}
				g[i][lb] = (float) sqrt (a[i][lb] - gk);
			}
		}
	}//gij = sqr (aij - (som gik*gjk)/gjj ) _ gii = sqr (aii - (som gik^2))

	for (i = lb+1; i < rows; i++){
		for (j = 0; j <= lb; j++){
			if (j != lb) {//calcula g[i][j]
				gk = 0;
				for (k = 0; k < j; k++){
					gk += g[i][k]*g[j+i-lb][k-j+lb];
				}
				g[i][j] = (a[i][j] - gk)/g[j+i-lb][lb];
			} else {//calcula valores da diagonal (g[i][i])
				gk = 0;
				for (k = 0; k < j; k++){
					gk += g[i][k]*g[i][k];
				}
				g[i][lb] = (float) sqrt (a[i][lb] - gk);
			}
		}
	}

	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			printf("%f ", g[i][j]);
		}
		printf("\n");
	}
	return a;
}

int main (void){
	float **a;
	int i, j;/*
	float g[10][5] = {	{0,0,4,1,-1},
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

	float g[3][3] = {{0,0,3},{0,4,8},{3,6,9}};

	a = malloc(sizeof (float *) * 3);

	for (i = 0; i < 3; i++){
		a[i] = malloc (sizeof (float) * 3);
	}

	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			a[i][j] = g[i][j];
			printf("%f ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
	fatoracaoCholesky(a, 3, 2);

	for (i = 0; i < 3; i++){
		free(a[i]);
	}
	free(a);

	return 0;
}
