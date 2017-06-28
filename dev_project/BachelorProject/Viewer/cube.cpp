#include "cube.h"

Cube::Cube(): cubeVAO(0), cubeVBO(0), isDisplayable(true) {}

void Cube::setUp() {
	glGenVertexArrays(1, &this->cubeVAO);
	glGenBuffers(1, &this->cubeVBO);
	glBindVertexArray(this->cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->cubeVertices), &this->cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, static_cast<GLvoid*>(nullptr));
	glBindVertexArray(0);
}

void Cube::render(UIController* uiController) {
	if (this->isDisplayable) {
		this->drawCube();
	}
}

void Cube::update(UIController* uiController) {
	this->isDisplayable = uiController->displayCube;
}

void Cube::drawCube() const {
	glBindVertexArray(this->cubeVAO);
	glBindVertexArray(this->cubeVBO);
	glActiveTexture(GL_TEXTURE0);
	glDrawArrays(GL_LINE_STRIP, 0, 36);
	glBindVertexArray(0);
}
