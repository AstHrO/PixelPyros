//
//  ParticleRendererSquare.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once

#include "ofMain.h"

class ParticleRendererStar : public ParticleRendererBase {
	
public:
	
	ParticleRendererStar(float len=50, float ang=45) : ParticleRendererBase(){
		length = len;
		angle = ang;
		
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
	}
	
	virtual void renderParticles(vector <Particle * > particles){
        //cout << "STAR RENDERER"<< endl;
        // BASIC TRIANGLE RENDERER
		//		ofDisableSmoothing();
		
		
		//ofMatrix4x4 mat;
		
		mesh.clear();
		
		for(std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
			
			Particle& p = **it; // *(particles[i]);
			if((!p.enabled) || (p.size<0.1)) continue;
			
			int vertexIndex = mesh.getNumVertices();
			
			
			ofVec3f p1(0,-1), p2(MIN(p.size*20,length),0), p3(0,1);
			ofVec3f scalar(1,p.size);
			p1 *= scalar;
			p2 *= scalar;
			p3 *= scalar;
			
			p1.rotate(0,0,angle);
			p2.rotate(0,0,angle);
			p3.rotate(0,0,angle);

			
			for(int i = 0; i<4; i++) {
			
				mesh.addVertex(p1+p.pos);
			
				mesh.addVertex(p2+p.pos);
			
				mesh.addVertex(p3+p.pos);
				mesh.addColor(p.getColour());
				mesh.addColor(p.getColour());
				mesh.addColor(p.getColour());
				
				p1.rotate(0,0,90);
				p2.rotate(0,0,90);
				p3.rotate(0,0,90);
				
			
				
			}
			
			
			
		}
		
		mesh.draw();
			
		
        
    }
	
	ofMesh mesh;
	
	
	float length;
	float angle;
	
	
	
	
};