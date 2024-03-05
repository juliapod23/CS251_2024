#include <gtest/gtest.h>

#include "canvaslist.h"
#include "shape.h"

// 1 - 4, Shape
TEST(Shape, DefaultConstructor) {
  Shape s;

  EXPECT_EQ(s.getX(), 0);
  EXPECT_EQ(s.getY(), 0);
}

TEST(Shape, ParametrizedConstructor) {
  Shape s(3, 4);

  EXPECT_EQ(s.getX(), 3);
  EXPECT_EQ(s.getY(), 4);

}

TEST(Shape, CopyConstructor) {
  Shape original(3,4);
  Shape copied(original);

  EXPECT_EQ(copied.getX(), original.getX());
  EXPECT_EQ(copied.getY(), original.getY());
}

TEST(Shape, GetAndSet) {
  Shape s;

  s.setX(5);
  s.setY(6);

  EXPECT_EQ(s.getX(), 5);
  EXPECT_EQ(s.getY(), 6);
}

TEST(Shape, Copy) {
  Shape original(3,4);
  Shape* copied = original.copy();

  EXPECT_NE(&original, copied);
  EXPECT_EQ(copied->getX(), original.getX());
  EXPECT_EQ(copied->getY(), original.getY());

  delete copied;
}

TEST(Shape, AsString) {
  Shape s(3,4);
  std::string expected = "It's a Shape at x: 3, y: 4";
  EXPECT_EQ(s.as_string(), expected);
}

TEST(Shape, Constructor) {
  Circle c(3, 4, 3);

  EXPECT_EQ(c.getX(), 3);
  EXPECT_EQ(c.getY(), 4);
  EXPECT_EQ(c.getRadius(),3);
}

TEST(CanvasList, Constructor) {
  CanvasList c;

  EXPECT_EQ(c.empty(), true);
}

TEST(CanvasList, Size) {
  CanvasList c;

  EXPECT_EQ(c.empty(), true);
}

TEST(CanvasList, PushAndSize){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  ASSERT_FALSE(c.empty());
  ASSERT_EQ(c.size(), 3);
}

TEST(CanvasList, ClearAndEmpty){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  c.clear();
  ASSERT_TRUE(c.empty());
  ASSERT_EQ(c.size(), 0);
}

TEST(CanvasList, DeepCopyConstructor){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  
  CanvasList copy(c);

  ASSERT_EQ(copy.size(), c.size());

  for(int i = 0; i < c.size(); i++){
    ASSERT_NE(copy.shape_at(i), c.shape_at(i));
  }
}

TEST(CanvasList, Assignment){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  
  CanvasList newC;
  newC = c;

  ASSERT_EQ(newC.size(), c.size());

  for(int i = 0; i < c.size(); i++){
    ASSERT_EQ(newC.shape_at(i)->as_string(), c.shape_at(i)->as_string());
  }
}

TEST(CanvasList, PushFrontAndBack){
  CanvasList c;
  c.push_front(new Circle(3));
  c.push_back(new Rect(4,5));
  
  ASSERT_EQ(c.size(), 2);
  ASSERT_EQ(c.shape_at(0)->as_string(), "It's a Circle at x: 0, y: 0, radius: 3");
  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Rectangle at x: 0, y: 0 with width: 4 and height: 5");
}

TEST(CanvasList, RemoveAt){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  c.remove_at(1);
  ASSERT_EQ(c.size(), 2);
  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Right Triangle at x: 0, y: 0 with base: 3 and height: 4");
}

TEST(CanvasList, RemoveEveryOther){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));
  c.push_back(new Circle(1));

  c.remove_every_other();
  
  ASSERT_EQ(c.size(), 2);
  ASSERT_EQ(c.shape_at(0)->as_string(), "It's a Circle at x: 0, y: 0, radius: 3");
  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Right Triangle at x: 0, y: 0 with base: 3 and height: 4");
}

TEST(CanvasList, PopFront){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));

  Shape* popped = c.pop_front();
  
  ASSERT_EQ(c.size(), 2);
  ASSERT_EQ(popped->as_string(), "It's a Circle at x: 0, y: 0, radius: 3");
  ASSERT_EQ(c.shape_at(0)->as_string(), "It's a Rectangle at x: 0, y: 0 with width: 4 and height: 5");

  delete popped;
}

