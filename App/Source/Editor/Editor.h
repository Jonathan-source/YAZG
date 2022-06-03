#pragma once

#include "Entities/Entity.h"
#include "Core/StateMachine.h"
#include "States/IState.h"

class Editor : public IState
{
public:
	Editor();
	virtual ~Editor() = default;

	void OnEnter() override;

	void OnInput() override;

	bool OnUpdate(float frameDelta) override;

	void OnRender() override;

	void OnExit() override;


private:
	Camera m_camera;
	Ray m_cameraRay;
	Vector3 m_cameraVelocity;
	const float m_cameraSpeed = 5.f;
	float m_cameraSpeedModifier = 1.0f;

	struct Object 
	{
		Vector3 position;
		Model model;
		Color color;
		BoundingBox boundingBox;
	};

	std::vector<Object> m_objects;
	
	struct Tiles {
		Vector3 position;
		unsigned int id;
		bool isOccupied;
	};
	const int GRID_X = 50;
	const int GRID_Y = 50;
	static const int NUM_TILES = 2500;
	std::array<Tiles, NUM_TILES> m_tiles;

	Rectangle m_currentTile;

	Rectangle m_itemRects[10];
	int m_itemSelected ;
	int m_itemSelectedPrev;
	int m_itemMouseHover;
	bool m_mouseWasPressed;
	bool m_isMouseOnPanel;

	Rectangle m_btnSaveRec;
	bool m_btnSaveMouseHover;
	bool m_showSaveMessage;
	int m_saveMessageCounter;

	Rectangle m_btnNewRec;
	bool m_btnNewMouseHover;

	void UpdateCamera(float frameDelta);
	void UpdateSaveMsgTimer(float frameDelta);
	void HandleCameraInput();
	void HandleMouseInput();
	void ZoomIn();
	void ZoomOut();
	void DrawObjects();
	void DrawTileGrid();
	void GenerateGrid();
	void SetupPanel();
	void HandleItemSelectionInput();
	void HandleItemPlacementInput();
	void DrawPanel();
};