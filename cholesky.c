#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//[a11,a21,a22,a31,a32,33]
//[0,0,1,0,1,2]
//[0,1,3]

float* fatoracaoCholesky (float **a, int rows, int lb) {

	// caa => vetor de dados, cja => vetor de colunas, cia => vetor de linhas.
	float g[rows][rows];
	// valor alterado de j.
	int jAlt;
	//acumulador para calculo dos somatórios.
	float gk;
	// iteradores.
	int i, j, k;

	//calcula g0,0
	g[0][lb] = (float) sqrt(a[0][lb]);

	//calcula termos das primeiras lb linhas (completa a primeira coluna da matriz original)
	for (i = 1; i <= lb; i++){
		for (j = lb-i; j <= lb; j++){
			if (i+j == lb){//calcula valores da primeira coluna da matriz original
				g[i][j] = a[i][j]/g[0][lb];
			}
			else if (j == lb) {//calcula g[i][j]

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

	for (i = 1; i < rows; i++){
		for (j = lb; i+j >= lb && j >= 0; j--){
			if (j == lb) {
				gk = 0;
				for (k = 0; k < lb; k++){
					gk += g[i][k]*g[i][k];
				}
				g[i][lb] = (float) sqrt (a[i][lb] - gk);
			} else {
				gk = 0;
				for (k = 0; k < lb; k++){
					gk += g[i][j]*g[i][k];
				}
				g[i][jAlt] = (a[i][jAlt] - gk)/g[jAlt][jAlt];
			}
//g00 = square a00, gi0 = ai0/g11, gii = sqr (aii - (som gik^2)), gij = sqr (aij - (som gik*gjk)/gjj )
		}
	}

	return 0;
}

int main (void){
	return 0;
}
