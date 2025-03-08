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
        mGrid[row - dx][column - dy] = '.';
    }

    void shuffleDirections(vector<pair<int, int>>& directions)
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(directions.begin(), directions.end(), g);
    }


    void generateMaze(int row, int column)
    {
        stack<pair<int, int>> st;
        mVisited[row][column] = true;
        mGrid[row][column] = '.';
        st.push({row, column});

        while(!st.empty())
        {
            vector<pair<int, int>> shuffledDirections = mDirections;
            shuffleDirections(shuffledDirections);
            auto [currentRow, currentColumn] = st.top();
            st.pop();

            for (const auto& [dx, dy] : shuffledDirections)
            {
                int newRow = currentRow + dx * 2;
                int newColumn = currentColumn + dy * 2;

                if (isInsideMaze(newRow, newColumn) && !mVisited[newRow][newColumn])
                {
                    carvePath(newRow, newColumn, dx, dy);
                    mGrid[newRow][newColumn] = '.';
                    mVisited[newRow][newColumn] = true;
                    st.push({currentRow, currentColumn});
                    st.push({newRow, newColumn});
                    break;
                }
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
