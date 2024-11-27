#include <deque>
#include <iostream>
#include <limits>
#include <numeric>

int main() {
    int prev = std::numeric_limits<int>::max();
    int prev_smoothed = std::numeric_limits<int>::max();
    int count = 0, count_smoothed = 0;

    std::deque<int> window;

    for (int d; std::cin >> d;) {
        if (d > prev) {
            ++count;
        }

        prev = d;

        // smoothed calc
        window.push_back(d);
        if (window.size() > 3) {
            window.pop_front();
        }

        if (window.size() == 3) {
            auto sum = std::accumulate(window.begin(), window.end(), 0);

            if (sum > prev_smoothed) {
                ++count_smoothed;
            }

            prev_smoothed = sum;
        }
    }

    std::cout << count << ", " << count_smoothed << '\n';

    return 0;
}
