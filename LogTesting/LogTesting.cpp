//
// Created by amit on 17/09/16.
//

#include "LogTesting.h"
#include "gtest/gtest.h"
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int returnValue;
    returnValue = RUN_ALL_TESTS();
    return returnValue;
}