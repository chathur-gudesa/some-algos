//Get choose(n, k)/2^n accurately in O(1) time per query
// O(n) construction


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

const int MAXN = 1E6 + 100;

double lfac[MAXN], p2[MAXN];

double choose(int n, int k) {
	if(k < 0 || k > n)
		return 0;
	return exp(lfac[n] - lfac[k] - lfac[n - k] - p2[n]);
}

int32_t main() {
	lfac[0] = 0.0;
	for(int i = 1; i < MAXN; i++)
		lfac[i] = lfac[i - 1] + log(i);
	p2[1] = log(2);
	for(int i = 2; i < MAXN; i++)
		p2[i] = p2[i - 1] + p2[1];
	int n, k;
	cin >> n >> k;
	cout << choose(n, k) << '\n';
	#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif
}
