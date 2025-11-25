#include "graph.hpp"

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

        iss >> u >> v >> w;
        adj[u-1].push_back({v-1, w});
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

float Graph::min_cycle_mean(){
    int s = 0;
    std::vector<std::vector<double>> D(n+1, std::vector<double>(n, INF));
    D[0][s] = 0;

    int last_k = 0;

    for(int k = 1; k <= n; k++){
        // std::cout << "D ROW" << k << ": ";
        for(int u = 0; u < n; u++){
            for(std::pair<int,double> edge: adj[u]){
                int v = edge.first;
                double w = (double)edge.second;
                if(D[k][v] > D[k-1][u] + w)
                    D[k][v] = D[k-1][u] + w;
            }
        }

        if ((k & (k - 1)) == 0) {
            bool converged = true;
            for (int v = 0; v < n; v++) {
                if (std::abs(D[k][v] - D[last_k][v]) > 1e-9) {
                    converged = false;
                    break;
                }
            }
            if (converged) {
                break;
            }
            last_k = k;
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