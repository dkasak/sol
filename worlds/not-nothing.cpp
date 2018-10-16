Camera* create_camera() {
    auto camera = new PerspectiveCamera();
    camera->look_from(Point3D(5.8, 3.7, 10.0));
    camera->look_at(Point3D(-3.1, 0.0, -1.0));
    camera->zoom(0.3);
    return camera;
}

World* build_world() {
    World* world = new World;

    ColourRGB bright_red(0.98, 0.29, 0.21);
    ColourRGB bright_green(0.72, 0.73, 0.15);
    ColourRGB bright_yellow(0.98, 0.74, 0.18);
    ColourRGB bright_blue(0.51, 0.65, 0.6);
    ColourRGB bright_purple(0.83, 0.53, 0.61);
    ColourRGB bright_aqua(0.56, 0.75, 0.49);
    ColourRGB bright_orange(1.0, 0.5, 0.098);

    ColourRGB red(0.8, 0.14, 0.11);
    ColourRGB green(0.6, 0.59, 0.1);
    ColourRGB yellow(0.84, 0.6, 0.13);
    ColourRGB blue(0.27, 0.52, 0.53);
    ColourRGB purple(0.69, 0.38, 0.53);
    ColourRGB aqua(0.41, 0.62, 0.42);
    ColourRGB orange(0.84, 0.36, 0.055);
    ColourRGB amaranth(0.96, 0.039, 0.3);

    ColourRGB faded_red(0.62, 0.0, 0.024);
    ColourRGB faded_green(0.47, 0.45, 0.055);
    ColourRGB faded_yellow(0.71, 0.46, 0.078);
    ColourRGB faded_blue(0.027, 0.4, 0.47);
    ColourRGB faded_purple(0.56, 0.25, 0.44);
    ColourRGB faded_aqua(0.26, 0.48, 0.35);
    ColourRGB faded_orange(0.69, 0.23, 0.012);

    world->set_ambient(orange * 0.04);
    world->set_background(faded_blue);

    auto m1 = new MatteMirror(0.8, amaranth, 0.2, amaranth);
    auto m2 = new MatteMirror(0.2, aqua, 0.8, aqua);
    auto m3 = new MatteMirror(0.4, red, 0.6, white);
    auto m4 = new Matte(1.0, yellow);
    auto mp = new Matte(1.0, green);

    auto s1 = new Sphere(Point3D(-2.0, 2.2, 4.0),
                         1.0);
    s1->set_material(m1);

    auto s2 = new Sphere(Point3D(0.5, 2.3, 4.0),
                         0.5);
    s2->set_material(m2);

    auto s3 = new Box(Point3D(-2.5, 0.2, 0.0),
                      Point3D(1.0, 1.0, 2.0),
                      Vector3D(0, -1, 0));
    /* auto s3 = new Box(3.5, 0.8, 2.0, */
    /*                   Vector3D(-2.5, -1.2, 0)); */
    s3->set_material(m3);

    auto s4 = new Sphere(Point3D(0.0, 0.5, -0.5),
                         0.3);
    s4->set_material(m4);

    auto p = new Plane(Point3D(0, -1.0, 0), Vector3D(0.0, 1.0, 0.0));
    p->set_material(mp);

    world->add_shape(s1);
    world->add_shape(s2);
    world->add_shape(s3);
    world->add_shape(s4);
    world->add_shape(p);

    auto l1 = new PointLight(Point3D(-2.0, 2.0, -2.0), white, 25.0);
    auto l2 = new PointLight(Point3D(5.5, 6.0,  0.0), white, 30.0);
    auto l3 = new PointLight(Point3D(2.5, 2.0,  0.0), green, 12.0);
    auto l4 = new DirectionalLight(Vector3D(1.5, -2.0,  3.0), green, 0.7);

    world->add_light(l1);
    world->add_light(l2);
    world->add_light(l3);
    world->add_light(l4);

    return world;
}
