// -*- mode: c++ -*-
#ifndef BOX_H
#define BOX_H

#include "ofMain.h"

class Box {
protected:
  ofVec3f position;
  ofVec3f velocity;
  ofVec3f acceleration;
  ofBoxPrimitive sphere;
  float width = 10;
  float height = 10;
  float depth = 10;
  bool isStatic;

public:
  Box(float x, float y, float z);
  Box(ofVec3f pos) : Box(pos.x, pos.y, pos.z) {}
  void applyForce(ofVec3f force);
  void update();
  void draw();
  void setStatic(bool setStatic);
  bool getStatic() {return isStatic; };
  ofVec3f getPosition();
  bool isColliding(Box& other);
  ofVec3f getSize() {
    return ofVec3f(width, height, depth);
  }
  void setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
  }

  void setVelocity(ofVec3f newVelocity) {
    velocity = newVelocity;
  }

  void checkEdges();

  static void resolveBoxCollision(Box& firstBox, Box& secondBox) {
    // auto diff = firstBall.getPosition() - secondBall.getPosition();
    // auto dist =	std::sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
    // auto projectedAxis = diff / dist;
    // /*projectedAxis.x /= dist;
    // projectedAxis.y /= dist;
    // projectedAxis.z /= dist;*/

    // float projectedVelocityFirstBall = projectedAxis.dot(firstBall.getVelocity());
    // float projectedVelocitySecondBall = projectedAxis.dot(secondBall.getVelocity());

    // // Paramètre de surface
    // float K_const = 0.5;

    // firstBall.setPosition(firstBall.getPosition() - firstBall.getVelocity());
    // secondBall.setPosition(secondBall.getPosition() - secondBall.getVelocity());

    // firstBall.setVelocity(-K_const * projectedAxis * projectedVelocityFirstBall);
    // secondBall.setVelocity(-K_const * projectedAxis * projectedVelocitySecondBall);
  }

  void setPosition(ofVec3f pos) {
    position = pos;
  }

  ofVec3f getVelocity() {
    return velocity;
  }

};

#endif /* BOX_H */
