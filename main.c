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
  PRINT_STRING("add_to_list");
  Status status = add_to_list(list, create_int_element(1));
  display_status(status, "Failed to add the number to the end of the list.");
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
  perform_add_to_list(list);
  return 0;
}
