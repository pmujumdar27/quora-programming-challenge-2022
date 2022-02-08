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

struct Node {
    bool isend;
    ll depth;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(ll depth){
    struct Node* nn = (struct Node*)malloc(sizeof(Node));
    nn->depth = depth;
    nn->isend = false;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

bool dfs1(struct Node* cur){
    if(cur==NULL) return false;
    if(cur->isend) return true;
    dfs1(cur->left);
    dfs1(cur->right);
    if(cur->left && cur->right){
        if(cur->left->isend && cur->right->isend) cur->isend = true;
    }
    return cur->isend;
}

vector<vector<ll> > finalbits;
vector<ll> masks;

void dfs2(struct Node* cur, vector<ll> &curbits){
    if(cur==NULL) return;
    if(cur->isend==true) {
        finalbits.push_back(curbits);
        masks.push_back(cur->depth);
    }
    else{
        curbits.push_back(0);
        dfs2(cur->left, curbits);
        curbits.pop_back();

        curbits.push_back(1);
        dfs2(cur->right, curbits);
        curbits.pop_back();
    }
}

string bitstoip(vector<ll> &ipbits){
    string ret = "";
    for(int i=0; i<4; i++){
        int curval = 0;
        for(int j=0; j<8; j++){
            curval += pow(2, (7-j))*ipbits[8*i+j];
        }
        ret += to_string(curval);
        ret+='.';
    }
    ret.pop_back();
    return ret;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n; cin>>n;

    vector<string> v(n);

    struct Node* head = createNode(0);

    for(ll i=0; i<n; i++){
        string s; cin>>s;
        
        ll l = s.length();

        ll cnt = 0;

        vector<ll> nos(5, 0);

        string cur = "";

        for(ll j=0; j<l; j++){
            if(s[j]=='.' || s[j]=='/'){
                ll curno = stoi(cur);
                nos[cnt] = curno;
                cnt++;
                cur = "";
            }
            else{
                cur+=s[j];
            }
        }

        nos[cnt] = stoi(cur);

        // for(ll x: nos) cout<<x<<" ";
        // newline;

        ll finalno = 0;

        for(ll i=0; i<4; i++){
            finalno += nos[i]*(1<<(8LL*(3LL-i)));
        }

        ll curbit = 1LL << 32LL;

        struct Node* curnode = head;

        vector<ll> curbits;

        for(ll i=0; i<32; i++){
            ll cb = finalno&1;
            curbits.push_back(cb);
            finalno/=2;
        }

        reverse(all(curbits));

        ll mask = nos.back();

        for(ll i=0; i<mask; i++){
            if(curbits[i]==1){
                if(curnode->right==NULL){
                    curnode->right = createNode(i+1);
                }
                curnode = curnode->right;
            }
            else{
                if(curnode->left==NULL){
                    curnode->left = createNode(i+1);
                }
                curnode = curnode->left;
            }
        }

        curnode->isend = true;
    }

    dfs1(head);

    vector<ll> dfsbits;

    dfs2(head, dfsbits);

    ll fcnt = finalbits.size();

    for(ll i=0; i<fcnt; i++){
        // for(int x: finalbits[i]) cout<<x<<" ";
        // newline;
        while(finalbits[i].size()<32) finalbits[i].push_back(0);
        cout<<bitstoip(finalbits[i])<<"/"<<masks[i]<<nline;
    }



    return 0;
}