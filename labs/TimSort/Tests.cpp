#include <gtest/gtest.h>
#include "Modules/Blocks.h"

TEST(TimSortTests, Test1) {
    EXPECT_EQ(MinRunLen(1000), 16);
    EXPECT_EQ(MinRunLen(10000), 10);
    EXPECT_EQ(MinRunLen(25), 13);
}
TEST(TimSortTests, Test2) {
    std::vector<int> nums = {5, 12, 3, -10, 9};
    std::vector<int> answer = {12, -10, 9, 5, 3};
    size_t n =5;
    std::vector<std::vector<int>> res;
    Cut(nums, MinRunLen(5), 0, res);
    EXPECT_EQ(res[0], answer);
}
TEST(TimSortTests, Test3) {
    std::vector<int> nums = {1, -2, 3, -4, 5, 6, -7, -8, 9, -10, 11, -10, -9, 8, 7, -7, -6, 6, 5, 4};
    std::vector<int> answer = {11, -10, -10, 9 ,-9, -8, 8, -7, 7, -7, 6, -6, 6, 5, 5, -4 ,4, 3, -2, 1};
    std::vector<std::vector<int>> res;
    Cut(nums, MinRunLen(20), 0, res);
    std::vector<int> part0 = {11, -10, 9, -8, -7, 6, 5, -4, 3, -2, 1};
    std::vector<int> part1 = {-10, -9, 8, 7, -7, -6, 6, 5, 4};
    EXPECT_EQ(res[0], part0);
    EXPECT_EQ(res[1], part1);
    nums = Blocks(res);
    EXPECT_EQ(nums, answer);
}
TEST(TimSortTests, Test4) {
    std::vector<int> nums = {-1, 2, 3, 4, 5, -6, 7, 8, -8, -8, 7, -7, 7, 6, -5, 4};
    std::vector<int> answer = {8, -8, -8, 7, 7, -7, 7, 6, -6, 5, -5, 4, 4, 3, 2, -1};
    std::vector<std::vector<int>> res;
    Cut(nums, MinRunLen(16), 0, res);
    std::vector<int> part0 = {8, 7, -6, 5, 4, 3, 2, -1 };
    std::vector<int> part1 = {-8, -8, 7, -7, 7,6,-5, 4 };
    EXPECT_EQ(res[0], part0);
    EXPECT_EQ(res[1], part1);
    nums = Blocks(res);
    EXPECT_EQ(nums, answer);
}
TEST(TimSortTests, Test5) {
    std::vector<int> nums = {51, -28, 3, 1, 0};
    std::vector<int> mas = {12, -10, 9, 5, 3};
    std::vector<int> answer = {51, -28, 12, -10, 9, 5, 3, 3, 1, 0};
    Merge(nums, mas);
    EXPECT_EQ(nums, answer);
}
TEST(TimSortTests, Test6) {
    std::vector<int> nums = {-10, 10, 9};
    std::vector<int> mas = {-10, -10, 7};
    std::vector<int> answer = {-10, 10, -10, -10, 9, 7};
    Merge(nums, mas);
    EXPECT_EQ(nums, answer);
}
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
