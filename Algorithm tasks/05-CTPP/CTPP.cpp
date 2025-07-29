#include <iostream>
#include <conio.h>

const int MAX_N = 100;
int N; // Grid size (NxN)
int grid[MAX_N][MAX_N];
bool covered[MAX_N][MAX_N];
int antennaRange; // Range of antenna coverage

int countCoverage(int x, int y);
void markCovered(int x, int y);
int placeTowers();

int main()
{
    std::cout << "Enter grid size N (NxN): ";
    std::cin >> N;

    std::cout << "Enter antenna range (integer >=0): ";
    std::cin >> antennaRange;

    std::cout << "Enter grid (0 or 1) row by row:\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cin >> grid[i][j];
            covered[i][j] = false;
        }
    }

    int towersUsed = placeTowers();
    std::cout << "Total towers used: " << towersUsed << '\n';

    std::cout << "Press Enter key to end the program...\n\n";

    getch();
}

// Checks how many currently uncovered users would be covered if a tower is placed at (x, y)
int countCoverage(int x, int y)
{
    int count = 0;
    for (int dx = -antennaRange; dx <= antennaRange; dx++)
    {
        for (int dy = -antennaRange; dy <= antennaRange; dy++)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
            {
                if (grid[nx][ny] == 1 && !covered[nx][ny])
                    count++;
            }
        }
    }
    return count;
}

// After a tower is placed, mark all cells in its range as covered
void markCovered(int x, int y)
{
    for (int dx = -antennaRange; dx <= antennaRange; dx++)
    {
        for (int dy = -antennaRange; dy <= antennaRange; dy++)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
            {
                covered[nx][ny] = true;
            }
        }
    }
}

int placeTowers()
{
    int towers = 0;

    while (true)
    {
        int maxCov = 0;
        int bestX = -1, bestY = -1;

        // loop through the grid
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int cov = countCoverage(i, j); // for each location, counts the coverage of tower
                if (cov > maxCov)
                {
                    maxCov = cov;
                    bestX = i;
                    bestY = j;
                }
            }
        }

        if (maxCov == 0)
            break;

        towers++;
        markCovered(bestX, bestY);
        std::cout << "Placed tower at (" << bestX << "," << bestY << "), covering " << maxCov << " users.\n";
    }

    return towers;
}