# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
typedef stack<int> si;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<ll, ll, ll, ll> tl4;
typedef stack<ll> sl;
typedef queue<ll> ql;
typedef priority_queue<ll> pql;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;

const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
const int INF = 0x7f7f7f7f;
const ll INF_LL = 0x7f7f7f7f7f7f7f7f;
ll POW(ll a, ll b, ll MMM) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a / GCD(a, b) * b; }
ll INV(ll a, ll m) {
	ll m0 = m, y = 0, x = 1;
	if (m == 1)	return 0;
	while (a > 1) {
		ll q = a / m;
		ll t = m;
		m = a % m, a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	if (x < 0) x += m0;
	return x;
}
pll EXGCD(ll a, ll b) {
	if (b == 0) return { 1,0 };
	auto t = EXGCD(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}
bool OOB(ll x, ll y, ll N, ll M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int)(a.size()))
#define sf1(a) cin >> a
#define sf2(a,b) cin >> a >> b
#define sf3(a,b,c) cin >> a >> b >> c
#define sf4(a,b,c,d) cin >> a >> b >> c >> d
#define sf5(a,b,c,d,e) cin >> a >> b >> c >> d >> e
#define sf6(a,b,c,d,e,f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a,b) cout << (a) << ' ' << (b) << ' '
#define pf3(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << ' '
#define pf4(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '
#define pf5(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' '
#define pf6(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a,b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << '\n'
#define pf4l(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << '\n'
#define pf5l(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << '\n'
#define pf6l(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << '\n'
#define pfvec(V) for(auto const &t : V) pf1(t)
#define pfvecl(V) for(auto const &t : V) pf1(t); pf0l()
class Node{
public:
    int tot;
    Node *l, *r;
    Node(int _tot, Node* _l, Node* _r){
        tot = _tot;
        l = _l;
        r = _r;
    }
    Node* upd(int st, int en, int pos){ // parent의 Node에 값이 pos인 새로운 자식을 1개 부착
        if(pos < st or pos > en) return this;
        if(st==en) return new Node(tot+1,0,0);
        int mid=(st+en)>>1;
        return new Node(tot+1,l->upd(st,mid,pos),r->upd(mid+1,en,pos));
    }
};
class PST{
public:
    int N;


     vector<Node*> seg;
    // anc :ancestor of u,v  parent : parent of anc
    int query(Node* u, Node* v, Node* anc, Node* parent, int st, int en, int k){
        if(st==en) return st;
        // the element has weight l to mid
        int cnt = u->l->tot + v->l->tot - anc->l->tot - parent->l->tot;
        int mid=(st+en)>>1;
        if(cnt >= k) return query(u->l,v->l,anc->l,parent->l,st,mid,k);
        return query(u->r,v->r,anc->r,parent->r,mid+1,en,k-cnt);
    }

};
int N,M;
int recover[100005];
int idx[100005];
int p[100005][20]; // lca에서 사용
int depth[100005];
vector<int> adj[100005];
PST pst;
void dfs(int cur){
    if(cur==0) return;
    pst.seg[cur] = pst.seg[p[cur][0]]->upd(1,N,idx[cur]);
    for(auto n : adj[cur]){
        if(p[n][0] != -1) continue;
        p[n][0] = cur;
        depth[n]=depth[cur]+1;
        dfs(n);
    }
}
int lca(int u, int v){
    if(depth[u]>depth[v]) swap(u,v);
    for(int i = 19; i >= 0; i--){
        if(p[v][i] == -1) continue;
        if(depth[u] <= depth[p[v][i]])
            v = p[v][i];
    }
    // now depth[u] == depth[v]
    int anc = u;
    if(u != v){
        for(int j = 19; j >= 0; j--){
            if(p[u][j] != -1 && p[u][j] != p[v][j]){
                u = p[u][j];
                v = p[v][j];
            }
        }
        anc = p[u][0];
    }
    return anc;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
    sf2(N,M);
    pst.seg.resize(N+5);
    vector<pii> V;
    rep(i,0,20){
        rep(j,1,N+1){
            p[j][i] = -1;
        }
    }
    rep(i,0,N){
        int t;
        sf1(t);
        V.push_back({t,i+1});
    }
    sort(all(V));
    rep(i,0,N){
        idx[V[i].Y] = i+1;
        recover[i+1] = V[i].X;
    }

    rep(i,0,N-1){
        int a,b;
        sf2(a,b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // consider root as 1

    pst.seg[0] = new Node(0,0,0);
    pst.seg[0]->l = pst.seg[0]->r = pst.seg[0];
    p[1][0] = 0;
    depth[1]=1;
    dfs(1);
    rep(j,1,20){
        rep(i,1,N+1){
            if(p[i][j-1]!=-1) p[i][j] = p[p[i][j-1]][j-1];
        }
    }
    while(M--){
        int u,v,k;
        sf3(u,v,k);
        int anc = lca(u,v);
        int val = pst.query(pst.seg[u], pst.seg[v], pst.seg[anc], (p[anc][0] == -1 ? 0 : pst.seg[p[anc][0]]), 1, N, k);
        pf1l(recover[val]);
    }
}
