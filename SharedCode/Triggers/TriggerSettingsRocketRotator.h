//
//  TriggerSettingsRocketRotator.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 10/09/2013.
//
//

#pragma once

#include "TriggerSettingsRocket.h"

class TriggerSettingsRocketRotator : public TriggerSettingsRocket {
	
	
	public :
	
	TriggerSettingsRocketRotator(float extent = 10, float speed = 2,
								 bool rotateonfire = false);
	
	
	
	virtual void doTrigger(ofVec3f& pos, float power, float direction);
	
	virtual void draw(float elapsedtime, ofVec3f pos, ofColor colour, float unitPower, bool active);
	
	
	
	float rotationExtent;
	float rotationSpeed;
	float rocketCount;
	bool rotateOnFire;
	float angle;
	float displayAngle;
	

	
	
	
	
	
	
};