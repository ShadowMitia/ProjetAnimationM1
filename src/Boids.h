// -*- mode: c++ -*-
#ifndef BOIDS_H
#define BOIDS_H

#include "ofMain.h"

class Boid {

  ofVec3f position;
  ofVec3f velocity;
  ofVec3f acceleration;

  float r;
  float maxSpeed;
  float maxForce;
  float angle;

public:
  Boid(ofVec3f pos) : position(pos) {
    r = 100;
    maxSpeed = 5.f;
    maxForce = 10.f;
    velocity = ofVec3f(ofRandom(20, 50), 0, ofRandom(20, 50));
  }

  void applyForce(ofVec3f force) {
    acceleration += force * ofGetLastFrameTime();
  }

  void update(std::vector<Boid>& boids, std::vector<Body>& bodies) {
    flock(boids, bodies);
    velocity += acceleration;
    position += velocity;
    acceleration *= 0;
    checkEdges();
  }

  ofVec3f seek(ofVec3f target) {
    ofVec3f newTarget = target - position;
    newTarget.normalize();
    newTarget *= maxSpeed;

    ofVec3f steer = newTarget - velocity;
    steer.limit(maxForce);
    angle += position.angle(steer);
    return steer;
  }

  void draw() {
    ofPushMatrix();
    ofDrawCone(position, 10, 30);
    ofPopMatrix();
  }

  // Separation
  // Method checks for nearby boids and steers away
  ofVec3f separate (std::vector<Boid>& boids) {
    float desiredseparation = 75.0f;
    ofVec3f steer = ofVec3f::zero();
    int count = 0;
    // For every boid in the system, check if it's too close
    for (auto& other : boids) {
      float d = position.distance(other.position);
      // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((d > 0) && (d < desiredseparation)) {
        // Calculate vector pointing away from neighbor
        ofVec3f diff = position - other.position;
        diff.normalize();
        diff / d;        // Weight by distance
        steer += diff;
        count++;            // Keep track of how many
      }
    }
    // Average -- divide by how many
    if (count > 0) {
      steer / ((float)count);
    }

    // As long as the vector is greater than 0
    if (steer.length() > 0) {
      // First two lines of code below could be condensed with new PVector setLength() method
      // Not using this method until Processing.js catches up
      // steer.setLength(maxSpeed);

      // Implement Reynolds: Steering = Desired - Velocity
      steer.normalize();
      steer *= maxSpeed;
      steer -= velocity;
      steer.limit(maxForce);
    }
    return steer;
  }

    ofVec3f separate (std::vector<Body>& boids) {
    float desiredseparation = 100.0f;
    ofVec3f steer = ofVec3f::zero();
    int count = 0;
    // For every boid in the system, check if it's too close
    for (auto& other : boids) {
      float d = position.distance(other.getPosition());
      // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((d > 0) && (d < desiredseparation)) {
        // Calculate vector pointing away from neighbor
        ofVec3f diff = position - other.getPosition();
        diff.normalize();
        diff / d;        // Weight by distance
        steer += diff;
        count++;            // Keep track of how many
      }
    }
    // Average -- divide by how many
    if (count > 0) {
      steer / ((float)count);
    }

    // As long as the vector is greater than 0
    if (steer.length() > 0) {
      // First two lines of code below could be condensed with new PVector setLength() method
      // Not using this method until Processing.js catches up
      // steer.setLength(maxSpeed);

      // Implement Reynolds: Steering = Desired - Velocity
      steer.normalize();
      steer *= maxSpeed;
      steer -= velocity;
      steer.limit(maxForce);
    }
    return steer;
  }

  // Alignment
  // For every nearby boid in the system, calculate the average velocity
  ofVec3f align (std::vector<Boid>& boids) {
    float neighbordist = 200;
    ofVec3f sum = ofVec3f::zero();
    int count = 0;
    for (auto& other : boids) {
      float d = position.distance(other.position);
      if ((d > 0) && (d < neighbordist)) {
        sum += other.position;
        count++;
      }
    }
    if (count > 0) {
      sum /= ((float)count);
      sum.normalize();
      sum *= maxSpeed;
      ofVec3f steer = sum - velocity;
      steer.limit(maxForce);
      return steer;
    }
    else {
      return ofVec3f::zero();
    }
  }

  // Cohesion
  // For the average position (i.e. center) of all nearby boids, calculate steering vector towards that position
  ofVec3f cohesion (std::vector<Boid>& boids) {
    float neighbordist = 200;
    ofVec3f sum = ofVec3f::zero();
    int count = 0;
    for (auto& other : boids) {
      float d = position.distance(other.position);
      if ((d > 0) && (d < neighbordist)) {
        sum += other.position; // Add position
        count++;
      }
    }
    if (count > 0) {
      sum /= count;
      return seek(sum);  // Steer towards the position
    }
    else {
      return ofVec3f::zero();
    }
  }



  void flock(std::vector<Boid>& boids, std::vector<Body>& bodies) {
    ofVec3f sep = separate(boids);
    ofVec3f ali = align(boids);
    ofVec3f coh = cohesion(boids);

    ofVec3f repulse = ofVec3f::zero();
    for (auto& other : bodies) {
      float d = position.distance(other.getPosition());
      if ((d > 0) && (d < 100)) {
        ofVec3f diff = position - other.getPosition();
	diff.y = 0; // On reste en 2D!
        diff / d;
        applyForce(diff);
      }
    }


    applyForce(sep);
    applyForce(ali);
    applyForce(coh);

    velocity.limit(maxSpeed);
  }



void checkEdges() {
  if (position.y < 0) {
    position.y = 0;
  }

  if (position.x < -1000) {
    position.x = 1000;
  } else if (position.x >= 1000) {
    position.x = -1000;
  }

  if (position.z < -1000) {
    position.z = 1000;
  } else if (position.z >= 1000) {
    position.z = -1000;
  }
}

};

#endif /* BOIDS_H */
