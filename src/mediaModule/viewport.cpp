/*
* This source is the property of Immersive Adventure
* http://immersiveadventure.net/
*
* It has been developped by part of the LSS Team.
* For further informations, contact:
*
* albertpla@immersiveadventure.net
*
* This source code mustn't be copied or redistributed
* without the authorization of Immersive Adventure
* (c) 2017 - all rights reserved
*
*/


#include "mediaModule/viewport.hpp"

ViewPort::ViewPort()
{
	isAlive = false;
	transparency = false;
	fader = false;
	fader.setDuration(VP_FADER_DURATION);
}

ViewPort::~ViewPort()
{
	deleteShader();

}

void ViewPort::createShader()
{
	shaderViewPort = nullptr;
	shaderViewPort= new shaderProgram();
	shaderViewPort->init("videoplayer.vert","videoplayer.frag");
	shaderViewPort->setUniformLocation("transparency");
	shaderViewPort->setUniformLocation("noColor");
	shaderViewPort->setUniformLocation("fader");

	initParam();
}

void ViewPort::initParam()
{
	// FullScreen mode
	float viewportPoints[8] = {-1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
	float viewportTex[8] =    { 0.0,  1.0, 1.0,  1.0,  0.0, 0.0, 1.0, 0.0};

	glGenBuffers(1,&viewport.pos);
	glBindBuffer(GL_ARRAY_BUFFER,viewport.pos);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*8, viewportPoints,GL_STATIC_DRAW);

	glGenBuffers(1,&viewport.tex);
	glBindBuffer(GL_ARRAY_BUFFER,viewport.tex);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*8,viewportTex,GL_STATIC_DRAW);

	glGenVertexArrays(1,&viewport.vao);
	glBindVertexArray(viewport.vao);

	glBindBuffer (GL_ARRAY_BUFFER, viewport.pos);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer (GL_ARRAY_BUFFER, viewport.tex);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(1);

	// Dual Half Screen mode
	float halfPoints[16] = {-1.0, -1.0, 1.0, -1.0,
							-1.f, 0.f, 1.f, 0.f,
							-1.f, 0.f, 1.f, 0.f,
							-1.0, 1.0, 1.0, 1.0};
	float halfTex[16] =    { 0.0,  0.5, 1.0,  0.5, 
							0.f, 0.0f, 1.0f, 0.0f,

							1.f, 0.0f, 0.0f, 0.0f,
							1.0, 0.5, 0.0, 0.5};

	glGenBuffers(1,&dual.pos);
	glBindBuffer(GL_ARRAY_BUFFER,dual.pos);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16, halfPoints,GL_STATIC_DRAW);

	glGenBuffers(1,&dual.tex);
	glBindBuffer(GL_ARRAY_BUFFER,dual.tex);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,halfTex,GL_STATIC_DRAW);

	glGenVertexArrays(1,&dual.vao);
	glBindVertexArray(dual.vao);

	glBindBuffer (GL_ARRAY_BUFFER, dual.pos);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer (GL_ARRAY_BUFFER, dual.tex);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(1);	
}

void ViewPort::deleteShader()
{
	if(shaderViewPort) shaderViewPort=nullptr;

	glDeleteBuffers(1,&viewport.vao);
	glDeleteBuffers(1,&viewport.tex);
	glDeleteVertexArrays(1,&viewport.pos);

	glDeleteBuffers(1,&dual.vao);
	glDeleteBuffers(1,&dual.tex);
	glDeleteVertexArrays(1,&dual.pos);
}

void ViewPort::draw()
{
	if (! isAlive)
		return;
	StateGL::enable(GL_BLEND);
	StateGL::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaderViewPort->use();

	for(int i=0; i<3; i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, videoTex[i]);
	}
	shaderViewPort->setUniform("transparency",transparency);
	shaderViewPort->setUniform("noColor",noColor);
	shaderViewPort->setUniform("fader", fader.getInterstate() );

	if (fullScreen) {
		glBindVertexArray(viewport.vao);
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	} else {
		glBindVertexArray(dual.vao);
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		glDrawArrays(GL_TRIANGLE_STRIP,4,4);
	}
	StateGL::disable(GL_BLEND);
	shaderViewPort->unuse();
}
