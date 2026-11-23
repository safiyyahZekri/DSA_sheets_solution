int minimumRounds(int n, vector<vector<int>> dependencies) {
    vector<int> inDegree(n);
    vector<vector<int>> adj(n);
    for(const auto& dep : dependencies){
        adj[dep[0]].push_back(dep[1]);
        inDegree[dep[1]]++;
    }
    queue<int> q;
    int rounds = 0;
    for(int i = 0 ; i < n;++i){
        if(inDegree[i] == 0)q.push(i);
    }
    int ord = 0;
    // level order traversal
    while(!q.empty()){
        int currentLevelSize = q.size();
        while(currentLevelSize--){
            const auto u = q.front();q.pop();
            ord++;
            for(const auto& v : adj[u]){
                if(--inDegree[v] == 0){
                    q.push(v);
                }
            }
        }
        rounds++;
    }
    
    return ord == n ? rounds : -1;
}
// dp on dags style
int minimumRounds(int n, vector<vector<int>> dependencies) {
    vector<int> inDegree(n);
    vector<vector<int>> adj(n);
    for(const auto& dep : dependencies){
        adj[dep[0]].push_back(dep[1]);
        inDegree[dep[1]]++;
    }
    queue<int> q;
    vector<int> dp(n,1);
    for(int i = 0 ; i < n;++i){
        if(inDegree[i] == 0)q.push(i);
    }
    int ord = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        ord++;
        for(const auto& v : adj[u]){
            dp[v] = max(dp[u]+1,dp[v]);
            if(--inDegree[v] == 0){
                q.push(v);
            }
        }
    }
    return ord == n ? *max_element(dp.begin(),dp.end()) : -1;
}

