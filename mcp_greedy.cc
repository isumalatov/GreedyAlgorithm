// Ilyas Umalatov X7278165E
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int mcp_greedy1(const vector<vector<int>> &matrix, int rows, int cols)
{
    int x = 0, y = 0;
    int count = 0;
    do
    {
        if (x == rows - 1 && y == cols - 1)
        {
            return matrix[x][y] + count;
        }
        int right = INT_MAX;
        int down = INT_MAX;
        int diag = INT_MAX;
        if (y < cols - 1)
        {
            right = matrix[x][y + 1];
        }
        if (x < rows - 1)
        {
            down = matrix[x + 1][y];
        }
        if (x < rows - 1 && y < cols - 1)
        {
            diag = matrix[x + 1][y + 1];
        }
        int minimo = min(right, min(down, diag));
        if (minimo == right)
        {
            y++;
            count += right;
        }
        else if (minimo == down)
        {
            x++;
            count += down;
        }
        else
        {
            x++;
            y++;
            count += diag;
        }
    } while (true);
}

int mcp_greedy2(const vector<vector<int>> &matrix, int rows, int cols)
{
    int x = rows - 1;
    int y = cols - 1;
    int count = matrix[x][y];
    do
    {
        int up = INT_MAX, left = INT_MAX, diag = INT_MAX;
        if (x > 0)
        {
            up = matrix[x - 1][y];
        }
        if (y > 0)
        {
            left = matrix[x][y - 1];
        }
        if (x > 0 && y > 0)
        {
            diag = matrix[x - 1][y - 1];
        }
        int minimo = min(left, min(up, diag));
        if (minimo == left)
        {
            y--;
            count += left;
        }
        else if (minimo == up)
        {
            x--;
            count += up;
        }
        else
        {
            x--;
            y--;
            count += diag;
        }
    } while (x > 0 || y > 0);
}

void mcp_greedy(const vector<vector<int>> &matrix, int rows, int cols, int* results)
{
    results[0] = mcp_greedy1(matrix, rows, cols);
    results[1] = mcp_greedy2(matrix, rows, cols);
}

int main(int argc, char *argv[])
{
    bool p2D = false;
    if (argc < 3)
    {
        cerr << "ERROR: missing filename.\nUsage:\nmcp [--p2D] -f file" << endl;
        return 1;
    }

    ifstream file;
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i]; // Convert to std::string

        if (arg == "--p2D")
        {
            p2D = true;
        }
        else if (arg == "-f")
        {
            file.open(argv[i + 1]);
            i++;
        }
        else
        {
            cerr << "ERROR: unknown option " << arg << ".\nUsage:\nmcp [--p2D] -f file" << endl;
            return 1;
        }
    }

    if (!file)
    {
        cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            file >> matrix[i][j];
        }
    }

    int results[2];
    mcp_greedy(matrix, rows, cols, results);
    cout << results[0] << " " << results[1] << endl;

    file.close();
    return 0;
}