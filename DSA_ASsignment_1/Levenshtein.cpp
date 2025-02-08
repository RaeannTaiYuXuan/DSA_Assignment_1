#include "Levenshtein.h"

//==================================== Raeann Tai Yu Xuan S10262832J - Function to determine two strings by counting max no of operation needed to transfer to another ====================================

/*
 * Computes the Levenshtein Distance (Edit Distance) between two strings.
 *
 * The Levenshtein Distance is a measure of the minimum number of operations
 * (insertions, deletions, and substitutions) required to convert one string into another.
 *
 * The function uses dynamic programming with a 2D table (dp) where:
 *   - dp[i][j] represents the edit distance between the first i characters of s1
 *     and the first j characters of s2.
 *   - If characters match, no operation is needed (dp[i][j] = dp[i-1][j-1]).
 *   - Otherwise, the minimum of three possible operations is considered:
 *     1. Substitution (dp[i-1][j-1])
 *     2. Insertion (dp[i][j-1])
 *     3. Deletion (dp[i-1][j])
 *
 * The algorithm has a time complexity of O(m * n), where:
 *   - m is the length of s1
 *   - n is the length of s2
 */


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
