#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

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
    std::vector<std::vector<std::string>> dp(m, std::vector<std::string>(n+1));
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n+1; j++) {
            if (A[i] == B[j-1]) {
                dp[i][j] = dp[i][j-1] + B[j-1];
            } else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }

    std::cout << value(values, dp[m-1][n]) << "\n";
    std::cout << dp[m-1][n] << "\n";
}