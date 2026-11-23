vector<int> blockedPackages(int n, vector<vector<int>> dependencies, int broken) {
    vector<vector<int>> adj(n);
    for(const auto& dep : dependencies){
        adj[dep[1]].push_back(dep[0]);
    }
    queue<int> q;
    q.push(broken);
    vector<bool> visited(n,false);
    visited[broken] = true;
    while(!q.empty()){
        const auto u = q.front();
        q.pop();
        for(const auto& v : adj[u]){
            if(!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }
    vector<int> ans;
    ans.reserve(n);
    for(int i = 0 ; i < n;++i){
        if(visited[i]){
           ans.push_back(i); 
        }
    }
    return ans;
}
