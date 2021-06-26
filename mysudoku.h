#ifndef MYSUDOKU_H
#define MYSUDOKU_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

using namespace std;


class mysudoku
{
    public:
        vector<vector<char>> gridformer();
        void gridsaver(vector<vector<char>> &);
        bool isColumn(vector<vector<char>> &, int, int);
        bool isRow(vector<vector<char>> &, int, int);
        bool boxCheck(vector<vector<char>> &, int, int, int);
        void dispGrid(vector<vector<char>> &);
        bool emptyfind(vector<vector<char>> &, int&, int&);
        bool isValid(vector<vector<char>> &, int, int&, int&);
        bool sudoku(vector<vector<char>> &);
        bool filechecker();
        bool filechecker2();

};

#endif // MYSUDOKU_H
