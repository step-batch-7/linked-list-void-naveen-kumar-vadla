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

void test_get_node_at(List_ptr list)
{
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  Element element3 = create_int_element(3);
  add_to_list(list, element1);
  add_to_list(list, element2);
  add_to_list(list, element3);

  PRINT_STRING("\nget_node_at");

  Node_ptr node = get_node_at(list, 0);
  Status status = node->element == element1;
  display_pass_or_fail(status);
  PRINT_STRING("should give the first node for position 0");

  node = get_node_at(list, 2);
  status = node->element == element3;
  display_pass_or_fail(status);
  PRINT_STRING("should give the last node for position as list length");

  node = get_node_at(list, 1);
  status = node->element == element2;
  display_pass_or_fail(status);
  PRINT_STRING("should give the required node for given position");

  node = get_node_at(list, -1);
  status = node == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should give NULL for position below 0");

  node = get_node_at(list, 3);
  status = node == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should give NULL for position above 0");

  clear_list(list);
}

void test_insert_at(List_ptr list)
{
  add_to_list(list, create_int_element(1));
  add_to_list(list, create_int_element(2));

  PRINT_STRING("\ninsert_at");

  int status = assert(insert_at(list, create_int_element(3), 2), Success);
  status = status && assert(list->length, 3);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the end of the list");

  status = assert(insert_at(list, create_int_element(0), 0), Success);
  status = status && assert(list->length, 4);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning of the list");

  status = assert(insert_at(list, create_int_element(6), 2), Success);
  status = status && assert(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the given position of the list");

  status = assert(insert_at(list, create_int_element(9), 9), Failure);
  status = status && assert(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should not add the given number if the given position is below 0");

  status = assert(insert_at(list, create_int_element(9), -9), Failure);
  status = status && assert(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should not add the given number if the given position is above list count");

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

  test_get_node_at(list);

  test_add_to_list(list);
  test_add_to_start(list);
  test_insert_at(list);

  test_clear_list(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  return 0;
}