// NOJ Problem #485 - More Flight Planning

// Reference: 
// https://blog.csdn.net/Non_Cease/article/details/6918848

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int lis(const vector<int>& data)
{
    vector<int> dp;
    for (int i = 0; i < data.size(); i++)
    {
        auto it = lower_bound(dp.begin(), dp.end(), data[i]);
        if (it == dp.end())
            dp.push_back(data[i]);
        else
            *it = data[i];
    }
    return dp.size();
}

vector<int> getPositions(const vector<int>& s1, const vector<int>& s2)
{
    unordered_map<int, vector<int>> positions;

    for (int i = 0; i < s2.size(); i++)
    {
        positions[s2[i]].push_back(i);
    }

    vector<int> s3;
    s3.reserve(s1.size());
    for (int i = 0; i < s1.size(); i++)
    {
        const auto& pos = positions.find(s1[i]);
        if (pos != positions.end())
        {
            const vector<int>& positionsList = pos->second;
            s3.insert(s3.end(), positionsList.rbegin(), positionsList.rend());
        }
    }
    return s3;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> arr1(n);
    vector<int> arr2(m);
    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> arr2[i];
    }

    vector<int> positions = getPositions(arr1, arr2);
    cout << lis(positions) << endl;

    return 0;
}