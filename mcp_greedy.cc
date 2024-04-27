//Ilyas Umalatov X7278165E
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int mcp_greedy1(const vector<vector<int>> &matrix, int rows, int cols, vector<pair<int, int>> &path)
{
    int x = 0;
    int y = 0;
    int count = matrix[x][y];
    path.push_back({x, y});
    do
    {
        if (x == rows - 1 && y == cols - 1)
        {
            return count;
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
        if (minimo == diag)
        {
            x++;
            y++;
            count += diag;
        }
        else if (minimo == right)
        {
            y++;
            count += right;
        }
        else if (minimo == down)
        {
            x++;
            count += down;
        }
        path.push_back({x, y});
    } while (true);
}

int mcp_greedy2(const vector<vector<int>> &matrix, int rows, int cols, vector<pair<int, int>> &path)
{
    int x = rows - 1;
    int y = cols - 1;
    int count = matrix[x][y];
    path.push_back({x, y});
    do
    {
        if (x == 0 && y == 0)
        {
            return count;
        }
        int up = INT_MAX;
        int left = INT_MAX;
        int diag = INT_MAX;
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
        if (minimo == diag)
        {
            x--;
            y--;
            count += diag;
        }
        else if (minimo == left)
        {
            y--;
            count += left;
        }
        else if (minimo == up)
        {
            x--;
            count += up;
        }
        path.push_back({x, y});
    } while (true);
}

void mcp_greedy(const vector<vector<int>> &matrix, int rows, int cols, int *results, vector<pair<int, int>> &path1, vector<pair<int, int>> &path2)
{
    results[0] = mcp_greedy1(matrix, rows, cols, path1);
    results[1] = mcp_greedy2(matrix, rows, cols, path2);
}

void mcp_print_path(const vector<vector<int>> &matrix, const vector<pair<int, int>> &path, int rows, int cols)
{
    int coste = 0;
    vector<vector<char>> charMatrix(rows, vector<char>(cols, '.'));
    for (int i = 0; i < path.size(); ++i)
    {
        charMatrix[path[i].first][path[i].second] = 'x';
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << charMatrix[i][j];
        }
        cout << '\n';
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (charMatrix[i][j] == 'x')
            {
                coste += matrix[i][j];
            }
        }
    }
    cout << coste << endl;
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
    vector<pair<int, int>> path1;
    vector<pair<int, int>> path2;
    mcp_greedy(matrix, rows, cols, results, path1, path2);
    cout << results[0] << " " << results[1] << endl;
    if (p2D)
    {
        if (results[0] <= results[1])
        {
            mcp_print_path(matrix, path1, rows, cols);
        }
        else
        {
            mcp_print_path(matrix, path2, rows, cols);
        }
    }
    file.close();
    return 0;
}