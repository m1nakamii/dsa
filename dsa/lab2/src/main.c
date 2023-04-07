#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

int main() {
  struct listnode *hashtab_KR[Hashtab_Size];
  struct listnode *fnv1_32[Hashtab_Size];

  char words[MaxKeys][MaxKeyLenght];

  struct listnode *node_KR, *node_Add;
  double time_KR = 0.0, time_Add = 0.0;
  clock_t begin, end;

  FILE *file = fopen("words.txt", "r");
  if (!file) {
    return 1;
  }

  for (int i = 0; fgets(words[i], MaxKeyLenght, file) && i < MaxKeys; i++) {
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);

  printf("#\t   KR\t\t fnv \tcolizii_kr\t colizii_fnv\n");
  hashtab_init(hashtab_KR);
  hashtab_init(fnv1_32);

  for (int i = 0; i < MaxKeys; i++) {
    hashtab_add(hashtab_KR, words[i], i);
    hashtab_add_Add(fnv1_32, words[i], i);
    if ((i + 1) % 10000 == 0) {
      char *word = words[0];
      begin = clock();
      node_KR = hashtab_lookup(hashtab_KR, word);
      end = clock();
      begin = clock();
      node_Add = hashtab_lookup_Add(fnv1_32, word);
      end = clock();
      time_Add = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("%d\t %f\t%f\t %d \t%d\n", i + 1, time_KR, time_Add,
             get_collisions(hashtab_KR), get_collisions(fnv1_32));
    }
  }
  free_table(hashtab_KR);
  free_table(fnv1_32);
  return 0;
}