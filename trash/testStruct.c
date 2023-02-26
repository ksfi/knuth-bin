#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int v;
  struct node *next;
  struct node *prev;
} node;

node *init(int val) {
  node *ret = malloc(sizeof(*ret));
  ret->v = val;
  ret->next = NULL;
  ret->prev = NULL;
  return ret;
  free(ret);
}

push(node *list, int val) {
  node *new = init(val);
  new->prev = list;
  list->next = new;
  return new;
  free(new);
}

void display(node *a) {
  node *temp = a;
  while (temp != NULL) {
    printf("%d\n", temp->v);
    temp = temp->prev;
  }
}

int main() {
  node *a = init(34);
  node *b = push(333);
  node *c = push(276);
  node *d = push(90);
  display(a);
}
