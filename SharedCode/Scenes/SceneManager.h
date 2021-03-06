

#pragma once 

#include "Scene.h"
#include "ParticleSystemManager.h"
#include "TriggerManager.h"

class SceneManager {

public :
	
	SceneManager();
	
	void addScene(Scene * scene);
    
	bool changeScene(int sceneIndex);
	bool changeScene(Scene * scene);
	bool changeScene(string scenename);
	bool nextScene();
	bool prevScene();
	
	bool update(float deltaTime);
	void draw();
	void drawGUI(); 
    void exit();
	
	bool nextPattern();
	bool previousPattern();
	bool changeTriggerPattern(int patternNum);
	
	bool togglePlayPause();
	bool toggleShowInterface();
	bool toggleRecord();
	
	bool autoSave();
	bool checkAutoSave();
    void resumeAutoSave();
	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);
	
	void updateUIScreen(ofRectangle screen);
	
	float getPositionForTime(float time);
	float getTimeForPosition(float position);
	int getCommandIndexAtPosition(ofPoint pos);
	ofRectangle getRectangleForCommand(SequenceCommand& command);
	ofRectangle getRectangleForCommand(int i);
	
	string getCurrentSceneName();
	string getCurrentTriggerPatternName();

	ofRectangle screenUI;

	vector <Scene*> scenes;
	
	int currentSceneIndex;
	Scene * currentScene;
	string currentSceneName;
	string currentSceneArrangement;

	bool nextFlag;
	bool previousFlag; 
	bool nextPatternFlag;
	bool previousPatternFlag;
		
	ParticleSystemManager & particleSystemManager;
	TriggerManager & triggerManager;
	
	ofParameter<float> musicVolume;
	ofParameter<bool> autoPlayNext;
	
	ofParameter<bool> ambientMode; 
	ofParameterGroup parameters;
	
    ofxXmlSettings autoSaveXml;
	
	bool showInterface;
	
	bool shiftPressed;
	bool altPressed;
	
	bool dragPlayHead;
	int dragCommandIndex;
	int mouseOverCommandIndex; 
	ofPoint dragClickOffset;
	
	float lastAutoSave = 0;
	
	
	ofRectangle playHeadRect;
	// time bar is the track along the bottom
	ofRectangle timeBarRect;

	
	
    
};