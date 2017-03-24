#include "ofApp.h"

#include "CollisionManager.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);

  ofEnableDepthTest();

  light.setup();
  light.setPointLight();
  light.setPosition(1000, 2000, 1000);
  light.enable();

  cam.setPosition({500, 100, 500});
  cam.lookAt({0, 100, 0}, cam.getUpDir());

  plane.setMode(OF_PRIMITIVE_LINE_LOOP);

  plane.addVertex({-1000, 0, -1000});
  plane.addColor(ofColor::red);
  plane.addVertex({1000, 0, -1000});
  plane.addColor(ofColor::red);
  plane.addVertex({1000, 0, 1000});
  plane.addColor(ofColor::red);
  plane.addVertex({-1000, 0, 1000});
  plane.addColor(ofColor::red);

  ceiling.setMode(OF_PRIMITIVE_LINE_LOOP);
  ceiling.addVertex({-1000, 1000, -1000});
  ceiling.addColor(ofColor::blue);
  ceiling.addVertex({1000, 1000, -1000});
  ceiling.addColor(ofColor::blue);
  ceiling.addVertex({1000, 1000, 1000});
  ceiling.addColor(ofColor::blue);
  ceiling.addVertex({-1000, 1000, 1000});
  ceiling.addColor(ofColor::blue);

  bodies.reserve(200);
  bodies.push_back(Body::BoxFactory({0, 0, 0}, {200, 200, 200}));
  bodies.push_back(Body::BoxFactory({500, 0, 0}, {200, 200, 200}));
  bodies.push_back(Body::BoxFactory({500, 0, -500}, {200, 200, 200}));
  bodies.push_back(Body::BoxFactory({-500, 0, -500}, {200, 200, 200}));
  bodies.push_back(Body::BoxFactory({-500, 0, 500}, {200, 200, 200}));

  for (auto i = 0U; i < 30; i++) {
    bodies.push_back(Body::SphereFactory({ofRandom(-1000, 1000), 0, ofRandom(-1000, 1000)}, 20));
    //bodies.push_back(Body::SphereFactory({std::sin((float)i * 10) * 100, 0, std::cos((float)i * 10) * 100}, 20));
  }
  for (auto& b : bodies) {
    b.setVelocity(ofVec3f(ofRandom(-10, 10), 0, ofRandom(-10, 10)));
  }

  boids.reserve(200);
  for (auto i = 0U; i < 50; i++) {
    boids.emplace_back(ofVec3f(ofRandom(-1000, 1000), 0, ofRandom(-1000, 1000)));
  }

  std::cout << "Setup finished\n";
}

//--------------------------------------------------------------
void ofApp::update() {
  ofSetWindowTitle("FPS " + std::to_string(ofGetFrameRate()));
  cam.move(camPosition);
  camPosition = {0, 0, 0};

  // Apply gravity and other external forces if necessary
  for (auto& b : bodies) { b.applyForce(GRAVITY); }
  // Update positions
  for (auto& b : bodies) { b.update(); }
  // Collision detection and resolution
  for (auto i = 0U; i < bodies.size(); i++) {
    for (auto j = 0U; j < bodies.size(); j++) {
      if (i == j) {
	continue;
      }
      if (bodies[i].isColliding(bodies[j])) {
	if (bodies[i].getType() == TBody::SPHERE && bodies[j].getType() == TBody::SPHERE) {
	  CollisionManager::resolveSphereSphereCollision(bodies[i], bodies[j]);
	} else if ((bodies[i].getType() == TBody::SPHERE && bodies[j].getType() == TBody::BOX)
		   || (bodies[i].getType() == TBody::BOX && bodies[j].getType() == TBody::SPHERE)) {
	  CollisionManager::resolveAABBSphereCollision(bodies[i], bodies[j]);
	} else if (bodies[i].getType() == TBody::BOX && bodies[j].getType() == TBody::BOX) {
	  CollisionManager::resolveAABBAABBCollision(bodies[i], bodies[j]);
	}
      }
    }
  }

  for (auto& b : boids) { b.update(boids, bodies); }

  // Make sure everything stays in the area
  for (auto& b : bodies) { b.checkEdges(); }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(ofColor::white);

  cam.begin();
  ofDrawAxis(25);
  ofSetColor(ofColor::gray);

  plane.draw();
  ceiling.draw();

  /*
  ofDrawBox(0, 0, 0, 100);
  ofDrawBox(300, 0, 0, 100);
  ofDrawBox(0, 300, 0, 100);
  ofPushMatrix();
  ofSetColor(ofColor::blue);
  perlinPlane.draw();
  for (auto i = 0U; i < 1000; i+=50) {
    for (auto j = 0U; j < 1000; j+=50) {
      ofDrawSphere(-500 + i, 10 * ofSignedNoise(ofRandom(0, 50) * ofGetLastFrameTime()), -500 + j, 5);
    }
  }

  ofPopMatrix();
  */
  for (auto& b : bodies) { b.draw(); }
  for (auto& b : boids) { b.draw(); }
  // Fountain
  /*
  ofPushMatrix();
  ofSetColor(ofColor::gray);
  ofDrawCone(-500, 0, -500, 80, 100);
  ofDrawCylinder(-500, 0, -500, 400, 60);
  ofDrawCylinder(-500, 100, -500, 75, 10);
  ofPopMatrix();
  */
  cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == OF_KEY_LEFT) {
    camPosition.x -= 50;
  } else if (key == OF_KEY_RIGHT) {
    camPosition.x += 50;
  } else if (key == OF_KEY_UP) {
    camPosition.z -= 50;
  } else if (key == OF_KEY_DOWN) {
    camPosition.z += 50;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  cam.pan(x - mouseX);
  mouseX = x;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
