// NOJ Problem #469 - Tans Covered

// Reference:
// https://www.geeksforgeeks.org/tiling-problem-using-divide-and-conquer-algorithm/?ref=rp

#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
void tiling(vector<vector<int>> &board, int l, int x, int y)
{
    if(l==2)
    {
        cnt++;
        for(int i = x; i < x+l; i++) 
        {
            for(int j = y; j < y+l; j++) 
            {
                board[i][j] = (board[i][j]==-1) ? cnt : board[i][j];
            }   
        }
        return;
    }

    vector<pair<int,int>> black;
    for(int i = x; i < x+l; i++) 
    {
        for(int j = y; j < y+l; j++) 
        {
            if(board[i][j] != -1) black.push_back(make_pair(i,j));
            if(black.size() > 1)
            {
                i = x+l;
                break;
            }
        }
        if(i == x+l-1)
        {
            cnt++;
            // cout << black[0].first << "," << black[0].second << " " << i << " " << j <<endl;
            if(black[0].first < x+l/2 && black[0].second < y+l/2)
            {
                board[x+l/2][y+l/2] = cnt;
                board[x+l/2][y+l/2-1] = cnt;
                board[x+l/2-1][y+l/2] = cnt;
            }
            else if (black[0].first >= x+l/2 && black[0].second < y+l/2)
            {
                board[x+l/2-1][y+l/2] = cnt;
                board[x+l/2][y+l/2] = cnt;
                board[x+l/2-1][y+l/2-1] = cnt;
            }
            else if (black[0].first < x+l/2 && black[0].second >= y+l/2)
            {
                board[x+l/2][y+l/2-1] = cnt;
                board[x+l/2][y+l/2] = cnt;
                board[x+l/2-1][y+l/2-1] = cnt;
            }
            else
            {
                board[x+l/2-1][y+l/2-1] = cnt;
                board[x+l/2][y+l/2-1] = cnt;
                board[x+l/2-1][y+l/2] = cnt;
            }
        }
    }
    tiling(board, l/2, x, y);
    tiling(board, l/2, x+l/2, y);
    tiling(board, l/2, x, y+l/2);
    tiling(board, l/2, x+l/2, y+l/2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n = 0, l = 0;
    cin >> n >> l;

    // board init
    vector<vector<int>> board(l);
    for (int i = 0; i < l; i++) board[i].resize(l, -1);
    for (int i = 0, x = 0, y = 0; i < n; i++)
    {
        cin >> x >> y;
        board[x][y] = 0;
    }
    tiling(board, l, 0, 0);

    // board print
    for (int i = 0; i < l; i++) 
    {
        for (int j = 0; j < l; j++) 
        {
            cout <<  board[j][i] << " ";
        }
        cout << endl;
    }
    return 0;
}