#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


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
        size_t pos = 0;

        //for vertices
        if(getline(infile, line)) 
        {
            // Parse vertices
        // Parse vertices
            size_t pos1 = line.find("{");
            size_t pos2 = line.find("}");
            string v_str = line.substr(pos1 + 1, pos2 - pos1 - 1) + ",";
            string delimiter = ",";
            string token;

            //vertices
            while ((pos = v_str.find(delimiter)) != string::npos) 
            {
                token = v_str.substr(0, pos);
                cout << token <<" " <<endl;
                add_vertex(token);
                v_str.erase(0, pos + delimiter.length());

            }

        }

            //edges

           if (getline(infile, line)) 
           {
            size_t pos1 = line.find("{");
            size_t pos2 = line.find("}");
            string e_str = line.substr(pos1 + 1, pos2 - pos1 - 1) + ",";
            int bracket_count = 0;
            string delimiter = ",";
            string token;
            size_t pos = 0;
            int start_pos = 0;
            while ((pos = e_str.find(delimiter, start_pos)) != string::npos) 
            {
                if (e_str[pos] == '(') {
                    bracket_count++;
                } else if (e_str[pos] == ')') {
                    bracket_count--;
                }
                if (bracket_count == 0) {
                    token = e_str.substr(start_pos, pos - start_pos + 1);
                    start_pos = pos + 1;
                    cout << token << endl;
                    // add_edge(token);
                }
            }
        }
        

    

            infile.close();
        }

};


int main() {

    Graph g;
    g.read_file("P2_test1.txt");
    cout << g.total_time<<endl;
  //  g.print_graph();
    return 0;
}

