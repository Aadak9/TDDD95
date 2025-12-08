#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

int getGold(int w, int h, const std::vector<std::vector<char>>& map, int startPosX, int startPosY)
{
    std::queue<std::pair<int,int>> Q;
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));

    Q.push(std::make_pair(startPosX, startPosY));
    visited[startPosY][startPosX] = true;

    int gold = 0;

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    while (!Q.empty()) 
    {
        std::pair<int,int> front = Q.front();
        int x = front.first;
        int y = front.second;
        Q.pop();

        if (map[y][x] == 'G') 
        {
            gold++;
        }

        bool adjacentTrap = false;
        for (int i = 0; i < 4; i++) 
        {
            int adjX = x + dx[i];
            int adjY = y + dy[i];

            if (adjX >= 0 && adjX < w && adjY >= 0 && adjY < h) 
            {
                if (map[adjY][adjX] == 'T') 
                {
                    adjacentTrap = true;
                    break;
                }
            }
        }

        if (adjacentTrap) 
        {
            continue;
        }

        for (int i = 0; i < 4; i++) 
        {
            int neighbour_x = x + dx[i];
            int neighbour_y = y + dy[i];

            if (neighbour_x < 0 || neighbour_x >= w || neighbour_y < 0 || neighbour_y >= h)
            {
                continue;
            }

            if (map[neighbour_y][neighbour_x] == '#' || map[neighbour_y][neighbour_x] == 'T')
            {
                continue;
            }

            if (visited[neighbour_y][neighbour_x])
            {
                continue;
            }

            visited[neighbour_y][neighbour_x] = true;
            Q.push(std::make_pair(neighbour_x, neighbour_y));
        }
    }

    return gold;
}

int main()
{
    int w;
    int h;
    std::cin >> w >> h;

    std::vector<std::vector<char>> map(h, std::vector<char>(w));

    int startPosX = -1;
    int startPosY = -1;

    for (int i = 0; i < h; i++) 
    {
        std::string row;
        std::cin >> row;

        for (int j = 0; j < w; j++) 
        {
            map[i][j] = row[j];

            if (map[i][j] == 'P')
            {
                startPosX = j;
                startPosY = i;
            }
        }
    }
    int gold = getGold(w, h, map, startPosX, startPosY);
    std::cout << gold << "\n";

    return 0;
}


