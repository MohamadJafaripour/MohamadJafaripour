#include <iostream>
#include <limits> // for std::numeric_limits
#include <conio.h>

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

// Grid size
int n, m;

// The map grid
int grid[MAX_ROWS][MAX_COLS];

// Visited cells
bool visited[MAX_ROWS][MAX_COLS];

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

void dfs(int x, int y);
int countIslands();

int main()
{
    // Input rows and columns
    while (true)
    {
        std::cout << "Enter number of rows and columns (max 100x100): ";
        if (std::cin >> n >> m && n > 0 && n <= MAX_ROWS && m > 0 && m <= MAX_COLS)
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter two integers between 1 and 100.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Input the grid
    std::cout << "Enter the grid row by row (each cell should be 0 or 1):\n";
    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        while (j < m)
        {
            int val;
            std::cin >> val;

            if (std::cin.fail() || (val != 0 && val != 1))
            {
                std::cout << "Invalid input. Enter only 0 or 1.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                j = 0; // reset row input
                std::cout << "Re-enter row " << i + 1 << ": ";
                continue;
            }

            grid[i][j] = val;
            visited[i][j] = false;
            ++j;
        }
    }

    int result = countIslands();
    std::cout << "Number of islands: " << result << '\n';
    std::cout << "\n\nPress Enter key to end the program...\n";

    getch();
}

// DFS function to visit connected land
void dfs(int x, int y)
{
    visited[x][y] = true;

    for (int dir = 0; dir < 4; ++dir)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Check bounds
        if (nx >= 0 && nx < n && ny >= 0 && ny < m)
        {
            if (!visited[nx][ny] && grid[nx][ny] == 1)
            {
                dfs(nx, ny);
            }
        }
    }
}

// Count connected components (islands)
int countIslands()
{
    int count = 0;
    // travels through the grid
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (!visited[i][j] && grid[i][j] == 1) // if in grid and not visited:
            { // search for island
                dfs(i, j); 
                ++count;
            }
        }
    }

    return count;
}