#include "Modules/Blocks.h"
int main() {
    size_t n;
    std::cin >> n;
    size_t min_run = MinRunLen(n);
    std::vector<int> input_nums(n);
    for (size_t i =0; i<n; ++i){
        std::cin >> input_nums[i];
    }
    std::vector<std::vector<int>> all_runs;
    Cut(input_nums, min_run, 0, all_runs);
    size_t c1 =0;
    for (std::vector<int>& i : all_runs){
        std::cout << "Part " << c1++ << ":";
        for (int j : i){
            std::cout << " " << j;
        }
        std::cout << "\n";
    }
    input_nums = Blocks(all_runs);
    std::cout << "Answer:";
    for (int i : input_nums){
        std::cout << " " << i;
    }
}
