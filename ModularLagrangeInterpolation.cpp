/*
Finds a polynomial with degree at most n - 1 which passes through the given points. The points are given modulo MOD and the coefficients are found modulo MOD.
Time Complexity : O(n^3 + n * log(MOD)) 
Verification : Problem C (Coefficients) in Contest 4 Open Finals of Moscow Trainings May 31, 2020
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

const int MOD = 1E9 + 7;

long long binpow(long long base, long long e) {
	long long ret = 1;
	while(e) {
		if(e & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		e >>= 1;
	}
	return ret;
}

long long inverse(long long x) {
	if(x < 0)
		x = (x % MOD + MOD) % MOD;
	return binpow(x, MOD - 2);
}

const int MAXN = 55;
long long x[MAXN], y[MAXN], c[MAXN];
int n;

int main() {
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> x[i] >> y[i];
	for(int i = 0; i < n; i++) {
		vector<long long> l(n); // l(x[i]) = y[i] and l(x[j]) = 0 for j != i 
		l[0] = 1;
		for(int j = 0; j < n; j++) {
			if(j != i) {
				vector<long long> l_new(n);
				for(int k = 0; k < n - 1; k++)
					l_new[k + 1] = l[k];
				for(int k = 0; k < n; k++)
					l_new[k] = ((l_new[k] - x[j] * l[k]) % MOD + MOD) % MOD;
				swap(l_new, l);
			}
		}
		long long denomInv = 0;
		for(int j = 0; j < n; j++)
			denomInv = ((denomInv + binpow(x[i], j) % MOD * l[j] % MOD) % MOD + MOD) % MOD;
		denomInv = inverse(denomInv);
		for(int j = 0; j < n; j++) {
			l[j] = l[j] * denomInv % MOD * y[i] % MOD;
			c[j] = (c[j] + l[j]) % MOD;
		}
	}
	// the requried polynomial is sum(c[i] * (x ^ i))
	for(int i = 0; i < n; i++)
		cout << c[i] << ' ';
	cout << '\n';
}
