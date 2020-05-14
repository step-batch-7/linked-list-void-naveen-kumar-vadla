#include <stdio.h>
#include "../linkedlist.h"
#include "../utils.h"
#include "test.h"

Status assert_integer(int actual, int expected)
{
  return actual == expected;
}

Status assert_list(List_ptr actual, List_ptr expected, Matcher matcher)
{
  Status status = assert_integer(actual->length, expected->length);
  Node_ptr actual_p_walk = actual->first;
  Node_ptr expected_p_walk = expected->first;
  while (actual_p_walk != NULL && expected_p_walk != NULL)
  {
    status = status && (*matcher)(actual_p_walk->element, expected_p_walk->element);
    actual_p_walk = actual_p_walk->next;
    expected_p_walk = expected_p_walk->next;
  }
  return status;
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
  status = status && match_int_elements(node->element, element);
  status = status && node->next == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should create a node and set its element to given element and next to NULL");
}

void test_add_to_list(List_ptr list)
{
  PRINT_STRING("\nadd_to_list");

  Element element = create_int_element(1);
  int status = assert_integer(add_to_list(list, element), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning if list is empty");

  element = create_int_element(2);
  status = assert_integer(add_to_list(list, element), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 1);
  status = status && assert_integer(list->length, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the end of the list");

  clear_list(list);
}

void test_add_to_start(List_ptr list)
{
  PRINT_STRING("\nadd_to_start");

  Element element = create_int_element(1);
  int status = assert_integer(add_to_start(list, element), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning of the list and make both head and last points the same node if list is empty");

  element = create_int_element(2);
  status = assert_integer(add_to_start(list, element), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 2);
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
  Status status = match_int_elements(node->element, element1);
  display_pass_or_fail(status);
  PRINT_STRING("should give the first node for position 0");

  node = get_node_at(list, 2);
  status = match_int_elements(node->element, element3);
  display_pass_or_fail(status);
  PRINT_STRING("should give the last node for position as list length");

  node = get_node_at(list, 1);
  status = match_int_elements(node->element, element2);
  display_pass_or_fail(status);
  PRINT_STRING("should give the required node for given position");

  node = get_node_at(list, -1);
  status = node == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should give NULL for position below 0");

  node = get_node_at(list, 3);
  status = node == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should give NULL for position above list count");

  clear_list(list);
}

void test_insert_at(List_ptr list)
{
  add_to_list(list, create_int_element(1));
  add_to_list(list, create_int_element(2));

  PRINT_STRING("\ninsert_at");

  Element element = create_int_element(3);
  int status = assert_integer(insert_at(list, element, 2), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 2);
  status = status && assert_integer(list->length, 3);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the end of the list");

  element = create_int_element(0);
  status = assert_integer(insert_at(list, element, 0), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 4);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the beginning of the list");

  element = create_int_element(6);
  status = assert_integer(insert_at(list, element, 2), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 2);
  status = status && assert_integer(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number at the given position of the list");

  element = create_int_element(9);
  status = assert_integer(insert_at(list, element, 9), Failure);
  status = status && assert_integer(search_node(list, element, &match_int_elements), -1);
  status = status && assert_integer(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should not add the given number if the given position is below 0");

  element = create_int_element(9);
  status = assert_integer(insert_at(list, element, -9), Failure);
  status = status && assert_integer(search_node(list, element, &match_int_elements), -1);
  status = status && assert_integer(list->length, 5);
  display_pass_or_fail(status);
  PRINT_STRING("should not add the given number if the given position is above list count");

  clear_list(list);
}

void test_reverse(List_ptr list)
{
  PRINT_STRING("\nreverse");

  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  Element element3 = create_int_element(3);
  List_ptr expected = create_list();

  List_ptr actual = reverse(list);
  Status status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give reversed empty list for given empty list");

  add_to_list(list, element1);
  add_to_start(expected, element1);

  actual = reverse(list);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give the same list for given list with single element");

  add_to_list(list, element2);
  add_to_start(expected, element2);

  actual = reverse(list);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give the reversed list for given list with two elements");

  add_to_list(list, element3);
  add_to_start(expected, element3);

  actual = reverse(list);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give the reversed list for given list with more than two elements");

  clear_list(list);
}

void test_search_node(List_ptr list)
{
  Element element = create_int_element(1);
  add_to_list(list, element);

  PRINT_STRING("\nsearch_node");

  int status = assert_integer(search_node(list, element, &match_int_elements), 0);
  display_pass_or_fail(status);
  PRINT_STRING("should give the position if the item is present in the list");

  element = create_int_element(2);
  status = assert_integer(search_node(list, element, &match_int_elements), -1);
  display_pass_or_fail(status);
  PRINT_STRING("should give -1 if the item is not present in the list");

  clear_list(list);
}

void test_remove_from_start(List_ptr list)
{
  Element element = create_int_element(1);
  add_to_list(list, element);

  PRINT_STRING("\nremove_from_start");

  Element actual = remove_from_start(list);
  int status = match_int_elements(actual, element);
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the first item from the list and give");

  actual = remove_from_start(list);
  status = actual == NULL;
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove the item from the list if the list is empty and give NULL");

  clear_list(list);
}

void test_remove_from_end(List_ptr list)
{
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  add_to_list(list, element1);
  add_to_list(list, element2);

  PRINT_STRING("\nremove_from_end");

  Element actual = remove_from_end(list);
  int status = match_int_elements(actual, element2);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the last item from the list");

  actual = remove_from_end(list);
  status = match_int_elements(actual, element1);
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the first item from the list if there is only one item");

  actual = remove_from_end(list);
  status = actual == NULL;
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove the item from the list if the list is empty and give NULL");

  clear_list(list);
}

void test_add_unique(List_ptr list)
{
  PRINT_STRING("\nadd_unique");

  Element element = create_int_element(1);

  int status = assert_integer(add_unique(list, element, &match_int_elements), Success);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should add the given number in the list if not exists");

  status = assert_integer(add_unique(list, element, &match_int_elements), Failure);
  status = status && assert_integer(search_node(list, element, &match_int_elements), 0);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should not add the given number in the list if exists");

  clear_list(list);
}

void test_clear_list(List_ptr list)
{
  add_to_list(list, create_int_element(1));

  PRINT_STRING("\nclear_list");

  int status = assert_integer(clear_list(list), Success);
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should clear the list and set to zero");

  status = assert_integer(clear_list(list), Failure);
  status = status && assert_integer(list->length, 0);
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
  test_search_node(list);

  test_add_to_list(list);
  test_add_to_start(list);
  test_insert_at(list);

  test_reverse(list);

  test_remove_from_start(list);
  test_remove_from_end(list);

  test_add_unique(list);

  test_clear_list(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  return 0;
}