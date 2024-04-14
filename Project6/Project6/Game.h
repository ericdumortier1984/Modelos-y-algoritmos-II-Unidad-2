#pragma once
#define M_PI 3.14159265358979323846
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Box2D.h"
#include "SFML_Renderer.h"

using namespace sf;

class Game
{
private:

	int _width;
	int _height;
	RenderWindow* _wnd;
	Color _clearColor;

	float _frameTime;
	int _fps;

	b2World* _world;
	b2Body* _body;
	b2Body* _box;
	b2Body* _cannon;
	b2Body* _crosshair;
	SFML* _render;

	Vector2f _cannonPosition;

public:

	Game(int _width, int _height);
	~Game(void);

	void InitPhysics();
	void UpdatePhysics();
	void Loop();
	void DoEvents();
	void DrawGame();
	void SetZoom();
	void UpdateCrosshairPosition();
	void ShootCannon(float _angle);
	float CalculateCannonAngle(Vector2f _mousePosition);
};