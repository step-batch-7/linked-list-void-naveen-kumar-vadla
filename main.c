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

  perform_clear_list(list);
  return 0;
}
