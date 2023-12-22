#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bubble (int *, int);
int selection (int *, int);
int insertion (int *, int);
void geraNumeros(int *, int);
void imprimir(int *, int, int);
void copiar(int *, int *, int);
void tabela(int , int , int );

int bubble (int vetor[], int total) {
    clock_t tempo;
    int i, j, tmp;

    tempo = clock();
    for (i= 0; i < total; i++) {
        for (j= i+1; j < total; j++) {
            if (vetor[i] > vetor[j]) {
                tmp= vetor[i];
                vetor[i]= vetor[j];
                vetor[j]= tmp;
            }
        }
    }
    tempo = clock() - tempo;
    return tempo;
}

int selection (int vetor[], int total) {
  clock_t tempo;
	int i, j, posMin, min, troca;

  tempo = clock();
	for (i= 0; i < total-1; i++) {
		troca= 0;
		posMin= i;
		min= vetor[i];
		for (j= i+1; j < total; j++) {
			if (vetor[j] < min) {
				posMin= j;
				min= vetor[j];
				troca= 1;
			}
		}
		if (troca) {
			vetor[posMin]= vetor[i];
			vetor[i]= min;
		}
	}
  tempo = clock() - tempo;
  return tempo;
}

int insertion (int vetor[], int total) {
  clock_t tempo;
	int i, j, tmp;

  tempo = clock();
	for (i= 1; i < total; i++) {
		tmp= vetor[i];
		for (j= i-1; j >= 0 && tmp < vetor[j]; j--) {
			vetor[j+1]= vetor[j];
		}
		vetor[j+1]= tmp;
	}
  tempo = clock() - tempo;
  return tempo;
}

//geral numeros fora de sequencia sem repetir.
void geraNumeros(int *vetor, int total) {

  srand(time(NULL));
	int i=0, j, igual;

  do{
    vetor[i] = rand()%total;
    igual=0;
    for(j=0; j<i; j++){
      if(vetor[j]==vetor[i]){
        igual=1;
      }
    }
    if(igual==0){
        i++;
    }
  }while(i < total);
}

void copiar(int *copia, int *vetor, int total){
  int i;
  for(i=0; i < total; i++){
    copia[i] = vetor[i];
  }
}

void imprimir(int *vetor, int total, int tempo){
  int i=0;
  for (i; i < total; i++){
      printf("%3i|", vetor[i]);
  }
  printf("\n");
  if(tempo != 0 ){
    printf("Tempo de Ordenacao:%f\n\n",((float)tempo)/CLOCKS_PER_SEC );
  }else{
    printf("\n\n");
  }
}

void tabela(int tBubble, int tSelection, int tInsertion){
  int menor, maior;
  char *strMenor = (char *)malloc(20 * sizeof(strMenor));
  char *strMaior = (char *)malloc(20 * sizeof(strMaior));
  printf("------ Tabela do tempo ------\n");
  printf("Bubble     |Selection  |Insertion  \n");
  printf("%-11f %-11f %-11f \n\n",((float)tBubble)/CLOCKS_PER_SEC,((float)tSelection)/CLOCKS_PER_SEC,((float)tInsertion)/CLOCKS_PER_SEC);

  maior = tInsertion;
  menor = tBubble;
  strMenor = "Bubble";
  strMaior = "Insertion";

  if(menor > tSelection){
    menor = tSelection;
    strMenor = "Selection";
  }
  if(menor > tInsertion){
    menor = tInsertion;
    strMenor = "Insertion";
  }
  if(maior < tSelection){
    maior = tSelection;
    strMaior = "Selection";
  }
  if(maior < tBubble){
    maior = tBubble;
    strMaior = "Bubble";
  }

  printf("O ordenacao mais rapida: %s\n",strMenor);
  printf("O ordenacao mais lenta : %s\n",strMaior);

}



main() {
  int tamanho, opcao;
  
  printf("Escolha o tamanho que sera o vetor desordenado *obs numero inteiro :");
  scanf("%i", &tamanho);

  int vetor[tamanho], vBubble[tamanho], vSelection[tamanho], vInsertion[tamanho];

  geraNumeros(vetor, tamanho );
  copiar(vBubble, vetor, tamanho);
  copiar(vSelection, vetor, tamanho);
  copiar(vInsertion, vetor, tamanho);

  int tBubble = bubble(vBubble, tamanho);
  int tSelection = selection(vSelection, tamanho);
  int tInsertion = insertion(vInsertion, tamanho);

  printf("\n\nElementos fora de Ordem sem repetir.\n");
  imprimir(vetor, tamanho, 0);

  while(1){
    printf("Escolha uma opcao de Ordenacao de dados:\n");
    printf("1-Ordenacao Bubblesort.\n");
    printf("2-Ordenacao Selectionsort.\n");
    printf("3-Ordenacao Insertionsort.\n");
    printf("Opcao ?:");
    scanf("%i", &opcao);
    printf("\n");

    switch (opcao){
      case 1: //Bubblesort
        printf(">> Voce escolheu Bubblesort <<\n");
        imprimir(vBubble, tamanho, tBubble);
        tabela(tBubble, tSelection, tInsertion);
        exit(0);

      case 2: //Selectionsort
        printf(">> Voce escolheu Selection <<\n");
	      imprimir(vSelection, tamanho, tSelection);
        tabela(tBubble, tSelection, tInsertion);
        exit(0);

      case 3: // Insertionsort
        printf(">> Voce escolheu Insertion <<\n");
        imprimir(vInsertion, tamanho, tInsertion);
        tabela(tBubble, tSelection, tInsertion);
        exit(0);

      default: printf("Opcao invalida!\n\n");
    }

  }

}
