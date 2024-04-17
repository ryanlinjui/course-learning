// NOJ Problem #513 - Optimizing Hotel Success

// Reference: 
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct Edge 
{
    int32_t dest;
    double success_prob;
};

vector<double> dijkstra(vector<vector<Edge>> &graph, int32_t start) 
{
    vector<double> success_prob_list(graph.size(), 0.0);
    vector<bool> visited(graph.size(), false);
    priority_queue<pair<double, int32_t>> pq;
    pq.push({1.0, start});
    success_prob_list[start] = 1.0;
    
    while (!pq.empty()) 
	{
        int32_t u = pq.top().second;
        pq.pop();
        
        if (visited[u])
		{
            continue;
		}
        visited[u] = true;
        
        for (int i = 0; i < graph[u].size(); i++) 
		{
			Edge edge = graph[u][i];
            int32_t v = edge.dest;
            double prob= edge.success_prob;
            double new_prob = success_prob_list[u] * prob;
            
            if (new_prob > success_prob_list[v]) 
			{
                success_prob_list[v] = new_prob;
                pq.push({new_prob, v});
            }
        }
    }
    
    return success_prob_list;
}

int main() 
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0, m = 0;
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n);
    
    for (int i = 0; i < m; i++) 
	{
        int32_t a, b;
        double p;
        cin >> a >> b >> p;
        graph[a].push_back({b, p});
        graph[b].push_back({a, p});
    }
    
    int32_t start = 0, end = 0;
    cin >> start >> end;
    vector<double> success_prob_list = dijkstra(graph, start);
    
    cout << fixed << setprecision(3) << success_prob_list[end] << endl;
    return 0;
}
