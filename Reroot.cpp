#include <bits/stdc++.h>
using namespace std;

#define mainspring cout<<"mainspring\n";
#define barrel cout<<"barrel\n";
#define escapement cout<<"escapement\n";

#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end() 
#define sz(v) (int)((v).size())
#define fs first
#define sd second
#define tik(i,a,b) for(int i = a; i < b; i++)
#define tok(i,a,b) for(int i = a; i >= b; i--)
#define error(args...) {string _s = #args; replace(_s.begin(), _s.end(), ',',' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it,args);}

typedef long long ll;
typedef unsigned long long ull;

#define int ll 

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

void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

const int MOD = 1E9 + 7, MAXN = 2E5 + 100;
int f_inv[MAXN], f[MAXN], dp1[MAXN], dp2[MAXN], des[MAXN], inv[MAXN], n;
vvi adj(MAXN);

ll pow(ll x, ll y) {
	if(y == 0)
	return 1;
	ll temp = pow(x, y/2);
	temp = (temp*temp)%MOD;
	if(y%2 == 1)
		temp *= x;
	return temp%MOD;
}

void DFS(int u = 0, int p = 0) {
	des[u] = 1;
	dp1[u] = 1;
	for(int v : adj[u]) {
		if(v != p) {
			DFS(v, u);
			des[u] += des[v];
			dp1[u] = (dp1[u]*dp1[v])%MOD;
			dp1[u] = (dp1[u]*f_inv[des[v]])%MOD;
		}
	}
	dp1[u] = (dp1[u]*f[des[u] - 1])%MOD;
}

void reroot(int u = 0, int p = 0) {
	//reroot to each child of u
	for(int v : adj[u]) {
		if(v == p)
			continue;
		dp2[v] = (dp2[u]*des[v])%MOD;
		dp2[v] = (dp2[v]*inv[des[0] - des[v]])%MOD;
		reroot(v, u);
	}
}

int32_t main() {
	f_inv[0] = f[0] = 1;
	for(int i = 0; i < MAXN - 1; i++) {
		f_inv[i + 1] = (f_inv[i]*pow(i + 1, MOD - 2))%MOD;
		f[i + 1] = (f[i]*(i + 1))%MOD;
	}
	inv[1] = 1;
	for(int i = 2; i < MAXN; i++)
		inv[i] = pow(i, MOD - 2);
	cin >> n;
	for(int i = 0, u, v; i < n - 1; i++) {
		cin >> u >> v, --u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	DFS();
	dp2[0] = dp1[0];
	reroot();
	int ans = 0;
	for(int i = 0; i < n; i++) {
		ans = (ans + dp2[i])%MOD;
	}
	cout << ans;
}