/**
 * Minimal Rotation - CSES
 * https://cses.fi/problemset/task/1110/
 */

#include <iostream>
#include <vector>
using namespace std;

// Rolling Hash parameters (should be reasonably collision-free for small strings)
const long long B = 26, M = 2'147'483'587ll;

/** Compute the smallest representation possible for c, to avoid overflow
 * This is possible because the only characters to work with are lowercase english letters
 */
int chrToInt(char c)
{
    return c - 'a' + 1;
}

int main()
{
    string s;
    cin >> s;

    // Concatenate a copy of s to quickly handle all the rotations
    s += s;
    const int N = s.size();

    vector<int> prehash(N + 1);
    vector<long long> power(N + 1);
    power[0] = 1;

    // Compute the prefixes' hash of s and save powers (expensive to compute)
    for (int i = 0; i < N; ++i)
    {
        prehash[i + 1] = (prehash[i] * B + chrToInt(s[i])) % M;
        power[i + 1] = (power[i] * B) % M;
    }

    // Search for the minimum
    int k = 0;
    for (int i = 1; i < N / 2; i++)
    {
        // Binary search for the last index of the largest common prefix
        int start = 0, end = N / 2 - 1;
        while (start <= end)
        {
            int mid = (start + end) / 2;
            int hash1 = (prehash[i + mid + 1] + M - (prehash[i] * power[mid + 1]) % M) % M;
            int hash2 = (prehash[k + mid + 1] + M - (prehash[k] * power[mid + 1]) % M) % M;

            if (hash1 == hash2)
                start = mid + 1;
            else
                end = mid - 1;
        }

        // Compare the two character after the largest common prefix to determine order
        if (start <= N / 2 - 1 && s[i + start] < s[k + start])
            k = i;
    }

    cout << s.substr(k, N / 2) << endl;
}