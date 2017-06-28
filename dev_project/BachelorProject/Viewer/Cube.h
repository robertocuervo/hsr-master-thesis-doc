#pragma once
#ifndef CUBE_H
#define CUBE_H
#include <glew/glew.h>
#include <gl/GL.h>
#include "IDisplayable.h"
#include "UIController.h"


class Cube: public IDisplayable {
public:
	Cube();

	void setUp();
	void render(UIController* uiController) override;
	void update(UIController* uiController) override;

private:
	GLuint cubeVAO, cubeVBO;
	bool isDisplayable;
	GLfloat cubeVertices[108] = {
		-163.84f, -163.84f, -163.84f,
		163.84f, -163.84f, -163.84f,
		163.84f, 163.84f, -163.84f,
		163.84f, 163.84f, -163.84f,
		-163.84f, 163.84f, -163.84f,
		-163.84f, -163.84f, -163.84f,

		-163.84f, -163.84f, 163.84f,
		163.84f, -163.84f, 163.84f,
		163.84f, 163.84f, 163.84f,
		163.84f, 163.84f, 163.84f,
		-163.84f, 163.84f, 163.84f,
		-163.84f, -163.84f, 163.84f,

		-163.84f, 163.84f, 163.84f,
		-163.84f, 163.84f, -163.84f,
		-163.84f, -163.84f, -163.84f,
		-163.84f, -163.84f, -163.84f,
		-163.84f, -163.84f, 163.84f,
		-163.84f, 163.84f, 163.84f,

		163.84f, 163.84f, 163.84f,
		163.84f, 163.84f, -163.84f,
		163.84f, -163.84f, -163.84f,
		163.84f, -163.84f, -163.84f,
		163.84f, -163.84f, 163.84f,
		163.84f, 163.84f, 163.84f,

		-163.84f, -163.84f, -163.84f,
		163.84f, -163.84f, -163.84f,
		163.84f, -163.84f, 163.84f,
		163.84f, -163.84f, 163.84f,
		-163.84f, -163.84f, 163.84f,
		-163.84f, -163.84f, -163.84f,

		-163.84f, 163.84f, -163.84f,
		163.84f, 163.84f, -163.84f,
		163.84f, 163.84f, 163.84f,
		163.84f, 163.84f, 163.84f,
		-163.84f, 163.84f, 163.84f,
		-163.84f, 163.84f, -163.84f,
		};

	void drawCube() const;
};

#endif
