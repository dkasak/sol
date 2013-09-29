Camera* create_camera() {
    auto camera = new PerspectiveCamera();
    camera->look_from(Point3D(0.0, 0.0, -5.0));
    camera->look_at(Point3D(0.0, 0.0, 1.0));
    camera->zoom(0.5);
    return camera;
}

World* build_world() {
    World* world = new World;

    world->set_background(ColourRGB(0.1, 0.2, 0.3));

    auto m1 = new Mirror(0.7, white);
    auto m2 = new Mirror(0.7, cyan);
    auto m3 = new Mirror(0.7, red);
    auto m4 = new Matte(1.0, yellow);
    auto mp = new Matte(0.8, white);

    auto s1 = new Sphere(Point3D( 0.0, 0.2, 6.0), 1.0);
    s1->set_material(m1);
    auto s2 = new Sphere(Point3D(-3.0, 0.2,  0.0), 1.0);
    s2->set_material(m2);
    auto s3 = new Sphere(Point3D( 3.0, 0.2,  0.0), 1.0);
    s3->set_material(m3);
    auto s4 = new Sphere(Point3D( 0.0, 0.5, -0.5), 0.3);
    s4->set_material(m4);

    auto p = new Plane(Point3D(0, -1.0, 0), Vector3D(0.0, 1.0, 0.0));
    p->set_material(mp);

    world->add_shape(s1);
    world->add_shape(s2);
    world->add_shape(s3);
    world->add_shape(s4);
    world->add_shape(p);

    auto l1 = new PointLight(Point3D( 0.0, 2.0, -2.0), white, 25.0);
    auto l2 = new PointLight(Point3D(-2.5, 2.0,  0.0), white, 50.0);
    auto l3 = new PointLight(Point3D( 2.5, 2.0,  0.0), green, 12.0);
    auto l4 = new DirectionalLight(Vector3D( -2.5, -2.0,  0.0), yellow, 0.4);

    world->add_light(l1);
    world->add_light(l2);
    world->add_light(l3);
    world->add_light(l4);

    return world;
}
