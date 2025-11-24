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

class Graph{
    public:
        Graph(std::ifstream& input);
        ~Graph();
        void print_graph();

    private:
        int n;
        int m;
        std::vector<std::vector<std::pair<int,int>>> adj;

};