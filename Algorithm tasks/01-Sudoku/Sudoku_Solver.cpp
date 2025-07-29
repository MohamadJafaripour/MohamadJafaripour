#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <string>

std::string Dash_1 = std::string(49, '-');

void show_board(int [][9]);
void table_input(int [][9]);
bool check_valid(int [][9]);
bool check_rows(int [][9]);
bool check_columns(int [][9]);
bool check_boxes(int [][9]);
bool solve_sudoku(int [][9]);
bool find_empty_cell(int [][9], int &, int &);
bool is_safe(int [][9], int, int, int);

int main()
{
    int board[9][9] = {0}; // Initialize board to zero

    std::cout << "\nWelcome to Sudoku game,\nYou can input a Sudoku puzzle to solve (use 0 for empty cells).\nHere is the initial table: \n"
              << Dash_1 << '\n';
    show_board(board);
    table_input(board);

    std::cout << "Your input board is:\n" << Dash_1 << '\n';
    show_board(board);

    std::cout << "Attempting to solve the Sudoku puzzle...\n";
    if (!check_valid(board))
    {
        std::cout << "Initial board is invalid. Cannot solve.\n";
    }
    else if (solve_sudoku(board))
    {
        std::cout << "\nSolution found:\n" << Dash_1 << '\n';
        show_board(board);
    }
    else
    {
        std::cout << "\nNo solution exists for the given Sudoku puzzle.\n";
    }

    std::cout << "Press Enter Key to close the program...\n";
    getch();
    return 0;
}

void show_board(int board[9][9])
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (j == 0)
                std::cout << '|';
            std::cout << "  " << board[i][j] << "  ";
            if ((j + 1) % 3 == 0)
                std::cout << '|';
        }
        std::cout << '\n';
        if ((i + 1) % 3 == 0)
            std::cout << Dash_1 << '\n';
    }
}

void table_input(int (*p)[9])
{
    for (int i = 0; i < 9; ++i)
    {
        std::cout << "Enter 9 numbers (0-9) for row " << i + 1 << " (use 0 for empty): ";
        for (int j = 0; j < 9; ++j)
        {
            std::cin >> p[i][j];
        }
    }
}

bool check_valid(int board[9][9])
{
    return check_rows(board) && check_columns(board) && check_boxes(board);
}

bool check_rows(int board[9][9])
{
    for (int i = 0; i < 9; ++i)
    {
        bool seen[10] = {false};
        for (int j = 0; j < 9; ++j)
        {
            int num = board[i][j];
            if (num == 0) continue;
            if (seen[num])
            {
                std::cout << "Duplicate " << num << " in row " << i + 1 << '\n';
                return false;
            }
            seen[num] = true;
        }
    }
    return true;
}

bool check_columns(int board[9][9])
{
    for (int j = 0; j < 9; ++j)
    {
        bool seen[10] = {false};
        for (int i = 0; i < 9; ++i)
        {
            int num = board[i][j];
            if (num == 0) continue;
            if (seen[num])
            {
                std::cout << "Duplicate " << num << " in column " << j + 1 << '\n';
                return false;
            }
            seen[num] = true;
        }
    }
    return true;
}

bool check_boxes(int board[9][9])
{
    for (int boxRow = 0; boxRow < 3; ++boxRow)
    {
        for (int boxCol = 0; boxCol < 3; ++boxCol)
        {
            bool seen[10] = {false};
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    int row = boxRow * 3 + i;
                    int col = boxCol * 3 + j;
                    int num = board[row][col];
                    if (num == 0) continue;
                    if (seen[num])
                    {
                        std::cout << "Duplicate " << num << " in 3x3 box starting at (" << row - row % 3 + 1 << "," << col - col % 3 + 1 << ")\n";
                        return false;
                    }
                    seen[num] = true;
                }
            }
        }
    }
    return true;
}

bool find_empty_cell(int board[9][9], int &row, int &col)
{
    for (row = 0; row < 9; ++row)
    {
        for (col = 0; col < 9; ++col)
        {
            if (board[row][col] == 0)
                return true;
        }
    }
    return false;
}

bool is_safe(int board[9][9], int row, int col, int num)
{
    for (int j = 0; j < 9; j++)
        if (board[row][j] == num)
            return false;

    for (int i = 0; i < 9; i++)
        if (board[i][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool solve_sudoku(int board[9][9])
{
    int row, col;
    if (!find_empty_cell(board, row, col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(board, row, col, num))
        {
            board[row][col] = num;
            if (solve_sudoku(board))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}