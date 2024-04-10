#pragma once
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
	SFML* _render;

public:

	Game(int _width, int _height);
	~Game(void);

	void InitPhysics();
	void UpdatePhysics();
	void Loop();
	void DoEvents();
	void DrawGame();
	void SetZoom();
	void ApplyForce(const b2Vec2& force, const b2Vec2& point, bool wake);
};