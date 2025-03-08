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

    bool isValidPath(int row, int column)
    {
        return (mGrid[row][column] == '.' || 
                mGrid[row][column] == 'E');
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

    bool solveMazeEntry(int row, int column)
    {
        if (row == mRows - 2 && column == mColumns - 2) return true;

        if (mGrid[row][column] == '.' || mGrid[row][column] == 'S')
        {
            if (mGrid[row][column] != 'S') mGrid[row][column] = 'X';

            for (const auto& [dx, dy] : mDirections)
            {
                int newRow = row + dx;
                int newColumn = column + dy;

                if (isInsideMaze(newRow, newColumn) && isValidPath(newRow, newColumn))
                {
                    if (solveMazeEntry(newRow, newColumn)) return true;
                }
            }

            mGrid[row][column] = '.';
        }

        return false;
    }

public:
    Maze(int rows, int columns)
    {
        mRows = (rows < 3) ? 3 : rows + (rows % 2 == 0);
        mColumns = (columns < 3) ? 3 : columns + (columns % 2 == 0);

        mGrid.assign(mRows, vector<char>(mColumns, '+'));
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
                cout << cell << " ";
            }
            cout << '\n';
        }
    }

    bool solveMaze(int row, int column)
    {
        return solveMazeEntry(row, column);
    }
};

const vector<pair<int, int>> Maze::mDirections = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Game
{
public:
    void run()
    {
        while (true)
        {
            int rows, cols;
            cout << "\nEnter maze dimensions (length breadth, at least 3 3): ";
            cin >> rows >> cols;

            cout << "\n\n\nCREATING MAZE\n\n\n";
            Maze maze(rows, cols);
            maze.displayMaze();

            cout << "\nPress enter to solve maze: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();

            cout << "\n\n\nSOLVING MAZE\n\n\n";
            if(maze.solveMaze(1, 1)) maze.displayMaze();
            else cout << "\nSomething went wrong! Try again.\n";

            cout << "\nEnter 'P'/'p' to play again (any other key to continue): ";
            char redo;
            cin >> redo;
            if (tolower(redo) != 'p') break;
        }
    }
};


int main()
{
    Game game;
    game.run();
    return 0;
}
