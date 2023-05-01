#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <dirent.h>
using namespace std;

const int INF = 0x3f3f3f3f; // use a large number that does not overflow


class Graph {
private:

    vector<string> vertices;
    vector<int> vertex_times;
    vector<pair<int, int>> edges;
    vector<int> weights;
    vector<vector<int>> adj_matrix;

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

        adj_matrix.resize(vertices.size(), vector<int>(vertices.size(), INF));


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

                for (int i = 0; i < edges.size(); i++) 
                {
                        int u = edges[i].first;
                        int v = edges[i].second;
                        //int u = find_index(edges[i].first);
                        //int v = find_index(edges[i].second);
                        adj_matrix[u][v] = weights[i];
                        adj_matrix[v][u] = weights[i];
                }

                // for (int i = 0; i < adj_matrix.size(); i++) 
                // {
                //             for (int j = 0; j < adj_matrix[i].size(); j++) 
                //             {
                //                 cout << adj_matrix[i][j] << " ";
                //             }
                //             cout << endl;
                //         }
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

            int getEdgeIndex(int u, int v) 
            {
                //cout << u << "," << v <<endl;
                
                if(adj_matrix[u][v]!=INF)
                    return adj_matrix[u][v];

                return -1; // edge not found
            }


        void tspDFS() {
            vector<int> best_route;
            vector<int> current_route;
            vector<bool> visited(vertices.size(), false);
            int current_time = 0;
            int best_distance = INF;

            int precalculation = 0;
            for (int i = 0; i < vertices.size(); i++) {
                precalculation += vertex_times[i];
            }

            if (precalculation > total_time) {
                cout << "Feasible Circuit Doesn't Exit " << endl;
                return;
            }

            visited[0] = true;
            current_route.push_back(0);
            int current_distance=0;
            tspDFSUtil(best_route, current_route, visited, current_time, current_distance, best_distance);
            
            if(!current_route.empty())
            {
                cout << "Best Distance = " << best_distance <<endl;
                cout << "Best path:  (";
                for (int i = 0; i < best_route.size(); i++)
                 {
                    cout << vertices[best_route [i]] << " ";
                }

                cout << vertices[0] << ")" << endl;
                cout << endl;
            }
            
            else if (current_route.empty())
                cout << "No Feasible Circuit " <<endl;
                
            return;
        }

        void tspDFSUtil(vector<int>& best_route, vector<int>& current_route, vector<bool>& visited, int& current_time, int & current_distance, int& best_distance) {
        if (current_route.size() == vertices.size()) { // base case: all cities have been visited
                        int total_distance = calculateDistance(current_route);
                        if (total_distance < best_distance) {

                            cout << "current best distance = " << best_distance << " new best distance = " << total_distance << endl;

                            
                            best_distance = total_distance;
                            best_route = current_route;

                               return;
            }
        }
            for (int i = 1; i < vertices.size(); i++) {
                if (!visited[i] && canVisit(vertices[i], current_time, current_route, current_distance,best_distance)) { // city has not been visited and can be visited within its time window
                    visited[i] = true;
                    current_route.push_back(i);
                    current_time += vertex_times[i];
                    tspDFSUtil(best_route, current_route, visited, current_time, current_distance, best_distance);
                    current_time -= vertex_times[i];
                    current_route.pop_back();
                    visited[i] = false;
                }
            }
        }

        int calculateDistance(vector<int>& route) 
        {

             int start_index = find_index(vertices[0]);
             int last_index = route.back();
            int return_index = adj_matrix[last_index][start_index];

             if(return_index==INF)
                return INF;
            
            cout << "New route = ";
                    int total_distance = 0;
                    for (int i = 1; i < route.size(); i++) {
                        int u = route[i - 1];
                        int v = route[i];
                           cout << vertices[u] << "," << vertices[v] << "= "<< adj_matrix[u][v] << ",";
                        if(adj_matrix[u][v]!=INF)
                            total_distance += adj_matrix[u][v];
                    }

                    // Add distance back to starting city
                    cout << vertices[last_index] << "," << vertices[start_index] << "= "<< adj_matrix[last_index][start_index] << " total distance = ";
                    total_distance += return_index;

                    cout << total_distance <<endl;
                    return total_distance;
        }

            bool canVisit(string city, int current_time, vector<int>& current_route, int & current_distance, int & best_time) {
                int city_index = find_index(city);
                int last_index = current_route.back();  

                // Check if the edge between the last visited city and the current city is infinite
                if (adj_matrix[last_index][city_index] == INF) 
                {
                    return false;
                }

                if(adj_matrix[last_index][city_index]+current_distance>best_time)
                {
                    
                    return false;
                }

                
                if (current_time + vertex_times[city_index] > total_time) { // city cannot be visited within its time window
                  
                    return false;
                }

                current_distance += adj_matrix[last_index][city_index];

                return true;
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
                //g.print_graph();
                //cout << "Depth First Traversal : " ;
                //g.dfsTraversal();
                g.tspDFS();
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

