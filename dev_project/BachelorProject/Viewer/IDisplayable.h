#pragma once

class UIController;

class IDisplayable {
public:
	virtual ~IDisplayable() {}

	virtual void render(UIController* uiController) = 0;
	virtual void update(UIController* uiController) = 0;

};
