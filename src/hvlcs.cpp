#include <iostream>
#include <unordered_map>
#include <fstream>

int main(int argc, char *argv[]) {
    std::unordered_map<std::string, int> values;
    std::string A, B;
    try {
        std::ifstream file(argv[1]);
        int K;
        file >> K;
        for (int i = 0; i < K; i++) {
            std::string s;
            file >> s;
            int v;
            file >> v;
            values[s] = v;
        }
        file >> A >> B;
    }
    catch (std::exception &err){
        std::cerr << "Error reading input file: " << err.what() << "\n";
    }
}