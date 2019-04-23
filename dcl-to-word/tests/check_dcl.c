#include <check.h>
#include "../src/dcl.h"
#include <stdlib.h>

void setup(void) {
    STACK = create_stack();
}

void teardown(void) {
}

START_TEST(test_tokenize_with_tokens_split_by_space)
{
  char *string = "char (*(*x[3])())[5]";
  char **res = tokenize(string);

  ck_assert_str_eq(*res, "char");
  ck_assert_str_eq(*(res+1), "(*(*x[3])())[5]");
}
END_TEST

START_TEST(test_tokenize_with_tokens_split_by_tab)
{
  char *string = "char\ta";
  char **res = tokenize(string);

  ck_assert_str_eq(*res, "char");
  ck_assert_str_eq(*(res+1), "a");
}
END_TEST


START_TEST(test_parse_declarator_with_pointer)
{
  char str[] = "*a";
  parse_declarator(str, 2);

  ck_assert_str_eq(pop(STACK), "a");
  ck_assert_str_eq(pop(STACK), "pointer to");
}
END_TEST

START_TEST(test_parse_declarator_with_pointer_to_pointer)
{
  char str[] = "**a";
  parse_declarator(str, 3);

  ck_assert_str_eq(pop(STACK), "a");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "pointer to");
}
END_TEST

START_TEST(test_parse_declarator_with_pointer_to_array)
{
  char str[] = "(*a)[20]";
  parse_declarator(str, 8);

  ck_assert_str_eq(pop(STACK), "a");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "array[20] of");
}
END_TEST

START_TEST(test_parse_declarator_with_array_of_pointer_to_int)
{
  char str[] = "*a[20]";
  parse_declarator(str, 6);

  ck_assert_str_eq(pop(STACK), "a");
  ck_assert_str_eq(pop(STACK), "array[20] of");
  ck_assert_str_eq(pop(STACK), "pointer to");
}
END_TEST

START_TEST(test_parse_declarator_with_function_returning_pointer)
{
  char str[] = "*func()";
  parse_declarator(str, 7);

  ck_assert_str_eq(pop(STACK), "func");
  ck_assert_str_eq(pop(STACK), "function returning");
  ck_assert_str_eq(pop(STACK), "pointer to");
}
END_TEST

START_TEST(test_parse_pointer_to_function_returning)
{
  char str[] = "(*func)()";
  parse_declarator(str, 9);

  ck_assert_str_eq(pop(STACK), "func");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "function returning");
}
END_TEST

START_TEST(test_parse_declarator_with_function_returning_pointer_to_array_of_pointer_to_function)
{
  char str[] = "(*(*func())[])()";
  parse_declarator(str, 16);

  ck_assert_str_eq(pop(STACK), "func");
  ck_assert_str_eq(pop(STACK), "function returning");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "array[] of");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "function returning");
}
END_TEST

START_TEST(test_parse_declarator_array_of_pointer_to_function_returning_pointer_to_array)
{
  char str[] = "(*(*a[3])())[5]";
  parse_declarator(str, 15);

  ck_assert_str_eq(pop(STACK), "a");
  ck_assert_str_eq(pop(STACK), "array[3] of");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "function returning");
  ck_assert_str_eq(pop(STACK), "pointer to");
  ck_assert_str_eq(pop(STACK), "array[5] of");
}
END_TEST

Suite *dcl_test_suite(void)
{
    Suite *s;
    s = suite_create("Dcl");

    TCase *tc_core;
    tc_core = tcase_create("tokens_split_by_space");
    tcase_add_test(tc_core, test_tokenize_with_tokens_split_by_space);
    suite_add_tcase(s, tc_core);

    TCase *tc_core2;
    tc_core2 = tcase_create("tokens_split_by_tab");
    tcase_add_test(tc_core2, test_tokenize_with_tokens_split_by_tab);
    suite_add_tcase(s, tc_core2);

    //* char *c
    //*   c: pointer to char
    TCase *tc_core3;
    tc_core3 = tcase_create("parse_declarator_with_pointer");
    tcase_add_checked_fixture(tc_core3, setup, teardown);
    tcase_add_test(tc_core3, test_parse_declarator_with_pointer);
    suite_add_tcase(s, tc_core3);

    //* char **argv
    //*   argv: pointer to pointer to char
    TCase *tc_core4;
    tc_core4 = tcase_create("parse_declarator_with_pointer_to_pointer");
    tcase_add_checked_fixture(tc_core4, setup, teardown);
    tcase_add_test(tc_core4, test_parse_declarator_with_pointer_to_pointer);
    suite_add_tcase(s, tc_core4);

    //* int (*daytab)[13]
    //*   daytab: pointer to array[13] of int
    TCase *tc_core5;
    tc_core5 = tcase_create("parse_declarator_with_pointer_to_array");
    tcase_add_checked_fixture(tc_core5, setup, teardown);
    tcase_add_test(tc_core5, test_parse_declarator_with_pointer_to_array);
    suite_add_tcase(s, tc_core5);

    //* int *daytab[13]
    //*   daytab: array[13] of pointer to int
    TCase *tc_core6;
    tc_core6 = tcase_create("parse_declarator_with_array_of_pointer_to_int");
    tcase_add_checked_fixture(tc_core6, setup, teardown);
    tcase_add_test(tc_core6, test_parse_declarator_with_array_of_pointer_to_int);
    suite_add_tcase(s, tc_core6);

    //* void *comp()
    //*   comp: function returning pointer to void
    TCase *tc_core7;
    tc_core7 = tcase_create("parse_declarator_with_function_returning_pointer");
    tcase_add_checked_fixture(tc_core7, setup, teardown);
    tcase_add_test(tc_core7, test_parse_declarator_with_function_returning_pointer);
    suite_add_tcase(s, tc_core7);


    //* void (*comp)()
    //*   comp: pointer to function returing void
    TCase *tc_core8;
    tc_core8 = tcase_create("parse_declarator_pointer_to_function_returning");
    tcase_add_checked_fixture(tc_core8, setup, teardown);
    tcase_add_test(tc_core8, test_parse_pointer_to_function_returning);
    suite_add_tcase(s, tc_core8);


    //* char (*(*x())[])()
    //*   x: function returning pointer to array[] of pointer to function returning char
    TCase *tc_core9;
    tc_core9 = tcase_create("parse_declarator_with_function_returning_pointer_to_array_of_pointer_to_function");
    tcase_add_checked_fixture(tc_core9, setup, teardown);
    tcase_add_test(tc_core9, test_parse_declarator_with_function_returning_pointer_to_array_of_pointer_to_function);
    suite_add_tcase(s, tc_core9);

    //* char (*(*x[3])())[5]
    //*   x: array[3] of pointer to function returning pointer to array[5] of char
    TCase *tc_core10;
    tc_core10 = tcase_create("parse_declarator_array_of_pointer_to_function_returning_pointer_to_array");
    tcase_add_checked_fixture(tc_core10, setup, teardown);
    tcase_add_test(tc_core10, test_parse_declarator_array_of_pointer_to_function_returning_pointer_to_array);
    suite_add_tcase(s, tc_core10);

    //* void func(void (*callback)(void *))
    //*  func: function returning void accepting argument pointer to function returning void accepting argument pointer to void
    //TCase *tc_core11;
    //tc_core11 = tcase_create("parse_declarator_function_returning_accespting");
    //tcase_add_checked_fixture(tc_core11, setup, teardown);
    //tcase_add_test(tc_core11, test_parse_declarator_with_array_of_pointer_to_int);
    //suite_add_tcase(s, tc_core11);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;
    s = dcl_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
