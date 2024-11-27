#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    static constexpr std::size_t pos_size = 12;

    std::vector<std::size_t> count(pos_size), numbers;
    std::size_t n = 0;

    for (std::string pos; std::cin >> pos; ++n) {
        assert(pos.size() == pos_size);

        std::size_t num = 0;

        for (std::size_t i = 0; i < pos_size; ++i) {
            num <<= 1;
            if (pos[i] == '1') {
                ++count[i];
                num |= 1;
            }
        }

        numbers.push_back(num);
    }

    // part 1
    std::cout << n << '\n';

    std::size_t gamma = 0, epsilon = 0;

    for (auto c : count) {
        std::cout << c << ' ';
        gamma = (gamma << 1) | (c > n / 2);
        epsilon = (epsilon << 1) | (c < n / 2);
    }

    std::cout << ", gamma = " << gamma << ", eps = " << epsilon << '\n';
    std::cout << (gamma * epsilon) << '\n';

    // part 2
    auto bit_filter = [](std::vector<std::size_t> nums, bool invert) {
        int mask = 1 << (pos_size - 1);

        while (nums.size() != 1) {
            std::size_t cnt = 0;

            for (auto n : nums) {
                cnt += (n & mask) != 0;
            }

            std::size_t n = nums.size();
            nums.erase(std::remove_if(nums.begin(), nums.end(),
                                      [&](std::size_t v) {
                                          auto b = v & mask;
                                          bool filter = (2 * cnt >= n) ? (b == 0) : (b != 0);
                                          return invert ? !filter : filter;
                                      }),
                       nums.end());

            mask >>= 1;
        }

        return nums[0];
    };

    auto oxy = bit_filter(numbers, false);
    auto co2 = bit_filter(numbers, true);

    std::cout << "oxy = " << oxy << '\n';
    std::cout << "co2 = " << co2 << '\n';
    std::cout << (oxy * co2) << '\n';

    return 0;
}
