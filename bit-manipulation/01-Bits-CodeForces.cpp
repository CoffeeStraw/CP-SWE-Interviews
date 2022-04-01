/**
 * Bits - CodeForces Div.1
 * https://codeforces.com/problemset/problem/484/A
 */

#include <iostream>
using namespace std;

int main()
{
    short unsigned n;
    cin >> n;

    while (n--)
    {
        // Due to constraints, we need types having at least 60 bits
        uint64_t l, r;
        cin >> l >> r;

        // Greedily set bits, from lsb to msb
        // Stop whenever setting the current bit would mean going over 'r'
        uint64_t set = 1;
        for (char pos = 0; pos < 60; pos++)
        {
            if ((l | set) > r)
                break;
            l |= set;
            set <<= 1;
        }

        cout << l << endl;
    }

    return 0;
}