#include "Game.h"
#include "Box2D.h"

using namespace sf;

Game::Game(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "EJERCICIO 6");
	_fps = 60;
	_wnd->setFramerateLimit(_fps);
	_frameTime = 1.f / _fps;
	InitPhysics();
	SetZoom();
}

void Game::Loop()
{

	while (_wnd->isOpen())
	{

		_wnd->clear(_clearColor);
		DoEvents();
		UpdatePhysics();
		DrawGame();
		_wnd->display();
	}
}

void Game::DoEvents()
{

	Event evt;
	while (_wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			_wnd->close();
			break;
		}
	}
}

void Game::InitPhysics()
{

	_world = new b2World(b2Vec2(0.f, 9.8f));
	_render = new SFML(_wnd);
	_render->SetFlags(UINT_MAX);
	_world->SetDebugDraw(_render);

	b2Body* groundShape = Box2D::CreateRectangularStaticBody(_world, 100.f, 10.f);
	groundShape->SetTransform(b2Vec2(50.f, 100.f), 0.f);

	b2Body* rightWallShape = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	rightWallShape->SetTransform(b2Vec2(100.f, 100.f), 0.f);

	b2Body* leftWallShape = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	leftWallShape->SetTransform(b2Vec2(0.f, 100.f), 0.f);

	_body = Box2D::CreateCircularDynamicBody(_world, 5.f, 1.f, 0.3f, 0.f);
	//_body->SetLinearVelocity(b2Vec2(10.f, 0.f));
	//_body->ApplyForce(const b2Vec2(10.f, 10.f), const b2Vec2(10.f, 10.f), true);
	_body->SetTransform(b2Vec2(10.f, 50.f), 0.f);
}

void Game::UpdatePhysics()
{

	_world->Step(_frameTime, 8, 8);
	_world->ClearForces();
	_world->DebugDraw();
}

void Game::SetZoom()
{

	View camara;
	camara.setSize(100.f, 100.f);
	camara.setCenter(50.f, 50.f);
	_wnd->setView(camara);

}

void Game::DrawGame()
{

	RectangleShape rightWallShape(Vector2f(5.f, 100.f));
	rightWallShape.setFillColor(Color::Yellow);
	rightWallShape.setPosition(95.f, 0.f);
	_wnd->draw(rightWallShape);

	RectangleShape leftWallShape(Vector2f(5.f, 100.f));
	leftWallShape.setFillColor(Color::Yellow);
	leftWallShape.setPosition(0.f, 0.f);
	_wnd->draw(leftWallShape);

	RectangleShape groundShape(Vector2f(100.f, 5.f));
	groundShape.setFillColor(Color::Green);
	groundShape.setPosition(0.f, 95.f);
	_wnd->draw(groundShape);

	CircleShape circle(5.f);
	circle.setFillColor(Color::Red);
	circle.setPosition(_body->GetPosition().x - 5.f, _body->GetPosition().y - 5.f);
	_wnd->draw(circle);
}

Game::~Game(void)
{
}