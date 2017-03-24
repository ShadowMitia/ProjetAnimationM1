// -*- mode: c++ -*-
#ifndef PHYSICS_OBJECTS_H
#define PHYSICS_OBJECTS_H

#include "ofMain.h"

class PhysicsObject {

 public:
  void applyForcee(ofVec3f force) {
    force /= mass;
    acceleration += force;
  }

  void updateForces() {
    velocity += acceleration;
    position += velocity;
    acceleration = {0, 0, 0};
  }

  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void checkEdges() = 0;
  virtual bool checkCollision(PhysicsObject* obj) = 0;

  void setPosition(ofVec3f pos) {
    position = pos;
  }

  void setPosition(int x, int y, int z) {
    position.x = x;
    position.y = y;
    position.z = z;
  }

  ofVec3f getPosition() {
    return position;
  }

  ofVec3f getVelocity() {
    return velocity;
  }

  ofVec3f getAcceleration() {
    return acceleration;
  }

  float getMass() {
    return mass;
  }

  ofColor getColor() {
    return color;
  }

  void setColor(ofColor c) {
    color = c;
  }

  virtual of3dPrimitive* getPrimitive() = 0;

 protected:

  ofVec3f acceleration = {0, 0, 0};
  ofVec3f velocity = {0, 0, 0};
  ofVec3f position = {0, 0, 0};
  float mass = 100.0;
  bool isStatic = false;

  ofColor color = ofColor::white;

  ~PhysicsObject() = default;
};

class Ball : public PhysicsObject {

 public:

 Ball(ofVec3f pos, int radius, bool staticObject = false) : sphere(radius, 100) {
    position = pos;
    this->radius = radius;
  }

  void draw() override {
    ofSetColor(color);
    sphere.draw();
  }

  void update() override {
    applyForce(ofVec3f(0, 0, -1));
    updateForces();
    //    std::cout << "Position x: " << position.x <<  " y: " << position.y
    //      << " z: " << position.z << "\n";
    //std::cout << "velocity : " << velocity.x << " " << velocity.y << " " << velocity.z << "\n";
    checkEdges();
    sphere.setPosition(position);
  }

  of3dPrimitive* getPrimitive() override {
    return &sphere;
  }

  float getRadius() {
    return radius;
  }

 protected:

  int radius;
  ofSpherePrimitive sphere;

  bool checkCollision(PhysicsObject* obj) override {
    auto other = obj->getPrimitive();

  }


  void checkEdges() override {
    if (position.x > 1000) {
      position.x = 1000;
      velocity.x *= -1;
    } else if (position.x < -1000) {
      velocity.x *= -1;
      position.x = 0;
    }

    if (position.y > 1000) {
      position.y = 1000;
      velocity.y *= -1;
    } else if (position.y < -1000) {
      velocity.y *= -1;
      position.y = 0;
    }

    if (position.z < 0) {
      velocity.z *= -1;
      position.z = 0;
    }

  }

};

class Box : public PhysicsObject {
 public:

 Box(ofVec3f pos, int size) : box(size, size, size) {
    position = pos;
    width = height = size;
  }

  void draw() override {
    ofSetColor(ofColor::white);
    ofDrawBox(position, width);
  }

  void update() override {

  }

  of3dPrimitive* getPrimitive() override {
    return &box;
  }

protected:
  ofVec2f size;
  int width;
  int height;

  ofBoxPrimitive box;

  bool checkCollision(PhysicsObject* obj) override {

  }

  void checkEdges() override {

  }

};


#endif
