#include "pch.h"
#include "Editor.h"

// Temporary colors.
Color colors[10] = {
	YELLOW, ORANGE, PINK, RED, GREEN, BLUE,
	PURPLE, BROWN, GRAY, BLACK
};

Editor::Editor()
	: m_cameraVelocity({ 0.f,0.f,0.f })
	, m_saveMessageCounter(0)
	, m_showSaveMessage(false)
{
}

void Editor::OnEnter()
{
	m_camera.position = { 0.0f, 10.0f, 10.0f };
	m_camera.target = { 0.0f, 0.0f, 0.0f };	
	m_camera.up = { 0.0f, 1.0f, 0.0f };	
	m_camera.fovy = 45.0f;  
	m_camera.projection = CAMERA_PERSPECTIVE;

	GenerateGrid();
	SetupPanel();
}

void Editor::OnInput()
{
	m_cameraRay = GetMouseRay(GetMousePosition(), m_camera);

	HandleCameraInput();

	HandleItemSelectionInput();

	HandleItemPlacementInput();

	if (IsKeyPressed(KEY_ESCAPE))
	{
		GetStateMachine()->Change("MainMenu");
	}
}

bool Editor::OnUpdate(float frameDelta)
{
	UpdateCamera(frameDelta);

	UpdateSaveMsgTimer(frameDelta);

	return true;
}

void Editor::OnRender()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	BeginMode3D(m_camera);

	DrawGrid(50, 1.0f);
	DrawTileGrid();
	DrawObjects();

	EndMode3D();

	DrawPanel();

	EndDrawing();
}

void Editor::OnExit()
{

}

void Editor::UpdateCamera(float frameDelta)
{
	const float velocity = frameDelta * m_cameraSpeed * m_cameraSpeedModifier;
	m_camera.position = Vector3Add(Vector3Scale(m_cameraVelocity, velocity), m_camera.position);
	m_camera.target = Vector3Add(Vector3Scale(m_cameraVelocity, velocity), m_camera.target);
}

void Editor::HandleCameraInput()
{
	if (IsKeyDown(KEY_A))
		m_cameraVelocity.x = -1.0f;

	if (IsKeyDown(KEY_W))
		m_cameraVelocity.z = -1.0f;

	if (IsKeyDown(KEY_D))
		m_cameraVelocity.x = 1.0f;

	if (IsKeyDown(KEY_S))
		m_cameraVelocity.z = 1.0f;

	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
		m_cameraVelocity.x = 0;

	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
		m_cameraVelocity.z = 0;

	if (IsKeyDown(KEY_LEFT_SHIFT))
		m_cameraSpeedModifier = 3.f;
	else 
		m_cameraSpeedModifier = 1.f;
}

void Editor::HandleMouseInput()
{
	// Mouse position in world space.
	Vector3 N = { 0.f, 1.f, 0.f };
	float t = (-Vector3DotProduct(m_cameraRay.position, N)) / (Vector3DotProduct(m_cameraRay.direction, N));
	Vector3 mousePosition = Vector3Add(m_cameraRay.position, Vector3Scale(m_cameraRay.direction, t));

	m_currentTile.x = mousePosition.x;
	m_currentTile.y = mousePosition.y;
}

void Editor::ZoomIn()
{

}

void Editor::ZoomOut()
{

}

void Editor::UpdateSaveMsgTimer(float frameDelta)
{
	if (m_showSaveMessage)
	{
		m_saveMessageCounter++; 
		if (m_saveMessageCounter > 120) // 60 frames per sec: 2s = 120.
		{
			m_showSaveMessage = false;
			m_saveMessageCounter = 0;
		}
	}
}

void Editor::DrawObjects()
{
	for (const auto& obj : m_objects)
	{
		DrawModel(obj.model, obj.position, 0.5f, obj.color);
	}
}

void Editor::DrawTileGrid()
{
	Rectangle rect;
	rect.width = 10.f;
	rect.height = 10.f;
		
	for (int i = 0; i < NUM_TILES; i++)
	{
		DrawRectangle(m_tiles[i].position.x,
			m_tiles[i].position.y,
			rect.width,
			rect.height,
			colors[3]);
	}
}

void Editor::GenerateGrid()
{
	float offset = -25.f;
	for (int y = 0; y < GRID_Y; ++y)
	{
		for (int x = 0; x < GRID_X; ++x)
		{
			int index = y * GRID_X + x;
			m_tiles[index].id = index;
			m_tiles[index].position = Vector3{ offset + x, offset + y, 0.f };
		}
	}
}

