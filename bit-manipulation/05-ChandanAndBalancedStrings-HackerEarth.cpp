#include <bits/stdc++.h>
using namespace std;

int main() {
	short unsigned t;
    cin >> t;
    
    while(t--){
        string s;
        cin >> s;

		unordered_map<long long, long long> freq;
        long long x = 0, res = 0;
        freq[x] = 1;
		
        for(auto c: s) {
            // XOR the numerical encoding of all the character c of s
            // and update the related frequency
			x ^= 1 << (c-'a');
			freq[x]++;
		}

        // Compute the number of possible pairs of equal XOR numbers
        for (auto& f: freq)
            res += f.second * (f.second-1) / 2;

		cout << res << endl;
	}
	return 0;
}