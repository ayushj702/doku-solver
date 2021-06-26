#include "mysudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

using namespace std;

vector<vector<char>> mysudoku::gridformer()
{
    string line;
    vector<vector<char>> grid;

    ifstream filein("sudoku.txt");
    assert(filein);

    while(getline(filein, line))
    {
       line.erase(remove(line.begin(), line.end(), ' '), line.end());
       grid.push_back(vector<char>(line.begin(), line.end()));
    }

    return grid;
}

void mysudoku::gridsaver(vector<vector<char>> &grid)
{
    ofstream fileoff("solved.txt");
    ostream_iterator<char> output_iterator(fileoff, " ");
    for(const auto& row : grid)
    {
        copy(row.begin(), row.end(), output_iterator);
        fileoff<<"\n";
    }
}
bool mysudoku::isColumn(vector<vector<char>> &A, int key, int column)
{
    for(int row=0; row<9; ++row)
    {
       
        if(A[row][column] - '0'==key)
        {
            return true;
        }
    }
    return false;
}

bool mysudoku::isRow(vector<vector<char>> &A, int key, int row)
{
    for(int column=0; column<9; ++column)
    {
       
        if(A[row][column] - '0'==key)
        {
            return true;
        }
    }
    return false;
}

bool mysudoku::boxCheck(vector<vector<char>> &A, int key, int b1, int b2)
{
    for(int row=b1; row<b1+3; ++row)
    {
        for(int column=b2; column<b2+3; ++column)
        {
            if(A[row][column] - '0' ==key)return true;
        }
    }
    return false;
}

void mysudoku::dispGrid(vector<vector<char>> &A)
{
    int row=0, column=0;
    cout<<"\n";
    for(row=0; row<9; ++row)
    {
        for(column=0; column<9; column++)
        {
            if(column==3 || column==6)
            {
                cout<<"|";
            }
            cout<<" "<<A[row][column]<<" ";
        }

        if(row==2 || row==5)
        {
            cout<<"\n";


                cout<<"----------------------------";

            //cout<<"\n";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool mysudoku::emptyfind(vector<vector<char>> &A, int& row, int& column)
{
    for(row=0; row<9; ++row)
    {
        for(column=0; column<9; ++column)
        {
            if(A[row][column]=='*')
            {
                return true;
            }

        }
    }
    return false;
}

bool mysudoku::isValid(vector<vector<char>> &A, int key, int& row, int& column)
{
    //this function is used to find if that position in the grid can be used for the purpose of solving sudoku or not
    int brow=row-row%3;
    int bcolumn=column-column%3;  //since a box resembles a 3x3 matrix i.e 3 rows and 3 columns

    bool checkRow=isRow(A, key, row);
    bool checkColumn=isColumn(A, key, column);
    bool checkBox=boxCheck(A, key, brow, bcolumn);

    bool res= ((checkRow==false) && (checkColumn)==false && (checkBox)==false);
    return res;
}

bool mysudoku::sudoku(vector<vector<char>> &A)
{
    int i,j;
    if(emptyfind(A,i,j)==false)
    {
        return true;            //this means that all the places in the sudoku grid have been filled
    }

    for(int k=1; k<=9; k++)
    {
        if(isValid(A, k, i, j)==true)
        {
            A[i][j]=(char)(k + '0');

            if(sudoku(A)==true)
            {
                return true;
            }

            A[i][j]='*';

        }
    }
    return false;
}

bool mysudoku::filechecker()
{
    ifstream fc("sudoku.txt");
    fc.seekg(0, ios::end);

    if (fc.tellg()==0)
    {
        return true;
    }

    return false;
}

bool mysudoku::filechecker2()
{
    ifstream fc("solved.txt");
    fc.seekg(0, ios::end);

    if (fc.tellg()==0)
    {
        return true;
    }

    return false;
}

int main()
{
    mysudoku ms;
    vector<vector<char>> res= ms.gridformer();

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~   Welcome to Sudoku Solver!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"\t\t\t  by-- \t\t   ayushj702\n";
    cout<<"***************************************************************************************";
    cout<<endl;
    cout<<"Please enter the sudoku you want to solve in the "<<" \"sudoku.txt\""<<" file and then save it.\n";
    cout<<"If you have entered the sudoku, press 1\n";
    int ch1;
    cin>>ch1;
    if(ch1==1)
    {
        if(ms.filechecker()==true)
        {
            cout<<"The file is empty. The program is exiting. Please try again.\n";
            exit(0);
        }
        else
        {
            cout<<"Checking if the sudoku.txt is empty or not.\nIt is not empty...\nContinuing........"<<endl;
        }
    }

    cout<<"\n1. Press 1 to Solve the Sudoku and display it.\n2. Press 2 to Solve the Sudoku and save it in the file "<<" \"solved.txt\""<<"\n3. Press 3 to Solve the Sudoku and simultaneously Display it and Save it into the file.\n\n";
    cout<<"\nEnter your choice: ";
    int ch2;
    cin>>ch2;

    switch(ch2)
    {
        case 1:
        {
            if(ms.sudoku(res))
            {
                cout<<"\nThe solved Sudoku is displayed-->\n";
                ms.dispGrid(res);
            }
            else
            {
                cout<<"\nThe Sudoku you have entered is INVALID\n";
            }
            break;
        }

        case 2:
        {
            if(ms.sudoku(res))
            {
                cout<<"\nThe solved Sudoku is being saved into the file......\n";
                ms.gridsaver(res);
            }
            else
            {
                cout<<"\nThe Sudoku you have entered is INVALID hence it can not be solved.\n";
            }
            break;
        }

        case 3:
        {
            if(ms.sudoku(res))
            {
                cout<<"\nThe solved Sudoku is displayed-->\n";
                ms.dispGrid(res);
                cout<<"\nThe solved Sudoku is now being saved into the file...\n";
                ms.gridsaver(res);
                if(ms.filechecker2()==false)
                {
                    cout<<"\nThe solution is now saved into the text file! Thank you for using our program!!!\n\n\n";
                }
            }
            else
            {
                cout<<"\nThe Sudoku you have entered is INVALID\n";
            }
            break;
        }

        default:
        {
            cout<<"\nInvalid Input. Program is exiting. Please Try Again.\n";
        }
    }


    return 0;
}



