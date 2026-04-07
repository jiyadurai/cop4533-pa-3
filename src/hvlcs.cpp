#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <utility>
#include <chrono>
#include <algorithm>

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
    if (argc < 2) {
        std::cerr << "File was not provided\n";
        std::cerr << "Usage: " << argv[0] << " <input filename>";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "File does not exist or could not be opened\n";
        return 1;
    }
    auto start = std::chrono::high_resolution_clock::now();
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



    const auto m = A.size();
    const auto n = B.size();
    // dp[i][j] is the maximum value that can be made from first i characters from A and first j characters from B
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // if there is a match and it is a character worth taking
            if (A[i] == B[j] && values[A[i]] > 0) {
                int v = dp[i][j];
                // take the character and add its value to the best made from before then
                dp[i + 1][j + 1] = v + values[A[i]];
            } else {
                // take the best value if we skip a character in A or B
                dp[i + 1][j + 1] = std::max(dp[i+1][j], dp[i][j+1]);
            }
        }

    }

    std::cout << dp[m][n] << "\n";

    std::string optimal;
    {
        int i = m;
        int j = n;
        while (i > 0 && j > 0) {
            // if there is a match on the previous character and that character had a positive value,
            // then we took that character and continue from that spot
            if (A[i-1] == B[j-1] && values[A[i - 1]] > 0 && dp[i][j] == dp[i-1][j-1] + values[A[i-1]]) {
                optimal += A[i-1];
                i--;
                j--;
            } else if (dp[i-1][j] > dp[i][j-1]) {
                // if it was better to skip A[i]
                i--;
            } else {
                // if it was not better to skip A[i]
                j--;
            }
        }
    }
    std::reverse(optimal.begin(), optimal.end());

    std::cout << optimal << "\n";

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //std::cout << "time elapsed: " << (duration.count() / 1000000) % 1000 << "s " << (duration.count() / 1000) % 1000 << "." << duration.count() % 1000 << "ms" << std::endl;


}