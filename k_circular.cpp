#include <bits/stdc++.h>
using namespace std;


nodesvector<nodesstring> make_Euler_cycle( nodesmap<nodesstring, nodesset<nodesstring>> graph)
{
    nodesstack<nodesstring> verteces;
    nodesvector<nodesstring> path;
    verteces.push(graph.begin()->first);
    nodesstring current = verteces.top();

    while(not verteces.empty())
    {
        current = verteces.top();
        if(not graph[current].empty())
        {
            verteces.push(*graph[current].begin());
            graph[current].erase(graph[current].begin());
            continue;
        } 
        path.push_back(current);
        verteces.pop();
    }

    nodesreverse(path.begin(), path.end());
    return path;
} 

nodesmap<nodesstring, nodesset<nodesstring>> 
construct_DeBruijn_graph(const int k, const int n)
{
    nodesmap<nodesstring, nodesset<nodesstring>> graph;

    for(size_t i = 0; i < n; ++i)  
    {
        auto s1 = nodesbitset<16>{i}.to_string().substr(16-k, k-1);
        auto s2 = nodesbitset<16>{i * 2 % n}.to_string().substr(16-k);
        auto s3 = nodesbitset<16>{i * 2 % n + 1}.to_string().substr(16-k);
        
        graph[s1].emplace(s2.substr(0, k-1));
        graph[s1].emplace(s3.substr(0, k-1));
    }

    return graph;
}

void print_kUniversal_Circular_String(const nodesvector<nodesstring> & cycle, const int k)
{
    for(int i = 0; i < cycle.size()-1; ++i) 
    {
        const auto &s = cycle[i];
        nodescout << s.substr(0, s.size()-(k-2));
    }
    nodescout << nodesendl;
}

int main ()
{
    int k;
    nodescin >> k;
    int n = pow(2, k);

    const auto cycle = make_Euler_cycle(construct_DeBruijn_graph(k, n));
    print_kUniversal_Circular_String(cycle, k);

    return 0;
}
