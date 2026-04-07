Names: Luke Gorman and Jeevan Iyadurai

UFIDs: 43500015 and 31691151

To compile:

in the main folder of the project, run

g++ -std=c++20 -o out/hvlcs src/hvlcs.cpp




To run:

in the out folder of the project, run

out [input file path]

ex. 

out ../inputs/test1.txt


Assumptions are as stated in the assignment specifications.

Problem 1:
Here is the graph of the execution times for different sized test cases.
![graph](image.png)
![lines of best fit](image-1.png)

Problem 2:
dp[i][j] = 

	0                                                     if i == 0 || j == 0

	max(dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + val[A[i]]) if A[i] == B[j]

	max(dp[i-1][j], dp[i][j-1])                            if A[i] != B[j]


Here, dp[i][j] represents the best value of the first i chars of A and j chars of B.

Obviously, if we have zero chars of either A or B, the best we can do is zero.

Otherwise, we could choose not to include the character at A[i], in which case it is the same value as dp[i-1][j], or not include the character at B[j], so it is dp[i][j-1]. We should take the greater of these two.

Or, if A[i] and B[j] match, we could include those two characters and add them to the value of the two substrings without those chars, dp[i-1][j-1].


Problem 3:

(Assuming there was a typo in the problem and we should calculate the value). Also, vectors are 0-indexed and strings are 1-indexed. And map has O(1) lookups on characters.

	int hvlcs(string A, string B, map<char, int> v) { 

		vector<vector<int>> dp = (A.size()+1, vector<int>(B.size()+1, 0));

		for (int i = 1; i < dp.size(); i++) {

			for (int j = 1; j < dp[i].size(); j++) {

				if (A[i] == B[j]) dp[i][j] = dp[i-1][j-1] + v[A[i]];

				dp[i][j] = max(dp[i][j], dp[i-1][j], dp[i][j-1]);

			}

		}

		return dp[A.size()][B.size()];

	}

The time complexity of this algorithm is O(n^2) where n is the length of the longer of strings A and B. The inside of the loop is O(1), and it happens O(n^2) times.



(Calculating the length of the string)

	int hvlcsLength(string A, string B, map<char, int> v) { 

		vector<vector<pair<int, int>>> dp = (A.size()+1, vector<pair<int,int>>(B.size()+1, pair<int, int>{0, 0}));

		for (int i = 1; i < dp.size(); i++) {

			for (int j = 1; j < dp[i].size(); j++) {

				if (A[i] == B[j]) dp[i][j] = pair<int, int>(dp[i-1][j-1].first + v[A[i]], dp[i-1][j-1].second + 1);

				dp[i][j] = max(dp[i][j], dp[i-1][j], dp[i][j-1]);
			}

		}

		return dp[A.size()][B.size()].second;

	}

The time complexity of this algorithm is O(n^2) where n is the length of the longer of strings A and B. The inside of the loop is O(1), and it happens O(n^2) times.
