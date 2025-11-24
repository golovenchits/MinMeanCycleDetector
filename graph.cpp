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
    adj = std::vector<std::vector<std::pair<int,int>>>(n);

    for(int i = 0; i < m; i++){
        std::getline(input, line);
        std::istringstream iss(line);

        int u, v;
        float w;

        iss >> u >> v >> w;
        adj[u-1].push_back({v, w});
    }
}

void Graph::print_graph(){
    for(int i = 0; i < n; i++){
        std::cout << "Edges for node " << i+1 << std::endl;
        for(std::pair<int,int> edge: adj[i]){
            std::cout << "(" << i+1 << "," << edge.first << ")=" << edge.second << " ";
        }
        std::cout << std::endl;
    }
}

Graph::~Graph(){
    
}