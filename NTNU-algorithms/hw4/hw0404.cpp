// NOJ Problem #515 - Hapi Patrol Officers

// Reference: 
// https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>

using namespace std;

bool bfs(vector<vector<int32_t>> &r_graph, int32_t s, int32_t t, vector<int32_t> &parent)
{
	vector<bool> visited(r_graph.size(), false);
	queue<int32_t> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) 
    {
		int32_t u = q.front();
		q.pop();

		for (int v = 0; v < r_graph.size(); v++) 
        {
			if (visited[v] == false && r_graph[u][v] > 0) 
            {
				if (v == t) 
                {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return false;
}

int32_t ford_fulkerson(vector<vector<int32_t>> &graph, int32_t s, int32_t t)
{
	int32_t u = 0, v = 0;
	vector<vector<int32_t>> r_graph = graph;
	vector<int32_t> parent(graph.size());
	int32_t max_flow = 0;

	while (bfs(r_graph, s, t, parent)) 
    {
		int32_t path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) 
        {
			u = parent[v];
			path_flow = min(path_flow, r_graph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) 
        {
			u = parent[v];
			r_graph[u][v] -= path_flow;
			r_graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0;
    cin >> n;
    int32_t office_num = n;

    n = n * 2 + 2;
	vector<vector<int32_t>> graph(n);
    for (int i = 0; i < n; i++)
	{
		graph[i].resize(n, 0);
	}

    for (int i = 0; i < office_num; i++)
    {
        cin >> graph[0][i+1];
        graph[i+1][office_num+i+1] = graph[0][i+1];
    }

    int32_t totle_patrol = 0;
    for (int i = 0; i < office_num; i++)
    {
        cin >> graph[n-office_num-1+i][n-1];
        totle_patrol += graph[n-office_num-1+i][n-1];
    }
    
    for (int i = 0; i < office_num; i++) 
	{
        for (int j = 0; j < office_num; j++) 
	    {
            int32_t num;
            cin >> num;
            if(num)
            {
                graph[i+1][n-office_num-1+j] = num;
            }
        }
    }

	cout << totle_patrol - ford_fulkerson(graph, 0, n-1) << endl;
	return 0;
}

