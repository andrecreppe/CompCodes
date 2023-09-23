#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#define VIS 1
#define NOT_VIS 0

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

vii adj;        // graph -> adjacency list
vii rev_adj;    // reverse graph

vi visited;
stack<int> st;

void DFS_stack(int u) {
    visited[u] = VIS;

    for(int v : adj[u]) {
        if(!visited[v]) {
            DFS_stack(v);
        }
    }

    st.push(u);
}

void DFS_SCC(int u, vi& scc) {
    visited[u] = VIS;
    scc.push_back(u);

    for(int v : rev_adj[u]) {
        if(!visited[v]) {
            DFS_SCC(v, scc);
        }
    }
}

vii findSCCs(int n) {
    visited.assign(n+1, NOT_VIS);

    for(int i=1; i<=n; i++) {
        if(!visited[i]) {
            DFS_stack(i);
        }
    }

    visited.assign(n+1, NOT_VIS);
    vii sccs;

    while(!st.empty()) {
        int u = st.top();
        st.pop();

        if(!visited[u]) {
            vi scc;
            DFS_SCC(u, scc);
            sort(scc.begin(), scc.end());  // Sort SCC in ASC order
            sccs.push_back(scc);
        }
    }

    sort(sccs.begin(), sccs.end());  // Sort by minimum node value
    return sccs;
}

int main() {
    int n, m, u, v;

    scanf("%d %d", &n, &m);

    adj.resize(n+1);
    rev_adj.resize(n+1);

    for(int i=0; i<m; i++) {
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    vii sccs = findSCCs(n);

    // ------------------------------

    vi ans;
    ans.assign(n+1, 0);

    int counter = 0;
    for(const vi& scc : sccs) {
        counter++;
        for(int node : scc) {
            ans[node] = counter;
        }
    }

    printf("%d\n", counter);
    for(int i=1; i<=n; i++) {
        printf("%d ", ans[i]);
    }

    return 0;
}
