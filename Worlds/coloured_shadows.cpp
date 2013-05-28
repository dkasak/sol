World* build_world() {
    World* world = new World;

    world->set_background(ColourRGB(0.1, 0.2, 0.3));

    auto m1 = new Matte(0.7, white);
    auto mp = new MatteMirror(0.7, white, 0.2, white);

    auto s1 = new Sphere(Point3D(0.0, 1.5, 2.0), 1.0);
    s1->set_material(m1);

    auto p = new Plane(Point3D(0.0, -1.0, 0.0), Vector3D(0.0, 1.0, 0.0));
    p->set_material(mp);

    world->add_shape(s1);
    world->add_shape(p);

    auto l1 = new PointLight(Point3D( 1.0, 4.0, 1.0), red, 25.0);
    auto l2 = new PointLight(Point3D(-1.0, 4.0, 1.0), green, 25.0);
    auto l3 = new PointLight(Point3D( 0.0, 4.0, 3.0), blue, 25.0);
    auto l4 = new PointLight(Point3D( 0.0, 0.1, 2.0), white, 1.0);

    world->add_light(l1);
    world->add_light(l2);
    world->add_light(l3);
    world->add_light(l4);

    world->set_ambient(ColourRGB(0.1, 0.1, 0.1));

    return world;
}

