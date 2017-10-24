#include "gtest/gtest.h"
#include "test_web_request_handler.h"

#ifdef BUILD_TEST

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif // BUILD_TEST