/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2018 of Association Sirius
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Spacecrafter is a free open project of the LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <GL/glew.h>

#include "appModule/appDraw.hpp"
#include "tools/log.hpp"
#include "tools/s_texture.hpp"
#include "tools/utility.hpp"
#include "tools/app_settings.hpp"
#include "tools/OpenGL.hpp"

AppDraw::AppDraw()
{}


AppDraw::~AppDraw()
{
	this->deleteShader();
}

void AppDraw::init(unsigned int _width, unsigned int _height)
{
    width=_width;
    height=_height;
}

void AppDraw::initSplash()
{
	shaderProgram *shaderSplash;
	shaderSplash = new shaderProgram();
	shaderSplash->init( "splash.vert", "splash.frag");

	float dataPos[]= {-1.0,-1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
	float dataTex[]= {0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 };

	VertexArray* splash = new VertexArray();
	splash->registerVertexBuffer(BufferType::POS2D, BufferAccess::STATIC);
	splash->registerVertexBuffer(BufferType::TEXTURE, BufferAccess::STATIC);
	splash->fillVertexBuffer(BufferType::POS2D, 8, dataPos);
	splash->fillVertexBuffer(BufferType::TEXTURE, 8, dataTex);

	int tmp=std::min(width, height);
	glViewport((width-tmp)/2, (height-tmp)/2, tmp, tmp);

	s_texture* tex_splash = new s_texture(AppSettings::Instance()->getUserDir()+"textures/splash/spacecrafter.png" , TEX_LOAD_TYPE_PNG_ALPHA);

	StateGL::disable(GL_BLEND);
	StateGL::BlendFunc(GL_ONE, GL_ONE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_splash->getID());

	shaderSplash->use();
	splash->bind();
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	splash->unBind();
	shaderSplash->unuse();

	if (shaderSplash) delete shaderSplash;
	if (splash) delete splash;
	if (tex_splash) delete tex_splash;
}


void AppDraw::createShader()
{
	shaderViewportShape =  nullptr;
	shaderViewportShape= new shaderProgram();
	shaderViewportShape->init( "viewportShape.vert", "viewportShape.frag");
	shaderViewportShape->setUniformLocation("radius");
	shaderViewportShape->setUniformLocation("decalage_x");
	shaderViewportShape->setUniformLocation("decalage_y");

	shaderColorInverse =  nullptr;
	shaderColorInverse = new shaderProgram();
	shaderColorInverse->init( "colorInverse.vert", "colorInverse.frag");

	float viewportShapePoints[8];

	viewportShapePoints[0]= -1.0; // point en haut a gauche
	viewportShapePoints[1]= 1.0;

	viewportShapePoints[2]= 1.0;  // point en haut a droite
	viewportShapePoints[3]= 1.0;

	viewportShapePoints[4]= -1.0; // point en bas à gauche
	viewportShapePoints[5]= -1.0;

	viewportShapePoints[6]= 1.0;  // point en bas à droite
	viewportShapePoints[7]= -1.0;

	m_viewportGL = std::make_unique<VertexArray>();
	m_viewportGL->registerVertexBuffer(BufferType::POS2D, BufferAccess::STATIC);
	m_viewportGL->fillVertexBuffer(BufferType::POS2D, 8, viewportShapePoints);
	// glGenBuffers(1,&dataGL.pos);
	// glBindBuffer(GL_ARRAY_BUFFER,dataGL.pos);
	// glBufferData(GL_ARRAY_BUFFER,sizeof(float)*8, viewportShapePoints,GL_STATIC_DRAW);

	// glGenVertexArrays(1,&dataGL.vao);
	// glBindVertexArray(dataGL.vao);

	// glBindBuffer (GL_ARRAY_BUFFER, dataGL.pos);
	// glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);

	// glEnableVertexAttribArray(0);
}

void AppDraw::deleteShader()
{
	if (shaderViewportShape) 
		delete shaderViewportShape;
	if (shaderColorInverse)
		delete shaderColorInverse;

	// glDeleteBuffers(1, &layer.pos);
	// glDeleteVertexArrays(1, &layer.vao);
	// glDeleteBuffers(1, &dataGL.pos);
	// glDeleteVertexArrays(1, &dataGL.vao);
}

//! dessine la première couche du tracé opengl sur le logiciel
void AppDraw::drawFirstLayer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

//! Fill with black around the circle
void AppDraw::drawViewportShape()
{
	StateGL::disable(GL_BLEND);
	StateGL::BlendFunc(GL_ONE, GL_ONE);

	shaderViewportShape->use();
	shaderViewportShape->setUniform("radius" , std::min(width, height)/2);
	shaderViewportShape->setUniform("decalage_x" , (width -std::min(width, height))/2);
	shaderViewportShape->setUniform("decalage_y" , (height -std::min(width, height))/2);


	//glBindVertexArray(dataGL.vao);
	m_viewportGL->bind();
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	m_viewportGL->unBind();
	//glBindVertexArray(0);
	shaderViewportShape->unuse();
}

void AppDraw::drawColorInverse()
{
	StateGL::enable(GL_BLEND);
	StateGL::BlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	shaderColorInverse->use();

	m_viewportGL->bind();
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	m_viewportGL->unBind();
	shaderColorInverse->unuse();
}