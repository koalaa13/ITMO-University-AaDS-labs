#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "bicone"

using namespace std;


const int N = 111111;
vector<int> up(N), tin(N), col(N), comp(N);
vector<vector<pair<int, int>>> g(N);
stack<int> has;
int timer = 0, c = 0;

void dfs(int v, int edge_id = -1) {
    has.push(v);
    col[v] = 1;
    tin[v] = up[v] = timer++;
    for (auto to : g[v]) {
        if (col[to.first] == 1 && to.second != edge_id) {
            up[v] = min(up[v], tin[to.first]);
        }
        if (col[to.first] == 0) {
            dfs(to.first, to.second);
            up[v] = min(up[v], up[to.first]);
            if (up[to.first] > tin[v]) {
                while (!has.empty() && has.top() != to.first) {
                    comp[has.top()] = c;
                    has.pop();
                }
                comp[has.top()] = c++;
                has.pop();
            }
        }
    }
    col[v] = 2;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    freopen(FILE".in", "r", stdin);
    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back({u - 1, i});
        g[u - 1].push_back({v - 1, i});
    }
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) {
            dfs(i);
        }
    }
    while (!has.empty()) {
        comp[has.top()] = c;
        has.pop();
    }
    cout << c + 1 << '\n';
    for_each(comp.begin(), comp.begin() + n, [](int v) { cout << v + 1 << ' '; });
    return 0;
}
