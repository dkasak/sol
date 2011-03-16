#ifndef SOL_SCENE_H
#define SOL_SCENE_H

#include <vector>
using namespace std;

namespace Sol {

class Scene {

private:
    Point  origin;
    Screen screen;
    Eye    eye;
    vector<const Shape&> objects;
    vector<const Light&> lights;
    double ambientLight;

public:
    Scene();
    void setOrigin(const Point &p);
    void setScreen(const Screen &s);
    void setEye(const Eye &e);
    void addShape(const Shape &s);
    void addLight(const Light &l);
    void setAmbient(double ambient);
    void render();
};

} // namespace Sol

#endif // SOL_SCENE_H

