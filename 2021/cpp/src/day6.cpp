#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number of days>\n";
        return -1;
    }

    std::size_t n_days = std::stoul(argv[1]) + 1;

    // age of fish -> number of fishes (max age - 8)
    std::vector<std::size_t> fishes(9, 0);

    std::string data;
    std::getline(std::cin, data);

    std::stringstream ss(data);

    for (std::size_t i; ss >> i;) {
        ++fishes[i];

        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    while (--n_days != 0) {
        std::size_t f0 = fishes[0];

        std::rotate(fishes.begin(), fishes.begin() + 1, fishes.end());
        fishes[8] = f0;
        fishes[6] += f0;
    }

    std::cout << std::accumulate(fishes.begin(), fishes.end(), std::size_t{0}) << '\n';

    return 0;
}
