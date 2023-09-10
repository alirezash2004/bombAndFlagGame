#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// change sentence color -- start
map<string, int> cmap = {
    {"Black", 0},
    {"Blue", 1},
    {"Green", 2},
    {"Aqua", 3},
    {"Red", 4},
    {"Purple", 5},
    {"Yellow", 6},
    {"White", 7},
    {"Gray", 8},
    {"Light_Blue", 9},
    {"Light_Green", 10},
    {"Light_Aqua", 11},
    {"Light_Red", 12},
    {"Light_Purple", 13},
    {"Light_Yellow", 14},
    {"Bright_White", 15}};
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void color(string s)
{
    SetConsoleTextAttribute(h, cmap[s]);
}
// change sentence color -- end

// main matrix class
class Matrix
{
private:
    int rows;
    int cols;
    vector<vector<char>> data;

public:
    // Constructor
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<char>(cols, '.')) {}

    // Accessor methods
    char getValue(int row, int col) const { return data[row][col]; }

    // Setter methods
    void setValue(int row, int col, char value) { data[row][col] = value; }

    // Print the matrix
    void printMatrix() const
    {
        char row_header[27] = "abcdefghijklmnopqrstuvwxyz";
        int index = 0;
        for (int i = -1; i < 2 * rows + 1; i++)
        {
            if (i == -1)
            {
                cout << "      ";
                unsigned short int a = 0;
                for (int j = 0; j < 4 * cols; j++)
                {
                    if (j % 4 == 0)
                    {
                        cout << row_header[a];
                        a++;
                    }
                    else
                    {
                        cout << " ";
                    }
                }
            }
            else
            {
                if (i % 2 == 0)
                {
                    cout << "    ";
                    for (int j = 0; j <= 4 * cols; j++)
                    {
                        cout << "-";
                    }
                }
                else
                {
                    if (index < 10)
                    {

                        cout << index << "   ";
                    }
                    else
                    {

                        cout << index << "  ";
                    }
                    cout << "|";
                    int col = 0;
                    for (int j = 0; j < 2 * cols; j++)
                    {
                        if (j % 2 == 0)
                        {
                            color("Yellow");
                            cout << " " << data[index][col];
                            // cout << " " << '.';
                            // cout << "i" << index;
                            // cout << "j" << col;
                            color("Gray");
                            col++;
                        }
                        else
                        {
                            cout << " |";
                        }
                    }
                    index++;
                }
            }
            cout << "\n";
        }
        color("Gray");
    }
    void printMatrix(float remaining_mines) const
    {
        system("cls");
        color("Aqua");
        cout << "Remaining Mines : " << remaining_mines << endl;
        color("Gray");
        printMatrix();
    }
};

