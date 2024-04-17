// NOJ Problem #512 - NSFW

// Reference: 
// https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

#include <iostream>
#include <vector>
#include <unordered_map>

#define INF 1e9

using namespace std;

void floyd_warshall(vector<vector<int32_t>> &graph)
{
    for (int k = 0; k < graph.size(); k++) 
	{
		for (int i = 0; i < graph.size(); i++) 
		{
            for (int j = 0; j < graph.size(); j++) 
			{
                if (graph[i][j] > (graph[i][k] + graph[k][j]) && (graph[k][j] != INF && graph[i][k] != INF))
				{
					graph[i][j] = graph[i][k] + graph[k][j];
				}   
            }
        }
    }
}

int main() 
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
	
	vector<vector<int32_t>> graph(n);
	for (int i = 0; i < n; i++)
	{
		graph[i].resize(n, INF);
		graph[i][i] = 0;
	}
	
    unordered_map<string, int32_t> township_num;

    for (int i = 0, count = 0; i < m; i++) 
	{
        string t, s;
        int32_t d;
        cin >> t >> s >> d;
		if (township_num.find(t) == township_num.end())
		{
			township_num[t] = count;
			count++;
		}
		if (township_num.find(s) == township_num.end())
		{
			township_num[s] = count;
			count++;
		}
		graph[township_num[t]][township_num[s]] = min(graph[township_num[t]][township_num[s]], d);
		graph[township_num[s]][township_num[t]] = min(graph[township_num[t]][township_num[s]], d);
    }
	
	floyd_warshall(graph);

	int32_t totle_distance = 0;
	string u, v;

	for (int i = 0; i < k; i++)
	{
		cin >> v;
		if(i == 0) 
		{
			u = v;
			continue;
		}

		totle_distance += graph[township_num[u]][township_num[v]];
		u = v;
	}
	
	cout << totle_distance << endl;
    return 0;
}