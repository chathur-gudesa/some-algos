//Construction time : O(nlogn)
//upd : O(logn)
//get : O(logn)
//memory : O(n)

#include <bits/stdc++.h>
using namespace std;

#define LOCAL
#define int ll

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

int get(vi& f, int pos) {
	int res = 0;
	for(; pos >= 0; pos = (pos&(pos + 1)) - 1)
		res += f[pos];
	return res;
}

void upd(vi &f, int pos, int del) {
	for(; pos < sz(f); pos |= pos + 1)
		f[pos] += del;
}

int32_t main() {
	int n;
	cin >> n;
	vi f(n);
	for(int i = 0; i < n; i++) {
		int del;
		cin >> del;
		upd(f, i, del);
	}
	int q;
	cin >> q;
	while(q--) {
		int flag;
		cin >> flag;
		if(flag) {
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << get(f, r) - get(f, l - 1) << '\n';
		}
		else {
			int pos, del;
			cin >> pos >> del;
			pos--;
			upd(f, pos, del);
		}
	}
	#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

    return 0;
}
