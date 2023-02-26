#include <stdio.h>
#include <stdlib.h>

// #include "header.h"

typedef struct Node {
  int val;
  struct Node *next;
  struct Node *previous;
} Node;

Node *getLast(Node *l) {
  Node *temp = malloc(sizeof(temp));
  while (temp->next != NULL)
    temp = temp->next;
  return temp;
  free(temp);
}

void push(Node *list, int v) {
  Node *temp = getLast(list);
  if (list->previous == NULL) {
    temp->previous = NULL;
    temp->previous = NULL;
    temp->val = v;
  }
  else {
    Node *new = malloc(sizeof(new));
    temp->next = new;
    new->previous = temp;
    new->val = v;
  }
}

typedef struct X {
  int val;
  int count;
  struct X *topStack;
  Node *top;
} X;

// seq
X *pushX(X* seq, int val, int count, Node *top) {
  size_t si = sizeof(X);
  printf("%lu\n", si);
  if (seq->topStack == seq) {
  }
  else {
  }
}

void top(int **input, int *output, int lenInput) {
}

int main() {
  X *seq = malloc(sizeof(seq));
  Node *top = malloc(sizeof(top));
  size_t b = sizeof(X);
  printf("b %lu\n", b);
  pushX(seq, 10, 1, top);
}
