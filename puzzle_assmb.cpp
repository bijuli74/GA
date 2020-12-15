#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct square
{
    string up;
    string left;
    string down;
    string right;
    
    int id;
};

bool operator<(const square& lhs, const square& rhs) { return lhs.id < rhs.id; }

struct square_puzzle
{
    void insert(square sq)
    {
        if(sq.up == black && sq.left == black)
            left_up = move(sq);
        else if(sq.left == black && sq.down == black)
            left_down = move(sq);
        else if(sq.down == black && sq.right == black)
            right_down = move(sq);
        else if(sq.right == black && sq.up == black)
            right_up = move(sq);
        else if(sq.up == black)
            up.emplace_back(move(sq));
        else if(sq.left == black)
            left.emplace_back(move(sq));
        else if(sq.down == black)
            down.emplace_back(move(sq));
        else if(sq.right == black)
            right.emplace_back(move(sq));
        else middle.emplace_back(move(sq));
    }

    bool check_borders()
    {
        for(int i = 0; i < (int)up.size(); ++i)
            if(up[i].down != middle[i].up) return false;

        for(int i = 0; i < (int)left.size(); ++i)
            if(left[i].right != middle[i * left.size()].left) return false;

        for(int i = 1; i <= (int)down.size(); ++i)
            if(down[down.size()-i].up != middle[middle.size()-i].down) return false;

        for(int i = 0; i < (int)right.size(); ++i)
            if(right[i].left != middle[i * right.size() + (right.size()-1)].right) return false;

        return true;
    }

    void permutate_until_correct_square()
    {
        while(left_up.right != up[0].left or up[0].right != up[1].left or up.back().right != right_up.left) 
            next_permutation(up.begin(), up.end());

        while(left_down.right != down[0].left or down[0].right != down[1].left or down.back().right != right_down.left)
            next_permutation(down.begin(), down.end());

        while(left_up.down != left[0].up or left[0].down != left[1].up or left.back().down != left_down.up)
            next_permutation(left.begin(), left.end());

        while(right_up.down != right[0].up or right[0].down != right[1].up or right.back().down != right_down.up)
            next_permutation(right.begin(), right.end());

        while(not check_borders())
             next_permutation(middle.begin(), middle.end());
    }

    void print_first_row()
    {
        cout << '(' << left_up.up << ',' << left_up.left << ',' << left_up.down << ',' << left_up.right << ");";
        for(auto & square : up)
            cout << '(' << square.up << ',' << square.left << ',' << square.down << ',' << square.right << ");";
        cout << '(' << right_up.up << ',' << right_up.left << ',' << right_up.down << ',' << right_up.right << ")" << endl;
    }

    void print_middle_rows()
    {
        for(int i = 0, j = 0; i < (int)left.size(); ++i) 
        {
            cout << '(' << left[i].up << ',' << left[i].left << ',' << left[i].down << ',' << left[i].right << ");";
            for(int k = 0; k < (int)up.size(); ++k, ++j)
                cout << '(' << middle[j].up << ',' << middle[j].left << ',' << middle[j].down << ',' << middle[j].right << ");";
            cout << "(" << right[i].up << ',' << right[i].left << ',' << right[i].down << ',' << right[i].right << ")" << endl;
        }
    }

    void print_last_row()
    {
        cout << '(' << left_down.up << ',' << left_down.left << ',' << left_down.down << ',' << left_down.right << ");";
        for(auto & square : down)
            cout << '(' << square.up << ',' << square.left << ',' << square.down << ',' << square.right << ");";
        cout << '(' << right_down.up << ',' << right_down.left << ',' << right_down.down << ',' << right_down.right << ")" << endl;
    }

    void print()
    {
        print_first_row();
        print_middle_rows();
        print_last_row();
    }

    square left_up, left_down, right_up, right_down;
    vector<square> up, left, down, right, middle;
    
    const string black = "black";
};


int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int id = 0;
    square_puzzle puzzle;
    string up, left, down, right, tmp;

    while(getline(cin, up, ','))
    {
        up = up.substr(1);
        getline(cin, left, ',');
        getline(cin, down, ',');
        getline(cin, right, ')');
        right = right.substr(0, right.size());
        getline(cin, tmp, '\n');
        puzzle.insert(square{move(up), move(left), move(down), move(right), id++});
    }
 
    puzzle.permutate_until_correct_square();
    puzzle.print();

    return 0;
}

