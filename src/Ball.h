// -*- mode: c++ -*-
#ifndef BALL_H
#define BALL_H

#include "ofMain.h"

class Ball {
protected:
  ofVec3f position;
  ofVec3f velocity;
  ofVec3f acceleration;
  ofSpherePrimitive sphere;
  float radius = 10;
  bool isStatic;

public:
  Ball(float x, float y, float z);
  Ball(ofVec3f pos) : Ball(pos.x, pos.y, pos.z) {}
  void applyForce(ofVec3f force);
  void update();
  void draw();
  void setStatic(bool setStatic);
  bool getStatic() {return isStatic; };
  ofVec3f getPosition();
  bool isColliding(Ball& other);
  void setRadius(float newRadius) {
    radius = newRadius;
  }
  float getRadius() {
    return radius;
  }

  void setVelocity(ofVec3f newVelocity) {
    velocity = newVelocity;
  }

  void checkEdges();

  static void resolveSphereCollision(Ball& firstBall, Ball& secondBall) {
    auto diff = firstBall.getPosition() - secondBall.getPosition();
    auto dist =	std::sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
    auto projectedAxis = diff / dist;
    /*projectedAxis.x /= dist;
    projectedAxis.y /= dist;
    projectedAxis.z /= dist;*/

    float projectedVelocityFirstBall = projectedAxis.dot(firstBall.getVelocity());
    float projectedVelocitySecondBall = projectedAxis.dot(secondBall.getVelocity());

    // Paramètre de surface
    float K_const = 0.5;

    firstBall.setPosition(firstBall.getPosition() - firstBall.getVelocity());
    secondBall.setPosition(secondBall.getPosition() - secondBall.getVelocity());

    firstBall.setVelocity(-K_const * projectedAxis * projectedVelocityFirstBall);
    secondBall.setVelocity(-K_const * projectedAxis * projectedVelocitySecondBall);
  }

  void setPosition(ofVec3f pos) {
    position = pos;
  }

  ofVec3f getVelocity() {
    return velocity;
  }

};

#endif /* BALL_H */
