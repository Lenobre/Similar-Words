#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief
 * Estrutura do nó
 * char de 46
 * Node apontando para o próximo nó
 */
struct Node
{
  char data[46];
  struct Node *next;
};

typedef struct Node Node;

/**
 * @brief
 *
 * @return Node* Retorna um ponteiro para memória onde há o primeiro nó
 */
Node *setupList()
{
  Node *node = calloc(1, sizeof(Node));

  if (node == NULL)
  {
    exit(EXIT_FAILURE);
  }

  return node;
}

/**
 * @brief
 *
 * @param list Ponteiro para lista
 * @param value Valor a ser inserido
 * @return int Status, sendo 0 como uma inserção falha e 1 para inserções relalizadas
 */
int insertList(Node *list, const char value[47])
{
  // Se os ponteiros forem nulos retorna 0
  if (list == NULL)
    return 0;

  // Percorre todos os nodes até encontrar um vazio
  Node *currentNode = list;
  while (currentNode->next != NULL)
  {
    currentNode = currentNode->next;
  }

  if (currentNode->data[0] == '\0')
  {
    strcpy(currentNode->data, value);
    return 1;
  }

  Node *newNode = setupList();
  strcpy(newNode->data, value);

  currentNode->next = newNode;

  return 1;
}

/**
 * @brief
 *
 * @param filename Nome do arquivo a ser lido, necessário estar presente em /data
 * @param input Entrada inseria pelo usuário, a ser válidado com o txt
 * @return Node* Retorna uma lista com as palavras válidas
 */
Node *readFileInsert(char *filename, const char *input)
{
  if (strlen(filename) == 0 || input[0] == '\0')
    exit(EXIT_FAILURE);

  char path[100];
  sprintf(path, "./data/%s", filename);

  FILE *file = fopen(path, "r");

  if (file == NULL)
    exit(EXIT_FAILURE);

  Node *list = setupList();
  char buffer[47];
  int i, isValid;
  while (fgets(buffer, 47, file) != NULL)
  {
    i = 0;
    isValid = 0;
    buffer[strcspn(buffer, "\n")] = '\0';

    for (i = 0; i < strlen(buffer); i++)
    {
      if (strchr(input, buffer[i]) == NULL)
      {
        isValid = 0;
        break;
      }

      isValid = 1;
    }

    for (i = 0; i < strlen(input); i++)
    {
      if (strchr(buffer, input[i]) == NULL)
      {
        isValid = 0;
        break;
      }
    }

    if (isValid == 1)
    {
      insertList(list, buffer);
    }
  }

  fclose(file);

  return list;
}

/**
 * @brief
 *
 * @param list Lista encadeada a ser printda (Ao mesmo tempo é feito um free)
 * @return int retorna 0 se houver algo de errado e 1 se tudo ocorreu bem
 */
int printLinkedList(Node *list)
{
  if (list == NULL)
    return 0;

  Node *current = list;
  Node *nextNode;
  while (current != NULL)
  {
    nextNode = current->next;
    printf("%s\n", current->data);
    free(current);
    current = nextNode;
  }

  return 1;
}
