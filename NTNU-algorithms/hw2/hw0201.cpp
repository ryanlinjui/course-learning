// NOJ Problem #481 - Weird Coin

// Reference:
// https://www.geeksforgeeks.org/coin-change-dp-7/

#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

uint64_t count(vector<uint64_t> coin_set, uint64_t n, uint64_t m)
{
	vector<uint64_t> table(n+1);
	table[0] = 1;
    bool is_mod = false;

	for (int i = 0; i < m; i++)
    {
        if(i>3) is_mod = true;
        for (int j = coin_set[i]; j <= n; j++)
        {
            table[j] = (is_mod) ? (table[j]+table[j-coin_set[i]])%1000000007 : table[j]+table[j-coin_set[i]];
        }
    }
	return table[n];
}

int main()
{
    vector<uint64_t> coin_set;
    uint64_t n = 0, m = 0;
    cin >> n;
    for (m;; m++)
    {
        if(n >= (1<<m)) coin_set.push_back(1<<m);
        else break;
    }
	cout << count(coin_set, n, m) << endl;
	return 0;
}