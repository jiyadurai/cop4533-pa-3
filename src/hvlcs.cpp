#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <utility>
#include <chrono>

int value(std::unordered_map<char, int> &values, const std::string &s) {
    int result = 0;
    for (auto c : s) {
        if (values.count(c) == 0) {
            return -1;
        }
        result += values[c];
    }
    return result;
}

int main(int argc, char *argv[]) {
    std::unordered_map<char, int> values;
    std::string A, B;
    try {
        std::ifstream file(argv[1]);
        int K;
        file >> K;
        for (int i = 0; i < K; i++) {
            char c;
            file >> c;
            int v;
            file >> v;
            values[c] = v;
        }
        file >> A >> B;
    }
    catch (std::exception &err){
        std::cerr << "Error reading input file: " << err.what() << "\n";
    }
    auto start = std::chrono::high_resolution_clock::now();

    const auto m = A.size();
    const auto n = B.size();
    // dp[i][j] is the pair<int, string> corresponding to value, string of the best possible subsequence using
    // the first i characters from A and the first j characters from B
    std::vector<std::vector<std::pair<int, std::string>>> dp(m+1, std::vector<std::pair<int, std::string>>(n+1));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // if there is a match and it is a character worth taking
            // if there is an illegal character, it will overlook that.
            if (A[i] == B[j] && values[A[i]] > 0) {
                auto &[v, s] = dp[i][j];
                // take the character and add its value to the best made from before then
                dp[i + 1][j + 1] = {v + values[A[i]], s + A[i]};
            } else {
                // take the best result we have from skipping a character in A or in B
                // note on the comparison of std::pair: it is lexicographic, so it first compares p1.first < p2.first
                // so the integer value of the subsequence is prioritized, and not the comparison of the strings.
                dp[i + 1][j + 1] = std::max(dp[i+1][j], dp[i][j+1]);
            }
        }

    }

    std::cout << dp[m][n].first << "\n";
    std::cout << dp[m][n].second << "\n";

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time elapsed: " << (duration.count() / 1000000) % 1000 << "s " << (duration.count() / 1000) % 1000 << "." << duration.count() % 1000 << "ms" << std::endl;


}