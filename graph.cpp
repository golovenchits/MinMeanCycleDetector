#include "graph.hpp"
// #define DEBUG

Graph::Graph(std::ifstream &input){
    std::string line;
    std::getline(input, line);
    std::istringstream iss1(line);
    char l;
    iss1 >> l >> n;
    std::getline(input, line);
    std::istringstream iss2(line);
    iss2 >> l >> m;
    adj = std::vector<std::vector<std::pair<int,double>>>(n);
    D = std::vector<std::vector<double>> (n+1, std::vector<double>(n, INF));
    P = std::vector<std::vector<int>> (n+1, std::vector<int>(n, -1));
    min_mean_cycle = std::vector<int>(n, -1);

    for(int i = 0; i < m; i++){
        std::getline(input, line);
        std::istringstream iss(line);

        int u, v;
        double w;

        iss >> v >> u >> w;
        adj[v-1].push_back({u-1, w});
    }
}

void Graph::print_graph(){
    for(int i = 0; i < n; i++){
        std::cout << "Edges for node " << i+1 << std::endl;
        for(std::pair<int,double> edge: adj[i]){
            std::cout << "(" << i+1 << "," << edge.first << ")=" << edge.second << " ";
        }
        std::cout << std::endl;
    }
}

float Graph::min_cycle_mean(bool early_termination, std::ofstream& output2){
    int s = 0;
    pi = std::vector<double>(n, INF);
    D[0][s] = 0;
    int pred;

    for(int k = 1; k <= n; k++){
        #ifdef DEBUG
        std::cout << "D ROW" << k << ": ";
        #endif
        for(int u = 0; u < n; u++){
            for(std::pair<int,double> edge: adj[u]){
                int v = edge.first;
                double w = (double)edge.second;
                if(D[k][v] > D[k-1][u] + w){
                    D[k][v] = D[k-1][u] + w;
                    P[k][v] = u+1;
                }
            }
        }
        #ifdef DEBUG
        for(int u = 0; u < n; u++){
            std::cout << D[k][u] << " ";
        }
        std::cout << std::endl;
        // std::cout << "P ROW " << k << ": ";
        // for(int u = 0; u < n; u++){
        //     std::cout << P[k][u] << " ";
        // }
        // std::cout << std::endl << std::endl;
        #endif


        if ((early_termination && (k & (k - 1)) == 0) || k == n) {
            #ifdef DEBUG
            std::cout << "checking early termination" <<std::endl;
            #endif
            double lambda_k = INF;
            pred = -1;
            //Compute lambda_k
            for(int i = 0; i < n; i++){
                if(std::isinf(D[k][i])){
                    continue;
                }
                double lambda_k_v = -INF;
                for(int j = 0; j < k; j++){
                    if(lambda_k_v < (D[k][i] - D[j][i])/(k-j)){
                        lambda_k_v = (D[k][i] - D[j][i])/(k-j);
                    }
                }
                if (lambda_k_v < lambda_k){
                    lambda_k = lambda_k_v;
                    pred = i;
                    #ifdef DEBUG
                    std::cout << "Updated lambda_k to " << lambda_k << std::endl;
                    #endif
                }
            }
            // probably correct up to here
            #ifdef DEBUG
            std::cout << "lambda_k = " << lambda_k << std::endl;
            #endif
            if (std::isinf(lambda_k)) continue;
            // Compute pi(v)
            for(int iv = 0; iv < n; iv++){
                double pi_k = INF;
                for (int j = 0; j <= k; j++){
                    if(pi_k > D[j][iv] - (j * lambda_k)){
                        pi_k =  D[j][iv] - (j * lambda_k);
                    }
                }
                if(pi_k < pi[iv]){
                    pi[iv] = pi_k;
                }
            }
            #ifdef DEBUG
            std::cout << "PI: ";
            for(int iv = 0; iv < n; iv++){
                std::cout<< pi[iv] << " ";
            }
            std::cout <<std::endl;
            #endif
            
            bool terminate = true;
            for(int iu = 0; iu < n; iu++){
                for(std::pair<int,double> edge: adj[iu]){
                    int v = edge.first;
                    double w = (double)edge.second;
                    if(pi[v] > pi[iu] + w - lambda_k){
                        terminate = false;
                        break;
                    }
                }
                if(!terminate) break;
            }
            if(terminate || k == n){
                #ifdef DEBUG
                std::cout << "terminating at k = " << k << std::endl;
                #endif
                lambda = lambda_k;
                calc_min_mean_cycle(pred, k, output2);
                return (float) lambda_k;
            }
        }
    }
    return 0;
}

void Graph::calc_min_mean_cycle(int v, int k, std::ofstream& out) {
    const double TOL = 1e-9;
    
    std::vector<std::vector<int>> zero_adj(n);
    for (int u = 0; u < n; ++u) {
        if (std::isinf(pi[u])) continue;
        for (auto &e : adj[u]) {
            int vv = e.first;
            double w = e.second;
            if (std::isinf(pi[vv])) continue;
            double r = w - lambda + pi[u] - pi[vv];
            if (std::fabs(r) <= TOL) {
                zero_adj[u].push_back(vv);
            }
        }
    }

    std::vector<int> visited(n, 0), instack(n, 0), parent(n, -1);
    std::vector<int> result_cycle;
    bool found = false;

    std::function<void(int)> dfs = [&](int u) {
        if (found) return;
        visited[u] = 1;
        instack[u] = 1;
        for (int wv : zero_adj[u]) {
            if (!visited[wv]) {
                parent[wv] = u;
                dfs(wv);
                if (found) return;
            } else if (instack[wv]) {
                found = true;
                std::vector<int> cyc;

                int x = u;
                cyc.push_back(wv);
                while (x != wv && x != -1) {
                    cyc.push_back(x);
                    x = parent[x];
                }

                std::reverse(cyc.begin(), cyc.end());

                if (!cyc.empty() && cyc.front() == cyc.back())
                    cyc.pop_back();

                result_cycle = cyc;
                return;
            }
        }
        instack[u] = 0;
    };

    for (int u = 0; u < n && !found; ++u) {
        if (!visited[u]) dfs(u);
    }

    if (!result_cycle.empty()) {
        for(int i = 0; i < (int)result_cycle.size(); i++){
            out << (result_cycle[i] + 1);
            if(i != (int)result_cycle.size()-1) out << " ";
        }
        out << "\n";
    }
}

Graph::~Graph(){
    
}