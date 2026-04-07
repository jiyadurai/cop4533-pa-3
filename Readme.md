Problem 1:

![graph](image.png)
![lines of best fit](image-1.png)

Problem 2:
dp[i][j] = 
	0                                                    if i == 0 || j == 0
	max(dp[i-1][j], dp[i-1][j-1] + val[A[i]])            if A[i] == B[j]
	dp[i-1][j]                                           if A[i] != B[j]

Here, dp[i][j] represents the best value of the first i chars of A and j chars of B.
Obviously, if we have zero chars of either A or B, the best we can do is zero.
Otherwise, we could choose not to include the character at A[i], in which case it is the same value as dp[i-1][j].
Or, if A[i] and B[j] match, we could include those two characters and add them to the value of the two substrings without those chars, dp[i-1][j-1].

Problem 3:

int hvlcs(string A, string B, map<char, int> v) { 
	vector<vector<int>> dp = (A.size(), vector<int>(B.size(), 0));
	for (int i = 1; i < dp.size(); i++) {
		for (int j = 1; j < dp[i].size(); j++) {
			if (A[i] == B[j]) dp[i][j] = dp[i-1][j-1] + v[A[i]];
			dp[i][j] = max(dp[i][j], dp[i-1][j]);
		}
	}
	return dp[A.size()-1][B.size()-1];
}

The time complexity of this algorithm is O(n^2) where n is the length of the longer of strings A and B.
