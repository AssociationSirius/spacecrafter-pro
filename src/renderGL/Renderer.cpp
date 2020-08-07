#include "renderGL/Renderer.hpp"
#include "renderGL/shader.hpp"
#include "renderGL/OpenGL.hpp"


void Renderer::clearColor()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::clearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}


void Renderer::clearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawArrays(shaderProgram* shader, VertexArray* va, GLenum mode, unsigned int first, unsigned int count )
{
    shader->use();
	va->bind();
	glDrawArrays(mode, first, count);
	va->unBind();
	shader->unuse();
}

void Renderer::drawArraysWithoutShader(VertexArray* va, GLenum mode, unsigned int first, unsigned int count )
{
	va->bind();
	glDrawArrays(mode, first, count);
	va->unBind();
}

void Renderer::viewport(int x, int y, int w, int h)
{
	glViewport(x,y,w,h);
}


void Renderer::drawMultiArrays(shaderProgram* shader, VertexArray* va, GLenum mode, unsigned int boucle, unsigned int count )
{
    shader->use();
	va->bind();
	// glDrawArrays(mode, boucle, count);
	for (unsigned int y=0; y<boucle; y++) {
		glDrawArrays(GL_TRIANGLE_STRIP,y*count , count);
	}
	va->unBind();
	shader->unuse();
}


void Renderer::drawElementsWithoutShader(VertexArray* va, GLenum mode)
{
	va->bind();
	glDrawElements(mode, va->getIndiceCount(), GL_UNSIGNED_INT, (void*)0 );
    va->unBind();
}