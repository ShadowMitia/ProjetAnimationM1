// -*- mode: c++ -*-
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "ofMain.h"
#include "Body.h"

namespace CollisionManager {
  static void resolveSphereSphereCollision(Body& firstBall, Body& secondBall) {
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

  static void resolveAABBAABBCollision(Body& firstBox, Body& secondBox) {

  }

  static void resolveAABBSphereCollision(Body& obj1, Body& obj2) {
    auto& box = obj1.getType() == TBody::BOX ? obj1 : obj2;
    auto& sphere = obj1.getType() == TBody::SPHERE ? obj1 : obj2;

    auto vel = sphere.getVelocity();

    if (vel.x >= vel.y && vel.x >= vel.z) {
      sphere.setVelocity({vel.x * -1, vel.y, vel.z});
    } else if (vel.y >= vel.x && vel.y >= vel.z) {
      sphere.setVelocity({vel.x, vel.y * -1, vel.z});
    } else if (vel.z >= vel.y && vel.z >= vel.x) {
      sphere.setVelocity({vel.x, vel.y, vel.z * -1});
    }
  }
};

#endif /* COLLISIONMANAGER_H */
