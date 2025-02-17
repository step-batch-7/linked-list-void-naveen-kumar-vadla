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

void display_pass_or_fail(Status status)
{
  status ? printf(PASS) : printf(FAIL);
  status ? PASSING_TESTS++ : FAILING_TESTS++;
}

void test_create_list(void)
{
  PRINT_STRING("\ncreate_list");

  List_ptr list = create_list();
  if (list == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    exit(12);
  }
  Status status = status && list->first == NULL;
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
  Status status = assert_integer(add_to_list(list, element), Success);
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
  Status status = assert_integer(add_to_start(list, element), Success);
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
  Status status = assert_integer(insert_at(list, element, 2), Success);
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
  if (expected == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    exit(12);
  }

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

  Status status = assert_integer(search_node(list, element, &match_int_elements), 0);
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
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  add_to_list(list, element1);
  add_to_list(list, element2);

  PRINT_STRING("\nremove_from_start");

  Element actual = remove_from_start(list);
  Status status = match_int_elements(actual, element1);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the first item from the list and give");

  actual = remove_from_start(list);
  status = match_int_elements(actual, element2);
  status = status && assert_integer(list->length, 0);
  status = status && list->first == NULL;
  status = status && list->last == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should remove the item and set the list first and last to NULL when there is only one element");

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
  Status status = match_int_elements(actual, element2);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the last item from the list");

  actual = remove_from_end(list);
  status = match_int_elements(actual, element1);
  status = status && assert_integer(list->length, 0);
  status = status && list->first == NULL;
  status = status && list->last == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should remove the item and set the list first and last to NULL when there is only one element");

  actual = remove_from_end(list);
  status = actual == NULL;
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove the item from the list if the list is empty and give NULL");

  clear_list(list);
}

