#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <QRect>

class Point
{
public:
    int x;
    int y;

    Point()
    {
        this->x = -1;
        this->y = -1;
    }

    static Point empty()
    {
        return Point(-1, -1);
    }

    bool isEmpty()
    {
        return (this->x == -1) && (this->y == -1);
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

    friend std::ostream& operator << (std::ostream& out, const Point& p);

    bool inRect(int M, int N) const
    {
        return (0 <= this->x) && (this->x < M) && (0 <= this->y) && (this->y < N);
    }

    bool inRect(const QRect& rect) const
    {
        return (rect.left() < this->x) && (this->x < rect.right()) &&
               (rect.top() < this->y) && (this->y < rect.bottom());
    }
};

#endif // POINT_H
