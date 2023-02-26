#include <stdio.h>
#include <stdlib.h>

// linked list of free mem
typedef struct header_free {
  int size;
  unsigned int flag_occ:1;
  struct header_free *next;
  struct header_free *prev;
} header_free;

header_free *init(int value) {
  header_free *ret = malloc(sizeof(*ret));
  ret->size = value;
  ret->flag_occ = 0;
  ret->next = NULL;
  ret->prev = NULL;
  return ret;
  free(ret);
}

// the pointer always points to the last member
header_free *push(header_free *list, int sizeFreed) {
  header_free *new = malloc(sizeof(*new));
  list->next = new;
  new->prev = list;
  new->size = sizeFreed;
  new->flag_occ = 0;
  new->next = NULL;
  list = new;
  return new;
  free(new);
}

void display(header_free *liste) {
  header_free *temp = liste;
  while (temp != NULL) {
    printf("%d\n", temp->size);
    temp = temp->prev;
  }
}

void display2(header_free *liste) {
  header_free *temp = liste;
  while (temp != NULL) {
    printf("%d\n", temp->size);
    temp = temp->next;
  }
}

header_free *pop(header_free *block) {
  block->flag_occ ^= 1;
  if (block->next == NULL && block->prev != NULL) {
    block->prev->next = block->next;
    block->prev = NULL;
  }
  else if (block->prev == NULL && block->next != NULL) {
    block->next->prev = block->prev;
    block->next = NULL;
  }
  else if (block->prev == NULL && block->next == NULL) {
    return block;
  }
  else {
    block->prev->next = block->next;
    block->next->prev = block->prev;
    block->prev = NULL;
    block->next = NULL;
  }
  return block;
}

// search algo for best fit
header_free *minSearch(header_free *list, int requestSize) {
  int diff, k = 0;
  header_free *ret = malloc(sizeof(*ret)),
              *temp = list;
  while (temp != NULL) {
    if ((k == 0 && temp->size - requestSize >= 0) ||
        (k > 0 && temp->size - requestSize >= 0 && diff > temp->size - requestSize)) {
      diff = temp->size - requestSize;
      ret = temp;
      if (diff == 0)
        break;
      if (k == 0)
        k++;
    }
    temp = temp->prev;
  }
  ret = pop(ret);
  return ret;
  free(ret);
}

// split within the list finding a block with his size
header_free *split(header_free *list, int block, int newSize) {
  if (newSize > block)
    exit(-1);
  header_free *sub1 = init(block - newSize),
              *sub2 = init(newSize);
  while (list->size != block)
    list = list->prev;
  if (list->next == NULL) {
    sub1->next = sub2;
    sub1->prev = list->prev;
    sub2->prev = sub1;
    list->prev->next = sub1;
  }
  else if (list->prev == NULL) {
    sub1->next = sub2;
    sub2->next = list->next;
    sub2->prev = sub1;
    list->next->prev = sub2;
   }
  else if (list->prev == NULL && list->next == NULL) {
    sub1->next = sub2;
    sub2->prev = sub1;
  }
  else {
    sub1->next = sub2;
    sub1->prev = list->prev;
    sub2->next = list->next;
    sub2->prev = sub1;
    list->prev->next = sub1;
    list->next->prev = sub2;
  }
  sub2 = pop(sub2);
  return sub2;
}

// splits where the header_free pointer points to
header_free *splitPoint(header_free *list, int newSize) {
  if (list->next == NULL)
    exit(-1);
  header_free *sub1 = init(list->size - newSize),
              *sub2 = init(newSize);
  if (list->next == NULL) {
    sub1->next = sub2;
    sub1->prev = list->prev;
    sub2->prev = sub1;
    list->prev->next = sub1;
  }
  else if (list->prev == NULL) {
    sub1->next = sub2;
    sub2->next = list->next;
    sub2->prev = sub1;
    list->next->prev = sub2;
   }
  else if (list->prev == NULL && list->next == NULL) {
    sub1->next = sub2;
    sub2->prev = sub1;
  }
  else {
    sub1->next = sub2;
    sub1->prev = list->prev;
    sub2->next = list->next;
    sub2->prev = sub1;
    list->prev->next = sub1;
    list->next->prev = sub2;
  }
  sub2 = pop(sub2);
  return sub2;
}

// coalesces the 2 following blocks (fifo order)
void coalesce(header_free *list) {
  if (list->next == NULL)
    exit(-1);
  list->size = list->size + list->next->size;
  list->next = list->next->next;
  list->next->next->prev = list;
  free(pop(list->next));
}

int main() {
  header_free *liste = init(111);
  header_free *liste1 = push(liste, 22);
  header_free *liste2 = push(liste1, 202);
  header_free *liste3 = push(liste2, 2);
  header_free *liste4 = push(liste3, 288);
  header_free *liste5 = push(liste4, 2288);
  header_free *liste6 = push(liste5, 200);
  display(liste6);
  header_free *s = split(liste6, 202, 10);
  coalesce(liste3);
  printf("-------\n");
  display(liste6);
}
