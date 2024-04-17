// NOJ Problem #514 - V's Trip

// Reference: 
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#include <iostream>
#include <queue>
#include <vector>
#include <stdint.h>

using namespace std;

struct Node 
{
    int32_t index;
    int32_t voucher;
    int32_t cost;
    int32_t cities;

    Node(int32_t i, int32_t v, int32_t c, int32_t ct) : index(i), voucher(v), cost(c), cities(ct) {}

    bool operator>(const Node& other) const 
    {
        if (cost != other.cost)
        {
            return cost > other.cost;
        }
        return cities < other.cities;
    }
};

void sol(vector<vector<pair<int32_t, int32_t>>>& graph) 
{
    vector<vector<Node>> dp(graph.size(), vector<Node>(2, {0, 0, numeric_limits<int>::max(), 0}));
    dp[0][0] = {0, 0, 0, 1};
    dp[0][1] = {0, 0, 0, 1};

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, 0, 0, 0});

    while (!pq.empty()) 
    {
        Node curr = pq.top();
        pq.pop();

        if (curr.cost > dp[curr.index][curr.voucher].cost)
        {
            continue;
        }

        for (auto& edge : graph[curr.index]) 
        {
            int32_t next_node = edge.first;
            int32_t next_cost = edge.second;

            if (curr.cost + next_cost < dp[next_node][curr.voucher].cost || (curr.cost + next_cost == dp[next_node][curr.voucher].cost && curr.cities + 1 > dp[next_node][curr.voucher].cities)) 
            {
                dp[next_node][curr.voucher] = {next_node, curr.voucher, curr.cost + next_cost, curr.cities + 1};
                pq.push(dp[next_node][curr.voucher]);
            }

            if (curr.voucher == 0) 
            {
                if (curr.cost < dp[next_node][1].cost || (curr.cost == dp[next_node][1].cost && curr.cities + 1 > dp[next_node][1].cities)) 
                {
                    dp[next_node][1] = {next_node, 1, curr.cost, curr.cities + 1};
                    pq.push(dp[next_node][1]);
                }
            }
        }
    }

    Node without_voucher = dp[graph.size() - 1][0];
    Node with_voucher = dp[graph.size() - 1][1];

    if (without_voucher.cost < with_voucher.cost)
    {
        cout << without_voucher.cost << " " << without_voucher.cities - 1 << endl;
    }
    else if (without_voucher.cost > with_voucher.cost)
    {
        cout << with_voucher.cost << " " << with_voucher.cities - 1 << endl;
    }
    else
    {
       cout << without_voucher.cost << " " << max(without_voucher.cities, with_voucher.cities) - 1 << endl;
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int32_t n = 0, m = 0;
    cin >> n >> m;
    vector<vector<pair<int32_t, int32_t>>> graph(n);

    for (int i = 0; i < m; i++) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u-1].emplace_back(v - 1, w);
        graph[v-1].emplace_back(u - 1, w);
    }

    sol(graph);
    return 0;
}