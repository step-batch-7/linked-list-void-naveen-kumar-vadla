#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

List_ptr create_list(void)
{
  List_ptr linked_list = malloc(sizeof(LinkedList));
  if (linked_list != NULL)
  {
    linked_list->first = NULL;
    linked_list->last = NULL;
    linked_list->length = 0;
  }
  return linked_list;
}

Node_ptr create_node(Element value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  if (new_node != NULL)
  {
    new_node->element = value;
    new_node->next = NULL;
  }
  return new_node;
}

void display_list(List_ptr list, Display_Data displayer)
{
  printf("List => ");
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    (*displayer)(p_walk->element);
    p_walk = p_walk->next;
  }
  printf("\n");
}
