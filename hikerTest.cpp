#include <gtest/gtest.h>

extern "C"
{
#include "hiker.h"
}

using namespace ::testing;

TEST(Hiker, Life_the_universe_and_everything)
{
    ASSERT_EQ(42, answer());
    //EXPECT_EQ(56, answer());
}

TEST(Calc, testAdd)
{
    ASSERT_EQ(300, sum(100,200));
}

TEST(FizzBuzz, testFizz)
{
    ASSERT_EQ(300, calcFizzBuzz(3));
}

TEST(FizzBuzz, testBuzz)
{
    ASSERT_EQ(500, calcFizzBuzz(5));
}

TEST(FizzBuzz, testFizzBuzz)
{ 
    ASSERT_EQ(1500, calcFizzBuzz(15));  
}

TEST(FizzBuzz, testNormalNumber)
{
    ASSERT_EQ(11, calcFizzBuzz(11));    
}

int main(int argc, char* argv[])
{
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

