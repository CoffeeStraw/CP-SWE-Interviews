/**
 * Implement strStr() - Leetcode
 * https://leetcode.com/problems/implement-strstr/
 */

using namespace std;

class Solution
{
public:
    // Rolling Hash parameters (should be reasonably collision-free for small strings)
    const long long B = 26, M = 2'147'483'587ll;

    /** Compute the smallest representation possible for c, to avoid overflow
     * This is possible because the only characters to work with are lowercase english letters
     */
    int chrToInt(char c)
    {
        return c - 'a' + 1;
    }

    int strStr(string s2, string s1)
    {
        // Base case
        if (s1.size() > s2.size())
            return -1;

        // Compute rolling hash of s1 and the first window of s2
        long long hash1 = 0, hash2 = 0, power = 1;
        for (int i = 0; i < s1.size(); ++i)
        {
            hash1 = (hash1 * B + chrToInt(s1[i])) % M;
            hash2 = (hash2 * B + chrToInt(s2[i])) % M;
            power = (power * B) % M;
        }

        if (hash1 == hash2)
            return 0;

        // Move the window, re-compute rolling hash in O(1) and check for a match
        for (int i = 0; i < s2.size() - s1.size(); ++i)
        {
            hash2 = (hash2 * B - chrToInt(s2[i]) * power + chrToInt(s2[i + s1.size()])) % M;
            if (hash2 < 0)
                hash2 += M;
            if (hash1 == hash2)
                return i + 1;
        }
        return -1;
    }
};