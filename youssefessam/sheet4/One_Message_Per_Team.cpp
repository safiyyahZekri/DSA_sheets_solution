// Using union find ^.^
struct DSU{
    vector<int> parent;
    vector<int> rank;
    vector<int> compParity;
    DSU() = default;
    DSU(int n,const vector<int>& v):rank(n,1),parent(n),compParity(n){
        iota(parent.begin(),parent.end(),0);
        for(int i = 0 ; i < n;++i){
            compParity[i] = v[i] & 1;
        }
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
        compParity[y] = (compParity[y] + compParity[x]) & 1;
        return true;
    }
};
int countBalancedTeams(vector<int> tasks, vector<vector<int>> relationships) {
    int n = tasks.size();
    DSU dsu(n,tasks);
    for(const auto& r : relationships){
        dsu.unite(r[0],r[1]);
    }
    unordered_set<int> unique_roots;
    for(int i = 0 ; i < n;++i){
        unique_roots.insert(dsu.f(i));
    }
    int count = 0;
    for(const auto& root : unique_roots){
        count += !(dsu.compParity[root]);
    }
    return count;
}

// Using dfs (iterative version is better ^>^)
int dfs(int node,const vector<vector<int>>& adj,vector<bool>& visited,const vector<int>& tasks){
    int sum = tasks[node] & 1;
    visited[node] = true;
    for(const auto& v : adj[node]){
        if(!visited[v]){
            sum = (sum + dfs(v,adj,visited,tasks)) & 1;
        }
    }
    return sum;
}
int countBalancedTeams(vector<int> tasks, vector<vector<int>> relationships) {
    int n = tasks.size();
    vector<vector<int>> adj(n);
    for(const auto& r : relationships){
        int u = r[0] , v = r[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> visited(n,false);
    int count = 0;
    for(int i = 0 ; i <n;++i){
        if(!visited[i]){
            if(!dfs(i,adj,visited,tasks)){
                count++;
            }
        }
    }
    return count;
}
