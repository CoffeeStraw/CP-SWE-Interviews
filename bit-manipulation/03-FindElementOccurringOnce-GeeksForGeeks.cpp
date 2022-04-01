/**
 * Find element occuring once when all other are present thrice - GeeksForGeeks Medium
 * https://practice.geeksforgeeks.org/problems/find-element-occuring-once-when-all-other-are-present-thrice/1
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int singleElement(int arr[], int n)
    {
        int once = 0, twice = 0;
        int not_thrice;

        for (int i = 0; i < n; i++)
        {
            // The following step will perform the following:
            // - 1st time seeing a number: XOR it to once;
            // - 2nd time seeing a number: remove it from once and XOR it to twice;
            // - 3rd time seeing a number: remove it from both once and twice.
            twice |= once & arr[i];
            once ^= arr[i];
            not_thrice = ~(once & twice);
            once &= not_thrice;
            twice &= not_thrice;
        }

        // Only one element appears once in the array, so it will be the only one left in once
        return once;
    }
};