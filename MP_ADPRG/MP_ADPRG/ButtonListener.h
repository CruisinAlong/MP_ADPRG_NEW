#pragma once

class UIButton;

class ButtonListener {
public:
	virtual void onButtonClick(UIButton* button) = 0;
	virtual  void onButtonReleased(UIButton* button) = 0;
protected:
	ButtonListener() {}
};