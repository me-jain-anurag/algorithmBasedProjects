#include <bits/stdc++.h>
using namespace std;

class Maze
{
private:
    vector<vector<char>> mGrid;
    vector<vector<bool>> mVisited;
    static const vector<pair<int, int>> mDirections;
    int mRows, mColumns;

    bool isInsideMaze(int row, int col)
    {
        return (row > 0 && row < mRows - 1 && 
                col > 0 && col < mColumns - 1);
    }

    void carvePath(int row, int column, int dx, int dy)
    {
        mGrid[row + dx][column + dy] = '.';
    }

    void generateMaze(int row, int column)
    {
        mVisited[row][column] = true;
        mGrid[row][column] = '.';

        vector<pair<int, int>> shuffledDirections = mDirections;
        random_device rd;
        mt19937 g(rd());
        shuffle(shuffledDirections.begin(), shuffledDirections.end(), g);

        for (const auto& [dx, dy] : shuffledDirections)
        {
            int newRow = row + dx * 2;
            int newCol = column + dy * 2;

            if (isInsideMaze(newRow, newCol) && !mVisited[newRow][newCol])
            {
                carvePath(row, column, dx, dy);
                generateMaze(newRow, newCol);
            }
        }
    }

public:
    Maze(int rows, int columns)
    {
        mRows = (rows < 3) ? 3 : rows + (rows % 2 == 0);
        mColumns = (columns < 3) ? 3 : columns + (columns % 2 == 0);

        mGrid.assign(mRows, vector<char>(mColumns, '#'));
        mVisited.assign(mRows, vector<bool>(mColumns, false));

        generateMaze(1, 1);

        mGrid[1][1] = 'S';
        mGrid[mRows - 2][mColumns - 2] = 'E';
    }

    void displayMaze()
    {
        for (const vector<char>& row : mGrid)
        {
            for (const char& cell : row)
            {
                cout << cell;
            }
            cout << '\n';
        }
    }
};

const vector<pair<int, int>> Maze::mDirections = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main()
{
    Maze maze(21, 41);
    maze.displayMaze();
    return 0;
}
