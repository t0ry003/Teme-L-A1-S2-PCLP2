//
// Created by rares on 4/28/2023.
//

#include <bits/stdc++.h>

using namespace std;

class Point {
    double x, y;
public:
    Point(double _x, double _y) : x(_x), y(_y) {}

    Point() : x(0), y(0) {}

    double getX() const { return x; }

    double getY() const { return y; }

    void setX(double _x) { x = _x; }

    void setY(double _y) { y = _y; }

    Point operator-(const Point &p) const {
        return Point(abs(x - p.x), abs(y - p.y));
    }
};

class Shape {
protected:
    Point mFirst;
    Point mSecond;
    string mName;
public:
    Shape(Point _first, Point _second) : mFirst(_first), mSecond(_second) {}

    Shape() : mFirst(Point()), mSecond(Point()) {}

    Point getFirst() const { return mFirst; }

    Point getSecond() const { return mSecond; }

    void setFirst(Point _first) { mFirst = _first; }

    void setSecond(Point _second) { mSecond = _second; }

    string getName() const { return mName; }

    void setName(string _name) { mName = _name; }

    virtual double getArea() const = 0;

    virtual double getPerimeter() const = 0;
};

class Quadrilateral : public Shape {
public:
    Quadrilateral() : Shape() {
        mName = "Unknown";
    }

    Quadrilateral(Point _first, Point _second, string _name) : Shape(_first, _second) {
        setName(_name);
    }

    double getLength() const {
        return (mFirst - mSecond).getX();
    }

    double getWidth() const {
        return (mFirst - mSecond).getY();
    }

    double getArea() const override {
        return getLength() * getWidth();
    }

    double getPerimeter() const override {
        return 2 * (getLength() + getWidth());
    }
};

class Circle : public Shape {
private:
    double mRadius;
public:
    Circle() : Shape() {
        mName = "Unknown";
        mRadius = 0;
    }

    Circle(Point _first, double _radius) : Shape(_first, Point()) {
        mName = "cerc";
        mRadius = _radius;
    }

    double getArea() const override {
        return M_PI * mRadius * mRadius;
    }

    double getPerimeter() const override {
        return 2 * M_PI * mRadius;
    }

    void setRadius(double _radius) {
        mRadius = _radius;
    }

    double getRadius() const {
        return mRadius;
    }
};

bool cmp(const Shape *a, const Shape *b) {
    if (a->getArea() == b->getArea())
        return a->getPerimeter() < b->getPerimeter();
    return a->getArea() < b->getArea();
}

int main() {
    vector<Shape *> shapes;
    int n;
    double min, max;
    cin >> n >> min >> max;

    if (n < 1 || n > 500) {
        cout << "Valoare de intrare invalida";
        return 0;
    }

    if (min > max) {
        cout << "Valoare de intrare invalida";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        if (name == "cerc") {
            double x, y, r;
            cin >> x >> y >> r;
            if ((r < 0 || r > 1000) || (x < -1000 || x > 1000) || (y < -1000 || y > 1000)) {
                cout << "Valoare de intrare invalida";
                return 0;
            }
            shapes.push_back(new Circle(Point(x, y), r));
        } else if (name == "dreptunghi" || name == "patrat") {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if ((x1 < -1000 || x1 > 1000) || (y1 < -1000 || y1 > 1000) || (x2 < -1000 || x2 > 1000) ||
                (y2 < -1000 || y2 > 1000)) {
                cout << "Valoare de intrare invalida";
                return 0;
            }
            shapes.push_back(new Quadrilateral(Point(x1, y1), Point(x2, y2), name));
        }
    }

    sort(shapes.begin(), shapes.end(), cmp);

    for (auto shape: shapes) {
        cout << fixed << setprecision(6) << shape->getName() << " " << shape->getArea() << " " << shape->getPerimeter()
             << endl;
    }

    return 0;
}