void test_remove_at(List_ptr list)
{
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  Element element3 = create_int_element(3);
  Element element4 = create_int_element(4);
  Element element5 = create_int_element(5);
  add_to_list(list, element1);
  add_to_list(list, element2);
  add_to_list(list, element3);
  add_to_list(list, element4);
  add_to_list(list, element5);

  PRINT_STRING("\nremove_at");

  Status status = match_int_elements(remove_at(list, 4), element5);
  status = status && assert_integer(list->length, 4);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the element at the end of the list for position list count");

  status = match_int_elements(remove_at(list, 0), element1);
  status = status && assert_integer(list->length, 3);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the element at the beginning of the list for position 0");

  status = match_int_elements(remove_at(list, 1), element3);
  status = status && assert_integer(list->length, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should remove the element at the given position of the list");

  status = match_int_elements(remove_at(list, 0), element2);
  status = status && assert_integer(list->length, 1);
  status = match_int_elements(remove_at(list, 0), element4);
  status = status && assert_integer(list->length, 0);
  status = status && list->first == NULL;
  status = status && list->last == NULL;
  display_pass_or_fail(status);
  PRINT_STRING("should remove the item and set the list first and last to NULL when there is only one element");

  status = remove_at(list, 9) == NULL;
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove the element if the given position is below 0");

  status = remove_at(list, -9) == NULL;
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove the element if the given position is above list count");

  clear_list(list);
}

void test_remove_first_occurrence(List_ptr list)
{
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  add_to_list(list, element1);
  add_to_list(list, element2);

  PRINT_STRING("\nremove_first_occurrence");

  Element actual = remove_first_occurrence(list, element1, &match_int_elements);
  int status = match_int_elements(actual, element1);
  status = status && assert_integer(search_node(list, element1, &match_int_elements), -1);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should remove first occurrence of the given number in the list if exists");

  actual = remove_first_occurrence(list, element1, &match_int_elements);
  status = actual == NULL;
  status = status && assert_integer(search_node(list, element1, &match_int_elements), -1);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove first occurrence of the given number in the list if not exists");

  clear_list(list);
}

void test_remove_all_occurrences(List_ptr list)
{
  Element element1 = create_int_element(1);
  Element element2 = create_int_element(2);
  add_to_start(list, element1);
  add_to_list(list, element1);
  add_to_list(list, element2);

  PRINT_STRING("\nremove_all_occurrences");

  List_ptr new_list = remove_all_occurrences(list, element1, &match_int_elements);
  int status = new_list->length != 0;
  status = status && assert_integer(search_node(list, element1, &match_int_elements), -1);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should remove all occurrences of the given number in the list if exists");

  new_list = remove_all_occurrences(list, element1, &match_int_elements);
  status = new_list->length == 0;
  status = status && assert_integer(search_node(list, element1, &match_int_elements), -1);
  status = status && assert_integer(list->length, 1);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove all occurrences of the given number in the list if not exists");

  clear_list(list);
}

void test_add_unique(List_ptr list)
{
  PRINT_STRING("\nadd_unique");

  Element element = create_int_element(1);

  Status status = assert_integer(add_unique(list, element, &match_int_elements), Success);
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

  Status status = assert_integer(clear_list(list), Success);
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should clear the list and set to zero");

  status = assert_integer(clear_list(list), Failure);
  status = status && assert_integer(list->length, 0);
  display_pass_or_fail(status);
  PRINT_STRING("should not clear the list if it is an empty list");
}

void test_map(List_ptr list)
{
  PRINT_STRING("\nmap");
  List_ptr expected = create_list();
  if (expected == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    exit(12);
  }

  List_ptr actual = map(list, &square_of_integer);
  Status status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give empty array for given empty array");

  add_to_list(list, create_int_element(2));
  add_to_list(expected, create_int_element(4));
  actual = map(list, &square_of_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should map a single value for a given single element array with given mapper");

  add_to_list(list, create_int_element(3));
  add_to_list(expected, create_int_element(9));
  actual = map(list, &square_of_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should map two values for a given two element array with given mapper");

  add_to_list(list, create_int_element(4));
  add_to_list(expected, create_int_element(16));
  actual = map(list, &square_of_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should map more values for a given large array with given mapper");

  clear_list(list);
}

void test_filter(List_ptr list)
{
  PRINT_STRING("\nfilter");
  List_ptr expected = create_list();
  if (expected == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    exit(12);
  }

  List_ptr actual = filter(list, &is_even_integer);
  Status status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should give empty array for given empty array");

  add_to_list(list, create_int_element(1));
  actual = filter(list, &is_even_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should filter no elements when there is only one element in array not and satisfying given predicate");

  add_to_list(list, create_int_element(2));
  add_to_list(expected, create_int_element(2));
  actual = filter(list, &is_even_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should filter one element when there is only one element satisfying given predicate");

  add_to_list(list, create_int_element(3));
  add_to_list(list, create_int_element(4));
  add_to_list(list, create_int_element(5));
  add_to_list(expected, create_int_element(4));
  actual = filter(list, &is_even_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should filter the elements satisfying given predicate for larger array");

  clear_list(list);
  clear_list(expected);
  add_to_list(list, create_int_element(1));
  add_to_list(list, create_int_element(3));
  add_to_list(list, create_int_element(5));
  actual = filter(list, &is_even_integer);
  status = assert_list(actual, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should filter empty when there is no elements satisfying given predicate");

  clear_list(list);
}

void test_reduce(List_ptr list)
{
  PRINT_STRING("\nreduce");

  Element expected = create_int_element(0);
  Element actual = reduce(list, create_int_element(0), &sum_integers);
  Status status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should give initial context for given empty array");

  add_to_list(list, create_int_element(1));
  expected = create_int_element(1);
  actual = reduce(list, create_int_element(0), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer for array with one values");

  add_to_list(list, create_int_element(2));
  expected = create_int_element(3);
  actual = reduce(list, create_int_element(0), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer for array with 2 values");

  add_to_list(list, create_int_element(3));
  add_to_list(list, create_int_element(4));
  add_to_list(list, create_int_element(5));
  expected = create_int_element(15);
  actual = reduce(list, create_int_element(0), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer for array more than 2 values");

  clear_list(list);

  add_to_list(list, create_int_element(1));
  expected = create_int_element(11);
  actual = reduce(list, create_int_element(10), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer and using given initial context for array with one values");

  add_to_list(list, create_int_element(2));
  expected = create_int_element(13);
  actual = reduce(list, create_int_element(10), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer and using given initial context for array with 2 values");

  add_to_list(list, create_int_element(3));
  add_to_list(list, create_int_element(4));
  add_to_list(list, create_int_element(5));
  expected = create_int_element(25);
  actual = reduce(list, create_int_element(10), &sum_integers);
  status = match_int_elements(actual, expected);
  display_pass_or_fail(status);
  PRINT_STRING("should reduce the array using given reducer and using given initial context for array more than 2 values");

  clear_list(list);
}

void test_forEach(List_ptr list)
{
  PRINT_STRING("\nforEach (display of list by forEach)");

  forEach(list, &display_int_element);
  display_pass_or_fail(Success);
  PRINT_STRING("should iterate on empty list");

  add_to_list(list, create_int_element(1));
  add_to_list(list, create_int_element(2));
  add_to_list(list, create_int_element(3));
  add_to_list(list, create_int_element(4));
  add_to_list(list, create_int_element(5));
  forEach(list, &display_int_element);
  PRINT_STRING("");
  display_pass_or_fail(Success);
  PRINT_STRING("should iterate on given list");

  List_ptr expected = create_list();
  if (expected == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    exit(12);
  }

  add_to_list(expected, create_int_element(1));
  add_to_list(expected, create_int_element(4));
  add_to_list(expected, create_int_element(9));
  add_to_list(expected, create_int_element(16));
  add_to_list(expected, create_int_element(25));
  forEach(list, &replace_element_with_its_square);
  Status status = assert_list(list, expected, &match_int_elements);
  display_pass_or_fail(status);
  PRINT_STRING("should iterate on given list and change its values with equalent squares");

  clear_list(list);
}

int main(void)
{
  List_ptr list = create_list();
  if (list == NULL)
  {
    PRINT_STRING("Memory_Not_Available");
    return 12;
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
  test_remove_at(list);

  test_remove_first_occurrence(list);
  test_remove_all_occurrences(list);

  test_add_unique(list);

  test_clear_list(list);

  test_map(list);
  test_filter(list);
  test_reduce(list);
  test_forEach(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  if (FAILING_TESTS)
  {
    return 1;
  }

  return 0;
}