//
//  TriggerSettingsRocketOrb.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 11/10/2013.
//
//

#include "TriggerSettingsRocketOrb.h"

void TriggerSettingsRocketOrb :: update(float deltatime, map<string, float>&triggerValues){
	
	values = &triggerValues;
	
	if(triggerValues.find("rot1") == triggerValues.end()) triggerValues["rot1"] = ofRandom(360);
	if(triggerValues.find("rot2") == triggerValues.end()) triggerValues["rot2"] = ofRandom(360);
	if(triggerValues.find("rot3") == triggerValues.end()) triggerValues["rot3"] = ofRandom(360);
	if(triggerValues.find("vel1") == triggerValues.end()) triggerValues["vel1"] = ofRandom(400,440);
	if(triggerValues.find("vel2") == triggerValues.end()) triggerValues["vel2"] = ofRandom(320,380);
	if(triggerValues.find("vel3") == triggerValues.end()) triggerValues["vel3"] = ofRandom(280,320);
	if(triggerValues.find("smoothSize") == triggerValues.end()) triggerValues["smoothSize"] = 1;

	
	deltaTime = deltatime;

}

void TriggerSettingsRocketOrb :: draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle) {

	elapsedTime = elapsedtime;
	map<string, float>& triggerValues = *values;
	
	float& rot1 = triggerValues["rot1"];
	float& rot2 = triggerValues["rot2"];
	float& rot3 = triggerValues["rot3"];
	float& vel1 = triggerValues["vel1"];
	float& vel2 = triggerValues["vel2"];
	float& vel3 = triggerValues["vel3"];
	float& smoothSize = triggerValues["smoothSize"]; 
	
	float speed = 1.5;
	
	if(unitPower<rechargeSettings->triggerPower ) speed = ofMap(unitPower, 0, rechargeSettings->triggerPower, 0, 0.5, true);
	rot1+= vel1 * deltaTime * speed;
	rot2+= vel2 * deltaTime * speed;
	rot3+= vel3 * deltaTime * speed;

	
	ofPushStyle();
	ofPushMatrix();
	
	float triggerPower = rechargeSettings->triggerPower;
    
	ofTranslate(pos);
	/*
	if(waitBrightness>0) {
		ofEnableBlendMode(OF_BLENDMODE_ADD);
	
		ofSetColor(waitBrightness*0.6 * abs(cos(elapsedtime*6)) );
		ofDrawBitmapString("WAIT", -16, -16, 0);
	}*/
	scale*=smoothSize;
	ofScale(0.75,0.75,0.75);
	ofScale(scale, scale, scale);
	
	float activeScale = 1;//ofMap(unitPower, 0, triggerPower, 0, 1, true);
	ofPushMatrix();
	ofScale(activeScale, activeScale, activeScale);
	
	ofDisableBlendMode();
	ofEnableAlphaBlending();
	ofFill();
	ofSetColor(0, 200);
	ofCircle(0,0, radius+2);
	ofSetColor(0, 70);
	ofCircle(0,0, radius+6);
	ofDisableAlphaBlending();
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	
	ofColor dimColour = ofColor::white;
	//dimColour.setHue(hue);
	//dimColour.setSaturation(saturation);
  // WHY DOES IT HAVE A CHECK FOR RESTORE SPEED? 
	if((triggerPower<=unitPower)  || (rechargeSettings->restoreSpeed==0)) {
		
		//ofCircle(0, 0, radius*0.5);
		//ofNoFill();
		
		dimColour.setHsb(hue, saturation, ofMap(unitPower, 0, triggerPower, 10,150, true));
		
	
		ofSetColor(dimColour);
		ofCircle(0, 0, radius*unitPower*0.5);
		
		ofSetColor(ofMap(unitPower, 0, triggerPower, 10,255, true));
		ofCircle(0, 0, radius*unitPower*0.3);
		
		dimColour.setHsb(hue, saturation, ofMap(unitPower, 0, triggerPower, 10,200, true));
		
		//ofSetColor(200);
		smoothSize += (1-smoothSize)*0.5;
	} else {
		
		smoothSize += (-smoothSize)*0.01;
		
		//waitBrightness+=3;
		//if(waitBrightness>255) waitBrightness = 255;
		dimColour.setBrightness(ofMap(unitPower, 0, triggerPower, 0,50, true));
		
		
	}
	
	ofSetColor(dimColour);
	

	ofSetLineWidth(1);
	
	ofPushMatrix();
	ofRotateY(30);
	ofRotateX(rot1);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotateZ(120);
	ofRotateX(rot2);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotateZ(240);
	ofRotateX(rot3);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	ofPopMatrix();
	if((rotateOnFire) || (rotationSpeed!=0)) {
		ofRotate(angle);
		ofTriangle(0, -10-(radius*2), radius*0.5, -10, radius*-0.5, -10);
		//0,0,0,-20);
	}
	
	
		
	ofPopStyle();
	ofPopMatrix();
	
	
	
}
