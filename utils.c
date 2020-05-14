#include "linkedlist.h"
#include "utils.h"

Element create_int_element(int value)
{
  Element element = malloc(sizeof(int));
  *(int *)element = value;
  return element;
}

void display_int_element(Element number)
{
  printf("%d ", *(int *)number);
}

Status match_int_elements(Element element_one, Element element_two)
{
  return *(int *)element_one == *(int *)element_two;
}