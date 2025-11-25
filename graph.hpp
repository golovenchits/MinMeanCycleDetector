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

#define INF std::numeric_limits<float>::infinity();

class Graph{
    public:
        Graph(std::ifstream& input);
        ~Graph();
        void print_graph();
        float min_cycle_mean();

    private:
        int n;
        int m;
        std::vector<std::vector<std::pair<int,double>>> adj;

};