#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <dirent.h>
using namespace std;


class Graph {
private:

    vector<string> vertices;
    vector<int> vertex_times;
    vector<pair<int, int>> edges;
    vector<int> weights;
    int total_time = 0;

public:

    void add_vertex(string v) 
    {
        vertices.push_back(v);
        vertex_times.push_back(0);

    }

    void add_edge(string v, string u) 
    {
    
    int index_v = find_index(v);
    int index_u = find_index(u);
    edges.push_back(make_pair(index_v, index_u));
    // weights.push_back(w); // Add the weight to the weights vector
    }

    void set_T(int t) {total_time = t;}

   void set_t(string v, int t) 
   {
        int index_v = find_index(v);
        //cout << v << " " << index_v << " " <<t <<endl;

        if (index_v != -1 && index_v < vertex_times.size()) 
        {
            //cout << v << " " << index_v << " " <<t <<endl;
            vertex_times[index_v] = t;
        }
    }





    int find_index(string v) 
    {
        for (int i = 0; i < vertices.size(); i++) 
        {
            if (vertices[i] == v) {
                //cout << i <<endl;
                return i;
            }
        }

        return -1; // If the vertex is not found, return -1
    }


    void read_file(string filename)
     {

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
               // cout << token <<" " <<endl;
                add_vertex(token);
                v_str.erase(0, pos + delimiter.length());

            }

        }

            //edges

        if (getline(infile, line)) 
        {
            size_t pos1 = line.find("{");
            size_t pos2 = line.find("}");
            string e_str = line.substr(pos1, pos2 - pos1 - 1) + ",";
            int bracket_count = 0;
            string delimiter = "),(";
            string token;
            size_t pos = 0;
            int start_pos = 0;
            int edges=0;

                while ((pos = e_str.find(delimiter, start_pos)) != string::npos) 
                {
                    // cout << ++edges<<endl;
                        token = e_str.substr(start_pos+1, pos - start_pos + 1);
                        start_pos = pos + 1;
                        string src = token.substr(1, token.find(',') - 1);
                        string dst = token.substr(token.find(',') + 1, token.length() - token.find(',') - 3);
                        // cout << src << "," << dst <<endl;
                    // cout << token;
                        add_edge(src,dst);
                    
                }

            token = e_str.substr(start_pos+1, e_str.length() - start_pos - 1);
            string src = token.substr(1, token.find(',') - 1);
            string dst = token.substr(token.find(',') + 1, token.length() - token.find(',') - 2);
            //cout << src << "," << dst <<endl;
            add_edge(src,dst);
          //  cout << ++edges << endl;
           //   cout << token << endl;
        }

                //weights
                if (getline(infile, line))
                {
                    size_t pos1 = line.find("{");
                    size_t pos2 = line.find("}");
                    string w_str = line.substr(pos1 + 1, pos2 - pos1 - 1) + ",";
                    string delimiter = ",";
                    string token;

                    while ((pos = w_str.find(delimiter)) != string::npos) 
                    {
                        token = w_str.substr(0, pos);
                        //cout << token <<" " <<endl;
                        weights.push_back(stod(token));
                        w_str.erase(0, pos + delimiter.length());
                    }
                }

                //times

         
              if(getline(infile, line))
              {

                // Parse the line to extract vertices and their times
                size_t pos = 0;
                while ((pos = line.find("t(", pos)) != string::npos)
                 {
                    pos += 2; // skip "t(" prefix
                    size_t endpos = line.find("=", pos);
                    string v = line.substr(pos, endpos - pos-1);
                    pos = endpos + 1;
                    endpos = line.find(",", pos);
                    int t = stoi(line.substr(pos, endpos - pos));
                // cout << v << " " << t << endl;
                    set_t(v,t);
                    pos = endpos;

                 }

                // Parse the line to extract total time T
                if(getline(infile, line))
                {
                    pos = line.find("T=");
                    if (pos != string::npos) {
                        int T = stoi(line.substr(pos + 2));
                        set_T(T);
                    // cout << "T " << T << endl;
                    }
                }
            }
    
                                
            infile.close();
        }

            void print_graph() 
            {
                cout << "Vertices: ";
                for (int i = 0; i < vertices.size(); i++)
                {
                    cout << vertices[i] << " ";
                }
                cout << endl;

                cout << "Edges: ";

                for (int i = 0; i < edges.size(); i++) 
                {
                    int src = edges[i].first;
                    int dst = edges[i].second;
                    int weight = weights[i]; // add this line to print the weight
                    cout << "(" << vertices[src] << "," << vertices[dst] << "," << weight << ") ";
                }

                cout << endl;

                   // Print vertex times
                    cout << "Vertex times: ";
                    for (int i = 0; i < vertices.size(); i++) 
                    {
                        cout << vertices[i] << " " << vertex_times[i] << " ";
                    }
                    cout << endl;
                            

              

                // Print total time
                cout << "Total time: " << total_time << endl;
            }

        void dfs(int v, vector<bool>& visited) 
        {
            visited[v] = true;
            cout << vertices[v] << " ";

            for (int i = 0; i < edges.size(); i++) 
            {
                if (edges[i].first == v) 
                {
                    int u = edges[i].second;
                    if (!visited[u]) 
                    {
                        dfs(u, visited);
                    }
                }
            }
        }

        void dfsTraversal() 
        {
            vector<bool> visited(vertices.size(), false);

            for (int v = 0; v < vertices.size(); v++)
            {
                if (!visited[v]) 
                {
                    dfs(v, visited);
                }
            }
        }

};




int main() 
{

    
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(".")) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                string filename = ent->d_name;
                if (filename.find(".txt") != string::npos) 
                {
                // Process the file
                cout << "Now reading: " << filename <<endl;
                cout << "---------------------" <<endl;
                Graph g;
                g.read_file(filename);
                g.print_graph();
                cout << "Depth First Traversal : " ;
                g.dfsTraversal();
                cout <<endl;
                cout << "---------------------" <<endl;
                cout <<endl<<endl;
                }
            }
        
            closedir(dir);
        }
         else {
        // Could not open directory
        perror("");
        return EXIT_FAILURE;
        }

        return 0;

}

