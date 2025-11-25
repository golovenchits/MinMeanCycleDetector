#include "graph.hpp"
#include <chrono>


int main(int argc, char* argv[]){
    std::ifstream input(argv[1]);
    Graph g(input);
    input.close();


    // g.print_graph();
    FILE* fptr1 = fopen(argv[2], "wb");
    float mean;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::ofstream output2(argv[3]);



    #ifdef COMPARE
    start = std::chrono::high_resolution_clock::now();
    mean = g.min_cycle_mean(false, output2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << mean << std::endl;
    std::cout << "Without early termination: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    mean = g.min_cycle_mean(true, output2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << mean << std::endl;
    std::cout << "With early termination: "<< duration.count() << std::endl;
    #endif

    #ifndef DEBUG
    mean = g.min_cycle_mean(true, output2);
    #endif

    // std::cout << mean << std::endl;
    fwrite(&mean, sizeof(float), 1, fptr1);
    fclose(fptr1);

    return EXIT_SUCCESS;
}