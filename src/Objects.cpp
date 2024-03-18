#include "../include/Objects.h"


Material::Material()
    : diffuse(Eigen::Vector3f::Zero()),
    specular(Eigen::Vector3f::Zero()),
    shininess(0.0),
    emission(Eigen::Vector3f::Zero()),
    ambient(Eigen::Vector3f::Zero()) {}
Material::Material(Eigen::Vector3f diffuse_,  Eigen::Vector3f specular_, float shininess_, Eigen::Vector3f emission_, Eigen::Vector3f ambient_)
    : diffuse(diffuse_),
    specular(specular_),
    shininess(shininess_),
    emission(emission_),
    ambient(ambient_) {}

Triangle::Triangle(float ax, float ay, float az,
        float bx, float by, float bz,
        float cx, float cy, float cz)
    :
    a(Eigen::Vector3f(ax,ay,az)), b(Eigen::Vector3f(bx,by,bz)), c(Eigen::Vector3f(cx,cy,cz)),
    normals_defined(false),
    na(Eigen::Vector3f::Zero()), nb(Eigen::Vector3f::Zero()), nc(Eigen::Vector3f::Zero()),
    transform(Eigen::Matrix4f::Identity()),
    inv_transform(Eigen::Matrix4f::Identity()),
    mat(Material()) {}
Triangle::Triangle(Eigen::Vector3f a_, Eigen::Vector3f b_, Eigen::Vector3f c_)
    :
    a(a_), b(b_), c(c_),
    normals_defined(false),
    na(Eigen::Vector3f::Zero()), nb(Eigen::Vector3f::Zero()), nc(Eigen::Vector3f::Zero()),
    transform(Eigen::Matrix4f::Identity()),
    inv_transform(Eigen::Matrix4f::Identity()),
    mat(Material()) {}
Triangle::Triangle(vert_norm a_,vert_norm b_, vert_norm c_):
    a(a_.pos), b(b_.pos), c(c_.pos),
    normals_defined(true),
    na(a_.normal), nb(b_.normal), nc(c_.normal),
    transform(Eigen::Matrix4f::Identity()),
    inv_transform(Eigen::Matrix4f::Identity()),
    mat(Material()) {}


Sphere::Sphere(Eigen::Vector3f pos_, float radius_)
    :
    pos(pos_), radius(radius_),
    transform(Eigen::Matrix4f::Identity()),
    inv_transform(Eigen::Matrix4f::Identity()),
    mat(Material()) {}
Sphere::Sphere(float x, float y, float z, float radius_)
    :
    pos(Eigen::Vector3f(x,y,z)), radius(radius_),
    transform(Eigen::Matrix4f::Identity()),
    inv_transform(Eigen::Matrix4f::Identity()),
    mat(Material()) {}

Light::Light()
    : pos(Eigen::Vector3f::Zero()), color(Eigen::Vector3f::Zero()), is_point(false) {}
Light::Light(Eigen::Vector3f pos_, Eigen::Vector3f color_, bool is_point_)
    : pos(pos_), color(color_), is_point(is_point_) {}

Camera::Camera(Eigen::Vector3f eye_, Eigen::Vector3f center_, Eigen::Vector3f up_, float fovy_)
    : eye(eye_), center(center_), up(up_), fovy(fovy_) {}
Camera::Camera(float ex, float ey, float ez,
    float cx, float cy, float cz,
    float ux, float uy, float uz,
    float fovy_)
    : eye(Eigen::Vector3f(ex,ey,ez)),
    center(Eigen::Vector3f(cx,cy,cz)),
    up(Eigen::Vector3f(ux,uy,uz)),
    fovy(fovy_) {}
Camera::Camera()
    :eye(Eigen::Vector3f::Zero()),
    center(Eigen::Vector3f::Zero()),
    up(Eigen::Vector3f::Zero()),
    fovy(0.0) {}
