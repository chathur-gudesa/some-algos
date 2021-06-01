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

const int MAX = 1E6, K = 25;
int st[MAX][K], st2[MAX][K];
int lg[MAX + 10];

int main() {
	lg[1] = 0;
	for(int i = 2; i < MAX + 1; i++)
		lg[i] = lg[i/2] + 1;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> st[i][0];
		st2[i][0] = st[i][0];
	}
	for(int j = 1; j < K; j++) {
		for(int i = 0; i < n; i++) {
			if(i + (1 << j) - 1 > n - 1)
				break;
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			st2[i][j] = __gcd(st[i][j - 1],  st[i + (1 << (j - 1))][j - 1]);
		}
	}
	int q;
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		--l;
		--r;
		int j = lg[r - l + 1];
		cout << min(st[l][j], st[r - (1 << j) + 1][j]);
		// r - l + 1 = length of the segment

	}
}