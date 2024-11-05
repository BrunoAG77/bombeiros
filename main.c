// Bruno Antico Galin | 10417318 
// Gabriel Lazareti Cardoso | 10417353 
// Guilherme Martins Silva | 10417140 
// Ismael de Sousa e Silva | 10410870 
// Referência: https://www.youtube.com/watch?v=pWrNOjw50As&pp=ygUNZGppa3N0cmEgZW0gYw%3D%3D
// Referência: https://www.youtube.com/watch?v=5y8dch2uHR4&pp=ygUNZGppa3N0cmEgZW0gYw%3D%3D
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ESQ 100
#define MAX_VAL 999

void caminhoMinimo(int mapa[MAX_ESQ][MAX_ESQ], int inicio, int fim, int n_esq){
  int distancia[MAX_ESQ];
  bool visitado[MAX_ESQ];
  int anterior[MAX_ESQ];
  for(int i = 0; i < n_esq; i++){
    distancia[i] = MAX_VAL;
    visitado[i] = false;
    anterior[i] = -1;
  }
  distancia[inicio] = 0;
}

int main(void){
  FILE *filein = fopen("bombeiro.txt","r"); //Leitura do arquivo de entrada
  if (filein == NULL) printf("Erro ao abrir o arquivo.");
  int loc_incendio, n_esq, esq1, esq2, tempo;
  int mapa[MAX_ESQ][MAX_ESQ];
  for (int i = 0; i < n_esq; i++){ //Inicializa o mapa e com 0 para o mesmo e infinito para o resto
    for (int j = 0; j < n_esq; j++){
      if (i == j) mapa[i][j] = 0;
      else mapa[i][j] = MAX_VAL;
    }
  }
  fscanf(filein,"%d",&loc_incendio); //Primeira linha
  fscanf(filein,"%d",&n_esq); //Segunda linha
  while (fscanf(filein, "%d" "%d" "%d", &esq1, &esq2, &tempo) != 3){ //Demais linhas
    if (esq1 == 0) break;
    mapa[esq1 - 1][esq2 - 1] = tempo; //Tempo de cada esquina
  }
  fclose(filein);
  caminhoMinimo(mapa, 0, loc_incendio, n_esq);
}
