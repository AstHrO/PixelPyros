//
//  TriggerManager.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 21/08/2013.
//
//

#include "TriggerManager.h"



TriggerManager::TriggerManager () {
	
	triggersDisabled = false;
	triggerDebug = false;

}




bool TriggerManager :: update(float deltaTime) {
	
	//if(!active) return false;
	int activeTriggers = 0;
	
	for(int i=0; i<triggers.size(); i++) {
		
		if( triggers[i]->update(deltaTime)) activeTriggers++;
		
	}
	/*
	if (activeTriggers==0)  {
		active = false;
	}*/
	
	return true;
	
	
}

void TriggerManager :: draw() {
	
	//if(!active) return;
	
	for(int i=0; i<triggers.size(); i++) {
		
		triggers[i]->draw();
		
	}
	
	
	
}


void TriggerManager :: setPattern(TriggerPattern tp ) {
	
	triggerPattern = tp;
	
	// TODO this is where we transfer the settings from the pattern
	// onto all the triggers.
	/*
	for(int i = 0; i<triggers.size(); i++) {
		
		Trigger * trigger = triggers[i];
		if(tp.triggers.size()>0) {
			TriggerSettings settings = tp.triggers[i%(tp.triggers.size())];
			//trigger->hue = sourcetrigger.hue;
			//trigger->saturation = sourcetrigger.saturation;
			
			trigger->copySettings(settings);
			
			trigger->active = true;
			
			cout << i << " hue : " << trigger->hue << endl ;
		} else {
			trigger->active = false;
			
		}
		
	}*/
	
	
	
	updateLayout();
}


void TriggerManager :: updateTriggerSettings(ofRectangle triggerarea, float spacing ){
	
	triggerArea = triggerarea;
	minimumSpacing = spacing;
	
	//if(spacing<=0) spacing = 0.1;
	//for(int i = 0; i<triggerPatterns.size() ; i++) {
	//	triggerPatterns[i]->updateLayout(triggerarea, spacing, triggerDebug, triggersDisabled);
	//}
	
	updateLayout();
	
}

void TriggerManager :: toggleDebug() {
		
	setShowTriggerDebug(!triggerDebug);
	
}
void TriggerManager::setShowTriggerDebug(bool debug){
	for(int i=0; i<triggers.size(); i++){

		triggers[i]->showDebugData = debug ;
	}
	triggerDebug = debug;
}

void TriggerManager::setTriggersDisabled(bool disabled){
	for(int i=0; i<triggers.size(); i++)
	{
		
		triggers[i]->disabled = disabled ;
	}
}

