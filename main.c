#include "linkedlist.h"
#include "utils.h"

void display_status(Status status, char *error_message);
void display_status(Status status, char *error_message)
{
  char *messages[4] = {error_message, "Done.", "Memory not available.\nTry again later.", "Invalid!"};
  if (status > 2)
  {
    status = 3;
  }
  char *message = messages[status];
  PRINT_STRING(message);
}

void perform_add_to_list(List_ptr list);
void perform_add_to_list(List_ptr list)
{
  PRINT_STRING("\nadd_to_list");
  Status status = add_to_list(list, create_int_element(1));
  display_status(status, "Failed to add the number to the end of the list.");
  display_list(list, &display_int_element);
}

void perform_add_to_start(List_ptr list);
void perform_add_to_start(List_ptr list)
{
  PRINT_STRING("\nadd_to_start");
  Status status = add_to_start(list, create_int_element(2));
  display_status(status, "Failed to add the number to the beginning of the list.");
  display_list(list, &display_int_element);
}

void perform_insert_at(List_ptr list);
void perform_insert_at(List_ptr list)
{
  PRINT_STRING("\ninsert_at");
  Status status = insert_at(list, create_int_element(0), 1);
  display_status(status, "The position you want to insert is invalid.");
  display_list(list, &display_int_element);
}

void perform_reverse(List_ptr list);
void perform_reverse(List_ptr list)
{
  PRINT_STRING("\nreverse");
  display_list(list, &display_int_element);

  List_ptr new_list = reverse(list);

  display_list(new_list, &display_int_element);
}

void perform_add_unique(List_ptr list);
void perform_add_unique(List_ptr list)
{
  PRINT_STRING("\nadd_unique");
  Status status = add_unique(list, create_int_element(5), &match_int_elements);
  display_status(status, "The number you entered is already present in the list.");
  display_list(list, &display_int_element);
}

void perform_remove_from_start(List_ptr list);
void perform_remove_from_start(List_ptr list)
{
  PRINT_STRING("\nremove_from_start");
  Element element = create_int_element(1);
  add_to_start(list, element);
  display_list(list, &display_int_element);

  Element actual = remove_from_start(list);
  Status status = actual != NULL && match_int_elements(actual, element);
  display_status(status, "The list is empty.");
  display_list(list, &display_int_element);
}

void perform_remove_from_end(List_ptr list);
void perform_remove_from_end(List_ptr list)
{
  PRINT_STRING("\nremove_from_end");
  Element element = create_int_element(1);
  add_to_list(list, element);
  display_list(list, &display_int_element);

  Element actual = remove_from_end(list);
  Status status = actual != NULL && match_int_elements(actual, element);
  display_status(status, "The list is empty.");
  display_list(list, &display_int_element);
}

void perform_remove_at(List_ptr list);
void perform_remove_at(List_ptr list)
{
  PRINT_STRING("\nremove_at");
  Element element = create_int_element(1);
  insert_at(list, element, 1);
  display_list(list, &display_int_element);

  Element actual = remove_at(list, 1);
  Status status = actual != NULL && match_int_elements(actual, element);
  display_status(status, "The Position you asked to remove is Invalid.");
  display_list(list, &display_int_element);
}

void perform_remove_first_occurrence(List_ptr list);
void perform_remove_first_occurrence(List_ptr list)
{
  PRINT_STRING("\nremove_first_occurrence");
  Element element = create_int_element(1);
  add_to_start(list, element);
  display_list(list, &display_int_element);

  Element actual = remove_first_occurrence(list, element, &match_int_elements);
  Status status = actual != NULL && match_int_elements(actual, element);
  display_status(status, "The element is not present in the list.");
  display_list(list, &display_int_element);
}

void perform_remove_all_occurrences(List_ptr list);
void perform_remove_all_occurrences(List_ptr list)
{
  PRINT_STRING("\nremove_all_occurrences");
  Element element = create_int_element(5);
  add_to_start(list, element);
  add_to_list(list, element);
  insert_at(list, element, 2);
  display_list(list, &display_int_element);

  List_ptr new_list = remove_all_occurrences(list, element, &match_int_elements);
  Status status = new_list->length != 0;
  status = status && search_node(list, element, &match_int_elements) == -1;
  display_status(status, "The element is not present in the list.");
  display_list(list, &display_int_element);
}

void perform_clear_list(List_ptr list);
void perform_clear_list(List_ptr list)
{
  PRINT_STRING("\nclear_list");
  Status status = clear_list(list);
  display_status(status, "The list you are trying to clear is empty");
  display_list(list, &display_int_element);
}

int main()
{
  List_ptr list = create_list();
  if (list == NULL)
  {
    display_status(Memory_Not_Available, "");
    return 0;
  }
  display_list(list, &display_int_element);

  perform_add_to_list(list);
  perform_add_to_start(list);
  perform_insert_at(list);

  perform_reverse(list);

  perform_remove_from_start(list);
  perform_remove_from_end(list);
  perform_remove_at(list);

  perform_remove_first_occurrence(list);
  perform_remove_all_occurrences(list);
  perform_add_unique(list);

  perform_clear_list(list);
  return 0;
}
