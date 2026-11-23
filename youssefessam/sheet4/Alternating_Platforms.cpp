
int minimumJumps(int n, vector<vector<int>> jumps, int target) {
    vector<vector<pair<int,int>>> adj(n);
    for(const auto& j : jumps){
        adj[j[0]].emplace_back(j[1],j[2]);
    }
    queue<pair<int,int>> q;
    vector<array<int,2>> dist(n, {-1, -1});
    q.push({0,0});
    q.push({0,1});
    dist[0][0] = 0;
    dist[0][1] = 0;
    while(!q.empty()){
        const auto [u , t] = q.front();q.pop();
        if(u == target)return dist[target][t];
        for(const auto& [v,ty] : adj[u]){
            if(ty != t && dist[v][ty] == -1){
                dist[v][ty] = dist[u][t] + 1;
                q.push({v,ty});
            }
        }
    }
    return -1;
}
