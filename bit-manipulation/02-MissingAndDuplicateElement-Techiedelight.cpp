#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        pair <int, int> findMissingAndDuplicate(vector <int> const & nums) {
            // XOR all the elements in A and numbers in the range 1...n
            // We will be left with the XOR between the missing number and the duplicate number
            int res = 0;
            for (int i = 0; i < nums.size(); i++)
                res ^= nums[i] ^ (i + 1);

            // Get the index of the first lsb set
            int k = ffs(res) - 1;

            // Either the duplicate or missing number will have the k-th bit set (not both)
            // Split res in two variables:
            // - x, holding the XOR of all the elements in nums and 1...n having the k-th bit set
            // - y, holding the XOR of the other elements
            int x = 0, y = 0;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] & (1 << k))
                    x ^= nums[i];
                else
                    y ^= nums[i];

                if ((i + 1) & (1 << k))
                    x ^= i + 1;
                else
                    y ^= i + 1;
            }

            // Either x or y is the missing element now
            // To distinguish between the two, we perform a linear search for the missing element
            if (find(nums.begin(), nums.end(), x) == nums.end())
                return make_pair(y, x);
            return make_pair(x, y);
        }
};