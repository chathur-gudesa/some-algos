//Construction : O(n)
//Queries : O(logn)
//The function f must be associative, make sure to change the null set values (see comments below)
//Verification : 
//Reference : https://cp-algorithms.com/data_structures/segment_tree.html

#include <bits/stdc++.h>
using namespace std;

#define int ll

#define pb push_back
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

const int INF = 1E15 + 5,  MAX = 2E5 + 100;

vector<int> ta(MAX), t(4*MAX);

int f(int x, int y) {
	return x + y;
}

void build_tree(int v, int l, int r) {
	if(l == r) {
		t[v] = ta[l];
		return;
	}
	int mid = (l + r)/2;
	build_tree(2*v + 1, l, mid);
	build_tree(2*v + 2, mid + 1, r);
	t[v] = f(t[2*v + 1], t[2*v + 2]);
}

int query(int v, int l, int r, int tl, int tr) {
	if(tl > tr)
		return 0; //change to 0 value (-INF for max queries, INF for min queries)
	if(l == tl && r == tr) {
		return t[v];
	}
	int mid = (l + r)/2;
	return f(query(2*v + 1, l, mid, tl, min(mid, tr)), query(2*v + 2, mid + 1, r, max(tl, mid + 1), tr));
}

void update(int v, int l, int r, int pos, int val) {
	if(l == pos && r == pos) {
		t[v] = val;
		return;
	}
	int mid = (l + r)/2;
	if(pos <= mid)
		update(2*v + 1, l, mid, pos ,val);
	else
		update(2*v + 2, mid + 1, r, pos, val);
	t[v] = f(t[2*v + 1], t[2*v + 2]);
}

int32_t main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> ta[i];
	build_tree(0, 0, n - 1);
	int q;
	cin >> q;
	while(q--) {
		int flag;
		cin >> flag;
		if(flag) {
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << query(0, 0, n - 1, l, r) << '\n';
		}
		else {
			int pos, val;
			cin >> pos >> val;
			--pos;
			update(0, 0, n - 1, pos, val);
		}
	}
}