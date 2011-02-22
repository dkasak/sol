#include <iostream>

#include "Vector.h"

int main() {
    Sol::Vector v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1);

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
    std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
    std::cout << "v1 * 3 = " << v1 * 3 << std::endl;
    std::cout << "v1 / 3 = " << v1 / 3 << std::endl;
    std::cout << "v1 dot v2 = " << v1.dot(v2) << std::endl;
    std::cout << "v1 cross v2 = " << v1.cross(v2) << std::endl;
    std::cout << "angle(v1, v2) = " << v1.angle(v2) << std::endl;

    std::cout << "v1.length() = " << v2.length() << std::endl;
    std::cout << "(v1 + v2).length() = " << (v1 + v2).length() << std::endl;

    v1 = v1 * 2;
    Sol::Vector v4 = v1 + Sol::Vector(1, 2, 3);
    std::cout << std::endl;
    std::cout << "v4 := 2v1 + i + 2j + 3k " << std::endl;
    std::cout << "v4 = " << v4 << std::endl << std::endl;

    v4 += Sol::Vector(2, 2, 2);
    std::cout << "v4 += 2i + 2j + 2k" << std::endl;
    std::cout << "v4 = " << v4 << std::endl << std::endl;

    v4 *= 2;
    std::cout << "v4 *= 2" << std::endl;
    std::cout << "v4 = " << v4 << std::endl << std::endl;

    v4 /= 5;
    std::cout << "v4 /= 2" << std::endl;
    std::cout << "v4 = " << v4 << std::endl << std::endl;

    std::cout << "v4.length() = " << v4.length() << std::endl;
    std::cout << "v4.normalised() = " << v4.normalised() << std::endl;
    std::cout << "v4 = " << v4 << std::endl;
    v4.normalise();
    std::cout << "v4 = " << v4 << " (after calling v4.normalise())" << std::endl;
    std::cout << "v4.length() = " << v4.length() << std::endl;

    return 0;
}

