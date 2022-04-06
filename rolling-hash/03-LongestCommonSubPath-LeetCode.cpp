/**
 * Longest Common Subpath - Leetcode
 * https://leetcode.com/problems/longest-common-subpath/
 */
using namespace std;

class Solution
{
public:
    // Rolling Hash parameters
    const long long B = 1299827, M = 1e11 + 7;

    bool check(vector<vector<int>> &paths, int k)
    {
        // Base case
        if (k == 0)
            return true;

        unordered_set<long long> prev;
        for (int i = 0; i < paths.size(); ++i)
        {
            // Early stop if no sub-arrays were found in common between two array
            if (i > 0 && prev.empty())
                break;

            // Compute rolling hash of the first window of paths[i]
            long long hash = 0, power = 1;
            for (int j = 0; j < k; ++j)
            {
                hash = (hash * B + paths[i][j]) % M;
                power = (power * B) % M;
            }

            // Save the common hashes between paths[i] and paths[i-1] in curr
            unordered_set<long long> curr;
            if (i == 0 || prev.count(hash))
                curr.insert(hash);

            for (int j = k; j < paths[i].size(); ++j)
            {
                hash = (hash * B + paths[i][j] - (power * paths[i][j - k] % M) + M) % M;
                if (i == 0 || prev.count(hash))
                    curr.insert(hash);
            }
            swap(prev, curr);
        }
        if (prev.empty())
            return false;
        return true;
    }

    int longestCommonSubpath(int elements, vector<vector<int>> &paths)
    {
        // Binary Search the answer
        int start = 0;
        int end = INT_MAX; // The end is set to the minimum size of the arrays, to avoid extra work
        for (int i = 0; i < paths.size(); ++i)
            end = min(end, (int)paths[i].size());

        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (check(paths, mid))
                start = mid + 1;
            else
                end = mid - 1;
        }
        return end;
    }
};