TEST(CanvasList, PopBack){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));

  Shape* popped = c.pop_back();
  
  ASSERT_EQ(c.size(), 2);
  ASSERT_EQ(popped->as_string(), "It's a Right Triangle at x: 0, y: 0 with base: 3 and height: 4");
  ASSERT_EQ(c.shape_at(0)->as_string(), "It's a Circle at x: 0, y: 0, radius: 3");
  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Rectangle at x: 0, y: 0 with width: 4 and height: 5");
}

TEST(CanvasList, Find){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));

  int i = c.find(0,0);
  
  ASSERT_EQ(i, 0);
}

TEST(CanvasList, ShapeAt){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));

  Shape* s = c.shape_at(1);

  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Rectangle at x: 0, y: 0 with width: 4 and height: 5");
}

TEST(CanvasList, InsertAfter){
  CanvasList c;
  c.push_back(new Circle(3));
  c.push_back(new Rect(4,5));
  c.push_back(new RightTriangle(3,4));

  c.insert_after(0, new Circle(2));
  
  ASSERT_EQ(c.size(), 4);
  ASSERT_EQ(c.shape_at(1)->as_string(), "It's a Circle at x: 0, y: 0, radius: 2");
  c.insert_after(2, new Rect(4,6));
  ASSERT_EQ(c.size(), 5);
  ASSERT_EQ(c.shape_at(3)->as_string(), "It's a Rectangle at x: 0, y: 0 with width: 4 and height: 6");
  c.insert_after(3, new RightTriangle(5,6));
  ASSERT_EQ(c.size(), 6);
  ASSERT_EQ(c.shape_at(4)->as_string(), "It's a Right Triangle at x: 0, y: 0 with base: 5 and height: 6");
}

TEST(Circle, CircleMutAccessor){
  Circle c(5, 16, 6);
  EXPECT_EQ(c.getX(),5);
  EXPECT_EQ(c.getY(),16);
  EXPECT_EQ(c.getRadius(),6);

  c.setX(2);
  c.setY(7);
  c.setRadius(8);
  EXPECT_EQ(c.getX(), 2);
  EXPECT_EQ(c.getY(),7);
  EXPECT_EQ(c.getRadius(),8);
}

TEST(RightTriangle, RightTriMutAccessor){
  RightTriangle t(5, 16, 6, 8);
  EXPECT_EQ(t.getX(),5);
  EXPECT_EQ(t.getY(),16);
  EXPECT_EQ(t.getBase(),6);
  EXPECT_EQ(t.getHeight(),8);

  t.setX(2);
  t.setY(7);
  t.setBase(8);
  t.setHeight(6);

  EXPECT_EQ(t.getX(), 2);
  EXPECT_EQ(t.getY(),7);
  EXPECT_EQ(t.getBase(),8);
  EXPECT_EQ(t.getHeight(),6);
}

TEST(Rectangle, RectMutAccessor){
  Rect r(5, 16, 6, 8);
  EXPECT_EQ(r.getX(),5);
  EXPECT_EQ(r.getY(),16);
  EXPECT_EQ(r.getWidth(),6);
  EXPECT_EQ(r.getHeight(),8);

  r.setX(2);
  r.setY(7);
  r.setWidth(8);
  r.setHeight(6);

  EXPECT_EQ(r.getX(), 2);
  EXPECT_EQ(r.getY(),7);
  EXPECT_EQ(r.getWidth(),8);
  EXPECT_EQ(r.getHeight(),6);
}

TEST(CanvasList, PopFrontEmpty){
  CanvasList c;

  Shape* popped = c.pop_front();

  ASSERT_EQ(popped, nullptr);
}

TEST(CanvasList, PopBackSingle){
  CanvasList c;

  c.push_back(new Circle(4));
  Shape* popped = c.pop_back();

  ASSERT_EQ(c.size(), 0);
  ASSERT_EQ(popped->as_string(), "It's a Circle at x: 0, y: 0, radius: 4");
  ASSERT_TRUE(c.empty());
}