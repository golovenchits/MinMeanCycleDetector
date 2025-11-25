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

float Graph::min_cycle_mean(bool early_termination){
    int s = 0;
    D = std::vector<std::vector<double>> (n+1, std::vector<double>(n, INF));
    P = std::vector<std::vector<int>> (n+1, std::vector<int>(n, -1));
    std::vector<double> pi(n, INF);
    D[0][s] = 0;

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
                    P[k][v] = u;
                }
            }
        }
        #ifdef DEBUG
        for(int u = 0; u < n; u++){
            std::cout << D[k][u] << " ";
        }
        std::cout << std::endl;
        #endif

        if (early_termination && (k & (k - 1)) == 0) {
            #ifdef DEBUG
            std::cout << "checking early termination" <<std::endl;
            #endif
            double lambda_k = INF;
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
                    }
                }
            }
            if(terminate){
                #ifdef DEBUG
                std::cout << "terminating at k = " << k << std::endl;
                #endif
                return (float) lambda_k;
            }
        }
    }
    double mean = INF;

    for(int v = 0; v < n; v++){
        if(std::isinf(D[n][v])){
            continue;
        }
        double v_mean = -INF;
        for(int k = 0; k < n; k++){
            if(v_mean < (D[n][v] - D[k][v])/(n-k)){
                v_mean = (D[n][v] - D[k][v])/(n-k);
            }
        }
        if (v_mean < mean){
            mean = v_mean;
        }
        // std::cout << mean << std::endl;
    }

    return (float)mean;
}

Graph::~Graph(){
    
}