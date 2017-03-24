#include "Box.h"

Box::Box(float x, float y, float z)
  : position({x, y, z}), velocity(0, 0, 0), acceleration(0, 0, 0) {
}

void Box::applyForce(ofVec3f force) {
  acceleration += force;
}

void Box::update() {
  if (!isStatic) {
    velocity += acceleration;
    position += velocity * ofGetLastFrameTime();
    acceleration *= 0;
  }
}

void Box::checkEdges() {
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

void Box::draw() {
  ofSetColor(ofColor::blue);
  ofDrawBox(position, width, height, depth);
}

ofVec3f Box::getPosition() {
  return position;
}

bool Box::isColliding(Box &other) {

  auto oPos = other.getPosition();
  auto oSize = other.getSize();
  auto pos = getPosition();
  auto size = getSize();

  auto otherMinX = oPos.x - oSize.x / 2;
  auto otherMinY = oPos.y - oSize.y / 2;
  auto otherMinZ = oPos.z - oSize.z / 2;

  auto otherMaxX = oPos.x + oSize.x / 2;
  auto otherMaxY = oPos.y + oSize.y / 2;
  auto otherMaxZ = oPos.z + oSize.z / 2;

  auto minX = pos.x - size.x / 2;
  auto minY = pos.y - size.y / 2;
  auto minZ = pos.z - size.z / 2;

  auto maxX = pos.x + size.x / 2;
  auto maxY = pos.y + size.y / 2;
  auto maxZ = pos.z + size.z / 2;

  return (minX <= otherMaxX && maxX >= otherMinX) &&
    (minY <= otherMaxY && maxY >= otherMinY) &&
    (minZ <= otherMaxZ && maxZ >= otherMinZ);
}

void Box::setStatic(bool setStatic) {
  isStatic = setStatic;
}
