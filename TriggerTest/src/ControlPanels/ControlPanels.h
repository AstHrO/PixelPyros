//
//  ControlPanels.h
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#pragma once

#include <iostream>
#include "ParameterManager.h"
#include "ofxPanel.h"
#include "ofxToggle.h"
#include "ofxSliderGroup.h"
#include "QuadWarp.h"
#include "LaserManager.h"
#include "MotionManager.h"
#include "CameraManagerWarped.h"

class ControlPanels {
    
    public:
    
    ControlPanels():parameterManager(*ParameterManager::instance()){};
    void setup(ParameterManager * parameterManager); 
	void updatePositions(vector<ofRectangle> screens); 
    void draw(MotionManager& motionManager, CameraManagerWarped& cameraManager);
    void drawPreviewScreen(MotionManager& motionManager, CameraManagerWarped& cameraManager);
    void exit();
    void keyPressed(int key);
    void mouseMoved(int x, int y);
	ofRectangle getPreviewScreenRect();
	
    ofFbo main;
    ofFbo camera;
    ofFbo motion;
    
    //QuadWarp * laserWarp;
    
	
	int panelMode;
	int PANEL_MODE_NONE = 0;
	int PANEL_MODE_APP = 1;
	int PANEL_MODE_MOTION = 2;
	int PANEL_MODE_LASER = 3;

    ofxPanel appGui;
    ofxPanel cameraCalibration;
    ofxPanel laserGui;
    ofxPanel rendererGui;
    ofxPanel triggerGui;
    ofxPanel motionGui;
	ofxPanel cameraGui;
	
    protected:

    void setupPanel( string name, ofRectangle rect, ofxPanel & panel );
    void setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel );
   // void layoutPanels(vector<ofxPanel> panels,ofRectangle space );
   // vector<ofxPanel> getVisiblePanels();
	void updatePreviewScreenSize();
   
    ParameterManager& parameterManager;
    
    //ofxPanel laserCalibration;
    //ofxPanel projectorCalibration;
	
	
	vector<ofxPanel*> panels; 
    
    ofRectangle previewScreenRect;
    ofRectangle screen;
	
    ofVec2f padding;
    
    
    int monitorCount;
    
    
};