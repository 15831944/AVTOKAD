#include <vector>
#include <iostream>
#include <cmath>
#include "miniwin.h"
using namespace miniwin;
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

class Object
{
public:
    Object()
    {}
    virtual Draw()
    {}
    virtual ~Object()
    {}

};

class Line_Object : public Object
{
public:
    Line_Object(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2)
    {}
    Draw()
    {
        linea(x1, y1, x2, y2);
    }
    ~Line_Object()
    {
    }
    float x1, y1, x2, y2;
};

class Rectangle_Object : public Object
{
public:
    Rectangle_Object(float x_left, float y_top, float x_right, float y_bottom) : x_left(x_left), y_top(y_top), x_right(x_right), y_bottom(y_bottom)
    {}
    Draw()
    {
        linea(x_left, y_top, x_right, y_top);
        linea(x_right, y_top, x_right, y_bottom);
        linea(x_right, y_bottom, x_left, y_bottom);
        linea(x_left, y_bottom, x_left, y_top);
    }
    ~Rectangle_Object()
    {
    }
    float x_left, y_top, x_right, y_bottom;
};

class Circle_Object : public Object
{
public:
    Circle_Object(float x_center, float y_center, float radius) : x_center(x_center), y_center(y_center), radius(radius)
    {}
    Draw()
    {
        circulo(x_center, y_center, radius);
    }
    ~Circle_Object()
    {
    }
    float x_center, y_center, radius;
};

void menu()
{
    linea(0, 0, 20, 0);
    linea(20, 0, 20, 20);
    linea(20, 20, 0, 20);
    linea(0, 20, 0, 0);
    linea( 5,5, 15,15);
}


enum objectos{LINE = 0, RECTANGLE, CIRCLE};

int main()
{
    float x_start, y_start, x_end, y_end;
    float x_mouse, y_mouse;
    objectos object = LINE;
    bool start_object = false;
    vector <Object*> p;
    vredimensiona(SCREEN_WIDTH, SCREEN_HEIGHT);
    while(1)
    {
 //       borra();
        menu();
        color_rgb(255, 0, 0);
        for(auto it = p.begin(); it != p.end(); it++)
        {
            (*it)->Draw();
        }
        raton(x, y);
        circulo(x, y, 10);
        if(object == LINE)
        {
            if(raton_boton_izq() == true && start_object == false)
            {
                start_object = true;
                x_start = raton_x();
                y_start = raton_y();
            }
            if(raton_boton_izq() == true && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                linea(x_start, y_start, x_end, y_end);
            }
            if(raton_boton_izq() == false && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                p.push_back(new Line_Object(x_start, y_start, x_end, y_end));
                start_object = false;
            }
        }
        if(object == RECTANGLE)
        {
            if(raton_boton_izq() == true && start_object == false)
            {
                start_object = true;
                x_start = raton_x();
                y_start = raton_y();
            }
            if(raton_boton_izq() == true && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                linea(x_start, y_start, x_end, y_start);
                linea(x_end, y_start, x_end, y_end);
                linea(x_end, y_end, x_start, y_end);
                linea(x_start, y_end, x_start, y_start);
            }
            if(raton_boton_izq() == false && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                p.push_back(new Rectangle_Object(x_start, y_start, x_end, y_end));
                start_object = false;
            }
        }
        if(object == CIRCLE)
        {
            if(raton_boton_izq() == true && start_object == false)
            {
                start_object = true;
                x_start = raton_x();
                y_start = raton_y();
            }
            if(raton_boton_izq() == true && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                circulo(x_start, y_start, sqrt((x_end - x_start) * (x_end - x_start) + (y_end - y_start) * (y_end - y_start)));
            }
            if(raton_boton_izq() == false && start_object == true)
            {
                x_end = raton_x();
                y_end = raton_y();
                p.push_back(new Circle_Object(x_start, y_start, sqrt((x_end - x_start) * (x_end - x_start) + (y_end - y_start) * (y_end - y_start))));
                start_object = false;
            }
        }
        if(raton_boton_der() == true)
        {
            cout << object << endl;
            if(object == LINE)
            {
                object = RECTANGLE;
            }
            else if (object == RECTANGLE)
            {
                object = CIRCLE;
            }
            else if (object == CIRCLE)
            {
                object = LINE;
            }
            do{
            }while(raton_boton_der() == true);
        }
        refresca();
    }
    return 0;
}

