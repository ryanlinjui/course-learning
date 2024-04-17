// NOJ Problem #483 - Flight Planning
// Reference: https://medium.com/偏偏的演算法筆記/刷題筆記-leetcode-longest-increasing-subsequence-lis-3a09ec45679a

#include <iostream>
#include <stdint.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

uint32_t binary_search(vector<uint32_t> v, uint32_t target) 
{
    int32_t left = 0, right = v.size() - 1;
    while (left <= right) 
    {
        uint32_t mid = (left + right) / 2;
        if (v[mid] < target)    left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

uint32_t lis(vector<pair<uint32_t,uint32_t>> data)
{
    vector<uint32_t> dp;
    for (int i = 0; i < data.size(); i++) 
    {
        uint32_t lis = binary_search(dp, data[i].second) + 1;
        if (lis - 1 == dp.size()) dp.push_back(data[i].second);
        else dp[lis - 1] = data[i].second;
    }
    return dp.size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    uint32_t alan_num = 0, roc_num = 0, r = 0;
    cin >> alan_num >> roc_num >> r;

    vector<pair<uint32_t,uint32_t>> data(r);
    for (int i = 0; i < r; i++)
	{
		cin >> data[i].first >> data[i].second;
	}
    sort(data.begin(),data.end());

    for (int i = 1, start = data[0].first, start_index = 0; i < r; i++)
    {
        if(start != data[i].first || i == r - 1)
        {
            if(i == r - 1)
            {
                if(data[i].first == data[i-1].first) i++;
                else break;
            }
            
            for (int j = 0; j < (i-start_index)/2 && i-start_index > 1; j++)
            {
                swap(data[j+start_index].second,data[i-j-1].second);
            }
            start = data[i].first;
            start_index = i;
        }
    }

    cout << lis(data) << endl;
	return 0;
}