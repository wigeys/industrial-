#ifndef CONE_H
#define CONE_H

class Cone {
public:
    Cone(); // конструктор по умолчанию
    Cone(double x, double y, double z, double r, double h); // конструктор для произвольного конуса
    Cone(double r, double h); // конструктор для конуса с центром в начале координат

    void input();
    void output();
    double surfaceArea();
    double volume();

private:
    double x_, y_, z_; // координаты центра основания
    double r_; // радиус основания
    double h_; // высота
};

#endif // CONE_H
