/**
 * Maximum subset XOR - GeeksForGeeks Hard
 * https://practice.geeksforgeeks.org/problems/maximum-subset-xor/1/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxSubarrayXOR(int nums[], int n)
    {
        int index = 0;
        for (int i = 31; i >= 0; i--)
        {
            // Find the maximum element with i-th bit set
            int maximum = -1;
            int maximumIndex = index;
            for (int j = index; j < n; j++)
                if ((nums[j] & (1 << i)) != 0 && nums[j] > maximum)
                {
                    maximum = nums[j];
                    maximumIndex = j;
                }

            if (maximum == -1)
                continue;

            // Move maximum to the dead zone
            swap(nums[index], nums[maximumIndex]);
            maximumIndex = index;

            // XOR the maximum with other elements having the i-th bit set
            for (int j = 0; j < n; j++)
                if (j != maximumIndex && (nums[j] & (1 << i)) != 0)
                    nums[j] ^= nums[maximumIndex];

            index++;
        }

        // Return the XOR of all the final elements as our answer
        int res = nums[0];
        for (int i = 1; i < n; i++)
        {
            res ^= nums[i];
        }
        return res;
    }
};