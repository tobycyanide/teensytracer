//
// Created by Adam Keim on 7/3/20.
//

#include "include/shapes.h"

std::vector<Intersection> Shape::intersect(Ray &ray) {
    auto ray2 = ray.transform(this->transform.inverse());
    return local_intersect(ray2);

}
Tuple Shape::normal_at(const Tuple& w_p) {
    Tuple local_point = this->transform.inverse() * w_p;
    Tuple local_normal = local_normal_at(local_point);
    Tuple world_normal = this->transform.inverse().transpose() * local_normal;
    Tuple new_world_normal = Vector(world_normal.x(), world_normal.y(), world_normal.z());
    return new_world_normal.normalized();
}



std::vector<Intersection> Sphere::local_intersect(Ray &ray) {
    auto xs = std::vector<Intersection>();
    auto sphere_to_ray = ray.origin - this->origin;
    auto a = ray.direction.dot(ray.direction);
    auto b = 2 * ray.direction.dot(sphere_to_ray);
    auto c = sphere_to_ray.dot(sphere_to_ray) - 1;
    float discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0) {
        return xs;
    } else {
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        xs.push_back(Intersection(t1, this));
        xs.push_back(Intersection(t2, this));
        return xs;
    }
}

Tuple Sphere::local_normal_at(const Tuple& w_p) {
    return w_p;
}

Tuple TestShape::local_normal_at(const Tuple& w_p) {
    return Vector(w_p.x(), w_p.y(), w_p.z());
}

Tuple Plane::local_normal_at(const Tuple& w_p) {
    return Vector(0, 1, 0);
}

std::vector<Intersection> Plane::local_intersect(Ray &ray) {
    auto xs = std::vector<Intersection>();
    if (fabs(ray.direction.y()) >= EPSILON) {
        float t = -ray.origin.y() / ray.direction.y();
        xs.emplace_back(t, this);
    }
    return xs;
}





