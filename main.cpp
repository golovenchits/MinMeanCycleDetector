#include "graph.hpp"


int main(int argc, char* argv[]){
    std::ifstream input(argv[1]);
    Graph g(input);
    input.close();

    // g.print_graph();

    FILE* fptr1 = fopen(argv[2], "wb");
    float mean = g.min_cycle_mean();
    // std::cout << mean << std::endl;
    fwrite(&mean, sizeof(float), 1, fptr1);
    fclose(fptr1);

    return EXIT_SUCCESS;
}