int main()
{
    // start section
    cout << "Hi\n";
    color("Gray");

    char choice;
    cout << "1- Play Game\n2- Exit\nYour Choice : ";
    cin >> choice;
    while (choice != '1' && choice != '2') // choice validate
    {
        color("Red");
        cout << "Wrong Choice! Enter Valid Number!\n";
        color("Gray");
        cout << "1- Play Game\n2- Exit\nYour Choice : ";
        cin >> choice;
    }

    switch (choice)
    {
    case '1':
    {
        // selecting game difficulty level
        color("Green");
        cout << "Select Game difficulty level(from 1 - 3) : ";
        cin >> choice;
        color("Gray");
        while (choice != '1' && choice != '2' && choice != '3') // choice validate
        {
            color("Red");
            cout << "Wrong Choice! Enter Valid Number!\n";
            color("Gray");
            cout << "Select Game difficulty level(from 1 - 3) : ";
            cin >> choice;
        }

        cout << "\n";
        int base_width, base_height, base_mines;

        if (choice == '1')
        {
            base_width = 10;
            base_height = 10;
            base_mines = 10;
        }
        else if (choice == '2')
        {
            base_width = 16;
            base_height = 16;
            base_mines = 40;
        }
        else
        {
            base_height = 16;
            base_width = 40;
            base_mines = 99;
        }

        Matrix frontMatrix(base_width, base_height);
        Matrix backMatrix(base_width, base_height);

        srand(time(NULL));
        for (int t = 0; t < base_mines; t++)
        {
            int rand1 = rand() % base_width, rand2 = rand() % base_height;
            backMatrix.setValue(rand1, rand2, '-');
        }

        unsigned short int remaining_mines = base_mines;
        // frontMatrix.printMatrix();
        // backMatrix.printMatrix(); // debug only

        do
        {

            if (remaining_mines == 0)
            {
                color("Green");
                cout << "YOU WIN THE GAME!";
                color("Gray");
                break;
            }

            frontMatrix.printMatrix(remaining_mines);

            color("Light_Blue");
            cout << "info: ";
            color("Gray");
            cout << "1-choose unit , 2-insert flag\nYour Choice : ";
            cin >> choice;
            while (choice != '1' && choice != '2')
            {
                color("Red");
                cout << "Wrong Choice! Enter Valid Number!\n";
                color("Gray");
                cout << "1-choose unit , 2-insert flag\nYour Choice : ";
                cin >> choice;
            }

            color("Light_Blue");
            cout << "info";
            color("Gray");
            cout << ": enter the coordinates: ";
            char inp[4];
            cin >> inp;
            string num = "";
            for (int i = 1; i < 4; i++)
            {
                num += inp[i];
            }

            int row = stoi(num);
            int col = (int)inp[0] - 97;
            // cout << "col : " << col << endl;

            if (choice == '1')
            {
                if (backMatrix.getValue(row, col) == '-')
                {
                    backMatrix.printMatrix();
                    color("Red");
                    cout << "YOU LOST THE GAME!";
                    color("Gray");
                    return 0;
                }

                if (frontMatrix.getValue(row, col) != '#')
                {
                    cout << "ch";
                    // set number of around mines
                    unsigned short int around_mines = 0;

                    if (row != 0)
                    {
                        if (backMatrix.getValue(row - 1, col) == '-')
                            around_mines++;
                        // cout << "\nCheck : (top) " << (backMatrix.getValue(row - 1, col) == '-'); // top
                        if (col != 0)
                        {
                            if (backMatrix.getValue(row - 1, col - 1) == '-')
                                around_mines++;
                            // cout << "\nCheck : (top-left) " << (backMatrix.getValue(row - 1, col - 1) == '-'); // top-left
                        }
                        if (col != base_width - 1)
                        {
                            if (backMatrix.getValue(row - 1, col + 1) == '-')
                                around_mines++;
                            // cout << "\nCheck : (top-right) " << (backMatrix.getValue(row - 1, col + 1) == '-'); // top-right
                        }
                    }

                    if (row != base_height - 1)
                    {
                        if (backMatrix.getValue(row + 1, col) == '-')
                            around_mines++;
                        // cout << "\nCheck : (bottom) " << (backMatrix.getValue(row + 1, col) == '-'); // bottom
                        if (col != 0)
                        {
                            if (backMatrix.getValue(row + 1, col - 1) == '-')
                                around_mines++;
                            // cout << "\nCheck : (bottom-left) " << (backMatrix.getValue(row + 1, col - 1) == '-'); // bottom-left
                        }
                        if (col != base_width - 1)
                        {
                            if (backMatrix.getValue(row + 1, col + 1) == '-')
                                around_mines++;
                            // cout << "\nCheck : (bottom-right) " << (backMatrix.getValue(row + 1, col + 1) == '-'); // bottom-right
                        }
                    }

                    if (col != 0)
                    {
                        if (backMatrix.getValue(row, col - 1) == '-')
                            around_mines++;
                        // cout << "\nCheck : (left) " << (backMatrix.getValue(row, col - 1) == '-'); // left
                    }

                    if (col != base_width - 1)
                    {
                        if (backMatrix.getValue(row, col + 1) == '-')
                            around_mines++;
                        // cout << "\nCheck : (right) " << (backMatrix.getValue(row, col + 1) == '-'); // right
                    }

                    frontMatrix.setValue(row, col, (char)'0' + around_mines);
                }
                else
                {
                    color("Red");
                    cout << "Wrong Choice! You Already Selected This Column!\n";
                    color("Gray");
                    continue;
                }
            }
            else
            {
                if (frontMatrix.getValue(row, col) == '.')
                {
                    // disarm mine
                    if (backMatrix.getValue(row, col) == '-')
                    {
                        remaining_mines--;
                        backMatrix.setValue(row, col, '.');
                    }

                    frontMatrix.setValue(row, col, '#');
                }
                else
                {
                    color("Red");
                    cout << "Wrong Choice! You Already Selected This Column!\n";
                    color("Gray");
                    continue;
                }
            }
            frontMatrix.printMatrix();
        } while (true);
        break;
    }
    case '2':
    {
        cout << "Bye!";
        return 0;
    }
    break;
    }
    return 0;
}