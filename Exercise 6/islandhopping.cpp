#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Coordinate
{
    double x;
    double y;
};

double euclideanDist(const Coordinate& a, const Coordinate& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double Edist = std::sqrt(dx * dx + dy * dy);
    return Edist;
}

std::vector<Coordinate> readIslands(int m)
{
    std::vector<Coordinate> islands(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> islands[i].x >> islands[i].y;
    }
    return islands;
}

int minKey(const std::vector<double>& key, const std::vector<bool>& inMST, int V)
{
    double minValue = 1e18;
    int minIndex = -1;

    for (int i = 0; i < V; i++)
    {
        if (!inMST[i] && key[i] < minValue)
        {
            minValue = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

double primMST(const std::vector<Coordinate>& islands)
{
    int V = islands.size();
    std::vector<double> key(V, 1e18);
    std::vector<bool> inMst(V, false);
    key[0] = 0.0;
    double totalLength = 0.0;

    for (int i = 0; i < V; i++)
    {
        int u = minKey(key, inMst, V);
        inMst[u] = true;
        totalLength += key[u];

        for (int j = 0; j < V; j++)
        {
            if (!inMst[j])
            {
                double dist = euclideanDist(islands[u], islands[j]);
                if (dist < key[j])
                {
                    key[j] = dist;
                }
            }
        }
    }
    return totalLength;
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m;
        std::cin >> m;
        std::vector<Coordinate> islands = readIslands(m);
        double totalLength = primMST(islands);

        std::cout << std::fixed << std::setprecision(6) << totalLength << "\n";

    }
    return 0;
}