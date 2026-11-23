const int INF = INT_MAX / 2; // greater than maxRisk in the constraints (1e9) 
int minimumRisk(int n, vector<vector<int>> roads, int start, int target) {
    if(start == target)return 0;
    vector<vector<pair<int,int>>> adj(n);
    for(const auto& road : roads){
        int u = road[0] , v = road[1] , w = road[2];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }               
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,start});
    vector<int> best(n,INF);
    best[start] = 0;
    while(!pq.empty()){
        const auto [d , u] = pq.top();pq.pop();
        if(best[u] < d)continue;
        for(const auto& [v,w] : adj[u]){
            int newW = max(w,d);
            if(newW < best[v]){
                best[v] = newW;
                pq.push({best[v],v});
            }
        }
    }
    return best[target] == INF ? -1 : best[target];
}
// Another solution using union find ^.^
struct DSU{
    vector<int> parent;
    vector<int> rank;
    DSU() = default;
    DSU(int n):rank(n,1),parent(n){
        iota(parent.begin(),parent.end(),0);
    }
    int f(int x){
        if(x != parent[x])parent[x] = f(parent[x]);
        return parent[x];
    }
    bool unite(int x,int y){
        x = f(x) , y = f(y);
        if(x == y)return false;
        if(rank[x] > rank[y])swap(x,y);
        parent[x] = y;
        rank[y] += rank[x];
        return true;
    }
    bool same(int x,int y){
        return f(x) == f(y);
    }
};

int minimumRisk(int n, vector<vector<int>> roads, int start, int target) {
    if(start == target)return 0;
    sort(roads.begin(),roads.end(),[](const auto& a,const auto& b){return a[2] < b[2];});
    DSU dsu(n);
    for(const auto& road : roads){
        int u = road[0] , v = road[1] , w = road[2];
        dsu.unite(u,v);
        if(dsu.same(start,target))return w;
    }
    return -1;
}

