#include <iostream>
#include <glm/glm.hpp>
#include <EasyBMP.h>
#include <vector>
#include <omp.h>

#define height 512
#define width 512
#define SIZE 4

double dot(glm::vec3 x, glm::vec3 y)
{
    return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}
class Ray
{
    public:
        glm::vec3 original;
        glm::vec3 direction;

        Ray(glm::vec3 original, glm::vec3 direction)
        {
            this -> original = original;
            this -> direction = glm::normalize(direction);
        }
};
class Camera
{
    public:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;

        Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 right)
        {
            this -> position = position;
            this -> direction = glm::normalize(direction);
            this -> right = glm::normalize(right);
            this -> up = glm::cross(this -> right, this -> direction);
        }

        Ray Virtual(int x, int y)
        {
            return Ray(this -> position, this -> direction + this -> up * ((y + 0.5f) / height - 0.5f) + this -> right * ((x + 0.5f) / width - 0.5f));
        }
};

class Triangle
{
    public:
        glm::vec3 vector_1;
        glm::vec3 vector_2;
        glm::vec3 vector_3;
        RGBApixel color;

        Triangle(glm::vec3 vector_1, glm::vec3 vector_2, glm::vec3 vector_3, RGBApixel color)
        {
            this -> vector_1 = vector_1;
            this -> vector_2 = vector_2;
            this -> vector_3 = vector_3;
            this -> color = color;
        }

        bool intersection(Ray ray, double &object)
        {
            glm::vec3 Stream_1 = this -> vector_2 - this -> vector_1;
            glm::vec3 Stream_2 = this -> vector_3 - this -> vector_1;
            glm::vec3 q = ray.original - this -> vector_1;
            glm::vec3 w = glm::cross(ray.direction, Stream_2);
            glm::vec3 e = glm::cross(q, Stream_1);

            double down = dot(w, Stream_1);
            double x = dot(w, q) / down;
            double y = dot(e, ray.direction) / down;

            if(x >= 0 and y >= 0 and x + y <= 1)
            {
                object = dot(e, Stream_2) / down;
                return true;
            }
            else
                return false;
        }
};

class Scene
{
    public:
        std::vector<Triangle> m_triangle;

        Scene(){}
};


RGBApixel RayTracing(Camera camera, Scene scene, int x, int y)
{
    RGBApixel new_color;
    bool intersect = false;
    double new_object = INFINITY;
    double object = 0.0f;

    for(int i = 0; i < scene.m_triangle.size(); i++)
    {
        if(scene.m_triangle[i].intersection(camera.Virtual(x, y), object))
        {
            if(new_object > object)
            {
                intersect = true;
                new_color = scene.m_triangle[i].color;
                new_object = object;
            }
        }
    }

    if(intersect)
    {
        return new_color;
    }

    new_color = {255, 255, 255, 1};
    return new_color;
}

int main(int argc, char ** argv) {
    BMP image;
    Camera camera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0));
    Scene scene = Scene();
    RGBApixel Color = {126, 0, 126, 1};


    for(int i = 0; i < SIZE*2; i++)
    {
        for(int j = 0; j < SIZE*2; j++)
        {
            scene.m_triangle.push_back(Triangle(glm::vec3(i - SIZE, -j + SIZE, SIZE),
                                                glm::vec3(i - SIZE + 1, -j + SIZE, SIZE),
                                                glm::vec3(i - SIZE, -j + SIZE + 1, SIZE),
                                                Color));
        }
    }
    image.SetSize(width, height);

    #pragma omp parallel for collapse(2)

    for(int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
            image.SetPixel(i, j, RayTracing(camera, scene, i, j));
    }
    image.WriteToFile("./myimage.bmp");
    return 0;
}