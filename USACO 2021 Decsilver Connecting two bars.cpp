#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;

int f[MAXN];
vector<int> e[MAXN];

int find(int x){
	if(x == f[x]) return x;
	f[x] = find(f[x]);
	return f[x];
}

int fminDist(vector<int> &v, vector<int> &u){
	int d = MAXN;
	for(int i = 0; i < v.size(); ++ i){
		int x = lower_bound(u.begin(), u.end(), v[i]) - u.begin();
		if(x < u.size())
			d = min(d, u[x] - v[i]);
		if(x > 0)
			d = min(d, v[i] - u[x - 1]);
	}
	return d;
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int T;
	scanf("%d\n", &T);
	for(int tt = 0; tt < T; ++ tt){
		int n, k;
		cin >> n >> k;
		for(int i = 1; i <= n; ++ i) f[i] = i, e[i].clear();
		for(int i = 1; i <= k; ++ i){
			int x, y;
			scanf("%d %d", &x, &y);
			int fx = find(x);
			int fy = find(y);
			if(fx != fy) f[fy] = fx;
		}
		long long ans = 1LL * n * n * 2;		
		
		if(find(1) == find(n)) ans = 0;
		for(int i = 1; i <= n; ++ i) e[find(i)].push_back(i);
		for(int i = 1; i <= n; ++ i)
			if(find(i) == i) sort(e[i].begin(), e[i].end());	
			
		for(int i = 1; i <= n; ++ i)
			if(find(i) == i){
				int d0 = fminDist(e[i], e[find(1)]);
				int d1 = fminDist(e[i], e[find(n)]);
				
				ans = min(ans, 1LL*d0*d0+1LL*d1*d1);
			}
		cout << ans << endl;
	}
}
