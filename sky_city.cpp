/**
 *    author:  Pushkar Mujumdar
 *    email:   pushkarm27@gmail.com
 *    github:  github.com/pmujumdar27
**/

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define all(V) V.begin(), V.end()

#define nline "\n"
#define newline cout<<"\n"
#define deb(x) cout<<#x<<" "<<x<<endl;

template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T> >; 

template<typename... T>
void read(T&... args){
    ((cin>>args), ...);
}

template<typename... T>
void write(T... args){
    ((cout<<args<<" "), ...);
}

void printarr(vector<ll> &v){
    for(ll x: v){
        cout<<x<<" ";
    }
    newline;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T,U> &p){
    os << p.first << " " << p.second;
    return os;
}

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

vector<pair<ll, ll> > nbrs = {{-1,0}, {1,0}, {0,-1}, {0,1}};

const ll MOD = 1e9+7;
const ll INF = 1e17+7;
const ll nax = 1e5+7;

bool prime[nax+1];

void SieveOfEratosthenes(ll n) {
	memset(prime, true, sizeof(prime));
	for (ll p=2; p*p<=n; p++) {
		if (prime[p] == true) {
			for (ll i = p*p; i<=n; i+=p)
				prime[i] = false;
		}
	}
}

ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vector<vector<pair<ll, ll> > > adj;
vector<ll> dist1;
vector<ll> c, r;
vector<ll> ans;

vector<map<ll, ll> > dp;

void dfs(ll u, ll par){

    for(pair<ll, ll> p: dp[u]){
        ans[u] = min(ans[u], p.second);
    }

    for(pair<ll, ll> pv: adj[u]){
        ll d = pv.first;
        ll v = pv.second;

        if(v==par) continue;

        ll curmincost = INF;

        for(auto p: dp[u]){
            ll lc = p.first;
            ll prevcost = p.second;
            curmincost = min(curmincost, prevcost);

            if(dp[v].find(lc)==dp[v].end()){
                dp[v][lc] = INF;
            }
            dp[v][lc] = min(dp[v][lc], d*lc+prevcost);
        }

        if(dp[v].find(c[u])==dp[v].end()){
            dp[v][c[u]] = INF;
        }

        ans[u] = curmincost;

        dp[v][c[u]] = min(dp[v][c[u]], curmincost + d*c[u] + r[u]);

        ans[v] = min(ans[v], dp[v][c[u]]);

        dfs(v, u);
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n; cin>>n;

    dp.resize(n);
    c.resize(n);
    r.resize(n);
    ans.resize(n, INF);

    adj.clear(); adj.resize(n);
    dist1.assign(n, 0);

    for(ll i=0; i<n-1; i++){
        ll x, y, d; read(x, y, d);
        x--; y--;
        adj[x].push_back({d, y});
        adj[y].push_back({d, x});
    }

    for(ll i=0; i<n; i++){
        cin>>c[i]>>r[i];
    }

    dp[0][c[0]] = r[0];

    dfs(0, -1);

    for(ll i=1; i<n; i++) cout<<ans[i]<<" ";
    newline;

    return 0;
}