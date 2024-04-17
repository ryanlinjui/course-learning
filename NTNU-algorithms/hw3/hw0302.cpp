// NOJ Problem #502 - Budget Cut

// Reference:
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdint.h>

using namespace std;

struct Graph
{
	int32_t V, E;
	vector<pair<int32_t, pair<int32_t, int32_t>>> edges;

	Graph(int32_t V, int32_t E)
	{
		this->V = V;
		this->E = E;
	}

	void add_edge(int u, int v, int w)
	{
		edges.push_back({w, {u, v}});
	}

	int32_t find_bottleneck();
    int32_t kruskalMST(int32_t bottle_neck);

};

struct DisjointSets
{
	int32_t *parent, *rnk;
	int32_t n;

	DisjointSets(int32_t n)
	{
		this->n = n;
		parent = new int32_t[n+1];
		rnk = new int32_t[n+1];
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	int32_t find(int32_t u)
	{
		if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
		return parent[u];
	}

	void merge(int32_t x, int32_t y)
	{
		x = find(x);
        y = find(y);

		if (rnk[x] > rnk[y])
        {
            parent[y] = x;
        }	
		else
        {
	        parent[x] = y;
        }

		if (rnk[x] == rnk[y])
        {
            rnk[y]++;
        }
	}
};

int32_t Graph::find_bottleneck()
{
	int32_t bottle_neck = 1e8;
    sort(edges.begin(), edges.end(), greater<pair<int32_t, pair<int32_t, int32_t>>>());

	DisjointSets ds(V);
	for (vector<pair<int32_t, pair<int32_t, int32_t>>>::iterator it = edges.begin(); it!=edges.end(); it++)
	{
		int32_t u = it->second.first;
		int32_t v = it->second.second;
		int32_t set_u = ds.find(u);
		int32_t set_v = ds.find(v);
		if (set_u != set_v)
		{
			bottle_neck = min(bottle_neck, it->first);
			ds.merge(set_u, set_v);
		}
	}
	return bottle_neck;
}

int32_t Graph::kruskalMST(int32_t bottle_neck)
{
	int32_t mst_wt = 0;
    sort(edges.begin(), edges.end());

	DisjointSets ds(V);
	for (vector<pair<int32_t, pair<int32_t, int32_t>>>::iterator it = edges.begin(); it!=edges.end(); it++)
	{
		int32_t u = it->second.first;
		int32_t v = it->second.second;
		int32_t set_u = ds.find(u);
		int32_t set_v = ds.find(v);
		if (set_u != set_v && it->first >= bottle_neck)
		{
			mst_wt += it->first;
			ds.merge(set_u, set_v);
		}
	}
	return mst_wt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0,m = 0;
    cin >> n >> m;
    
    Graph g(n, m);
	for (int i = 0, u = 0, v = 0, w = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    int32_t bottle_neck = g.find_bottleneck();
    int32_t mst_wt = g.kruskalMST(bottle_neck);
	cout << mst_wt << endl;

	return 0;
}