#ifndef __HEADER__
#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void bar() {
  printf("----------\n");
}

typedef struct Node {
  int val;
  struct Node *next;
  struct Node *prev;
  size_t len;
} Node;

Node *getElement(Node *liste, size_t pos) {
  int ret;
  Node *temp = liste;
  for (size_t i = 0; i < pos; i++) {
    if (i == pos - 1)
      return temp;
    if (temp->next != NULL)
      temp = temp->next;
    else if (temp->next == NULL)
      break;
  }
}

Node *getFirstElement(Node *liste) {
  Node *ret = liste;
  while (ret->prev != NULL) {
    ret = ret->prev;
  }
  return ret;
}

void display(Node *liste) {
  Node *temp = liste;
  if (temp->prev != NULL) {
    temp = getFirstElement(temp);
  }
  while (temp != NULL) {
    printf("display list %d\n", temp->val);
    temp = temp->next;
  }
  free(temp);
}

Node *init(int val) {
  Node *ret = malloc(sizeof(Node));
  ret->val = val;
  ret->next = NULL;
  ret->prev = NULL;
  ret->len = 1;
  return ret;
  free(ret);
}

Node *getLastElement(Node *liste) {
  size_t len = liste->len;
  int ret;
  Node *temp = liste;
  for (size_t i = 0; i < len; i++) {
    if (i == len - 2)
      return temp;
    temp = temp->next;
  }
  free(temp);
}

int getLastElementVal(Node *liste) {
  size_t len = liste->len;
  int ret;
  Node *temp = liste;
  for (size_t i = 0; i < len; i++) {
    if (i == len - 1) return temp->val;
    temp = temp->next;
  }
  free(temp);
}

void updateLen(Node *node, size_t len) {
  while (node != NULL) {
    node->len = len;
    node = node->prev;
  }
}

void updateLenBackward(Node *node, size_t len) {
  while (node != NULL) {
    node->len = len;
    node = node->next;
  }
}

Node *add(Node *prev, int val) {
  Node *newNode = malloc(sizeof(Node));
  newNode->prev = prev;
  newNode->next = NULL;
  newNode->val = val;
  prev->next = newNode;
  newNode->len = prev->len + 1;
  updateLen(newNode, newNode->len);
  return newNode;
  free(newNode);
}

Node *addFirst(Node *next, int val) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = val;
  newNode->next = next;
  newNode->prev = NULL;
  next->prev = newNode;
  newNode->len = next->len + 1;
  updateLenBackward(newNode, newNode->len);
  return newNode;
  free(newNode);
}

Node *removeElement(Node *liste, size_t pos) {
  if (liste->len == 1) 
    return NULL;
  if (pos == 0) {
    liste = liste->next;
    Node *ret = init(liste->val);
    Node *temp = ret;
    liste = liste->next;
    size_t k = 1;
    while (liste != NULL) {
      if (k != pos) {
        Node *newNode = add(temp, liste->val);
        temp = newNode;
      }
      liste = liste->next;
      k++;
    }
    return ret;
    free(ret);
  }
  else {
    Node *ret = init(liste->val), *temp = ret;
    liste = liste->next;
    size_t k = 1;
    while (liste != NULL) {
      if (k != pos) {
        Node *newNode = add(temp, liste->val);
        temp = newNode;
      }
      liste = liste->next;
      k++;
    }
    return ret;
    free(ret);
  }
}

Node *liste(int *liste, size_t len) {
  Node *ret = init(liste[0]);
  Node *temp = ret;
  for (size_t i = 1; i < len; i++) {
    Node *newNode = add(temp, liste[i]);
    temp = newNode;
  }
  return ret;
  free(ret);
}

Node **cutHalf(Node *original) {
  Node *first = init(original->val); 
  Node *temp = first;
  size_t len = floor(original->len / 2),
         max = original->len;
  for (size_t i = 1; i < len; i++) {
    original = original->next;
    Node *newNode = add(temp, original->val);
    temp = newNode;
  }
  original = original->next;
  Node *second = init(original->val); 
  Node *temp2 = second;
  for (size_t i = len + 1; i < max; i++) {
    original = original->next;
    Node *newNode = add(temp2, original->val);
    temp2 = newNode;
  }

  Node *ret[2] = {first, second};
  return ret;
  free(first);
  free(second);
}

#endif
