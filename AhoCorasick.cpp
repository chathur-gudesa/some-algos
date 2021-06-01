/*
Reference : https://cp-algorithms.com/string/aho_corasick.html and https://github.com/jakobkogler/Algorithm-DataStructures/blob/master/Strings/AhoCorasick.h
Aho Corasick automaton for computing occurences of a set of strings in a given text 
Space : O(m * k), m = sum of length of all strings stored, k = size of alphabet
Time : O(len + ans) where len = length of text and ans = number of matches in the text
Verification : Buying a New String https://www.codechef.com/MAY20A/problems/TWOSTRS
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
	int p, link, elink, idx, go[K], next[K];
	bool is_leaf;
	char pch;
	Vertex(int p = -1, char pch = '$') : pch(pch), p(p) {
		fill(begin(next), end(next), -1);
		fill(begin(go), end(go), -1);
		is_leaf = false;
		link = -1;
		idx = -1;
		elink = -1;
	}
};

class AC {
	private :
		vector<Vertex> t;
	public :
		AC() : t(1) {}

		void add_string(const string& s, int idx) {
			int v = 0;
			for(char ch : s) {
				int c = ch - 'a';
				if(t[v].next[c] == -1) {
					t[v].next[c] = sz(t);
					t.emplace_back(v, ch);
				}
				v = t[v].next[c];
			}
			t[v].is_leaf = true;
			t[v].idx = idx;
		}

		int go(int v, char ch) {
			 int c = ch - 'a';
			 if(t[v].go[c] == -1) {
			 	if(t[v].next[c] > -1)
			 		return t[v].go[c] = t[v].next[c];
			 	return t[v].go[c] = (v == 0 ? 0 : go(get_link(v), ch)); 
			 }
			 return t[v].go[c];
		}

		int get_link(int v) {
			if(t[v].link == -1) {
				if(v == 0 || t[v].p == 0)
					return 0;
				return t[v].link = go(get_link(t[v].p), t[v].pch);
			}
			return t[v].link;
		}

		int get_elink(int v) {
			if(t[v].elink == -1) {
				if(v == 0 || t[v].p == 0)
					return 0;
				int vs = get_link(v);
				if(t[vs].is_leaf)
					return t[v].elink = vs;
				return t[v].elink = get_elink(vs);
			}
			return t[v].elink;
		}

		int transition(int v, char ch) {
			int c = ch - 'a';
			return v = go(v, ch);
		}

		bool is_leaf(int v) {
			return t[v].is_leaf;
		}

		int get_idx(int v) {
			return t[v].idx;
		}
};

int32_t main() {
	AC ac;
	int n;
	cin >> n;
	string s[n];
	for(int i = 0; i < n; i++) {
		cin >> s[i];
		ac.add_string(s[i], i);
	}
	string t;
	cin >> t;
	int v = 0;
	for(int i = 0; i < sz(t); i++) {
		char ch = t[i];
		v = ac.transition(v, ch);
		int tv = v;
		while(tv > 0) {
			if(ac.is_leaf(tv)) {
				cout << "The string " << s[ac.get_idx(tv)] << " occurs at position " << i + 2 - sz(s[ac.get_idx(tv)]) << '\n';
			}
			tv = ac.get_elink(tv);
		}
	}
}
