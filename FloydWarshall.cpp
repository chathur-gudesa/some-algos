/*
Given a directed graph with possibly negative edges (but no negative cycles), find shortest path between any two nodes u and v.
Time Complexity : O(n^3) Work actually faster (apparently, needs verification) because operations are simple
Verification : 
Reference : https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end() 
#define sz(v) (int)((v).size())
#define fs first
#define sd second

typedef long long ll;

typedef pair < int, int > pi;
typedef pair < pi, int > ppi;

typedef vector < int > vi;
typedef vector < vector < int > > vvi;
typedef vector < pi > vpi;
typedef vector < vpi > vvpi;
typedef vector < ppi > vppi;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

vector<string> vec_splitter(string s) {
	s += ',';
	vector<string> res;
	while(!s.empty()) {
		res.push_back(s.substr(0, s.find(',')));
		s = s.substr(s.find(',') + 1);
	}
	return res;
}

void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
	stringstream ss; ss << H;
	cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}

#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif

double get_time() {
	return 1.0 * clock() / CLOCKS_PER_SEC;
}

const int MAXN = 200, INF = 1E9 + 5;
int d[MAXN][MAXN];
int n, m;

int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			d[i][j] = INF;
	}
	for(int i = 0, u, v, w; i < m; i++) {
		cin >> u >> v >> w;
		--u, --v;
		d[u][v] = w; // directed graph!
	}
	for(int k = 0; k < n; k++) {
		// INV : d[i][j] = min dist from i to j s.t. only intermediate nodes are in [0, k)
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	// d[u][v] = shortest path from u to v
}
