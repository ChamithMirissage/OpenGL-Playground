#ifndef OPENGLPLAYGROUND_POINT_H
#define OPENGLPLAYGROUND_POINT_H

struct Point {
    float x, y;

    Point(){}

    Point(float _x, float _y){
        this->x = _x;
        this->y = _y;
    }

    static Point middle(Point p1, Point p2){
        return Point((p1.x + p2.x)*0.5, (p1.y + p2.y)*0.5);
    }

    float distance(Point p){
        return (pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
    }
};

#endif //OPENGLPLAYGROUND_POINT_H
