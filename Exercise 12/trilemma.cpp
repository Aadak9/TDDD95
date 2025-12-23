#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
};

std::string triLength(const Point& p1, const Point& p2, const Point& p3)
{
    double d12 = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    double d13 = std::sqrt(std::pow(p3.x - p1.x, 2) + std::pow(p3.y - p1.y, 2));
    double d23 = std::sqrt(std::pow(p3.x - p2.x, 2) + std::pow(p3.y - p2.y, 2));

    if(d12 == d13 || d12 == d23 || d13 == d23)
    {
        return "isosceles";
    }
    return "scalene";
}

std::string triAngles(const Point& p1, const Point& p2, const Point& p3)
{
    double toDegree = 180 / std::acos(-1.0);

    double dot1 =
        (p2.x - p1.x) * (p3.x - p1.x) +
        (p2.y - p1.y) * (p3.y - p1.y);

    double len12 = std::sqrt(
        (p2.x - p1.x) * (p2.x - p1.x) +
        (p2.y - p1.y) * (p2.y - p1.y)
    );

    double len13 = std::sqrt(
        (p3.x - p1.x) * (p3.x - p1.x) +
        (p3.y - p1.y) * (p3.y - p1.y)
    );

    double A = std::acos(dot1 / (len12 * len13));
    A *= toDegree;

    double dot2 =
        (p1.x - p2.x) * (p3.x - p2.x) +
        (p1.y - p2.y) * (p3.y - p2.y);

    double len21 = std::sqrt(
        (p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y)
    );

    double len23 = std::sqrt(
        (p3.x - p2.x) * (p3.x - p2.x) +
        (p3.y - p2.y) * (p3.y - p2.y)
    );

    double B = std::acos(dot2 / (len21 * len23));
    B *= toDegree;

    double dot3 =
        (p1.x - p3.x) * (p2.x - p3.x) +
        (p1.y - p3.y) * (p2.y - p3.y);

    double len31 = std::sqrt(
        (p1.x - p3.x) * (p1.x - p3.x) +
        (p1.y - p3.y) * (p1.y - p3.y)
    );

    double len32 = std::sqrt(
        (p2.x - p3.x) * (p2.x - p3.x) +
        (p2.y - p3.y) * (p2.y - p3.y)
    );

    double C = std::acos(dot3 / (len31 * len32));
    C *= toDegree;

    if (A > 90 || B > 90 || C > 90)
    {
        return "obtuse";
    }
    if(A == 90 || B == 90 || C == 90)
    {
        return "right";
    }
    return "acute";   
}

bool isTriangle(const Point& p1, const Point& p2, const Point& p3)
{
    double area =
        (p2.x - p1.x) * (p3.y - p1.y) -
        (p2.y - p1.y) * (p3.x - p1.x);

    const double eps = 1e-9;
    return std::abs(area) > eps;
}


int main()
{
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        Point p1, p2, p3;
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        std::string caselength = triLength(p1, p2, p3);
        std::string caseangle = triAngles(p1, p2, p3);
        if (isTriangle(p1, p2, p3))
        {
            std::cout << "Case #" << i + 1 << ": " << caselength << ' ' << caseangle << ' ' << "triangle" << '\n';
        }
        else
        {
            std::cout << "Case #" << i + 1 << ": " << "not a triangle" << '\n';
        }
    }
    return 0;
}