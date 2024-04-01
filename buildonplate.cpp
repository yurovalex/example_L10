#include "buildonplate.h"
#include <cmath>

//Нормализация значений до диапазана (-1;1)
double BuildOnPlate::normalize(double value, double min, double max) {
    return (2 * (value - min) / (max - min)) - 1;
}

//Построение эллипса
void BuildOnPlate::DrawEllipse()
{
    objGL->ClearVertexArray();
    auto flag = objGL->isEmptyVertexArray();
    if (flag == false) {
        return;
    }
    double a = 400; //основной радиус эллипса: для примера 400
    double b = 200; //вспомогательный радиус
    double interval = a > b ? a: b;
    double t = -interval;
    int posX = WIDTH/2;
    int posY = HEIGHT/4;
    double delta = 0.05;
    double x = 0, y = 0;
    double _x = -0.78, _y = 0.05;
    while(t <= interval)
    {
         objGL->AddVertexArray(_x,_y);
        //параметрическое уравнение эллипса
        x = a*(1 - t*t)/(1 + t*t);
        y = b*2*t/(1 + t*t);
        x += posX;
        y += b;
        y += posY;
        _x = normalize(x,0,WIDTH);
        _y = normalize(y,0,HEIGHT);
        objGL->AddVertexArray(_x,_y);
        t += delta;
    }
}

//Построение ветки гиперболы
void BuildOnPlate::DrawHyperbola()
{
    double interval = 0.9;
    double a = 5;
    double b = 10;
    double t = -interval;
    double x = 0, y = 0;
    double posX = WIDTH/2;
    double posY = HEIGHT/2;
    double _x = 0.095, _y = -0.25;
    while(t <= interval)
    {
        objGL->AddVertexArray(_x,_y);
        //параметрическое уравнение гиперболы
        x = a*(1+t*t)/(1-t*t);
        y = b*2*t/(1-t*t);
        x +=posX;
        y += posY;
        _x = normalize(x,0,WIDTH);
        _y = normalize(y,0,HEIGHT);
         objGL->AddVertexArray(_x,_y);
        //SetPixel(x,y,BLACK);
        t += 0.01;
    }
}


