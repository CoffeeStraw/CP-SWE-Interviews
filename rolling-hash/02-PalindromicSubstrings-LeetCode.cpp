/**
 * Palindromic Substrings - Leetcode
 * https://leetcode.com/problems/palindromic-substrings/
 */

#include <vector>
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

    int countSubstrings(string s)
    {
        const int N = s.size();

        vector<int> prehash(N + 1), posthash(N + 1); // Integer are sufficient, given the chosen base M
        vector<long long> power(N + 1);
        power[0] = 1;

        // Compute the prefixes' and postfixes' hash of s and save powers (expensive to compute)
        for (int i = 0; i < N; ++i)
        {
            prehash[i + 1] = (prehash[i] * B + chrToInt(s[i])) % M;
            power[i + 1] = (power[i] * B) % M;
        }
        for (int i = N - 1; i >= 0; --i)
            posthash[i] = (posthash[i + 1] * B + chrToInt(s[i])) % M;

        // ===================================================================
        // Start counting palindromes using an "expand around center" approach
        // ===================================================================
        int res = 0;

        // Search for palindromes having odd length
        for (int i = 0; i < N; ++i)
        {
            // Binary search: search for the largest palindrom having center s[i]
            int start = 1, end = min(i + 1, N - i) + 1;
            while (end - start > 1)
            {
                int mid = (start + end) / 2;
                int l = i - mid + 1, r = i + mid - 1;

                // O(1) hashing of sub-strings
                // It is a slightly different formula from the one discussed in the editorial, because of 2 reasons:
                //     1) Modulo of negative numbers doesn't return a positive result;
                //     2) Risk of overflow.
                int s_hash = (prehash[r + 1] + M - (prehash[l] * power[r - l + 1]) % M) % M;
                int s_rev_hash = (posthash[l] + M - (posthash[r + 1] * power[r - l + 1]) % M) % M;

                if (s_hash == s_rev_hash)
                    start = mid;
                else
                    end = mid;
            }
            res += start;
        }

        // Search for palindromes having even length
        for (int i = 0; i + 1 < N; ++i)
        {
            int start = 0, end = min(i + 1, N - i - 1) + 1;
            while (end - start > 1)
            {
                int mid = (start + end) / 2;
                int l = i - mid + 1, r = i + mid;

                int s_hash = (prehash[r + 1] + M - (prehash[l] * power[r - l + 1]) % M) % M;
                int s_rev_hash = (posthash[l] + M - (posthash[r + 1] * power[r - l + 1]) % M) % M;

                if (s_hash == s_rev_hash)
                    start = mid;
                else
                    end = mid;
            }
            res += start;
        }

        return res;
    }
};