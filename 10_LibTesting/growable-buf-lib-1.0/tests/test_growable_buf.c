#include <check.h>
#include <stdlib.h>
#include "growable_buf.h"

START_TEST(test_init)
{
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);
    ck_assert_uint_eq(buf_size(a), 0);

    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    ck_assert(a[0] == (float)1.3f);

    buf_free(a);
}
END_TEST

START_TEST(test_clear_and_free)
{
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_nonnull(a);
    buf_free(a);
    ck_assert_ptr_null(a);
}
END_TEST

START_TEST(test_clear_null)
{
    float *a = 0;
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_null(a);
}
END_TEST

START_TEST(test_push)
{
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);

    ck_assert_uint_eq(buf_size(ai), 10000);

    int match = 0;
    for (int i = 0; i < (int)buf_size(ai); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);

    buf_free(ai);
}
END_TEST

START_TEST(test_grow_and_trunc)
{
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);

    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);

    buf_free(ai);
}
END_TEST

START_TEST(test_pop)
{
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_uint_eq(buf_size(a), 4);

    ck_assert(buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3);

    ck_assert(buf_pop(a) == (float)1.3f);
    ck_assert(buf_pop(a) == (float)1.2f);
    ck_assert(buf_pop(a) == (float)1.1f);
    ck_assert_uint_eq(buf_size(a), 0);

    buf_free(a);
}
END_TEST

static Suite *create_tests(void)
{
    Suite *s = suite_create("GrowableBuf");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_init);
    tcase_add_test(tc, test_clear_and_free);
    tcase_add_test(tc, test_clear_null);
    tcase_add_test(tc, test_push);
    tcase_add_test(tc, test_grow_and_trunc);
    tcase_add_test(tc, test_pop);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    Suite *s = create_tests();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
