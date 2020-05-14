#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define PRINT_STRING(string) printf("%s\n", string)

Element create_int_element(int value);
void display_int_element(Element number);
Status match_int_elements(Element element_one, Element element_two);

Mapper square_of_integer;
Predicate is_even_integer;

#endif
