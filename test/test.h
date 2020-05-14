#ifndef __TEST_H
#define __TEST_H

#define PRINT_STRING(string) printf("%s\n", string)

// ✔ = \u2714  HEAVY CHECK MARK
// ✘ = \u2718  HEAVY BALLOT X

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define PASS GREEN "\u2714 " RESET
#define FAIL RED "\u2718 " RESET

int PASSING_TESTS = 0;
int FAILING_TESTS = 0;

Status assert(int actual, int expected);
Status assert_list(List_ptr actual, List_ptr expected, Matcher matcher);
void display_pass_or_fail(int status);

void test_create_list(void);
void test_create_node(void);

void test_get_node_at(List_ptr list);
void test_search_node(List_ptr list);

void test_add_to_list(List_ptr list);
void test_add_to_start(List_ptr list);
void test_insert_at(List_ptr list);

void test_reverse(List_ptr list);

void test_remove_from_start(List_ptr list);
void test_remove_from_end(List_ptr list);

void test_add_unique(List_ptr list);

void test_create_list(void);

#endif
