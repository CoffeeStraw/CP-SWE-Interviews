/**
 * Chandan and Balanced Strings - HackerEarth Hard
 * https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/practice-problems/algorithm/chandan-and-balanced-strings/
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    short unsigned t;
    cin >> t;

    while (t--)
    {
        string s;
        cin >> s;

        unordered_map<long long, long long> freq;
        long long x = 0, res = 0;
        freq[x] = 1;

        // XOR the numerical encoding of all the character c of s
        // and update the related frequency
        for (auto c : s)
        {
            x ^= 1 << (c - 'a');
            freq[x]++;
        }

        // Compute the number of possible pairs of equal XOR numbers
        for (auto &f : freq)
            res += f.second * (f.second - 1) / 2;

        cout << res << endl;
    }
    return 0;
}