// -*- mode: c++ -*-
#pragma once

#include "ofMain.h"

#include "Body.h"
#include "Boids.h"

const ofVec3f GRAVITY{0, -10, 0};

class ofApp : public ofBaseApp{

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  std::vector<Body> bodies;

  std::vector<Boid> boids;

  ofCamera cam;
  ofVec3f camPosition;

  float mouseX = 0.0;
  float mouseY = 0.0;

  ofMesh plane;
  ofMesh ceiling;

  ofLight light;

  void moveCamera(float speed) {
    auto camPos = cam.getPosition();
    auto camLook = cam.getLookAtDir();

    auto vec = camLook - camPos;

    camPos += vec * speed;

    camLook += vec * speed;

    cam.lookAt(camLook);
  }
};

/* Gestion de l'orientation de la caméra */
/*
void rotate_camera(double speed)
{
	vect_x = cam_look_x - cam_pos_x;
	vect_z = cam_look_z - cam_pos_z;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(speed);
	float sinTheta = (float)sin(speed);

	double new_x = sqrt(pow(vect_x,2) + pow(vect_z,2)) * cosTheta;
	double new_z = sqrt(pow(vect_x,2) + pow(vect_z,2)) * sinTheta;

	cam_look_x = cam_pos_x + new_x;
	cam_look_z = cam_pos_z + new_z;
}

*/
