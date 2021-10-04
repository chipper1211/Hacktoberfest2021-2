/*
Question:
You are given a context free grammar G and a string S. Find the minimum Levenshtein distance between S and any string W accpeted by G
Input Format :
  The first line of the input contains two space-separated integers V and R denoting the number of non-terminals and the number of productions of G respectively.
  The following R lines describe productions.
  Each line starts with an integer T denoting the production type.
  If T=0, a space and three space-separated integers X, Y and Z denoting a production X→YZ follow.
  If T=1, a space, an integer X, another space and a character c denoting a production X→c follow.
  If T=2, a space and a single integer X denoting a production X→ε follows.
  The next line contains a single integer ST denoting the starting symbol of G.
  Last line contains the string S as explained in statement
 
 Output Format : 
  Print a single line containing one integer — the minimum distance. It is guaranteed that the minimum distance fits in a 64-bit signed integer.
*/
// Code in C++: 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MN = 222;
int N, M, G;
vector<pii> D[MN];
vector<int> T[MN];
string S;
int psum[MN][MN];
int calc(int s, int l, int r) 
{
    return psum[s][r] - (l? psum[s][l - 1] : 0);
}
struct Info 
{
    int s, l, r;
    bool operator <(const Info &i) const 
    {
        if(s != i.s) return s < i.s;
        if(l != i.l) return l < i.l;
        if(r != i.r) return r < i.r;
        return false;
    }
};
priority_queue<pair<ll, Info> > pq;
ll dist[MN][MN][MN];
int main() 
{
    std::ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < M; i++) 
    {
        int t; cin >> t;
        if(t == 0) 
        {
            int x, y, z; cin >> x >> y >> z;
            D[x].push_back(pii(y, z));
        }
        if(t == 1) 
        {
            int x; char c; cin >> x >> c;
            T[x].push_back(N + c);
        }
        if(t == 2) 
        {
            int x; cin >> x;
            T[x].push_back(N + 128);
        }
    }
    cin >> G;
    cin >> S;
    for(int i = 0; i < 128; i++) 
    {
        for(int j = 0; j < S.size(); j++) 
        {
            psum[N + i][j] = S[j] == i;
            if(j) psum[N + i][j] += psum[N + i][j - 1];
        }
    }
    for(int i = 0; i < MN; i++) for(int j = 0; j < MN; j++) for(int k = 0; k < MN; k++) dist[i][j][k] = 1e18;
    for(int s = N; s < N + 128; s++) 
    {
        for(int l = 0; l <= S.size(); l++) 
        {
            for(int r = l - 1; r < (int)S.size(); r++) 
            {
                if(r < l) 
                {
                    dist[s][l][r+1] = 1;
                    pq.push({ -dist[s][l][r+1], {s, l, r} });
                }
                else 
                {
                    dist[s][l][r+1] = r - l + 1 - (calc(s, l, r) != 0);
                    pq.push({ -dist[s][l][r+1], {s, l, r} });
                }
            }
        }
    }
    for(int l = 0; l <= S.size(); l++) 
    {
        for(int r = l - 1; r < (int)S.size(); r++) 
        {
            dist[N + 128][l][r+1] = r - l + 1;
            pq.push({ -dist[N + 128][l][r+1], {N + 128, l, r} });
        }
    }
    while(!pq.empty()) 
    {
        Info u = pq.top().second;
        ll ud = -pq.top().first;
        pq.pop();
        if(dist[u.s][u.l][u.r+1] < ud) continue;
        if(u.s == G && u.l == 0 && u.r == (int)S.size() - 1) 
        {
            cout << ud;
            return 0;
        }
        if(u.s >= N) 
        {
            for(int s = 0; s < N; s++) 
            {
                for(int i = 0; i < T[s].size(); i++) 
                {
                    if(T[s][i] == u.s) 
                    {
                        Info nxt = { s, u.l, u.r };
                        if(dist[nxt.s][nxt.l][nxt.r+1] > ud) 
                        {
                            dist[nxt.s][nxt.l][nxt.r+1] = ud;
                            pq.push({ -dist[nxt.s][nxt.l][nxt.r+1], nxt });
                        }
                    }
                }
            }
        }
        else 
        {
            for(int s = 0; s < N; s++) 
            {
                for(int i = 0; i < D[s].size(); i++) 
                {
                    if(D[s][i].first == u.s) 
                    {
                        for(int r = u.r; r < (int)S.size(); r++) 
                        {
                            Info tmp = { D[s][i].second, u.r + 1, r };
                            Info nxt = { s, u.l, r };
                            if(dist[nxt.s][nxt.l][nxt.r+1] > dist[tmp.s][tmp.l][tmp.r+1] + ud) 
                            {
                                dist[nxt.s][nxt.l][nxt.r+1] = dist[tmp.s][tmp.l][tmp.r+1] + ud;
                                pq.push({ -dist[nxt.s][nxt.l][nxt.r+1], nxt });
                            }
                        }
                        if(u.r < u.l) 
                        {
                            Info tmp = { D[s][i].second, u.l, u.r };
                            Info nxt = { s, u.l, u.r };
                            if(dist[nxt.s][nxt.l][nxt.r+1] > dist[tmp.s][tmp.l][tmp.r+1] + ud) 
                            {
                                dist[nxt.s][nxt.l][nxt.r+1] = dist[tmp.s][tmp.l][tmp.r+1] + ud;
                                pq.push({ -dist[nxt.s][nxt.l][nxt.r+1], nxt });
                            }
                        }
                    }
                    if(D[s][i].second == u.s) 
                    {
                        for(int l = 0; l <= u.l; l++) 
                        {
                            Info tmp = { D[s][i].first, l, u.l - 1 };
                            Info nxt = { s, l, u.r };
                            if(dist[nxt.s][nxt.l][nxt.r+1] > dist[tmp.s][tmp.l][tmp.r+1] + ud) 
                            {
                                dist[nxt.s][nxt.l][nxt.r+1] = dist[tmp.s][tmp.l][tmp.r+1] + ud;
                                pq.push({ -dist[nxt.s][nxt.l][nxt.r+1], nxt });
                            }
                        }
                        if(u.r < u.l) 
                        {
                            Info tmp = { D[s][i].first, u.l, u.r };
                            Info nxt = { s, u.l, u.r };
                            if(dist[nxt.s][nxt.l][nxt.r+1] > dist[tmp.s][tmp.l][tmp.r+1] + ud) 
                            {
                                dist[nxt.s][nxt.l][nxt.r+1] = dist[tmp.s][tmp.l][tmp.r+1] + ud;
                                pq.push({ -dist[nxt.s][nxt.l][nxt.r+1], nxt });
                            }
                        }
                    }
                }
            }
        }
    }
}

// Time Complexity of Code is the same as CYK Algorithm which is O(|S|^3 * N) , where N is the number of productions of Grammer
