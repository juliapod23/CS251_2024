#include "shape.h"

#include <string>

using namespace std;

Shape::Shape() {
    x = 0;
    y = 0;
}

Shape::Shape(int x, int y) {
    this->x = x;
    this->y = y;
}

Shape::~Shape() {}

Shape* Shape::copy() {
    return new Shape(x, y);
}

int Shape::getX() const {
    return x;
}

int Shape::getY() const {
    return y;
}

void Shape::setX(int x) {
    this->x = x;
}

void Shape::setY(int y) {
    this->y = y;
}

string Shape::as_string() const {
    return "It's a Shape at x: " + to_string(x) + ", y: " + to_string(y);
}

// Circle
Circle::Circle() {
    Shape(0, 0);
    this->radius = 0;
}
Circle::Circle(int r) {
    Shape(0, 0);
    this->radius = r;
}
Circle::Circle(int x, int y, int r) {
    Shape(x, y);
    this->x = x;
    this->y = y;
    this->radius = r;
}

Circle::~Circle() {}

Circle* Circle::copy() {
    return new Circle(x, y, radius);
}

int Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(int r) {
    this->radius = r;
}

string Circle::as_string() const {
    return "It's a Circle at x: " + to_string(x) + ", y: " + to_string(y) + ", radius: " + to_string(radius);
}

// Rectangle
Rect::Rect() {
    Shape(0, 0);
    this->width = 0;
    this->height = 0;
}
Rect::Rect(int w, int h) {
    Shape(0, 0);
    this->width = w;
    this->height = h;
}
Rect::Rect(int x, int y, int w, int h) {
    Shape(x, y);
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

Rect::~Rect() {}

Rect* Rect::copy() {
    return new Rect(x, y, width, height);
}

int Rect::getWidth() const {
    return width;
}

int Rect::getHeight() const {
    return height;
}

void Rect::setWidth(int w) {
    this->width = w;
}

void Rect::setHeight(int h) {
    this->height = h;
}

string Rect::as_string() const {
    return "It's a Rectangle at x: " + to_string(x) + ", y: " + to_string(y) +
           " with width: " + to_string(width) + " and height: " + to_string(height);
}

// Right Triangle
RightTriangle::RightTriangle() {
    Shape(0, 0);
    this->base = 0;
    this->height = 0;
}
RightTriangle::RightTriangle(int b, int h) {
    Shape(0, 0);
    this->base = b;
    this->height = h;
}
RightTriangle::RightTriangle(int x, int y, int b, int h) {
    Shape(x, y);
    this->x = x;
    this->y = y;
    this->base = b;
    this->height = h;
}

RightTriangle::~RightTriangle() {}

RightTriangle* RightTriangle::copy() {
    return new RightTriangle(x, y, base, height);
}

int RightTriangle::getBase() const {
    return base;
}

int RightTriangle::getHeight() const {
    return height;
}

void RightTriangle::setBase(int b) {
    this->base = b;
}

void RightTriangle::setHeight(int h) {
    this->height = h;
}

string RightTriangle::as_string() const {
    return "It's a Right Triangle at x: " + to_string(x) + ", y: " + to_string(y) +
           " with base: " + to_string(base) + " and height: " + to_string(height);
}