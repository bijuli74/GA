#include <bits/stdc++.h>
using namespace std;

int calculate_overlap(const string& a, const string& b, const int mer) noexcept
{
    for (int i = 0, n= a.size()-mer+1; i < n; ++i)
        if(strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0) 
            return a.size() - i;
    return 0;
}

string assemble_genome(vector<string> reads, const int mer) noexcept
{    
    string genome;
    genome.reserve(1000);
    genome += reads.front();

    string first_read = reads.front(), cur_read = "";
    int cur_index = 0;

    while(reads.size() > 1)
    {
        cur_read = move(reads[cur_index]);
        reads.erase(reads.begin() + cur_index);
        
        int max_overlap = -1;

        for(int j = 0; j < (int)reads.size(); ++j)
        {
            int overlap = calculate_overlap(cur_read, reads[j], mer);
            if(overlap > max_overlap) max_overlap = overlap, cur_index = j;
        }

        genome += reads[cur_index].substr(max_overlap);
    }

    genome.erase(0, calculate_overlap(reads[0], first_read, mer));
    return genome;
}

int main ()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    vector<string> reads;
    reads.reserve(1618);
	string s;

    while(cin >> s)
        if(reads.back() != s) reads.emplace_back(move(s));

    cout << assemble_genome(move(reads), 12) << '\n';   

    return 0;
}
