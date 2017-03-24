// -*- mode: c++ -*-
#ifndef BODY_H
#define BODY_H

#include "ofMain.h"

enum class TBody {
  BOX,
  SPHERE,
};

class Body {

public:
  static Body BoxFactory(ofVec3f pos, ofVec3f s) {
    Body b = Body(pos, s, TBody::BOX);
    ofBoxPrimitive box(s.x / 2, s.y / 2, s.z / 2);
    b.primitive = std::make_unique<ofBoxPrimitive>(box);
    b.isStatic = true;
    return b;
  }

  static Body SphereFactory(ofVec3f pos, float r) {
    Body b = Body(pos, ofVec3f(r,r,r), TBody::SPHERE);
    ofSpherePrimitive sphere(r, 10);
    b.primitive = std::make_unique<ofSpherePrimitive>(sphere);
    b.isStatic = false;
    return b;
  }

private:
  Body(ofVec3f pos, ofVec3f s, TBody t) : position(pos), velocity({0, 0, 0}), acceleration({0, 0, 0}), size({s.x / 2, s.y / 2, s.z / 2}), type(t) { }

public:
  void update() {
    if (!isStatic) {
      velocity += acceleration;
      position += velocity;
      acceleration *= 0;
    }
  }

  void draw() {
    ofPushMatrix();
    ofTranslate(position);
    primitive->draw();
    ofPopMatrix();
  }

  void applyForce(ofVec3f force) {
    acceleration += force * ofGetLastFrameTime();
  }
  void checkEdges() {
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

  bool isColliding(Body& other) {
    auto minA = position - size;
    auto maxA = position + size;
    auto minB = other.position - other.size;
    auto maxB = other.position + other.size;

    if (type == TBody::SPHERE && other.type == TBody::SPHERE) {
      return position.distance(other.getPosition()) <= (other.size.x) + (size.x);
    } else if (type == TBody::BOX && other.type == TBody::BOX) {
      return (minA.x <= maxB.x && maxA.x >= minB.x)
	&&   (minA.y <= maxB.y && maxA.y >= minB.y)
	&&   (minA.z <= maxB.z && maxA.z >= minB.z);
    } else if (type == TBody::BOX && other.type == TBody::SPHERE) {
      auto x = std::max(minA.x, std::min(other.position.x, maxA.x));
      auto y = std::max(minA.y, std::min(other.position.y, maxA.y));
      auto z = std::max(minA.z, std::min(other.position.z, maxA.z));
      auto distance = ofVec3f(x, y, z).distance(other.position);
      return distance < other.size.x;
    } else if (type == TBody::SPHERE && other.type == TBody::BOX) {
      auto x = std::max(minB.x, std::min(position.x, maxB.x));
      auto y = std::max(minB.y, std::min(position.y, maxB.y));
      auto z = std::max(minB.z, std::min(position.z, maxB.z));
      auto distance = ofVec3f(x, y, z).distance(position);
      return distance < size.x;
    }
    return false;
  }

private:
  ofVec3f position;
  ofVec3f velocity;
  ofVec3f acceleration;

  bool isStatic;

  ofVec3f size;

  TBody type;

  std::unique_ptr<of3dPrimitive> primitive;

public:
  void setPosition(ofVec3f pos) { position = pos; }
  void setVelocity(ofVec3f vel) { velocity = vel; }
  void setAcceleration(ofVec3f acc) { acceleration = acc; }

  ofVec3f getPosition() const { return position; }
  ofVec3f getVelocity() const { return velocity; }
  ofVec3f getAcceleration() const { return acceleration; }

  bool getStatic() { return isStatic; }

  void setSize(ofVec3f s) { size = ofVec3f(s.x / 2, s.y / 2, s.z / 2); }
  ofVec3f getSize() const { return ofVec3f(size.x * 2, size.y * 2, size.z * 2); }

  TBody getType() const { return type; }

};

#endif /* BODY_H */
