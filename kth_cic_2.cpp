#include <bits/stdc++.h>

using namespace std;

vector<string> 
make_Euler_cycle(map<string, set<string>> graph)
{
    stack<string> vertex;
    vector<string> path;
    vertex.push(graph.begin()->first);
    string current = vertex.top();

    while(not vertex.empty())
    {
        current = vertex.top();
        if(not graph[current].empty())
        {
            vertex.push(*graph[current].begin());
            graph[current].erase(graph[current].begin());
            continue;
        } 
        path.push_back(current);
        vertex.pop();
    }

    reverse(path.begin(), path.end());
    return path;
}

map<string, set<string>> construct_DeBruijn_graph(const int k, const int n)
{
    auto calc_overlap = [](const auto& a, const auto& b, int mer) {
        for (size_t i = 1; i < a.size(); ++i)  if(a[i] != b[i-1]) return false;
        return true;
    };

    vector<string> mers;
    map<string, set<string>> graph;

    for(size_t i = 0; i < n; ++i)
        mers.emplace_back(bitset<16>{i}.to_string().substr(16-k));

    for(auto & m1 : mers)
        for(auto & m2 : mers)
            if(calculate_overlap(m1, m2, k-1))
                graph[m1.substr(0, k-1)].emplace(m2.substr(0, k-1));

    return graph;
}

void print_kUniversal_Circular_String(const vector<string> & cycle, const int k)
{
    for(size_t i = 0; i < cycle.size()-1; ++i) {
        const auto& s = cycle[i];
        cout << s.substr(0, s.size()-(k-2));
    }
    cout << endl;
}

int main ()
{
    int k;
    cin >> k;
    int n = pow(2, k); //no of edges

    const auto cycle = make_Euler_cycle(construct_DeBruijn_graph(k, n));
    print_kUniversal_Circular_String(cycle, k);

    return 0;
}

/*
 * We can observe that every node in this graph has equal in-degree and out-degree, which means that a Eulerian circuit exists in this graph.
The Eulerian circuit will correspond to a de Bruijn sequence as every combination of a node and an outgoing edge represents a unique string of length n.
The de Bruijn sequence will contain the characters of the starting node and the characters of all the edges in the order they are traversed in.
* 
Therefore the length of the string will be 2^k+k-1. We will use Hierholzer’s Algorithm to find the Eulerian circuit. 
* The time complexity of this approach is O(2k).
* 
* /
