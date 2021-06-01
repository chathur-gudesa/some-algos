/*
Finds briges in a CONNECTED graph
Time Complexity : O(n + m)
Reference : https://codeforces.com/blog/entry/68138
Verification : CodeForces 118E Bertown Roads https://codeforces.com/problemset/problem/118/E
*/
#include <bits/stdc++.h>
using namespace std;

/*
The edge from u (!= 0) to its parent is a bridge iff dp[u] = 0
*/

const int MAX = 2E5 + 100;

int n, m;
int col[MAX], par[MAX], dp[MAX];
vector<int> adj[MAX];

void DFS(int u = 0) {
	col[u] = 1;
	for(int v : adj[u]) {
		if(col[v])
			continue;
		par[v] = u;
		DFS(v);
		dp[u] += dp[v];
	}
	for(int v : adj[u]) {
		if(v == par[u] || u == par[v])
			continue;
		if(col[v] == 1)
			dp[u]++;
		else
			dp[u]--;
	}
	col[u] = 2;
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	DFS();
}