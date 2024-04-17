// NOJ Problem #467 - Exploration progress

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n=0,m=0;
    cin >> n >> m;

    int *t = new int[n];
    int *t_diff = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
        t_diff[i] = 0;
    }

    int begin = 0, end = 0, percent = 0,ans=-1;
    for (int i = 0; i < m && ans==-1; i++)
    {
        cin >> begin >> end >> percent;
        if(percent==0) continue;
        t_diff[begin] += percent;
        if(end<n-1) t_diff[end+1] -= percent;
        for(int j = 0, sum = 0; j < n; j++)
        {
            sum += t_diff[j];
            if(t[j]-sum>0) break;
            if(j==n-1) ans = i+1;
        }
    }
    cout << ans << endl;
    delete [] t;
    delete [] t_diff;
    return 0;
}