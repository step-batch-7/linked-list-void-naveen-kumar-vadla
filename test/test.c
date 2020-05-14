#include <stdio.h>
#include "../linkedlist.h"
#include "../utils.h"
#include "test.h"

int assert(int actual, int expected)
{
  return actual == expected;
}

void display_pass_or_fail(int status)
{
  status ? printf(PASS) : printf(FAIL);
  status ? PASSING_TESTS++ : FAILING_TESTS++;
}

void test_create_list(void)
{
  PRINT_STRING("\ncreate_list");

  List_ptr list = create_list();
  Status status = list != NULL;
  status = status && list->first == NULL;
  status = status && list->last == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should create a list and set its first and last to NULL");
}

void test_create_node(void)
{
  PRINT_STRING("\ncreate_node");

  Element element = create_int_element(1);
  Node_ptr node = create_node(element);
  Status status = node != NULL;
  status = status && node->element == element;
  status = status && node->next == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should create a node and set its element to given element and next to NULL");
}

void test_add_to_list(List_ptr list)
{
  PRINT_STRING("\nadd_to_list");

  int status = assert(add_to_list(list, create_int_element(1)), Success);
  status = status && assert(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning if list is empty");

  status = assert(add_to_list(list, create_int_element(2)), Success);
  status = status && assert(list->length, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the end of the list");

  clear_list(list);
}

void test_add_to_start(List_ptr list)
{
  PRINT_STRING("\nadd_to_start");

  int status = assert(add_to_start(list, create_int_element(1)), Success);
  status = status && assert(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning of the list and make both head and last points the same node if list is empty");

  status = assert(add_to_start(list, create_int_element(2)), Success);
  status = status && assert(list->length, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning of the list and modify nodes next if list is not empty");

  clear_list(list);
}

void test_clear_list(List_ptr list)
{
  add_to_list(list, create_int_element(1));

  PRINT_STRING("\nclear_list");

  int status = assert(clear_list(list), Success);
  status = status && assert(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should clear the list and set to zero");

  status = assert(clear_list(list), Failure);
  status = status && assert(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not clear the list if it is an empty list");
}

int main(void)
{
  List_ptr list = create_list();
  if (list == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    return 0;
  }

  test_create_list();
  test_create_node();

  test_add_to_list(list);
  test_add_to_start(list);

  test_clear_list(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  return 0;
}