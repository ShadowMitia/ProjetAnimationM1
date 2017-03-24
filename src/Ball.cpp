#include "Ball.h"

Ball::Ball(float x, float y, float z)
  : position({x, y, z}), velocity(0, 0, 0), acceleration(0, 0, 0) {
}

void Ball::applyForce(ofVec3f force) {
  acceleration += force;
}

void Ball::update() {
  if (!isStatic) {
    velocity += acceleration;
    position += velocity * ofGetLastFrameTime();
    acceleration *= 0;
  }
}

void Ball::checkEdges() {
  if (position.y < 0) {
    velocity.y *= -1;
    position.y = 0;
  } else if (position.y >= 1000) {
    velocity.y *= -1;
    position.y = 1000;
  }

  if (position.x < -1000) {
    velocity.x *= -1;
    position.x = -1000;
  } else if (position.x >= 1000) {
    velocity.x *= -1;
    position.x = 1000;
  }

  if (position.z < -1000) {
    velocity.z *= -1;
    position.z = -1000;
  } else if (position.z >= 1000) {
    velocity.z *= -1;
    position.z = 1000;
  }
}

void Ball::draw() {
  ofSetColor(ofColor::blue);
  ofDrawSphere(position, radius);
}

ofVec3f Ball::getPosition() {
  return position;
}

bool Ball::isColliding(Ball &other) {
  auto oPos = other.getPosition();
  auto oRadius = other.getRadius();
  auto pos = getPosition();
  auto t = (pos - oPos) * (pos - oPos);
  return t.x + t.y + t.z <= (radius + oRadius) * (radius + oRadius);
}

void Ball::setStatic(bool setStatic) {
  isStatic = setStatic;
}
