#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <utility>

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

    const auto m = A.size();
    const auto n = B.size();
    // dp[i][j] stores the maximum value possible from the characters up to index i in A and up to index j in B
    std::vector<std::vector<std::pair<int, std::string>>> dp(m+1, std::vector<std::pair<int, std::string>>(n+1));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i] == B[j] && values[A[i]] > 0) {
                auto &[v, s] = dp[i][j];
                dp[i + 1][j + 1] = {v + values[A[i]], s + A[i]};
            } else {
                dp[i + 1][j + 1] = std::max(dp[i+1][j], dp[i][j+1]);
            }
        }

    }

    std::cout << dp[m][n].first << "\n";
    std::cout << dp[m][n].second << "\n";

}