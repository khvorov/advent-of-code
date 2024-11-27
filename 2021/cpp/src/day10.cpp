#include <bits/stdc++.h>

int main()
{
    using scores_type = std::unordered_map<char, std::size_t>;

    const scores_type checker_scores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    const scores_type autocomplete_scores = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

    std::size_t checker_result = 0;
    std::vector<std::size_t> autocomplete_results;

    for (std::string data; std::getline(std::cin, data);) {
        // check if the line is incorrect (part 1)
        std::deque<char> stack;

        std::size_t checker_score = 0;

        for (const char c : data) {
            if (c == '[' || c == '(' || c == '{' || c == '<') {
                stack.push_back(c);
            } else if (c == ']') {
                if (stack.empty() || stack.back() != '[') {
                    checker_score = checker_scores.at(c);
                    break;
                } else {
                    stack.pop_back();
                }
            } else if (c == ')') {
                if (stack.empty() || stack.back() != '(') {
                    checker_score = checker_scores.at(c);
                    break;
                } else {
                    stack.pop_back();
                }
            } else if (c == '}') {
                if (stack.empty() || stack.back() != '{') {
                    checker_score = checker_scores.at(c);
                    break;
                } else {
                    stack.pop_back();
                }
            } else if (c == '>') {
                if (stack.empty() || stack.back() != '<') {
                    checker_score = checker_scores.at(c);
                    break;
                } else {
                    stack.pop_back();
                }
            }
        }

        checker_result += checker_score;

        // incomplete line (part 2)
        std::size_t autocomplete_score = 0;

        if (!stack.empty() && checker_score == 0) {
            for (; !stack.empty(); stack.pop_back()) {
                autocomplete_score *= 5;
                autocomplete_score += autocomplete_scores.at(stack.back());
            }

            autocomplete_results.push_back(autocomplete_score);
        }
    }

    std::sort(autocomplete_results.begin(), autocomplete_results.end());
    std::size_t autocomplete_result = autocomplete_results[autocomplete_results.size() / 2];

    std::cout << checker_result << ' ' << autocomplete_result << '\n';

    return 0;
}
