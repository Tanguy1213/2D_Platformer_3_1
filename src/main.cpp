#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

#include <Box2D/Box2D.h>

struct body
{
	b2BodyDef DEF;
	b2PolygonShape SHAPE;
	b2FixtureDef FIX;
	b2Body * BOD;
	sf::RectangleShape RECT;
};

int main()
{

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(800, 600), "2D Platformer!");
	window.setFramerateLimit(60.f);


	float32 timeStep = 1 / 30.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position


	//PLAYER
	sf::RectangleShape sh_character(sf::Vector2f(100, 100));
	sh_character.setOrigin(0, 0);
	sh_character.setFillColor(sf::Color::Blue);

	b2BodyDef m_bodyDef;
	m_bodyDef.position.Set(0, 350);
	m_bodyDef.type = b2_dynamicBody;

	b2PolygonShape m_bodyShape;
	m_bodyShape.SetAsBox(50.0f, 50.0f);

	b2FixtureDef m_bodyFix;
	m_bodyFix.shape = &m_bodyShape;
	m_bodyFix.density = 0.1f;
	m_bodyFix.friction = 0.0f;

	b2Body* m_body = myWorld->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_bodyFix);

	//GROUND
	sf::RectangleShape ground1(sf::Vector2f(300, 25));
	ground1.setOrigin(0, 0);
	ground1.setFillColor(sf::Color(200, 75, 20, 255));

	b2BodyDef m_ground1;
	m_ground1.position.Set(0, 500);
	m_ground1.type = b2_staticBody;

	b2PolygonShape m_groundShape;
	m_groundShape.SetAsBox(260.f, 50.f);


	b2FixtureDef m_groundFix;
	m_groundFix.shape = &m_groundShape;
	m_groundFix.density = .7f;
	m_groundFix.friction = 0.f;

	b2Body* m_groundBody = (*myWorld).CreateBody(&m_ground1);
	m_groundBody->CreateFixture(&m_groundShape, 1.0f);

	float speed = 5.0f;
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					std::cout << "User's going left\n";
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					std::cout << "User's going right\n";
				}
			}
		}
		
		sh_character.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
		ground1.setPosition(m_groundBody->GetPosition().x, m_groundBody->GetPosition().y);

		b2Vec2 vel = m_body->GetLinearVelocity();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			vel.x = -50.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			vel.x = 50.0f;
		}
		window.clear();

		m_body->SetLinearVelocity(vel);

		window.draw(sh_character);
		window.draw(ground1);
		
		window.display();
	}
	delete myWorld;

	return EXIT_SUCCESS;
}