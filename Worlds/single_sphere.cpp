World* build_world() {
    World* world = new World;

    world->set_background(black);

    auto m1 = new Matte(0.7, red);
    auto mp = new Matte(0.8, white);

    auto s1 = new Sphere(Point3D( 0.0, 0.8, 6.0), 1.0);
    s1->set_material(m1);

    auto p = new Plane(Point3D(0, -1.0, 0), Vector3D(0.0, 1.0, 0.0));
    p->set_material(mp);

    world->add_shape(s1);
    world->add_shape(p);

    auto l1 = new PointLight(Point3D( -2.0, 1.8, 4.0), white, 20.0);

    world->add_light(l1);

    return world;
}
