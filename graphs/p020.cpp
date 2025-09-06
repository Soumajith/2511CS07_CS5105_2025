
class Solution {
public:
    int rows, cols;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
        queue<pair<int, int>> q;
        q.push({i, j});
        visited[i][j] = true;

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                    !visited[nx][ny] && grid[nx][ny] == '1') {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
    void dfs()
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        rows = grid.size();
        cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int islands = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    ++islands;
                    bfs(grid, visited, i, j);
                }
            }
        }
        return islands;
    }
};
