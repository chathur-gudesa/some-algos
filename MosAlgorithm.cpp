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

ll pow(ll x, ll y) {
	if(y == 0)
	return 1;
	ll temp = pow(x, y/2);
	temp = (temp*temp);
	if(y%2 == 1)
		temp *= x;
	return temp;
}

const int MAXN = 2E5 + 100;

struct query{
	int l, r, i;
} Q[MAXN];

int block_size;

bool cmp(query x, query y) {
	if(x.l/block_size != y.l/block_size)
		return x.l/block_size < y.l/block_size;
	return x.r < y.r;
}

int32_t main() {
	//return the sum of[l:r]
	//Complexity = O((q + n)sqrt(n)*F), where F is moving pointer one unit cost
	//Do inserts first then deletes
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++)
		scanf("%lld", a + i);
	int tl = 1, tr = 0, cur = 0;
	int q;
	cin >> q;
	block_size = ceil(sqrt(n));
	// vppi queries[block_size];
	vi res(q);
	for(int i = 0; i < q; i++) {
		int l, r;
		scanf("%lld %lld", &Q[i].l, &Q[i].r);
		Q[i].i = i;
		--Q[i].l, --Q[i].r;
		// queries[l/block_size].pb({{l, r}, i});
	}
	sort(Q, Q + q, cmp);
	for(int i = 0; i < q; i++) {
		int l, r;
		l = Q[i].l, r = Q[i].r;
		int pos = Q[i].i;
		while(tr < r) {
			tr++;
			cur += a[tr];
		}
		while(tl < l) {
			cur -= a[tl];
			tl++;
		}
		while(tr > r) {
			cur -= a[tr];
			tr--;
		}
		while(tl > l) {
			tl--;
			cur += a[tl];
		}
		res[pos] = cur;
	}
	for(int i = 0; i < q; i++)
		cout << i + 1 << " " << res[i] << '\n';
}