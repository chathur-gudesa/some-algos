/*
Lazy Propagation, supports range updates and range queries of the from add to range [l : r] and find max in range [l : r]
Construction : O(n)
Query : O(logn)
Reference : https://cp-algorithms.com/data_structures/segment_tree.html
Verification : 
*/

#include <bits/stdc++.h>
using namespace std;

#define int ll
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

const int MAXN = 2E5 + 100, INF = 1E9 + 5;
vector<int> ta(MAXN), t(4*MAXN), lazy(4*MAXN);

void push(int v) {
	t[2*v + 1] += lazy[v];
	lazy[2*v + 1] += lazy[v];
	t[2*v + 2] += lazy[v];
	lazy[2*v + 2] += lazy[v];
	lazy[v] = 0;
}

void build_tree(int v, int l, int r) {
	if(r < l)
		return;
	if(l == r) {
		t[v] = ta[l];
		return;
	}
	int mid = (l + r)/2;
	build_tree(2*v + 1, l, mid);
	build_tree(2*v + 2, mid + 1, r);
	t[v] = max(t[2*v + 1], t[2*v + 2]);
}

void update(int v, int l, int r, int tl, int tr, int val) {
	if(tr < tl)
		return;
	if(tr == r && tl == l) {
		lazy[v] += val;
		t[v] += val;
		return;
	}
	push(v);
	int mid = (l + r)/2;
	update(2*v + 1, l, mid, tl, min(tr, mid), val);
	update(2*v + 2, mid + 1, r, max(tl, mid + 1), tr, val);
	t[v] = max(t[2*v + 2], t[2*v + 1]);
}

int query(int v, int l, int r, int tl, int tr) {
	if(tr < tl)
		return -INF;
	if(tl == l && tr == r)
		return t[v];
	push(v);
	int mid = (l + r)/2;
	return max(query(2*v + 1, l, mid, tl, min(mid, tr)), 
			query(2*v + 2, mid + 1, r, max(tl, mid + 1), tr));
}

int32_t main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> ta[i];
	build_tree(0ll, 0ll, n - 1);
	int q;
	cin >> q;
	while(q--) {
		int flag;
		cin >> flag;
		if(flag) {
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << query(0ll, 0ll, n - 1, l, r) << '\n';
		}
		else {
			int l, r, k;
			cin >> l >> r >> k;
			--l, --r;
			update(0, 0, n - 1, l, r, k);
		}
	}
}