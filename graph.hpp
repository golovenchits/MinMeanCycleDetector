#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <climits>
#include <vector>
#include <limits>
#include <cmath>

#define INF std::numeric_limits<double>::infinity()

class Graph{
    public:
        Graph(std::ifstream& input);
        ~Graph();
        void print_graph();
        float min_cycle_mean(bool, std::ofstream&);
        void calc_min_mean_cycle(int, int, std::ofstream&);
        double lambda;


    private:
        int n;
        int m;
        std::vector<std::vector<std::pair<int,double>>> adj;
        std::vector<std::vector<double>> D;
        std::vector<std::vector<int>> P;
        std::vector<int> min_mean_cycle;
        std::vector<double> dist;
        std::vector<double> pi;


};