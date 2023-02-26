#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int v;
  struct node *prev;
  struct node *next;
} node;

node *init(int val) {
  node *ret = malloc(sizeof(*ret));
  ret->v = val;
  ret->prev = NULL;
  ret->next = NULL;
  return ret;
}

node *push(node *l, int val) {
  node *ret = malloc(sizeof(*ret));
  ret->v = val;
  ret->prev = l;
  l->next = ret;
  return ret;
}

void displatB(node *liste) {
  node *temp = liste;
  while (temp != NULL) {
    printf("b %d\n", temp->v);
    temp = temp->prev;
  }
}

void displatS(node *liste) {
  node *temp = liste;
  while (temp != NULL) {
    printf("d %d\n", temp->v);
    temp = temp->next;
  }
}

int main() {
  node *l = init(23);
  node *l2 = l;
  l = push(l, 222);
  l = push(l, 34);
  l = push(l, 657);
  displatB(l);
  printf("-----\n");
  displatS(l2);
}
