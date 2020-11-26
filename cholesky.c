#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//[a11,a21,a22,a31,a32,33]
//[0,0,1,0,1,2]
//[0,1,3]

int fatoracaoCholesky (int *vaa , int *vja, int *via) {


// caa => vetor de dados, cja => vetor de colunas, cia => vetor de linhas.
int* caa, cja, cia;
// recuperar qtd de linhas.
int lin = sizeof via / sizeof via[0];
// acumulador para posição das linhas e colunas.
int atual = 0;
//acumulador para calculo dos somatórios.
int gk;
// iteradores.
int i, j, k;
// preencher os ponteiros para o inicio das linhas.
for (i = 0; i < lin-1; i++) {
  atual += i;
  cia[i] = atual;
// preencher as colunas de valor da matriz triangular inferior.
  for (j = 0; j <= i; j++) {
    cja[atual+j] = j;
  }
}
// gerar cada valor da matriz c.
for (i = 0; i < lin-1; i++) {
  for (j = 0; j <= i; j++) {
// preenchimento da diagonal principal.
    if (i==j) {
// preenchimento do elemento (0,0).
      if (i==0) {
        caa[cia[i]+j]= (int) sqrt (vaa[via[i]+j]);
      }
// preenchimento dos demais valores da diagonal.
      else{
        while (k<i && vji[cia[i]+k]>vji[cia[i]+k-1]) {
          gk += pow(vaa[via[i]+k],2);
        }k=0;
        while (k<=j) {
          if (vja[cia[i]+k]==j) {
            caa[cia[i]+j]= (int) sqrt (vaa[via[i]+k] - gk );
          }else{
            caa[cia[i]+j]= (int) sqrt (0 - gk );}
        }
        gk=0;
      }
    }else{
// preenchimento dos valores da coluna (1,j)
      if (i==0) {
        caa[cia[i]+j] = vaa[i]/caa[0];
      }
// preenchimento dos demais valores.
      else{
        while (k<i && vji[cia[i]+k]>vji[cia[i]+k-1]) {
          gk += caa[cia[i]+k]*caa[k+cia[j]];
        }
        while (k<=j) {
          if (vja[cia[i]+k]==j) {
            caa[cia[i]+j] = (vaa[via[i]+k] - gk) / caa[cia[j]+j];
          }else{
            caa[cia[i]+j] = (0 - gk) / caa[cia[j]+j];
        }
        gk = 0;
      }
    }
  }
}
}
return caa;
}
