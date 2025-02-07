#include "Levenshtein.h"

// Function to compute Levenshtein Distance (Edit Distance)
int levenshteinDistance(const string& s1, const string& s2) {
    int len1 = s1.size();
    int len2 = s2.size();

    // Dynamically allocate 2D array
    int** dp = new int* [len1 + 1];
    for (int i = 0; i <= len1; i++)
        dp[i] = new int[len2 + 1];

    // Initialize base cases
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    // Compute edit distance
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min({ dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1] }) + 1;
        }
    }

    int distance = dp[len1][len2];

    // Free allocated memory
    for (int i = 0; i <= len1; i++)
        delete[] dp[i];
    delete[] dp;

    return distance;
}
