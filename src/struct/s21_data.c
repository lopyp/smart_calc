#include <stdio.h>
#include <stdlib.h>

#include "data.h"

int push(list_t **head, char value) {
  int error = 0;
  list_t *tmp = malloc(sizeof(list_t));
  if (tmp == NULL) {
    error = 1;
  } else {
    tmp->type = 3;
    tmp->next = *head;
    tmp->op = value;
    *head = tmp;
  }
  return error;
}

int pushDouble(list_t **head, double value) {
  int error = 0;
  list_t *tmp = malloc(sizeof(list_t));
  if (tmp == NULL) {
    error = 1;
  } else {
    tmp->type = 1;
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
  }
  return error;
}

int popChar(list_t **head, char *value) {
  list_t *out;
  int error;
  if ((*head) == NULL) {
    error = 2;
  } else {
    out = *head;
    *head = (*head)->next;
    *value = out->op;
    free(out);
  }
  return error;
}

int popDouble(list_t **head, double *value) {
  list_t *out;
  int error;
  if ((*head) == NULL) {
    error = 2;
  } else {
    out = *head;
    *head = (*head)->next;
    *value = out->value;
    free(out);
  }
  return error;
}

int peek(const list_t *head, char *head_val) {
  int error = 0;
  if (head == NULL) {
    error = 2;
  } else {
    *head_val = head->op;
  }
  return error;
}
/*
void printNode(const list_t *head) {
  while (head) {
    if (head->type == 3 || head->type == 2) {
      printf("%c ", head->op);
    } else if (head->type == 1) {
      printf("%lf ", head->value);
    } else if (head->type == 0) {
      printf("||||");
    }
    head = head->next;
  }
  printf("\n");
}
*/
void pushBackChar(list_t **head, char value) {
  list_t *last = getLastelem(*head);
  list_t *tmp = malloc(sizeof(list_t));
  tmp->op = value;
  if (value == 'x')
    tmp->type = 2;
  else
    tmp->type = 3;
  tmp->next = NULL;
  last->next = tmp;
}

void pushBackDouble(list_t **head, double value) {
  list_t *last = getLastelem(*head);
  list_t *tmp = malloc(sizeof(list_t));
  tmp->value = value;
  tmp->type = 1;
  tmp->next = NULL;
  last->next = tmp;
}

list_t *getLastelem(list_t *head) {
  if (head == NULL) {
    return NULL;
  }
  while (head->next) {
    head = head->next;
  }
  return head;
}

list_t *init(char a) {
  list_t *lst;
  lst = malloc(sizeof(list_t));
  lst->value = 0;
  lst->type = 0;
  lst->x = 0;
  lst->op = a;
  lst->next = NULL;
  return (lst);
}
