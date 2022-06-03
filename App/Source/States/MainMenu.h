#pragma once

#include "Core/StateMachine.h"

class MainMenu : public IState
{
public:
	MainMenu();
	virtual ~MainMenu() = default;

	void OnEnter() override;
	void OnInput() override;
	bool OnUpdate(float frameDelta) override;
	void OnRender() override;
	void OnExit() override;

	//Initialize all buttons for menu
	void InitButtons();

private:	
	//Mouse
	Vector2 mousePoint;

	//Menu buttons
	int m_Numframes; //Number of frames for t_startButton sprite texture
	float frameHeight; //Define frame rectangle height for t_startButton
	float buttonPadding; //Padding between buttons

	Rectangle srcRecStartButton;
	Rectangle srcRecEditorButton;
	Rectangle srcRecHighscoreButton;
	Rectangle srcRecExitButton;

	Rectangle startBtnBounds;
	Rectangle editorBtnBounds;
	Rectangle highscoreBtnBounds;
	Rectangle exitBtnBounds;

	int startBtnState; // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
	int editorBtnState;
	int highscoreBtnState;
	int exitBtnState;

	bool startBtnAction;
	bool editorBtnAction;
	bool highscoreBtnAction;
	bool exitBtnAction;

	Sound fxButton;

	Texture2D t_startButton;
	Texture2D t_editorButton;
	Texture2D t_highscoreButton;
	Texture2D t_exitButton;
};