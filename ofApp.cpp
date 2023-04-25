#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	auto base_noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	this->camera_location = glm::vec3(
		ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.z, (ofGetFrameNum()) * 0.01), 0, 1, -500, 500));

	this->target_location = glm::vec3(
		ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + 100) * 0.01), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + 100) * 0.01), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.z, (ofGetFrameNum() + 100) * 0.01), 0, 1, -500, 500));

	for (int k = 0; k < 7; k++) {

		auto param = glm::vec3(15, 0, 0);
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto start_index = this->face.getNumVertices();

		ofColor color;
		for (int i = 0; i < 100; i++) {

			int index = this->face.getNumVertices();

			auto base_location = glm::vec3(
				ofMap(ofNoise(base_noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
				ofMap(ofNoise(base_noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
				ofMap(ofNoise(base_noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500));

			auto location = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.02), 0, 1, -100, 100),
				ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.02), 0, 1, -100, 100),
				ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.02), 0, 1, -100, 100));

			location += base_location;

			this->face.addVertex(location + param);
			this->face.addVertex(location - param);

			color.setHsb(ofMap(k, 0, 7, 0, 255), 200, 255);

			this->face.addColor(color);
			this->face.addColor(color);

			this->frame.addVertex(location + param);
			this->frame.addVertex(location - param);

			this->frame.addColor(ofColor(255));
			this->frame.addColor(ofColor(255));

			if (i > 0) {

				this->face.addIndex(index + 0); this->face.addIndex(index - 1); this->face.addIndex(index - 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index - 1);

				this->frame.addIndex(index + 0); this->frame.addIndex(index - 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index - 1);
			}
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
		this->frame.addIndex(frame.getNumVertices() - 1); this->frame.addIndex(frame.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto camera_location = this->camera_location + glm::vec3(0, 0, 500);

	this->cam.setPosition(camera_location);
	this->cam.setTarget(target_location);
	this->cam.lookAt(target_location);

	this->cam.begin();

	this->face.drawFaces();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}