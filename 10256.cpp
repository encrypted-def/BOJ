#include <bits/stdc++.h>
using namespace std;

class NODE {
public:
	int state, fail;
	vector<int> next;
	NODE(int num) {
		next.resize(num);
		state = -1;
		fail = 0;
	}
};
class Trie
{
public:
	int nsz; // node size
	vector<NODE> node;
	int MX;
	int num; // 등장 가능한 문자의 갯수	
	Trie(int _MX, int _num) {
		MX = _MX;
		num = _num;
		node.resize(MX, NODE(num));
		nsz = 0;
	}
	int c2i(char c) { // character to int
		if (c == 'A')return 0;
		else if (c == 'C')return 1;
		else if (c == 'G') return 2;
		else return 3;
	}
	void insert(string& P, int ptag) // ptag : pattern의 tag
	{
		int cur = 0;
		for (auto c : P) {
			int n = c2i(c);
			if (node[cur].next[n] == 0) {
				++nsz;
				node[cur].next[n] = nsz;
				cur = nsz;
			}
			else
				cur = node[cur].next[n];
		}
		node[cur].state = ptag;
	}

	void Fail()
	{
		int root = 0;
		queue <int> q;
		node[root].fail = root;
		q.push(root);

		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (int n = 0; n < num; ++n) {
				int child = node[cur].next[n];
				if (!child) continue;
				if (cur == root)
					node[child].fail = root;
				else {
					int t = node[cur].fail;
					while (t != root && node[t].next[n] == 0)
						t = node[t].fail;
					if (node[t].next[n])
						t = node[t].next[n];
					node[child].fail = t;
				}
				if (node[node[child].fail].state != -1)
					node[child].state = node[node[child].fail].state;
				q.push(child);
			}
		}
	}

	int Aho(string& S) {
		int cnt = 0;
		int cur = 0, root = 0;
		for (int i = 0; i < S.size(); i++) {
			int n = c2i(S[i]);
			while (cur != root && node[cur].next[n] == 0)
				cur = node[cur].fail;
			if (node[cur].next[n])
				cur = node[cur].next[n];
			if (node[cur].state != -1)
				cnt++;
		}
		return cnt;
	}
};

int T;
int N, M;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int N, M;
		cin >> N >> M;
		string S, Marker;
		cin >> S >> Marker;
		vector<string> P;
		for (int i = 0; i < M; i++) {
			for (int j = i + 1; j <= M; j++) {
				reverse(Marker.begin() + i, Marker.begin() + j);
				P.push_back(Marker);
				reverse(Marker.begin() + i, Marker.begin() + j);
			}
		}
		sort(P.begin(), P.end());
		P.erase(unique(P.begin(), P.end()), P.end());
		Trie T(P.size()*M + 15, 4);
		for (int i = 0; i < P.size(); i++)
			T.insert(P[i], i);
		T.Fail();
		cout << T.Aho(S) << '\n';
	}
}
