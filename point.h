#ifndef POINT_H
#define POINT_H

class Point
{
public:
    int x;
    int y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void operator = (const Point& p)
    {
        this->x = p.x;
        this->y = p.y;
    }

    bool operator == (const Point& p)
    {
        return (this->x == p.x) && (this->y == p.y);
    }

    bool inRect(int M, int N) const
    {
        return (0 <= this->x) && (this->x < M) && (0 <= this->y) && (this->y < N);
    }
};

#endif // POINT_H

