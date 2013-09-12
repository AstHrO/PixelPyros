//
//  Pattern.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 20/08/2012.
//
//

#pragma once

#include "Trigger.h"
#include "TriggerSettings.h"
#include "TriggerSettingsRocket.h"

class TriggerPattern  {

	
	public :
	
	TriggerPattern(){
		
	};
	
	TriggerPattern(TriggerSettings* trigger){
		addTriggerSettings(trigger);

	};
	
	TriggerPattern(vector<TriggerSettings*> triggers){
		for(int i = 0; i<triggers.size(); i++) {
			addTriggerSettings(triggers[i]);
		}
		
	};
	
	
	//template <typename T>
	void addTriggerSettings(TriggerSettings* trigger = TriggerSettings::blank){

		triggers.push_back(trigger);
	}
	
	TriggerSettingsRocket* addRocketTrigger(RocketSettings* rocketSettings) {
		
		TriggerSettingsRocket* ts = new TriggerSettingsRocket();
		// TODO - THIS IS BAD - should store these pointers somewhere and clear
		// them later.
		
		//TriggerableRocket* tr = new TriggerableRocket();
		ts->rocketSettings = rocketSettings;
		
		addTriggerSettings(ts);
		
		return ts;
	}

	vector <TriggerSettings*> triggers;
	
	// TODO ADDITIONAL STUFF THAT TRIGGER PATTERN NEEDS
	// Mirrored - on by default - what else? specific positions? 
	// auto-rotate - triggers should rotate to give everyone a try
	
	// probably don't need this in future, just helps me test.
	//TriggerableBase defaultTriggerable;

};
