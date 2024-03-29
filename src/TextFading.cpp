//
//  TextFading.cpp
//  TextFadings
//
//
//

#include "TextFading.hpp"

TextFading::TextFading()
{
	ofImage newImg;
	texts.push_back(newImg);
    setup();
}

TextFading::TextFading(vector<ofImage> _texts) {
	texts = _texts;
    setup();
}

void TextFading::setup() {
	ofSetCircleResolution(100);
	inc = 0;
}

void TextFading::update(int _inc) {
	inc = (_inc % incMax);
}

void TextFading::draw() {
	ofPushMatrix();
	ofPushStyle();
	if (inc >= fadeInStart) { // Fade in
		// Change the textIncrementer
		if (inc == fadeInStart) {
			textIncrementer = (textIncrementer + 1) % texts.size();
		}
		float easedValue = quadEaseOut(ofClamp(float(inc - fadeInStart)/float(incMax - fadeInStart), 0.0, 1.0));
		// Change the opacity
		ofSetColor(255, 255, 255, ofMap(easedValue, 0.0, 1.0, 0, 255));
	} else if (inc >= fadeOutStart) { // Fade out
		float easedValue = quadEaseOut(ofClamp(float(inc - fadeOutStart)/float(fadeInStart - fadeOutStart), 0.0, 1.0));
		// Change the opacity
		ofSetColor(255, 255, 255, ofMap(easedValue, 0.0, 1.0, 255, 0));
	}
	// Left image
	texts[textIncrementer].draw(0, 100, 639, 414);
	// Center image
	texts[(textIncrementer + 1) % texts.size()].draw(fixedWidth/3.0, 100, 639, 414);
	// Right image
	texts[(textIncrementer + 2) % texts.size()].draw(fixedWidth/3.0 * 2.0, 100, 639, 414);
	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
float TextFading::quadEaseOut(float t) {
	return -1.0 *(t)*(t-2);
}
