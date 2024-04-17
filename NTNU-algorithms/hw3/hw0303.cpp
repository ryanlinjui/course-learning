// NOJ Problem #503 - Lava

// Reference: 
// https://www.geeksforgeeks.org/flood-fill-algorithm/

#include <iostream>
#include <stdint.h>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

bool is_valid(vector<vector<int32_t>> room, int32_t visit_time, int32_t x, int32_t y)
{
    if(x < 0 || x >= room.size() || y < 0 || y >= room[0].size())
    {
        return false;
    }

    if (room[x][y] == -2 || room[x][y] == -3)
    {
        return false;
    }
    
    if(room[x][y] == -1)
    {
        return true;
    }
    return false;
}
 
void flood_fill(vector<vector<int32_t>> &room, vector<pair<int32_t, int32_t>> lava_list)
{
    queue<pair<int32_t,int32_t>> queue;
    for (int i = 0; i < lava_list.size(); i++)
    {
        queue.push(lava_list[i]);
    }

    while(!queue.empty())
    {
        pair<int32_t, int32_t> point = queue.front();
        
        int32_t x = point.first;
        int32_t y = point.second;
        // cout << "=======(" << x << "," << y << ")========\n";
        
        queue.pop();
        if(is_valid(room, room[x][y], x+1, y)) // down
        {
            // cout << "down: " << x+1 << " " << y << endl;
            room[x+1][y] = room[x][y] + 1;
            pair<int32_t, int32_t> p(x+1, y);
            queue.push(p);
        }

        if(is_valid(room, room[x][y], x-1, y)) // up
        {
            // cout << "up: " << x-1 << " " << y << endl;
            room[x-1][y] = room[x][y] + 1;
            pair<int32_t, int32_t> p(x-1, y);
            queue.push(p);
        }
 
        if(is_valid(room, room[x][y], x, y+1)) // right
        {
            // cout << "right: " << x << " " << y+1 << endl;
            room[x][y+1] = room[x][y] + 1;
            pair<int32_t, int32_t> p(x, y+1);
            queue.push(p);
        }
 
        if(is_valid(room, room[x][y], x, y-1)) // left
        {
            // cout<< "left: "  << x << " " << y-1 << endl;
            room[x][y-1] = room[x][y] + 1;
            pair<int32_t, int32_t> p(x, y-1);
            queue.push(p);
        }
    }
}

// void floodFill(vector<vector<int> >& screen, int sr, int sc, int row, int col, int source, int color){
//     if (sr < 0 || sr >= row || sc < 0 || sc >= col)
//         return;
 
//     if (screen[sr][sc] != source)
//         return;
   
//     screen[sr][sc] = color;
//     floodFill(screen, sr - 1, sc, row, col, source,
//               color); // left
//     floodFill(screen, sr + 1, sc, row, col, source,
//               color); // right
//     floodFill(screen, sr, sc + 1, row, col, source,
//               color); // top
//     floodFill(screen, sr, sc - 1, row, col, source,
//               color); // bottom
// }

bool is_valid_m(vector<vector<int32_t>> room, int32_t x, int32_t y)
{
    if(x < 0 || x >= room.size() || y < 0 || y >= room[0].size())
    {
        return false;
    }
    return true;
}

bool maze(vector<vector<int32_t>> room, int32_t threshold, int32_t x, int32_t y)
{
    if(x < 0 || x >= room.size() || y < 0 || y >= room[0].size())
    {
        return false;
    }

    // cout << x << " " << y << endl;

    if (is_valid_m(room, x, y+1)) // right
    {
        if(room[x][y+1] == -3)
        {
            return true;
        }
        if(room[x][y+1] > threshold)
        {
            room[x][y+1] = -1;
            return maze(room, threshold, x, y+1);
        }
    }

    if (is_valid_m(room, x, y-1)) // left
    {
        if(room[x][y-1] == -3)
        {
            return true;
        }
        if(room[x][y-1] > threshold)
        {
            room[x][y-1] = -1;
            return maze(room, threshold, x, y-1);
        }
    }
    
    if (is_valid_m(room, x-1, y)) // up
    {
        if(room[x-1][y] == -3)
        {
            return true;
        }
        if(room[x-1][y] > threshold)
        {
            room[x-1][y] = -1;
            return maze(room, threshold, x-1, y);
        }
    }

    if (is_valid_m(room, x+1, y)) // down
    {
        if(room[x+1][y] == -3)
        {
            return true;
        }
        if(room[x+1][y] > threshold)
        {
            room[x+1][y] = -1;
            return maze(room, threshold, x+1, y);
        }
    }

    return false;
}

int32_t binary_search(vector<vector<int32_t>> room, pair<int32_t, int32_t> src)
{
    int32_t low = 0, high = room.size() + room[0].size(), mid = 0;
    while (low <= high)
    {
        mid = (high + low) / 2;
        // cout << mid << " " << high <<" "<< low << endl;
        if(maze(room, mid, src.first, src.second))
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return mid;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0, m = 0, x = 0, y = 0;
    cin >> n >> m;
    vector<vector<int32_t>> room;
    vector<pair<int32_t, int32_t>> lava_list;
    pair<int32_t, int32_t> bed_point;
    
    /*
        L : 0, increasing number, store point
        O : -2
        C : -1
        B : -2, store point 
        D : -3
    */

    string element = "";
    for (int i = 0; i < n; i++)
    {
        cin >> element;
        vector<int32_t> tmp;
        for (int j = 0; j < element.size(); j++)
        {   
            if(element[j] == 'L')
            {
                pair<int32_t, int32_t> a(i, j);
                lava_list.push_back(a);
                tmp.push_back(0);
            }
            else if(element[j] == 'O')
            {
                tmp.push_back(-2);
            }
            else if(element[j] == 'C')
            {
                tmp.push_back(-1);
            }
            else if(element[j] == 'B')
            {
                bed_point.first = i;
                bed_point.second = j;
                tmp.push_back(-2);
            }
            else if(element[j] == 'D')
            {
                tmp.push_back(-3);
            }
            
        }
        room.push_back(tmp);
    }

    flood_fill(room, lava_list);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << room[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    cout << binary_search(room, bed_point) - 1 << endl;
	return 0;
}