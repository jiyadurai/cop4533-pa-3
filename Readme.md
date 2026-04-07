Problem 1:

![graph](image.png)
![lines of best fit](image-1.png)

Problem 2:


dp[i][j] = 
	0                                              if i == 0 || j == 0
	max(dp[i-1][j], dp[i-1][j-1] + val[A[i]])            if A[i] == B[j]
	dp[i-1][j]                                           if A[i] != B[j]

