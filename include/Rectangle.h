//
// Created by jdemoss on 11/11/19.
//

#ifndef LEAVINGTERRA_RECTANGLE_H
#define LEAVINGTERRA_RECTANGLE_H

#include "Vector2.h"

class Rectangle {
public:
    Rectangle();
    Rectangle(Vector2 Position, Vector2 Size);

    Vector2 GetPosition();
    Vector2 GetSize();
    double GetX();
    double GetY();
    double GetWidth();
    double GetHeight();

    Rectangle& SetPosition(Vector2 Position);
    Rectangle& SetSize(Vector2 Size);

    Rectangle Copy();
    Rectangle DeepCopy();

protected:
    Vector2 Position;
    Vector2 Size;
};

#endif //LEAVINGTERRA_RECTANGLE_H