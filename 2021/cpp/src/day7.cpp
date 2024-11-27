#include <bits/stdc++.h>

int main()
{
    std::vector<int> crabes;

    std::string data;
    std::getline(std::cin, data);

    std::stringstream ss(data);

    for (std::size_t i; ss >> i;) {
        crabes.push_back(i);

        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    const std::size_t n = crabes.size();

#if 0
    int sum = 0;

    std::sort(crabes.begin(), crabes.end());

    sum += std::abs(crabes[0] - crabes[1]);
    sum += std::abs(crabes[n - 1] - crabes[n - 2]);

    for (std::size_t i = 1; i < n - 1; ++i) {
        sum += std::min(std::abs(crabes[i] - crabes[i - 1]), std::abs(crabes[i] - crabes[i + 1]));
    }
#else
    int sum = std::numeric_limits<int>::max();

    for (int i = 0; i < int(n); ++i) {
        int curr_sum = 0;
        for (int j = 0; j < int(n); ++j) {
            int d = std::abs(crabes[j] - i);
            curr_sum += d * (d + 1);
        }

        curr_sum /= 2;

        sum = std::min(sum, curr_sum);
    }
#endif

    std::cout << sum << '\n';

    return 0;
}
