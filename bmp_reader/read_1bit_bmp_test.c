#include <stdlib.h>
#include <check.h>
#include "read_1bit_bmp.h"

START_TEST (testFor1)
{
    unsigned char arr[4] = {0x01,0x00, 0x00, 0x00};
    ck_assert_int_eq(1, lsb_to_int(arr));
}
END_TEST

START_TEST (testFor0)
{
    unsigned char arr[4] = {0x00, 0x00, 0x00, 0x00};
    ck_assert_int_eq(0, lsb_to_int(arr));
}
END_TEST

START_TEST (testFor255)
{
    unsigned char arr[4] = {0xFF, 0x00, 0x00, 0x00};
    ck_assert_int_eq(255, lsb_to_int(arr));
}
END_TEST

START_TEST (testFor61695)
{
    unsigned char arr[4] = {0xFF, 0xF0, 0x00, 0x00};
    ck_assert_int_eq(61695, lsb_to_int(arr));
}
END_TEST

START_TEST (testFor268435456)
{
    unsigned char arr[4] = {0x00, 0x00, 0x00, 0x10};
    ck_assert_int_eq(268435456, lsb_to_int(arr));
}
END_TEST

Suite * lsb_to_int_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("lsb_to_int");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testFor0);
    tcase_add_test(tc_core, testFor1);
    tcase_add_test(tc_core, testFor255);
    tcase_add_test(tc_core, testFor61695);
    tcase_add_test(tc_core, testFor268435456);
    suite_add_tcase(s, tc_core);

    return s;
}

START_TEST (testForBorderPixelsIn1x1Image)
{
    //the img should look like this
    //|B|W|
    //|W|B|
    unsigned char byte_array[8] = { 0x40, 0x00, 0x00, 0x00,
                                    0x80, 0x00, 0x00, 0x00 };
    ck_assert_int_eq(0, extract_pixel(byte_array, 4, 0, 0));
    ck_assert_int_eq(1, extract_pixel(byte_array, 4, 0, 1));
    ck_assert_int_eq(1, extract_pixel(byte_array, 4, 1, 0));
    ck_assert_int_eq(0, extract_pixel(byte_array, 4, 1, 1));
}
END_TEST

START_TEST (testForBorderPixels)
{
    unsigned char byte_array[4] = { 0x01, 0x00,
                                    0x00, 0x01 };
    ck_assert_int_eq(0, extract_pixel(byte_array, 2, 0, 0));
    ck_assert_int_eq(0, extract_pixel(byte_array, 2, 0, 15));
    ck_assert_int_eq(0, extract_pixel(byte_array, 2, 1, 0));
    ck_assert_int_eq(1, extract_pixel(byte_array, 2, 1, 15));
}
END_TEST


START_TEST (testForBiggerImage)
{
    unsigned char byte_array[15] = { 0x01, 0x00, 0x10, 0xFF, 0x12,
                                     0x00, 0x01, 0x12, 0xDD, 0x11,
                                     0x10, 0x11, 0x10, 0x00, 0x00 };
    ck_assert_int_eq(0, extract_pixel(byte_array, 5, 0, 0));
    ck_assert_int_eq(1, extract_pixel(byte_array, 5, 0, 31));
    ck_assert_int_eq(0, extract_pixel(byte_array, 5, 1, 23));
    ck_assert_int_eq(1, extract_pixel(byte_array, 5, 2, 3));
}
END_TEST

Suite * extact_pixel_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("extract_pixel");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testForBorderPixels);
    tcase_add_test(tc_core, testForBorderPixelsIn1x1Image);
    tcase_add_test(tc_core, testForBiggerImage);
    suite_add_tcase(s, tc_core);

    return s;
}

START_TEST (testFor1x1Image)
{
    ck_assert_int_eq(4, get_scan_line_size_in_bytes(8, 2));
}
END_TEST

Suite * get_scan_line_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("get_scan_line_size_in_bytes");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testFor1x1Image);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *lsb;
    SRunner *sr;

    lsb = lsb_to_int_suite();
    sr = srunner_create(lsb);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    Suite *s;
    s = extact_pixel_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    Suite *sl;
    sl = get_scan_line_suite();
    sr = srunner_create(sl);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

