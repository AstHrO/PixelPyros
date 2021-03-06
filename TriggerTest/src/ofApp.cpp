

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_WARNING);
	useFbo = true;
	spanAll = true;
    fboWarper1.label = "leftScreen";
	fboWarper2.label = "rightScreen";
	
	//triggerArea.set(APP_WIDTH*0.15,APP_HEIGHT*0.85,APP_WIDTH*0.7,APP_HEIGHT*0.5);
    
	fboWarper1.setDstPoint(0, ofVec2f(0,0));
	fboWarper1.setDstPoint(1, ofVec2f(APP_WIDTH/2,0));
	fboWarper1.setDstPoint(2, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
	fboWarper1.setDstPoint(3, ofVec2f(0,APP_HEIGHT));
	fboWarper1.setSrcPoint(0, ofVec2f(0,0));
	fboWarper1.setSrcPoint(1, ofVec2f(APP_WIDTH/2,0));
	fboWarper1.setSrcPoint(2, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
	fboWarper1.setSrcPoint(3, ofVec2f(0,APP_HEIGHT));
	fboWarper1.boundsRectangle.set(0,0,APP_WIDTH/2, APP_HEIGHT);
	fboWarper1.useBoundsRect = true;
	
	
	fboWarper2.setDstPoint(0, ofVec2f(APP_WIDTH/2 +1,0));
	fboWarper2.setDstPoint(1, ofVec2f(APP_WIDTH,0));
	fboWarper2.setDstPoint(2, ofVec2f(APP_WIDTH,APP_HEIGHT));
	fboWarper2.setDstPoint(3, ofVec2f(APP_WIDTH/2 +1,APP_HEIGHT));
	fboWarper2.setSrcPoint(0, ofVec2f(APP_WIDTH/2,0));
	fboWarper2.setSrcPoint(1, ofVec2f(APP_WIDTH,0));
	fboWarper2.setSrcPoint(2, ofVec2f(APP_WIDTH,APP_HEIGHT));
	fboWarper2.setSrcPoint(3, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
	fboWarper2.boundsRectangle.set(APP_WIDTH/2,0,APP_WIDTH/2, APP_HEIGHT);
	fboWarper2.useBoundsRect = true;
	
  
	fboWarper1.loadSettings();
	fboWarper2.loadSettings();
	
	initSounds();
	
    paused = false;
	triggerShowDebug = false;
	triggersDisabled = false;
    
    drawCameraIntoFBO = true;
    
	renderer.load("shaders/default");
    
	lastUpdateTime = ofGetElapsedTimef();
  
    ofBackground(0);

	
	cameraManager.init();
	//cameraManager.addVidPlayer("../../../TestMovies/TestPyrosCamCropped.mov");
	cameraManager.addVidPlayer("../../../TestMovies/NottinghamTestFootage2.mov", 1280,720);

    //motionManager.init(cameraManager.getWidth(), cameraManager.getHeight());
	motionManager.init(1024, 768);

	fbo.allocate(APP_WIDTH, APP_HEIGHT, GL_RGBA, 4); 
	controlPanels.main = fbo;
	fbo.begin();
	ofClear(0,0,0);
	fbo.end();

    paused = false;
    altPressed = false;
	shiftPressed = false;
	
	setupScenes();
	

    triggerManager.setDisplaySize(APP_WIDTH, APP_HEIGHT);
	
	appParams.setName("App Settings");
    
	appParams.add(timeSpeed.set("time speed", 1, 0,2));
	// these should be loaded and saved, but not time speed
	appParams.add(edgeBlendSize.set("edge blend size", 0, 0, 50));
	
	appParams.add(sceneInterstitial->foreground.set("interstitial foreground", 200,0,255));
	appParams.add(sceneInterstitial->background.set("interstitial background", 40,0,255));
	
	appParams.add(sceneManager.musicVolume);
	appParams.add(soundPlayer.globalVolume);
	

	
	motionManager.parameters.add(cameraPreviewBrightness.set("camera preview brightness", 255,0,255));
	
	
	parameterManager.registerParameterGroup("app", &appParams );
    parameterManager.registerParameterGroup("renderer", &renderer.paramters );
    parameterManager.registerParameterGroup("triggers", &triggerManager.parameters);
    parameterManager.registerParameterGroup("motion", &motionManager.parameters);
    parameterManager.registerParameterGroup("particles", &particleSystemManager.parameters);
    parameterManager.registerParameterGroup("camera", &cameraManager.parameters );
       
    // Now that all of the parameters should be registered with the
	// ParameterManager, setup the control gui
    
	//calculateScreenSizes();
	controlPanels.setup( &parameterManager);
	timeSpeed = 1;
	
	updateScreenSizes();
	
    oscParams = new ofParameterGroup();
    oscParams->setName("OSC");
    oscParams->add( controlPanels.appGui.getParameter() );
    oscParams->add( controlPanels.triggerGui.getParameter() );
    oscParams->add( controlPanels.motionGui.getParameter() );
    oscParams->add( controlPanels.laserGui.getParameter() );
    oscParams->add( controlPanels.rendererGui.getParameter());

    sync.setup(*oscParams, 6667, "10.0.1.51", 8000);
    //sync.setup(*oscParams, 6667, "192.168.43.32", 8000);
}

//--------------------------------------------------------------f
void ofApp::update(){

		
	if(cameraManager.update()){
		
		ofImage image(cameraManager.getPixelsRef()); 

		motionManager.update(cameraManager.getPixelsRef(), cameraManager.getCameraLabel());
		
		triggerManager.updateMotion(motionManager, cameraManager.warper.inverseHomography );
	
	}
	
	
	
	float time = ofGetElapsedTimef(); 
	deltaTime =  time - lastUpdateTime;
	
	if(deltaTime>0.1) deltaTime = 0.1;
	
	deltaTime*=timeSpeed;
	
	lastUpdateTime = time;
	
	
	if ( triggersDisabled != triggerManager.triggersDisabled ) {
		triggerManager.setTriggersDisabled(triggersDisabled) ;
		
	}
	
    if( !paused ) {
		
		triggerManager.update(deltaTime);
	    sceneManager.update(deltaTime);
        particleSystemManager.update(deltaTime);
    }
		
    sync.update();
    
//	ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
//	if(uiScreenRect.inside(mousePos)) {
//		ofShowCursor();
//	} else {
//		ofHideCursor();
//	}
//	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	
	ofSetColor(cameraPreviewBrightness);
	if(!drawCameraIntoFBO) {
		cameraManager.draw();
	}
	
	
	if(useFbo) {
		fbo.begin();
		ofClear(0);
	}
	
	if(drawCameraIntoFBO)
		cameraManager.draw();
	
	ofSetColor(255);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	particleSystemManager.draw();
	
	sceneManager.draw();

	triggerManager.draw();
	
	if(useFbo) {
		fbo.end();
        
			
		renderer.draw(fbo, fboWarper1, fboWarper2, edgeBlendSize);
	}
	
	ofDisableBlendMode();
	ofDisableAlphaBlending();
	
	// draw the warper UIs if necessary
	fboWarper1.draw();
	fboWarper2.draw();
	

	
	ofPushStyle();
	float d = ofGetLastFrameTime();
	
	if(d<1.0/50.0)
		ofSetColor(ofColor::black);
	else if(d<1.0/40.0)
		ofSetColor(ofColor::green);
	else if(d<1.0/30.0)
		ofSetColor(ofColor::yellow);
	else if(d<1.0/20.0)
		ofSetColor(ofColor::orange);
	else 
		ofSetColor(ofColor::red);
	if(d>1.0/30.0)
		ofRect(uiScreenRect.x, uiScreenRect.y, (d-(1.0/30.0))*4000,4);
	ofPopStyle();
	ofDrawBitmapString(ofToString(ofGetFrameRate()),uiScreenRect.x+8,uiScreenRect.y+14);

	
	ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
	float modval = 0.3;
	if(!uiScreenRect.inside(mousePos) && (modff((float)ofGetElapsedTimef(), &modval) > 0.2)) {
		ofDrawBitmapString("CHECK MOUSE CURSOR",uiScreenRect.x+8,uiScreenRect.y+34);
	}
	
	ofPushMatrix();
	ofTranslate(uiScreenRect.x+8, uiScreenRect.y+54);
	
	ofDrawBitmapString("Current Scene       : "+sceneManager.getCurrentSceneName(),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("Current Arrangement : "+sceneManager.getCurrentTriggerPatternName(),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("particle systems : "+ofToString(particleSystemManager.particleSystems.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare part sys     : "+ofToString(particleSystemManager.spareParticleSystems.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("active part sys    : "+ofToString(particleSystemManager.activeParticleSystemCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("particles          : "+ofToString(particleSystemManager.allParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare particles    : "+ofToString(particleSystemManager.spareParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("active particles   : "+ofToString(particleSystemManager.activeParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("physics objects    : "+ofToString(particleSystemManager.physicsObjects.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare physics objs : " +ofToString(particleSystemManager.sparePhysicsObjects.size()),0,0);

	ofTranslate(0,20);
	ofDrawBitmapString("active physics objs: " +ofToString(particleSystemManager.activePhysicsObjectCount),0,0);

	ofPopMatrix();
	
    controlPanels.draw(motionManager, cameraManager);
	sceneManager.drawGUI();
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	//bool shiftPressed = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	if(key == OF_KEY_SHIFT) {
        shiftPressed = true;
    }

	cout << "SHIFT PRESSED : "<< shiftPressed << endl;
	if(key == OF_KEY_ALT){
        altPressed = true;
    }

   // if( shiftPressed ) {
        if(key=='w') {
            cameraManager.toggleWarperGui();
        }else if(key=='e') {
            drawCameraIntoFBO = !drawCameraIntoFBO;
        } else if ((shiftPressed) && (key=='1')) {
			cout << "SHIFT 1" << endl;
			
            fboWarper1.visible = !fboWarper1.visible;
			cout << "FBO WARPER VISIBLE " << fboWarper1.visible << endl;
        } else if ((shiftPressed) && (key=='2')) {
            fboWarper2.visible = !fboWarper2.visible;
        }

        //if(!cameraManager.warper.guiVisible) {

        if(key==OF_KEY_LEFT) {
            if(altPressed)
                sceneManager.prevScene();
            else
                sceneManager.previousPattern();
        } else if(key==OF_KEY_RIGHT) {
            if(altPressed)
                sceneManager.nextScene();
            else
                sceneManager.nextPattern();
        }

        //}
        if(key=='c') {
            cameraManager.next();
        } else if( key == 'R' ) {
            if(!cameraManager.capturing)
                cameraManager.beginCapture();
            else
                cameraManager.endCapture();
            
        } else if( key == 'P' ) {
            paused = !paused;
        }
        else if ( key == 't' )
        {
            triggersDisabled = !triggersDisabled ;
        }
        else if ( key == 'd' )
        {
            triggerManager.toggleDebug();//triggerShowDebug = !triggerShowDebug ;
        }
        else if ( key == 'k' )
        {
			particleSystemManager.killAllParticles();
			sceneGame->killInvadersAndAsteroids();
        }
        else if ( key == 'q' ){
            sceneManager.changeScene("SlideShow");
        }
        else if ( key == 's' ){
            sync.parameterChanged(*oscParams);
        }
        else if(key == 'F') {
			ofToggleFullscreen();
			updateScreenSizes();
		} else if(key == 'f') {
			spanAll = !spanAll;
			int monitorCount;
			glfwGetMonitors(&monitorCount);
			ofGetWindowPtr()->setMonitorSpan(spanAll?monitorCount:monitorCount-1);
    
			updateScreenSizes();
		}
   // }
    
    controlPanels.keyPressed(key);
	
	
}

void ofApp::keyReleased(int key){
	if(key == OF_KEY_SHIFT) shiftPressed = false;
	if(key == OF_KEY_ALT) altPressed = false;
}

void ofApp:: mousePressed(int x, int y, int button ) { 

}

void ofApp:: setupScenes() { 
	
	
	TriggerRechargeSettings::superFastMultiples->minTriggerInterval = 0.1;
	TriggerRechargeSettings::fastMultiples->triggerPower = 0.3;
	
	TriggerRechargeSettings::mediumMultiples->minTriggerInterval = 0.2;
	TriggerRechargeSettings::mediumMultiples->triggerPower = 0.3;
	TriggerRechargeSettings::mediumMultiples->restoreSpeed = 0.5;
	
	TriggerRechargeSettings::fastMultiples->minTriggerInterval = 0.1;
	TriggerRechargeSettings::fastMultiples->triggerPower = 0.3;
	TriggerRechargeSettings::fastMultiples->restoreSpeed = 0.7;
	
	sceneManager.addScene(new SceneCalibration("Calibration"));
	sceneManager.addScene(sceneInterstitial = new SceneSlideshow("SlideShow"));
	sceneManager.addScene(new SceneIntro("Intro"));
	
	
	
}

void ofApp::initSounds() {
	soundPlayer.setScreenRect(ofRectangle(0,0,APP_WIDTH, APP_HEIGHT));
	
	soundPlayer.defaultPath = "../../../Sounds/";
	
	
	soundPlayer.globalVolume = 1;
	
}



void ofApp::mouseMoved( int x, int y ){
	
	triggerManager.mouseMoved(x, y, previewRect);

}

void ofApp::calculateScreenSizes(){
    int monitorCount;
	
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	
	//cout << "RESIZE" << " " << ofGetWindowMode()<< endl;
    screens.clear();
    
    int leftMost = 0,
		topMost = 0;
    
    for(int i = 0; i < monitorCount; i++){
		
		ofRectangle screen;
		
		int x=0,
		y=0,
		w=0,
		h=0;
		
        glfwGetMonitorPos(monitors[i],&x,&y);
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[i]);
		screen.x = x;
		screen.y = y;
        screen.width = desktopMode->width;
        screen.height = desktopMode->height;
        
        screens.push_back(screen);
        //cout << i << " " << screen << endl;
		if( leftMost > screen.x ) leftMost = screen.x;
		if( topMost > screen.y ) topMost = screen.y;

    }
    
    for(int i = 0; i < monitorCount; i++){
		screens[i].x -= leftMost;
		screens[i].y -= topMost;

    }
    
	std::sort( screens.begin(), screens.end(), screenSort );
	/*
    for(int i = 0; i < monitorCount; i++){
		cout << i << " " << screens[i] << endl;
    }*/
    
	uiScreenRect = screens.back();
		

}

void ofApp::updateScreenSizes() {
	
//	ofToggleFullscreen();
	//cout << ofGetWindowMode()<< endl;
	
    calculateScreenSizes();

	controlPanels.updatePositions(screens);
	sceneManager.updateUIScreen(uiScreenRect);
	
	

}
//--------------------------------------------------------------
void ofApp::windowResized(int width, int height){
	
	updateScreenSizes();
	
}


void ofApp::exit() { 
    controlPanels.exit();
    sceneManager.exit();
}
