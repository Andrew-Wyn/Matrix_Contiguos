#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int **getmatrixfromfile(int **matrix, int *n){
  //get matrix from txt file
  FILE *file = fopen("matrix.txt", "r");
  char *matrixtxt;
  int c, nm=0;

  if (file == NULL)
    return 0; //could not open file

  matrixtxt = (char*)calloc(1, sizeof(char));

  while ((c = fgetc(file)) != EOF){ //EOF End Of File
    matrixtxt[nm++] = (char) c;
    matrixtxt = (char*) realloc(matrixtxt, sizeof(char)*(nm+1));
  }
  // don't forget to terminate with the null character
  matrixtxt[nm] = '\0';

  int appor = 0, appoc = 0;

  char* token, *end_str = matrixtxt;
  token = (char*)strtok_r(matrixtxt, "\n", &end_str);
  while(token != NULL ) {
    matrix = (int**) realloc(matrix, sizeof(int*)*((++appor)));
    matrix[appor-1] = (int*) calloc(1, sizeof(int));
    int count=0;
    char* token1, *end_token = token;
    token1 = (char*)strtok_r(token, " ", &end_token);
    while(token1 != NULL) {
      matrix[appor-1] = (int*) realloc(matrix[appor-1], sizeof(int)*((++appoc)));
      matrix[appor-1][appoc-1] = atoi(token1);
      token1 = (char*)strtok_r(NULL, " ", &end_token);
    }
    appoc = 0;
    token = (char*)strtok_r(NULL, "\n", &end_str);
  }

  *n = appor;

  return matrix;
}

void printmatrix(int **matrix, int n){
  printf("\n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  int n = 0;
  int fullpippor = 0, fullpippoc = 0; 
  int countrighe = 0, countcolonne = 0;
  int load = 0;

  int **matrix = (int**) calloc(1, sizeof(int*));

  int **congrighe = (int**) calloc(1, sizeof(int*));
  *congrighe = (int*) calloc(3, sizeof(int));

  int **congcolonne = (int**) calloc(1, sizeof(int*));
  *congcolonne = (int*) calloc(3, sizeof(int));

  matrix = getmatrixfromfile(matrix, &n);

  printmatrix(matrix, n);

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      do{
        if(j < n-1){
          if(matrix[i][j] == matrix[i][j+1]){
            congrighe[countrighe][0] = matrix[i][j];
            congrighe[countrighe][1] = i;
            congrighe[countrighe][2]++;
            //printf("++++++++++%d %d %d++++++++++\n", congrighe[countrighe][0], congrighe[countrighe][1], congrighe[countrighe][2]);
            j++;
            load = 1;
          }else{
            if(load){
              //printf("\n\n\n%d %d %d\n", congrighe[countrighe][0], congrighe[countrighe][1], congrighe[countrighe][2]);
              congrighe = (int**) realloc(congrighe, sizeof(int*)*((++countrighe)+2));
              congrighe[countrighe] = (int*) calloc(3, sizeof(int));
              //printf("%d %d %d\n\n\n", congrighe[countrighe-1][0], congrighe[countrighe-1][1], congrighe[countrighe-1][2]);
              load=0;
            }
            break;
          }
        }else{
          if(load && i < n-1){
            //printf("\n\n\n%d %d %d\n", congrighe[countrighe][0], congrighe[countrighe][1], congrighe[countrighe][2]);
            congrighe = (int**) realloc(congrighe, sizeof(int*)*((++countrighe)+1));
            congrighe[countrighe] = (int*) calloc(3, sizeof(int));
            //printf("%d %d %d\n\n\n", congrighe[countrighe-1][0], congrighe[countrighe-1][1], congrighe[countrighe-1][2]);
            load=0;
            fullpippor = 0;
          }
          break;
        }
      }while(1);
    }
    load = 0;
    for(int j=0; j<n; j++){
      do{
        if(j < n-1){
          if(matrix[j][i] == matrix[j+1][i]){
            congcolonne[countcolonne][0] = matrix[j][i];
            congcolonne[countcolonne][1] = i;
            congcolonne[countcolonne][2]++;
            //printf("------------%d %d %d------------\n", congcolonne[countcolonne][0], congcolonne[countcolonne][1], congcolonne[countcolonne][2]);
            j++;
            load = 1;
          }else{
            if(load){
              //printf("\n\n\n-%d %d %d-\n", congcolonne[countcolonne][0], congcolonne[countcolonne][1], congcolonne[countcolonne][2]); 
              congcolonne = (int**) realloc(congcolonne, sizeof(int*)*(++countcolonne+1));//fix realloc with the pointers
              congcolonne[countcolonne] = (int*) calloc(3, sizeof(int));
              //printf("-%d %d %d-\n\n\n", congcolonne[countcolonne-1][0], congcolonne[countcolonne-1][1], congcolonne[countcolonne-1][2]);
              load=0;
            }
            break;
          }
        }else{
          if(load && i< n-1){
            //printf("\n\n\n%d %d %d\n", congcolonne[countcolonne][0], congcolonne[countcolonne][1], congcolonne[countcolonne][2]);
            congcolonne = (int**) realloc(congcolonne, sizeof(int*)*(++countcolonne+1));
            congcolonne[countcolonne] = (int*) calloc(3, sizeof(int));
            //printf("%d %d %d\n\n\n", congcolonne[countcolonne-1][0], congcolonne[countcolonne-1][1], congcolonne[countcolonne-1][2]);
            load=0;
            fullpippoc = 0;
          }
          break;
        }
      }while(1);
    } 
  }

  fflush(stdout);

  if(fullpippor) countrighe++; 
  if(fullpippoc) countcolonne++;
  
  //TODO: stampare in ordine i risultati/ aggiungere il numero di occorrenze da stampare

  for(int i=0; i<countrighe; i++){
    printf("il numero: %d si ripete orizontalmente nella righa: %d per: %d volte\n", congrighe[i][0], congrighe[i][1]+1, congrighe[i][2]+1);
  }

  for(int i=0; i<countcolonne; i++){
    printf("il numero: %d si ripete verticalmente nella colonna: %d per: %d volte\n", congcolonne[i][0], congcolonne[i][1]+1, congcolonne[i][2]+1);
  }

  return 0;
}