void TriggerManager :: updateLayout() {
	
	cout << " ____________________________________ UPDATE LAYOUT _______________" << endl; 
	
	//triggers.clear();
	//triggerCount = 0;
	//triggersLeft.clear();
	//triggersRight.clear();
	
	/*
	for(int i = 0; i<triggerPattern.triggers.size(); i++) {
			
		
		TriggerBase* trigger = triggerPattern.triggers.at(i)->clone();
		
		trigger->start();
		
		trigger->disabled = triggersDisabled;
		trigger->showDebugData = triggerDebug;
		triggers.push_back(trigger);
		
	}
	
	triggerCount = triggers.size();
	*/
	
	

	
	float xPos = triggerArea.x;
	
	int triggerIndex = 0;
	triggerCount = 0;
	
	if(triggerPattern.triggers.size()==0) {
		//cout << "NO TRIGGER PATTERNS :( " << endl;
		//  should probably disable all the triggers
		
		
		for(int i = 0; i<triggers.size(); i++) {
			triggers[i]->active = false;
			
		}
		
		return;
		
	}
	// TODO implement fixed position triggers
	/*
	if(false) { // triggerPattern.fixedPosition) {
		
		
		for (int i = 0; i<triggerPattern.triggers.size(); i++) {
			
			TriggerBase* trigger = triggerPattern.triggers[i];
			
			float yvar = triggerPattern.verticalVariations[triggerIndex];
			float ypos = triggerPattern.verticalPositions[triggerIndex] + ofRandom(-yvar, yvar);
			ypos *= triggerArea.height/2;
			
			if(!trigger->fixedPosition) trigger->pos.x = xPos + triggerArea.x;
			trigger->pos.y = ypos + triggerArea.getCenter().y;
			
			xPos += 50;			
			
			if(triggers.size()<=i)
				triggers.push_back(trigger);
			
			//if(active)
			trigger->start();
			
			trigger->disabled = triggersDisabled;
			trigger->showDebugData = triggerDebug;
			
			triggerCount++;
		}
		
		
		
		
		
	} else 
	*/	
	float spacing = triggerArea.width / floor(triggerArea.width / minimumSpacing);
	int numOfTriggers =  floor(triggerArea.width / minimumSpacing);
	while (triggerCount<=numOfTriggers ) { //(triggerArea.width/2)-minimumSpacing/2) {
		/*
		TriggerBase* triggerLeft;
		TriggerBase* triggerRight;
	
		if(triggersLeft.size()>triggerCount) {
			triggerLeft = triggersLeft[triggerCount];
			triggerRight = triggersRight[triggerCount];
	
		} else {
			triggerLeft = triggerPattern.triggers[triggerIndex]->clone();
			triggerRight = triggerPattern.triggers[triggerIndex]->clone();
			
			triggersLeft.push_back(triggerLeft);
			triggersRight.push_back(triggerRight);
			triggers.push_back(triggerLeft);
			triggers.push_back(triggerRight);
	
			
		}*/
		
		
		//float yvar = triggerPattern.verticalVariations[triggerIndex];
		//float ypos = triggerPattern.verticalPositions[triggerIndex] + ofRandom(-yvar, yvar);
		//ypos *= triggerArea.height/2;
		
		Trigger * trigger;
		
		if(triggers.size()>triggerCount) {
			trigger = triggers.at(triggerCount);
			
		} else {
			trigger = new Trigger();
			triggers.push_back(trigger);
			

		}
		
		trigger->copySettings(triggerPattern.triggers[triggerIndex]);
		
		//cout << triggerCount << " " << triggerIndex << " " << trigger->hue << endl;
		
		triggerIndex++;
		if(triggerIndex>=triggerPattern.triggers.size()) triggerIndex = 0;

		
		trigger->start();
		
		trigger->disabled = triggersDisabled;
		trigger->showDebugData = triggerDebug;
		
		
		
		trigger->pos.y = triggerArea.getCenter().y; //ypos +
		trigger->pos.x = xPos;
		//triggerRight->pos = triggerLeft->pos;
		
		//cout << triggerCount << " " << trigger->pos << endl;
				
		//lastSpacing = (minimumSpacing * triggerPattern.horizSpacings[triggerIndex]);
		
		xPos+=spacing;
		
		triggerCount++;
		
		
	}
	
	
	// times by two to get both sets
	//triggerCount *=2;
	// and subtract one to get rid of double in middle
	triggerCount--;
	
	for(int i = triggerCount+1; i<triggers.size(); i++) {
		triggers[i]->active = false;
		
	}
	
	/*
	float spacing = (triggerArea.width/2) / (xPos- (lastSpacing*0.5)) ;
	//cout << "spacing " << spacing << endl;
	//cout << triggerCount << endl;
	
	
	for(int i = 0; i<triggers.size(); i+=2) {
		
		//cout << i <<  " trigger ";
		
		triggers[i]->pos.x *=spacing;
		triggers[i+1]->pos.x = (triggerArea.x + triggerArea.width) - triggers[i]->pos.x;
		triggers[i]->pos.x+=triggerArea.x;
		
		// disable spares!
		if(i>=triggerCount)
			triggers[i]->stop();
		else {
			//if(active)
				triggers[i]->start();
			triggers[i]->disabled = triggersDisabled;
			triggers[i]->showDebugData = triggerDebug;
		}
		
		if(i+1>=triggerCount)
			triggers[i+1]->stop();
		else {
			//if(active)
				triggers[i+1]->start();
			triggers[i+1]->disabled = triggersDisabled;
			triggers[i+1]->showDebugData = triggerDebug;
		}
		
	}
	

	 */
	
	
	
}


void TriggerManager :: mouseMoved(int x, int y){

	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		float distance = trigger->pos.distance(ofVec3f(x,y));
		if(distance<100) {
			trigger->registerMotion(1.0f-(distance/100.0f));

		}

	}

}
