#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

std::vector<std::string> split_string(const std::string& s, char  * delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, *delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class Graph {
public:
    vector<string> vertices;
    vector<int> vertex_times;
    vector<pair<int, int>> edges;
    vector<int> weights;
    int total_time = 0;

    void add_vertex(string v) {
        vertices.push_back(v);
    }

    void add_edge(string v, string u, int w) {
    int index_v = find_index(v);
    int index_u = find_index(u);
    edges.push_back(make_pair(index_v, index_u));
    weights.push_back(w); // Add the weight to the weights vector
    }

    void set_T(int t) {
    total_time = t;
    }

    void set_t(string v, int t) {
    int index_v = find_index(v);
    if (index_v != -1) {
        vertex_times[index_v] = t;
    }
    }




    int find_index(string v) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == v) {
            return i;
        }
    }
    return -1; // If the vertex is not found, return -1
    }


    void read_file(string filename) {
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        // Parse vertices
        size_t pos1 = line.find("{");
        size_t pos2 = line.find("}");
        string v_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        vector<string> vertices = split_string(v_str, ",");
        for (string v : vertices) {
            add_vertex(v);
        }

        // Parse edges
        pos1 = line.find("{", pos2);
        pos2 = line.find("}", pos1);
        string e_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        vector<string> edges = split_string(e_str, ",");
        for (string e : edges) {
            size_t pos = e.find("(");
            string v1_str = e.substr(pos + 1, e.find(",") - pos - 1);
            string v2_str = e.substr(e.find(",") + 1, e.find(")") - e.find(",") - 1);
            int w = 0;

            // Parse weights
            pos = line.find("Weights");
            string weights_str = line.substr(pos + 9);
            vector<string> weights = split_string(weights_str, ",");
            for (int i = 0; i < edges.size(); i++) {
                if (e == edges[i]) {
                    w = stoi(weights[i]);
                    break;
                }
            }
            add_edge(v1_str, v2_str, w);
        }

        // Parse t-values and T
        pos1 = line.find("t(");
        pos2 = line.find(")");
        while (pos1 != string::npos && pos2 != string::npos) {
            string v_str = line.substr(pos1 + 2, pos2 - pos1 - 2);
            int t = stoi(line.substr(pos2 + 1, line.find(",", pos2) - pos2 - 1));
            set_t(v_str, t);
            pos1 = line.find("t(", pos2);
            pos2 = line.find(")", pos1);
        }
        int T = stoi(line.substr(line.find("T=") + 2));
        set_T(T);
    }
    infile.close();
    }
};


int main() {

    Graph g;
    g.read_file("P2_test1.txt");
    cout << "hello " <<endl;
    cout << g.total_time<<endl;
  //  g.print_graph();
    return 0;
}

