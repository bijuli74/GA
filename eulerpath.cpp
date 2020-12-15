#include <bits/stdc++.h>
using namespace std;


bool check_degrees(const vector<int> &in, const vector<int> &out)
{
    assert(in.size() == out.size());
    for(size_t i = 0; i < in.size(); ++i)
        if(in[i] != out[i]) return false;
    return true;
}

vector<int> make_euler_cycle(vector<vector<int>> graph)
{
    stack<int> verteces;
    vector<int> path;
    verteces.push(0);
    int current = 0;

    while(not verteces.empty())
    {
        current = verteces.top();
        if(not graph[current].empty())
        {
            verteces.push(graph[current].back());
            graph[current].pop_back();
            continue;
        } 
        path.push_back(current);
        verteces.pop();
    }

    reverse(path.begin(), path.end());
    path.pop_back();
    return path;
}   

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int num_verteces, num_edges;

    cin >> num_nodes>> num_edges;

    vector<vector<int>> graph(num_verteces);
    
    vector<int> in(num_verteces), out(num_verteces);

    for(int i = 0; i < num_edges; ++i) 
    {
        int from, to;
        cin >> from >> to;
        graph[--from].push_back(--to);
        ++in[to];
        ++out[from];
    }

    if (not check_degrees(in, out))
    {
        cout << 0 << endl;
        return 0;
    }

    auto cycle = make_euler_cycle(move(graph));

    cout << 1 << '\n';
    for(auto v : cycle)
        cout << v+1 << ' ';
    cout << endl;

    return 0;
}
