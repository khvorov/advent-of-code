#include <bits/stdc++.h>

int main()
{
    std::vector<std::vector<int>> heights;
    std::string data;

    std::size_t rows = 0, cols = 0;

    while (std::getline(std::cin, data)) {
        if (!cols) {
            cols = data.size();
        }

        std::vector<int> row;
        row.reserve(cols);

        for (auto c : data) {
            row.push_back(c - '0');
        }

        heights.push_back(std::move(row));
    }

    rows = heights.size();

    // part 1
    std::vector<std::pair<int, int>> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    std::vector<std::pair<int, int>> lowest_points;
    int result = 0;

    for (int i = 0; i < int(rows); ++i) {
        for (int j = 0; j < int(cols); ++j) {
            int highest_neighbors = 0;

            for (auto [dx, dy] : dirs) {
                int x = i + dx, y = j + dy;

                if (x >= 0 && x < int(rows) && y >= 0 && y < int(cols)) {
                    if (heights[i][j] < heights[x][y]) {
                        ++highest_neighbors;
                    }
                } else {
                    ++highest_neighbors;
                }
            }

            if (highest_neighbors == 4) {
                result += heights[i][j] + 1;
                lowest_points.emplace_back(i, j);
            }
        }
    }

    std::cout << "p1: " << result << '\n';

    // part 2
    // do BFS from each lowest point to find size of a basin
    // basins are surrounded by 9-s
    std::queue<std::pair<int, int>> q;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for (auto [i, j] : lowest_points) {
        q.push(std::make_pair(i, j));
        heights[i][j] = 9;  // mark as visited
        std::size_t basin = 1;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : dirs) {
                int x1 = x + dx, y1 = y + dy;

                if (x1 >= 0 && x1 < int(rows) && y1 >= 0 && y1 < int(cols) && heights[x1][y1] != 9) {
                    q.push(std::make_pair(x1, y1));
                    heights[x1][y1] = 9;
                    ++basin;
                }
            }
        }

        pq.push(basin);
        if (pq.size() > 3) {
            pq.pop();
        }
    }

    // calculate result
    for (result = 1; !pq.empty(); pq.pop()) {
        result *= pq.top();
    }

    std::cout << "p2: " << result << '\n';

    return 0;
}
