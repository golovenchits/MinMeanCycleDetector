#include "graph.hpp"


int main(int argc, char* argv[]){
    std::ifstream input(argv[1]);
    Graph g(input);
    input.close();

    g.print_graph();
}