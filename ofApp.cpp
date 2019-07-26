#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	vector<char> charactors = { 
		'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R',
		'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '!' };

	int span = this->font_size * 1.3;
	for (int i = 0; i < charactors.size(); i++) {

		int x = (i % 6) * span - span * 3;
		int y = (i / 6) * (span * 1.5) - (span * 1.5) * 3;
		int z = 0;
		int rotate = 0;

		float noise_value = ofNoise(x * 0.005, y * 0.005, ofGetFrameNum() * 0.005);
		if (noise_value > 0.5) {

			z = ofMap(noise_value, 0.5, 1, 0, -500);
			rotate = ofMap(noise_value, 0.5, 1, 0, 360 * 5);
		}

		ofPushMatrix();
		ofTranslate(x, y, z);
		ofRotateX(rotate);
		ofRotateY(rotate);

		auto path = font.getCharacterAsPoints(charactors[i], true, false);
		auto outline = path.getOutline();

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {
				
				auto location = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(string{ charactors[i] }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ charactors[i] }) * 0.5);
				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(string{ charactors[i] }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ charactors[i] }) * 0.5);
				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}