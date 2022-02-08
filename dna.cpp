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

void SieveOfEratosthenes(int n) {
	memset(prime, true, sizeof(prime));
	for (int p=2; p*p<=n; p++) {
		if (prime[p] == true) {
			for (int i = p*p; i<=n; i+=p)
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

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin>>n;

    string s; cin>>s;

    int bestscore = 0;
    int bestfold = 1;

    for(int fold=1; fold<n; fold++){
        int curscore = 0;
        for(int i=fold-1, j=fold; i>=0, j<n; i--, j++){
            if(s[i]=='A' && s[j]=='T' || s[i]=='T' && s[j]=='A' || s[i]=='G' && s[j]=='C' || s[i]=='C' && s[j]=='G'){
                curscore++;
            }
        }
        if(curscore > bestscore){
            bestscore = curscore;
            bestfold = fold;
        }
    }

    cout<<bestfold<<" "<<bestscore<<nline;

    return 0;
}