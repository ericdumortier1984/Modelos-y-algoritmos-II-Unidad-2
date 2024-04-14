#include "Game.h"
#include "Box2D.h"

using namespace sf;

Game::Game(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "EJERCICIO 6");
	_fps = 60;
	_wnd->setFramerateLimit(_fps);
	_wnd->setMouseCursorVisible(false);
	_frameTime = 1.f / _fps;
	_cannonPosition = Vector2f(50.f, 50.f);

	SetZoom();
	InitPhysics();
}

void Game::Loop()
{

	while (_wnd->isOpen())
	{

		_wnd->clear(_clearColor);
		DoEvents();
		UpdatePhysics();
		UpdateCrosshairPosition();
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
		case Event::MouseMoved://Aqu� actualizamos la posici�n del crosshair
			UpdateCrosshairPosition();
			break;
		case Event::MouseButtonPressed://Aqu� pulsando el mouse, el disparo del ca�on sigue la direcci�n del mouse con muy poca precisi�n :(
			Vector2i _mousePosition = Mouse::getPosition(*_wnd);
			Vector2f _worldMousePosition = _wnd->mapPixelToCoords(_mousePosition);
			float _cannonAngle = CalculateCannonAngle(_worldMousePosition);
			ShootCannon(_cannonAngle);
		}
	}
}

void Game::UpdateCrosshairPosition()
{
	//Aqu� nos aseguramos que la posici�n del mouse en la ventana coincida con la posici�n del objeto _crosshair en el mundo fisico
	Vector2i mousePosition = Mouse::getPosition(*_wnd);
	Vector2f worldMousePosition = _wnd->mapPixelToCoords(mousePosition);
	_crosshair->SetTransform(b2Vec2(worldMousePosition.x, worldMousePosition.y), _crosshair->GetAngle());
}

float Game::CalculateCannonAngle(Vector2f _worldMousePosition)
{
	//Aqu� obtenemos el angulo de tiro del ca�on en radianes y nos devuelde en grados
	float _dx = _worldMousePosition.x - _cannonPosition.x;
	float _dy = _worldMousePosition.y - _cannonPosition.y;
	float _angleInRadians = atan2(_dy, _dx);
	float _angleInDegrees = _angleInRadians * 180 / M_PI;

	return _angleInDegrees;
}

void Game::ShootCannon(float _angle)
{
	//Aqu� creamos el circulo din�mico que ser�a la bala de ca�on
	//y le damos potencia al disparo cambiando los valores de forceMagnitude 
	//tambi�n aplicamos un impulso lineal con la posici�n de la bala
	_body = Box2D::CreateCircularDynamicBody(_world, 3.f, 0.05f, 0.f, 0.f);
	float _forceMagnitude = 100.0f;
	b2Vec2 _forceVector(cos(_angle * M_PI / 180.f) * _forceMagnitude, sin(_angle * M_PI / 180.f) * _forceMagnitude);
	_body->ApplyLinearImpulse(_forceVector, _body->GetPosition(), true);
	_body->SetTransform(b2Vec2(10.f, 80.f), 0.f);
}

void Game::InitPhysics()
{

	_world = new b2World(b2Vec2(0.f, 9.8f));
	_render = new SFML(_wnd);
	_render->SetFlags(UINT_MAX);
	_world->SetDebugDraw(_render);

	b2Body* groundShape = Box2D::CreateRectangularStaticBody(_world, 100.f, 10.f);
	groundShape->SetTransform(b2Vec2(50.f, 100.f), 0.f);

	b2Body* leftWallShape = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	leftWallShape->SetTransform(b2Vec2(0.f, 100.f), 0.f);

	_crosshair = Box2D::CreateCircularDynamicBody(_world, 1.f, 0.f, 0.f, 0.f);
	_crosshair->SetTransform(b2Vec2(0.f, 0.f), 0.f);

	_box = Box2D::CreateRectangularDynamicBody(_world, 10.f, 10.f, 0.f, 0.f, 0.f);
	_box->SetTransform(b2Vec2(70.f, 30.f), 0.f);
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

	CircleShape crosshair(1.0f);
	crosshair.setOrigin(1.0f, 1.0f);
	crosshair.setFillColor(Color::White);
	crosshair.setPosition(_crosshair->GetPosition().x, _crosshair->GetPosition().y);
	_wnd->draw(crosshair);

	RectangleShape leftWallShape(Vector2f(5.f, 100.f));
	leftWallShape.setFillColor(Color::Yellow);
	leftWallShape.setPosition(0.f, 0.f);
	_wnd->draw(leftWallShape);

	RectangleShape groundShape(Vector2f(100.f, 5.f));
	groundShape.setFillColor(Color::Green);
	groundShape.setPosition(0.f, 95.f);
	_wnd->draw(groundShape);
}

Game::~Game(void)
{

	delete _world;
	delete _wnd;
	delete _render;
}