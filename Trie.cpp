/*
A simple trie where K is alphabet size
Can store strings and answer queries on whether they are stored or not
Space : O(m * k), m = sum of length of all strings stored, k = size of alphabet
Time : O(n) per query, n = length of string queried
Please test it on some problem	
*/

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

const int K = 26;

struct Vertex {
	int next[K];
	bool is_leaf;
	Vertex() {
		fill(begin(next), end(next), -1);
		is_leaf = false;
	}
};

class Trie {
	private :
		vector<Vertex> t;
	public :
		Trie() : t(1) {}

		void add_string(const string& s) {
			int v = 0;
			for(char ch : s) {
				int c = ch - 'a';
				if(t[v].next[c] == -1) {
					t[v].next[c] = sz(t);
					t.emplace_back();
				}
				v = t[v].next[c];
			}
			t[v].is_leaf = true;
		}

		bool find_string(const string& s) {
			int v = 0;
			for(char ch : s) {
				int c = ch - 'a';
				if(t[v].next[c] == -1)
					return false;
				v = t[v].next[c];
			}
			return t[v].is_leaf;
		}
};

int32_t main() {
	int q;
	cin >> q;
	Trie T;
	while(q--) {
		string s;
		cin >> s;
		T.add_string(s);
	}
	cin >> q;
	while(q--) {
		string s;
		cin >> s;
		cout << T.find_string(s) << '\n';
	}
}
