#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define PRINT_STRING(string) printf("%s\n", string)

Element create_int_element(int value);
ElementProcessor display_int_element;
ElementProcessor replace_element_with_its_square;
Matcher match_int_elements;

Mapper square_of_integer;
Predicate is_even_integer;
Reducer sum_integers;

#endif
