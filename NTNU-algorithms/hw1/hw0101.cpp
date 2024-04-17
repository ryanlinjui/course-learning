// NOJ Problem #466 - Insertion Sort

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n=0,q=0;
    cin >> n >> q;
    int *a = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
    int mode = 0,position=0;
    for (int p = 0; p < q; p++)
    {
        cin >> mode;
        if (mode-1)
        {
            int ans=0;
            cin >> position;
            for (int i = 0; i < n; i++)
            {
                if (a[i] < a[position-1] || (a[i] == a[position-1] && position-1 > i)) ans++;
            }
            cout << ans + 1 << endl;
        }
        else
        {
            cin >> position;
            cin >> a[position-1];
        }
    }
    delete [] a;
    return 0;
}