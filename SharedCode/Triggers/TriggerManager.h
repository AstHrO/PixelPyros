//
//  TriggerManager.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 21/08/2013.
//
//

#pragma once
#include "Trigger.h"
#include "TriggerPattern.h"

class TriggerManager {
	
	public :
	
	TriggerManager();
	
	bool update(float deltaTime);
	void draw();
	
	void updateTriggerSettings(ofRectangle triggerarea, float spacing);
	void setShowTriggerDebug(bool);
	void setTriggersDisabled(bool disabled);
	void toggleDebug(); 
	
	
	void updateLayout();
	void setPattern(TriggerPattern tp);
	
	void mouseMoved(int x, int y); 
	
	TriggerPattern triggerPattern;
	
	ofRectangle triggerArea;
	//bool active;
	bool triggerDebug;
	bool triggersDisabled;
	

	
	vector <Trigger*> triggers;
	//vector <TriggerBase*> triggersLeft;
	//vector <TriggerBase*> triggersRight;
	
	float minimumSpacing;
	int triggerCount;

	
	
};