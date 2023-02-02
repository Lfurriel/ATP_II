#include <stdio.h>
int comb = 0;

void combinationUtil(int arr[], int data[], int start, int end, int index, int r){
  int i, j;

  if (index == r) {
    /*for (j=0; j<r; j++){
        p*/
    comb++;
    //printf("\nA\n");
    return;
  }
 
  for (i=start; i<=end && end-i+1 >= r-index; i++) {
    data[index] = arr[i];
    combinationUtil(arr, data, i+1, end, index+1, r);
  }
}

void printCombination(int arr[], int n, int r){
  int data[r];
 
  combinationUtil(arr, data, 0, n-1, 0, r);
}
 
int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int r;
  int n = sizeof(arr)/sizeof(arr[0]);

  for(r = 20; r > 0; r--){
    printCombination(arr, n, r);
  }
  printf("combinacoes: %d", comb);
  
}