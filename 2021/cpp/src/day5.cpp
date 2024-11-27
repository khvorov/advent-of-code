#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>

struct pair_hash {
    // good enough for this task
    std::size_t operator()(const std::pair<int, int>& v) const { return v.first * 100000 + v.second; }
};

int main() {
    std::string cmd;
    int x1, y1, x2, y2;

    std::unordered_map<std::pair<int, int>, int, pair_hash> map;

    while (std::scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) > 0) {
#if 0
        // solution for part 1
        if (x1 == x2 || y1 == y2) {
            for (int i = std::min(x1, x2); i <= std::max(x1, x2); ++i) {
                for (int j = std::min(y1, y2); j <= std::max(y1, y2); ++j) {
                    map[std::make_pair(i, j)]++;
                }
            }
        }
#else
        int dx = x2 - x1, dy = y2 - y1;

        if (dx) {
            dx = (dx > 0) ? 1 : -1;
        }

        if (dy) {
            dy = (dy > 0) ? 1 : -1;
        }

        for (int x = x1, y = y1;; x += dx, y += dy) {
            map[std::make_pair(x, y)]++;

            if (x == x2 && y == y2) {
                break;
            }
        }
#endif
    }

    int count = 0;
    for (auto& [k, v] : map) {
        if (v > 1) {
            ++count;
        }
    }

    std::cout << count << '\n';

    return 0;
}
