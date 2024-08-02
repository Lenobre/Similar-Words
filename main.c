#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "linkedList.h"
#include <string.h>

int main(void)
{
  while (1)
  {
    printf("Insira a palavra a ser validada: ");

    char *input = malloc(47);

    if (input == NULL)
    {
      return 1;
    }
 
    scanf("%47s", input);
    
    Node *list = readFileInsert("palavras.txt", input);

    if (strlen(list->data) == 0)
      printf("Nao foi possivel encontrar nenhum resultado.");
    else
      printLinkedList(list);

    free(input);

    getchar();
    getchar();

    system("cls");
  }

  return 0;
}
