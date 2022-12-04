#include <gtest/gtest.h>
#include "../src/buf.h"

TEST(GrowableBuf, InitializationAndFree) {
    float *a = NULL;

    ASSERT_EQ(buf_capacity(a), 0) << "capacity init";
    ASSERT_EQ(buf_size(a), 0) << "size init";
    buf_push(a, 1.3f);
    ASSERT_EQ(buf_size(a), 1) << "size 1";
    ASSERT_EQ(a[0], (float)1.3f) << "value";
    buf_clear(a);
    ASSERT_EQ(buf_size(a), 0) << "clear";
    ASSERT_NE(a, static_cast<float *>(NULL)) << "clear not-free";
    buf_free(a);
    ASSERT_EQ(a, static_cast<float *>(NULL)) << "free";
}

TEST(GrowableBuf, ClearingNull) {
    float *a = 0;
    buf_clear(a);
    ASSERT_EQ(buf_size(a), 0) << "clear empty";
    ASSERT_EQ(a, static_cast<float *>(NULL)) << "clear no-op";
}

TEST(GrowableBuf, PushAndAccessOp) {
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);

    ASSERT_EQ(buf_size(ai), 10000) << "size 10000";
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;

    ASSERT_EQ(match, 10000) << "match 10000";
    buf_free(ai);
}

TEST(GrowableBuf, GrowAndTrunc) {
    long *ai = 0;
    buf_grow(ai, 1000);
    ASSERT_EQ(buf_capacity(ai), 1000) << "grow 1000";
    ASSERT_EQ(buf_size(ai), 0) << "size 0 (grow)";
    buf_trunc(ai, 100);
    ASSERT_EQ(buf_capacity(ai), 100) << "trunc 100";
    buf_free(ai);
}

TEST(GrowableBuf, PushPop) {
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ASSERT_EQ(buf_size(a), 4) << "size 4";
    ASSERT_EQ(buf_pop(a), (float)1.4f) << "pop 3";
    buf_trunc(a, 3);
    ASSERT_EQ(buf_size(a), 3) << "size 3";
    ASSERT_EQ(buf_pop(a), (float)1.3f) << "pop 2";
    ASSERT_EQ(buf_pop(a), (float)1.2f) << "pop 1";
    ASSERT_EQ(buf_pop(a), (float)1.1f) << "pop 0";
    ASSERT_EQ(buf_size(a), 0) << "size 0 (pop)";
    buf_free(a);
}