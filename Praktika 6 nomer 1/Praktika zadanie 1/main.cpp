#include "cone.h"
#include <iostream>

int main() {
    // Создание статических объектов конусов
    Cone cone1(1, 2, 3, 4, 5);
    Cone cone2(2, 4);

    // Вывод параметров каждого конуса и их объёма и площади поверхности
    cone1.output();
    std::cout << "Surface area: " << cone1.surfaceArea() << std::endl;
    std::cout << "Volume: " << cone1.volume() << std::endl;
    cone2.output();
    std::cout << "Surface area: " << cone2.surfaceArea() << std::endl;
    std::cout << "Volume: " << cone2.volume() << std::endl;

    // Создание динамического объекта конуса с помощью конструктора по умолчанию
    Cone* cone3 = new Cone();
    cone3->input();
    cone3->output();
    std::cout << "Surface area: " << cone3->surfaceArea() << std::endl;
    std::cout << "Volume: " << cone3->volume() << std::endl;
    delete cone3;

    // Создание массива конусов
    Cone cones[] = { Cone(1, 2, 3, 4, 5), Cone(2, 4), Cone(3, 5, 7, 2, 3) };
    const int nCones = sizeof(cones) / sizeof(cones[0]);

    // Вывод параметров каждого конуса и их объёма и площади поверхности
    for (int i = 0; i < nCones; ++i) {
        cones[i].output();
        std::cout << "Surface area: " << cones[i].surfaceArea() << std::endl;
        std::cout << "Volume: " << cones[i].volume() << std::endl;
    }

    return 0;
}