void Editor::SetupPanel()
{
	for (int i = 0; i < 10; i++)
	{
		m_itemRects[i].x = 20 + 60.0f * i + 4 * i;
		m_itemRects[i].y = 20;
		m_itemRects[i].width = 60;
		m_itemRects[i].height = 60;
	}

	m_btnNewRec = { GetScreenWidth() / 1.5f - 10, 20, 80, 60 };
	m_btnSaveRec = { GetScreenWidth() / 1.2f - 10, 20, 80, 60 };
}

void Editor::HandleItemSelectionInput()
{
	Vector2 mousePos = GetMousePosition();

	if (m_itemSelected >= 10) m_itemSelected = 10 - 1;
	else if (m_itemSelected < 0) m_itemSelected = 0;

	m_isMouseOnPanel = false;
	m_btnSaveMouseHover = false;
	m_btnNewMouseHover = false;

	// Check if mouse hover panel
	if (mousePos.y <= 100.f)
	{
		m_isMouseOnPanel = true;

		// Choose item with mouse
		for (int i = 0; i < 10; i++)
		{
			if (CheckCollisionPointRec(mousePos, m_itemRects[i]))
			{
				m_itemMouseHover = i;
					break;
			}
			else 
				m_itemMouseHover = -1;
		}

		if ((m_itemMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_itemSelected = m_itemMouseHover;
			m_itemSelectedPrev = m_itemMouseHover;
		}

		// Check mouse hover save button
		if (CheckCollisionPointRec(mousePos, m_btnSaveRec))
		{
			m_btnSaveMouseHover = true;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				m_showSaveMessage = true;
			}
		}

		// Check mouse hover save button
		if (CheckCollisionPointRec(mousePos, m_btnNewRec))
		{
			m_btnNewMouseHover = true;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				m_objects.clear();
			}
		}
	}
}

void Editor::DrawPanel()
{
	// Draw top panel
	DrawRectangle(0, 0, GetScreenWidth(), 100, RAYWHITE);
	DrawLine(0, 100, GetScreenWidth(), 100, LIGHTGRAY);

	// Draw item selection rectangles
	for (int i = 0; i < 10; i++) 
		DrawRectangleRec(m_itemRects[i], colors[i]);

	DrawRectangleLines(20, 20, 60, 60, LIGHTGRAY);
	
	// Draw faded rectangle on item hover
	if (m_itemMouseHover >= 0) 
		DrawRectangleRec(m_itemRects[m_itemMouseHover], Fade(WHITE, 0.6f));

	// Draw rectangle boarder around current selected item
	Rectangle rect = { m_itemRects[m_itemSelected].x - 4, m_itemRects[m_itemSelected].y - 4,
		m_itemRects[m_itemSelected].width + 8, m_itemRects[m_itemSelected].height + 8 };
	DrawRectangleLinesEx(rect, 2, BLACK);

	// Drawn new button
	DrawRectangleLinesEx(m_btnNewRec, 2, m_btnNewMouseHover ? RED : BLACK);
	DrawText("NEW!", GetScreenWidth() / 1.5f, 40, 20, m_btnNewMouseHover ? RED : BLACK);

	// Draw save button
	DrawRectangleLinesEx(m_btnSaveRec, 2, m_btnSaveMouseHover ? RED : BLACK);
	DrawText("SAVE!", GetScreenWidth() / 1.2f, 40, 20, m_btnSaveMouseHover ? RED : BLACK);

	// Draw save image message
	if (m_showSaveMessage)
	{
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
		DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
		std::string name = "name-of-the-map";
		std::string text = "LEVEL SAVED: " + name;
		DrawText(text.c_str(), GetScreenWidth() / 3, 180, 20, RAYWHITE);
	}
}

void Editor::HandleItemPlacementInput()
{
	if (!m_isMouseOnPanel)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Ray ray = GetMouseRay(GetMousePosition(), m_camera);
			RayCollision collision = {0};
			for (int i = 0; i < m_objects.size() && !collision.hit; ++i)
			{
				Vector3 cubePosition = m_objects[i].position;
				Vector3 cubeSize = { 0.5f, 0.5f, 0.5f };

				// Check collision between ray and box			
				collision = GetRayCollisionBox(ray,
                            BoundingBox { Vector3 { cubePosition.x - cubeSize.x, cubePosition.y - cubeSize.y, cubePosition.z - cubeSize.z },
                                          Vector3 { cubePosition.x + cubeSize.x, cubePosition.y + cubeSize.y, cubePosition.z + cubeSize.z }});
			}

			if (!collision.hit)
			{
				static Model model = LoadModel("../resources/meshes/cube.obj");
				m_objects.push_back(
					{
						Vector3{0,0,0},
						model,
						colors[m_itemSelected],
						GetMeshBoundingBox(model.meshes[0])
					});
				TraceLog(TraceLogLevel::LOG_DEBUG, "Object created!");
			}
		}
	}
}

