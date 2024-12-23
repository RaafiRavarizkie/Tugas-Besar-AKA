#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std;

int tspRecursive(const vector<vector<int>>& graph, int pos, int visited, vector<vector<int>>& dp) {
    if (visited == ((1 << graph.size()) - 1)) {
        return graph[pos][0];
    }
    if (dp[pos][visited] != -1) {
        return dp[pos][visited];
    }

    int ans = INT_MAX;
    for (int city = 0; city < graph.size(); ++city) {
        if ((visited & (1 << city)) == 0) {
            int newAns = graph[pos][city] + tspRecursive(graph, city, visited | (1 << city), dp);
            ans = min(ans, newAns);
        }
    }
    return dp[pos][visited] = ans;
}

int main()
{
    int n;
    cout << "Masukkan jumlah kota: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                graph[i][j] = (i + j);
            } else {
                graph[i][j] = 0;
            }
        }
    }

    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    auto start = steady_clock::now();
    int shortestPath = tspRecursive(graph, 0, 1, dp);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Jarak terpendek: " << shortestPath << endl;
    cout << "Waktu eksekusi: " << duration.count() << " mikrodetik" << endl;


    return 0;
}
