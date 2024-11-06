// Bruno Antico Galin | 10417318 
// Gabriel Lazareti Cardoso | 10417353 
// Guilherme Martins Silva | 10417140 
// Ismael de Sousa e Silva | 10410870 
// Referência: https://www.youtube.com/watch?v=pWrNOkw50As&pp=ygUNZGppa3N0cmEgZW0gYw%3D%3D
// Referência: https://www.youtube.com/watch?v=5y8dch2uHR4&pp=ygUNZGppa3N0cmEgZW0gYw%3D%3D
// Referência: https://www.youtube.com/watch?v=yrMnrJzgJg4
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ESQ 100
#define MAX_VAL 999

void RotaMaisRapida(int mapa[MAX_ESQ][MAX_ESQ], int inicio, int fim, int n_esq, FILE *fileout){
  //Inicialização de varíaveis distância, visitado e rota
  int distancia[MAX_ESQ];
  bool visitado[MAX_ESQ];
  int rota[MAX_ESQ];
  for(int i = 0; i < n_esq; i++){ //Inicialização de todas as distâncias como infinito, visitado como falso, e rota -1 (já que não tem rota prévia)
    distancia[i] = MAX_VAL;
    visitado[i] = false;
    rota[i] = -1;
  }
  distancia[inicio] = 0; //Distância inicial é 0
  
  for (int i = 0; i < n_esq - 1; i++){ //Algoritmo principal de rota mínima
    int esquina = -1;
    int rotaMin = MAX_VAL;
    for (int j = 0; j < n_esq; j++){ //Encontrando a esquina com a menor distância ainda não visitada
      if (!visitado[j] && distancia[j] < rotaMin){
        rotaMin = distancia[j];
        esquina = j;
      }
    }
    if (esquina == -1) break; //Se não houver esquinas disponíveis, quebra o laço
    visitado[esquina] = true; //Marca a esquina como visitada
    for (int k = 0; k < n_esq; k++){ //Atualiza a distância das próximas esquinas
      if (!visitado[k] && mapa[esquina][k] && distancia[esquina] != MAX_VAL && distancia[esquina] + mapa[esquina][k] < distancia[k]){ //Se a esquina não foi visitada, se a distância até ela é menor que a distância
        distancia[k] = distancia[esquina] + mapa[esquina][k]; //Atualiza a distância mínima em k
        rota[k] = esquina; //Armazena a rota vindo da esquina
      }
    }
  }
  printf("\nO resultado está no arquivo 'rotas.txt'.\n");
  if (distancia[fim] == MAX_VAL) fprintf(fileout, "As rotas possíveis acabaram até a esquina %d.\n",fim + 1);  
  else{
    fprintf(fileout, "Rota mais rápida até a esquina %d: ", fim + 1);
    int caminho[MAX_ESQ], last = 0;
    for (int i = fim; i != -1; i = rota[i]) caminho[last++] = i + 1; //Monta a rota do fim até o início
    while (last > 0) fprintf(fileout, "%d ", caminho[--last]); //Exibe a rota mais rápida
    fprintf(fileout, "\nTempo calculado para a rota = %d",distancia[fim]); //Exibe o tempo total calculado para a rota
  }
}

int main(void){
  FILE *filein = fopen("bombeiro.txt","r"); //Leitura do arquivo de entrada
  if (filein == NULL){
    printf("Erro ao abrir o arquivo.");
    return 1;
  }
  FILE *fileout = fopen("rotas.txt","w"); //Escrita no arquivo de saída
  if (fileout == NULL){
    printf("Erro ao abrir o arquivo.");
    return 1;
  }
  int loc_incendio, n_esq, esq1, esq2, tempo;
  int mapa[MAX_ESQ][MAX_ESQ];
  for (int i = 0; i < n_esq; i++){ //Inicializa o mapa e com 0 para o mesmo e infinito para o resto
    for (int k = 0; k < n_esq; k++){
      if (i == k) mapa[i][k] = 0;
      else mapa[i][k] = MAX_VAL;
    }
  }
  fscanf(filein,"%d",&loc_incendio); //Primeira linha tem o local do incêndio
  fscanf(filein,"%d",&n_esq); //Segunda linha tem o número de esquinas
  while (fscanf(filein, "%d" "%d" "%d", &esq1, &esq2, &tempo) == 3){ //Demais linhas tem primeira esquina, segunda esquina, e o tempo da sub-rota
    if (esq1 == 0) break;
    mapa[esq1 - 1][esq2 - 1] = tempo; //Tempo de cada esquina
  }
  fclose(filein);
  printf("---Bombeiros---");
  RotaMaisRapida(mapa, 0, loc_incendio - 1, n_esq, fileout);
  fclose(fileout);
}
