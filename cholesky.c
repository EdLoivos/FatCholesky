#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//[a11,a21,a22,a31,a32,33]
//[0,0,1,0,1,2]
//[0,1,3]

int* fatoracaoCholesky (int *vaa , int *vja, int *via) {

int* caa, cja, cia;
int lin = sizeof via / sizeof via[0];
int atual = 0;
int i , j;
for (i = 0; i < lin-1; i++) {
  atual += i;
  cia[i] = atual;

  for (j = 0; j <= i; j++) {
    cja[atual+j] = j;
  }
for (i = 0; i < lin-1; i++) {
  for (j = 0; j <= i; j++) {
    caa[i+j]= 0;
  }
}
}
