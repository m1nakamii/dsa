#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libraries/hashtab.h"
#include "../libraries/header.h"

unsigned int hashtab_hash(char *key) {
  unsigned int h = 0, hash_mul = 31;
  while (*key)
    h = h * hash_mul + (unsigned int)*key++;
  return h % Hashtab_Size;
}

unsigned int fnv1_32(const void *data, size_t n) {
  const unsigned int fnv_prime = 0x01000193;
  unsigned int hash = 0x811c9dc5;
  const unsigned char *d = (const unsigned char *)data;
  size_t i;
  for (i = 0; i < n; i++) {
    hash = hash * fnv_prime;
    hash = hash ^ d[i];
  }
  return hash;
}

unsigned int AddHash(char *s) {
  unsigned int h = 0;
  while (*s)
    h += (unsigned int)*s++;
  return h % Hashtab_Size;
}

void hashtab_init(struct listnode **hashtab) {
  int i;
  for (i = 0; i < Hashtab_Size; i++)
    hashtab[i] = NULL;
}
void hashtab_add(struct listnode **hashtab, char *key, int value) {
  struct listnode *node;

  int index = hashtab_hash(key);
  node = (struct listnode *)malloc(sizeof(*node));

  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->next = hashtab[index];
    hashtab[index] = node;
  }
}

void hashtab_add_Add(struct listnode **hashtab, char *key, int value) {
  struct listnode *node;

  unsigned int index = AddHash(key);
  node = (struct listnode *)malloc(sizeof(*node));

  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->next = hashtab[index];
    hashtab[index] = node;
  }
}

struct listnode *hashtab_lookup_Add(struct listnode **hashtab, char *key) {
  struct listnode *node;

  int index = AddHash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
      return node;
  }
  return NULL;
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key) {
  struct listnode *node;

  int index = hashtab_hash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
      return node;
  }
  return NULL;
}
void hashtab_delete(struct listnode **hashtab, char *key) {
  struct listnode *node, *prev = NULL;
  int index = hashtab_hash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key)) {
      if (prev == NULL)
        hashtab[index] = node->next;
      else
        prev->next = node->next;
      free(node);
      return;
    }
    prev = node;
  }
}

int get_collisions(struct listnode **hashtab) {
  int count = 0;
  for (int i = 0; i < Hashtab_Size; i++) {
    for (struct listnode *j = !hashtab[i] ? NULL : hashtab[i]->next; j != NULL;
         j = j->next) {
      count += 1;
    }
  }
  return count;
}

void free_table(struct listnode **hashtab) {
  for (int i = 0; i < Hashtab_Size; i++) {
    struct listnode *current = hashtab[i];
    while (current != NULL) {
      struct listnode *temp = current;
      current = current->next;
      free(temp);
    }
  }
}