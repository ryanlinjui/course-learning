// NOJ Problem #500 - Shopocalypse Now: Finding Critical Roads in a Town

// Reference: 
// https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
// https://stackoverflow.com/questions/28917290/how-can-i-find-bridges-in-an-undirected-graph

#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <stdint.h>

using namespace std;

class Graph
{
    int32_t node_num; 
    list<int32_t> *adj;
    vector<int32_t> low;
    vector<int32_t> pre;
    int32_t cnt;
    void dfs(int32_t u, int32_t v);

    public:
        Graph(int32_t node_num);
        void add_edge(int32_t v, int32_t w);
        void run_bridge();
        vector<pair<int32_t, int32_t>> bridge;
};

Graph::Graph(int32_t node_num)
{
    this->node_num = node_num;
    adj = new list<int32_t>[node_num];
    for (int i = 0; i < node_num; i++) 
    {
        low.push_back(-1);
        pre.push_back(-1);
    }
    cnt = 0;
}

void Graph::add_edge(int32_t u, int32_t v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::dfs(int32_t u, int32_t v)
{
    pre[v] = cnt++;
    low[v] = pre[v];
    
    for (list<int32_t>::iterator w = adj[v].begin(); w != adj[v].end(); w++)
    {
        if (pre[*w] == -1) 
        {
            dfs(v, *w);
            low[v] = min(low[v], low[*w]);
            if (low[*w] == pre[*w]) 
            {
                pair<int32_t, int32_t> a(v, *w);
                if(a.first > a.second)
                {
                    swap(a.first, a.second);
                }
                bridge.push_back(a);
            }
        }
        else if (*w != u)
        {
            low[v] = min(low[v], pre[*w]);
        }
    }
}

void Graph::run_bridge()
{
    for (int i = 0; i < node_num; i++)
    {
        if (pre[i] == -1) 
        {
            dfs(i, i);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0,m = 0;
    cin >> n >> m;
    
    Graph g(n);
    
    for (int i = 0, u = 0, v = 0; i < m; i++)
    {
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.run_bridge();
    sort(g.bridge.begin(),g.bridge.end());
    
    if(g.bridge.size() == 0) 
    {
        cout << "No Critical Road" << endl;
    }
    else
    {
        for (int i = 0; i < g.bridge.size(); i++)
        {   
            cout << g.bridge[i].first << " " << g.bridge[i].second << endl;
        }
    } 

    return 0;
}