// bellman ford
const int INF = INT_MAX / 2;
vector<string> minimumCosts(int n, vector<vector<int>> routes) {
    vector<int> dist(n,INF);
    dist[0] = 0;
    for(int i = 0 ; i < n-1;++i){
        for(const auto& route : routes){
            int u = route[0] , v = route[1] , w = route[2];
            if(dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
            }
        }
    }
    vector<string> ans(n);
    for(int i = 0 ; i < n;++i){
        if(dist[i] != INF){
            ans[i] = to_string(dist[i]);
        }else{
            ans[i] = "INF";
        }
    }
    return ans;
}

// using spfa
// spfa optimizes bellman ford by eliminating redundant checks (doesn't blindly iterate over all edges)
// spfa avg time complexity = O(E) but an adversary can force it to run in the worst case = O(V*E)
const int INF = INT_MAX / 2;
vector<string> minimumCosts(int n, vector<vector<int>> routes) {
    vector<vector<pair<int,int>>> adj(n);
    for(const auto& route : routes){
        int u = route[0] , v = route[1] , w = route[2];
        adj[u].push_back({v, w});
    }

    vector<int> dist(n,INF);
    vector<bool> inQueue(n,false);
    queue<int> q;

    dist[0] = 0;
    q.push(0);
    inQueue[0] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for(const auto& [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                if(!inQueue[v]){
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    vector<string> ans(n);
    for(int i = 0 ; i < n;++i){
        if(dist[i] != INF){
            ans[i] = to_string(dist[i]);
        }else{
            ans[i] = "INF";
        }
    }
    return ans;
}

