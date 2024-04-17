// NOJ Problem #482 - BST

#include <iostream>
#include <stdint.h>
#include <algorithm>

using namespace std;

#define MAX_LEN 400

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint64_t table[MAX_LEN][MAX_LEN];
    uint64_t a[MAX_LEN];
    int32_t n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a,a+n);

    table[0][0] = a[0];
    for (int i = 0; i < n-1; i++)
    {
        table[i][i] = a[i];
        table[i+1][i+1] = a[i+1];
        table[i][i+1] = table[i][i] + table[i+1][i+1];
    }
    
    for (int i = 2; i < n; i++)
    {
        for (int j = 0; j < n-i; j++)
        {
            table[j][j+i] = 1e10;
            for (int k = j; k <= j+i; k++)
            {    
                if(k == j) 
                {
                    table[j][j+i] = min(table[j][j+i], table[k][k]+table[k+1][j+i]);
                }
                else if(k == j+i) 
                {
                    table[j][j+i] = min(table[j][j+i], table[k][k]+table[j][k-1]);
                }
                else
                {
                    table[j][j+i] = min(table[j][j+i], table[k][k]+max(table[j][k-1],table[k+1][j+i]) );
                }   
            }   
        }
    }
	cout << table[0][n-1] << endl;
	return 0;
}