//Segment tree query : Find number of elements strictly greater than x or strictly less than X
// Query : O(log^2(n))
//Construction : O(nlogn)
//Verification : https://codeforces.com/contest/1350/problem/D
//Reference : https://cp-algorithms.com/data_structures/segment_tree.html

#include <bits/stdc++.h>
using namespace std;

#define mainspring cout<<"mainspring\n";
#define barrel cout<<"barrel\n";
#define escapement cout<<"escapement\n";

#define int ll
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

const int MAX = 1E6 + 100;

vector<int> t[4*MAX];
vector<int> ta(MAX);

void build_tree(int v, int l, int r) {
	if(l == r) {
		t[v] = vector<int>(1, ta[l]);
		return;
	}
	t[v].clear();
	int mid = (l + r)/2;
	build_tree(2*v + 1, l, mid);
	build_tree(2*v + 2, mid + 1, r);
	merge(all(t[2*v + 1]), all(t[2*v + 2]), back_inserter(t[v]));
}

int find_greater(int v, int l, int r, int tl, int tr, int x) {
	int mid = (l + r)/2;
	if(tl > tr)
		return 0;
	if(tl == l && tr == r) {
		return t[v].end() - upper_bound(t[v].begin(), t[v].end(), x);
	}
	return find_greater(2*v + 1, l, mid, tl, min(tr,mid), x) + find_greater(2*v + 2, mid + 1, r, max(tl,mid + 1), tr, x);
}

int find_lesser(int v, int l, int r, int tl, int tr, int x) {
	int mid = (l + r)/2;
	if(tl > tr)
		return 0;
	if(tl == l && tr == r) {
		return lower_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
	}
	return find_lesser(2*v + 1, l, mid, tl, min(tr,mid), x) + find_lesser(2*v + 2, mid + 1, r, max(tl,mid + 1), tr, x);
}

int32_t main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> ta[i];
	build_tree(0, 0, n - 1);
}