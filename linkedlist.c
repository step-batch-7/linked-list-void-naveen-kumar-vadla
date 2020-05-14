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

Status add_to_list(List_ptr list, Element value)
{
  Node_ptr new_node = create_node(value);
  Node_ptr *ptr_to_set = &list->first;
  if (new_node == NULL)
  {
    return Memory_Not_Available;
  }
  if (list->first != NULL)
  {
    ptr_to_set = &list->last->next;
  }
  (*ptr_to_set) = new_node;
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element value)
{
  Node_ptr new_node = create_node(value);
  if (new_node == NULL)
  {
    return Memory_Not_Available;
  }
  if (list->first == NULL)
  {
    list->last = new_node;
  }
  new_node->next = list->first;
  list->first = new_node;
  list->length++;
  return Success;
}

Node_ptr get_node_at(List_ptr list, int position)
{
  if (position < 0 || position > list->length)
  {
    return NULL;
  }
  Node_ptr p_walk = list->first;
  for (int i = 0; i < position; i++)
  {
    p_walk = p_walk->next;
  }
  return p_walk;
}

Status insert_at(List_ptr list, Element value, int position)
{
  if (position == 0)
  {
    return add_to_start(list, value);
  }
  if (position < 0 || position > list->length)
  {
    return Failure;
  }
  Node_ptr new_node = create_node(value);
  if (new_node == NULL)
  {
    return Memory_Not_Available;
  }
  if (position == list->length)
  {
    list->last = new_node;
  }
  Node_ptr before_node = get_node_at(list, position - 1);
  new_node->next = before_node->next;
  before_node->next = new_node;
  list->length++;
  return Success;
}

List_ptr reverse(List_ptr list)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_start(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}

int search_node(List_ptr list, Element value, Matcher *matcher)
{
  int index = -1;
  Node_ptr p_walk = list->first;
  for (int i = 0; i < list->length; i++)
  {
    if ((*matcher)(p_walk->element, value))
    {
      index = i;
      break;
    }
    p_walk = p_walk->next;
  }
  return index;
}

Status add_unique(List_ptr list, Element value, Matcher matcher)
{
  int index = search_node(list, value, matcher);
  if (index != -1)
  {
    return Failure;
  }
  return add_to_list(list, value);
}

Element remove_from_start(List_ptr list)
{
  Element element = NULL;
  Node_ptr first = list->first;
  if (first != NULL)
  {
    list->first = first->next;
    element = first->element;
    list->length--;
  }
  return element;
}

Element remove_from_end(List_ptr list)
{
  if (list->length <= 1)
  {
    return remove_from_start(list);
  }
  Node_ptr before_node = get_node_at(list, list->length - 2);
  Element element = before_node->next->element;
  before_node->next = NULL;
  list->last = before_node;
  list->length--;
  return element;
}

Element remove_at(List_ptr list, int position)
{
  if (position == 0)
  {
    return remove_from_start(list);
  }
  if (position < 0 || position >= list->length)
  {
    return NULL;
  }
  Node_ptr before_node = get_node_at(list, position - 1);
  if (position == list->length - 1)
  {
    list->last = before_node;
  }
  Node_ptr temp = before_node->next;
  before_node->next = temp->next;
  list->length--;
  return temp->element;
}

Element remove_first_occurrence(List_ptr list, Element value, Matcher *matcher)
{
  int index = search_node(list, value, matcher);
  if (index == -1)
  {
    return NULL;
  }
  return remove_at(list, index);
}

List_ptr remove_all_occurrences(List_ptr list, Element value, Matcher *matcher)
{
  List_ptr new_list = create_list();
  Element element = remove_first_occurrence(list, value, matcher);
  while (element != NULL)
  {
    add_to_list(new_list, element);
    element = remove_first_occurrence(list, value, matcher);
  }
  return new_list;
}

Status clear_list(List_ptr list)
{
  Status status = Failure;
  while (list->length > 0)
  {
    Node_ptr first = list->first;
    list->first = first->next;
    list->length--;
    status = Success;
    free(first);
  }
  return status;
}

List_ptr map(List_ptr list, Mapper *mapper)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    Element element = (*mapper)(p_walk->element);
    add_to_list(new_list, element);
    p_walk = p_walk->next;
  }
  return new_list;
}

List_ptr filter(List_ptr list, Predicate *predicate)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    Status result = (*predicate)(p_walk->element);
    if (result)
    {
      add_to_list(new_list, p_walk->element);
    }
    p_walk = p_walk->next;
  }
  return new_list;
}

Element reduce(List_ptr list, Element context, Reducer *reducer)
{
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    context = (*reducer)(context, p_walk->element);
    p_walk = p_walk->next;
  }
  return context;
}
