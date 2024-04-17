// NOJ Problem #504 - Corgi-Ball

#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

int32_t find_minimum_ball(vector<vector<int32_t>> seq, int32_t ball_num, vector<int32_t> last_list)
{   
    vector<int32_t> group(ball_num+1);
    vector<int32_t> prev_ball(ball_num+1, -1);

    for (int i = 0; i < seq.size(); i++)
    {
        for (int j = 0; j < seq[i].size(); j++)
        {   
            if(j == 0)
            {
                prev_ball[seq[i][j]] = -1;
            }
            else
            {
                prev_ball[seq[i][j]] = seq[i][j-1];
            }
        }
    }

    int32_t minimum_ball = 1;
    for (int i = 1; i <= ball_num; i++)
    {
        if(prev_ball[i] != -1)
        {
            minimum_ball = max(group[prev_ball[i]]+1, minimum_ball);
        }
        group[i] = minimum_ball;
    }

    if(minimum_ball > 3 && last_list[0] < last_list[2] && last_list[2] < last_list[1])
    {
        if(group[last_list[1]] == group[last_list[2]])
        {
            minimum_ball++;
        }
    }

    return minimum_ball;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0, m = 0;
    cin >> n >> m;

    vector<vector<int32_t>> seq;
    vector<int32_t> last_list;

    vector<int32_t> sub_seq;
    for (int i = 0, a = 0; i < m; i++)
    {
        cin >> a;
        if(i >= m - 3)
        {
            last_list.push_back(a);
        }

        if(sub_seq.size() == 0)
        {
            sub_seq.push_back(a);
        }
        else if(sub_seq.back() > a)
        {
            seq.push_back(sub_seq);
            sub_seq.clear();
            sub_seq.push_back(a);
        }
        else
        {
            sub_seq.push_back(a);
        }
        if (i == m - 1)
        {
            seq.push_back(sub_seq);
            break;
        }
    } 

    cout << find_minimum_ball(seq, n, last_list) << endl;
	return 0;
}