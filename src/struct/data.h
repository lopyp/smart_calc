#ifndef STASH_H
#define STASH_H

typedef struct list {
  double value;
  double x;
  char op;
  int type;
  struct list *next;
} list_t;

int push(list_t **head, char value);
int pushDouble(list_t **head, double value);
int popChar(list_t **head, char *value);
int peek(const list_t *head, char *head_val);
void printNode(const list_t *head);
int popDouble(list_t **head, double *value);
list_t *init(char a);

void pushBackChar(list_t **head, char value);
void pushBackDouble(list_t **head, double value);
list_t *getLastelem(list_t *head);

#endif
