#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

#include <Box2D/Box2D.h>

void draw(sf::RenderWindow& window, sf::Sprite background, sf::Text text, sf::Sprite sh_character, sf::RectangleShape ground1,
	sf::RectangleShape ground2, sf::RectangleShape ground3, sf::RectangleShape ground4)
{

	window.draw(background);
	window.draw(text);
	window.draw(sh_character);
	window.draw(ground1);
	window.draw(ground2);
	window.draw(ground3);
	window.draw(ground4);

}

int main()
{

	b2Vec2 gravity(0, 12); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(1600, 600), "2D Platformer!");
	window.setFramerateLimit(60.f);

	//DEATH TEXT
	sf::Font font;
	sf::Text text;
	font.loadFromFile("data/ARDESTINE.ttf");

	float32 timeStep = 1 / 30.0;    //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	//BACKGROUND
	sf::Texture texture;
	texture.loadFromFile("data/Space001.png");
	texture.setRepeated(true);

	sf::Sprite background;
	background.setTexture(texture);

	//PLAYER
	sf::Texture box_texture;
	box_texture.loadFromFile("data/RTS_Crate.png");
	sf::Sprite sh_character(box_texture);
	sh_character.setOrigin(0, 0);
	sh_character.setScale(0.14f, 0.14f);
	b2BodyDef m_bodyDef;
	m_bodyDef.position.Set(0, 350);
	m_bodyDef.type = b2_dynamicBody;

	b2PolygonShape m_bodyShape;
	m_bodyShape.SetAsBox(35.0f, 35.0f);

	b2FixtureDef m_bodyFix;
	m_bodyFix.shape = &m_bodyShape;
	m_bodyFix.density = 0.1f;
	m_bodyFix.friction = 0.0f;

	b2Body* m_body = myWorld->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_bodyFix);

	//GROUND
	sf::RectangleShape ground1(sf::Vector2f(300, 25));
	ground1.setOrigin(100, 0);
	ground1.setFillColor(sf::Color::Yellow);

	b2BodyDef m_ground1;
	m_ground1.position.Set(0, 500);
	m_ground1.type = b2_staticBody;

	b2PolygonShape m_groundShape;
	m_groundShape.SetAsBox(150.f, 35.f);


	b2FixtureDef m_groundFix;
	m_groundFix.shape = &m_groundShape;
	m_groundFix.density = .7f;
	m_groundFix.friction = 0.f;

	b2Body* m_groundBody = (*myWorld).CreateBody(&m_ground1);
	m_groundBody->CreateFixture(&m_groundShape, 1.0f);

	//GROUND2
	sf::RectangleShape ground2(sf::Vector2f(300, 25));
	ground2.setOrigin(100, 0);
	ground2.setFillColor(sf::Color::Yellow);

	b2BodyDef m_ground2;
	m_ground2.position.Set(500, 400);
	m_ground2.type = b2_staticBody;

	b2PolygonShape m_ground2Shape;
	m_ground2Shape.SetAsBox(150.f, 35.f);


	b2FixtureDef m_ground2Fix;
	m_ground2Fix.shape = &m_ground2Shape;
	m_ground2Fix.density = .0f;
	m_ground2Fix.friction = 0.f;

	b2Body* m_ground2Body = (*myWorld).CreateBody(&m_ground2);
	m_ground2Body->CreateFixture(&m_ground2Shape, 1.0f);

	//GROUND3
	sf::RectangleShape ground3(sf::Vector2f(300, 25));
	ground3.setOrigin(100, 0);
	ground3.setFillColor(sf::Color::Yellow);

	b2BodyDef m_ground3;
	m_ground3.position.Set(1000, 500);
	m_ground3.type = b2_staticBody;

	b2PolygonShape m_ground3Shape;
	m_ground3Shape.SetAsBox(150.f, 35.f);


	b2FixtureDef m_ground3Fix;
	m_ground3Fix.shape = &m_ground3Shape;
	m_ground3Fix.density = .0f;
	m_ground3Fix.friction = 0.f;

	b2Body* m_ground3Body = (*myWorld).CreateBody(&m_ground3);
	m_ground3Body->CreateFixture(&m_ground3Shape, 1.0f);

	//GROUND4
	sf::RectangleShape ground4(sf::Vector2f(300, 25));
	ground4.setOrigin(100, 0);
	ground4.setFillColor(sf::Color::Yellow);

	b2BodyDef m_ground4;
	m_ground4.position.Set(1500, 400);
	m_ground4.type = b2_staticBody;

	b2PolygonShape m_ground4Shape;
	m_ground4Shape.SetAsBox(150.f, 35.f);


	b2FixtureDef m_ground4Fix;
	m_ground4Fix.shape = &m_ground4Shape;
	m_ground4Fix.density = .0f;
	m_ground4Fix.friction = 0.f;

	b2Body* m_ground4Body = (*myWorld).CreateBody(&m_ground4);
	m_ground4Body->CreateFixture(&m_ground4Shape, 1.0f);

	float speed = 5.0f;
	bool Is_grounded = true;


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
		ground2.setPosition(m_ground2Body->GetPosition().x, m_ground2Body->GetPosition().y);
		ground3.setPosition(m_ground3Body->GetPosition().x, m_ground3Body->GetPosition().y);
		ground4.setPosition(m_ground4Body->GetPosition().x, m_ground4Body->GetPosition().y);

		b2Vec2 vel = m_body->GetLinearVelocity();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (m_body->GetPosition().x <= 0)
					vel.x = -0.f;
				else
					vel.x = -50.f;

			}

			if (event.key.code == sf::Keyboard::Right)
			{
				vel.x = 50.f;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (m_body->GetPosition().x <= 0)
					vel.x = -0.f;
				else
					vel.x = 0.f;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				vel.x = 0.f;
			}
		}


		if (event.type == sf::Event::KeyPressed && (Is_grounded == true))
		{
			Is_grounded = false;
			if (event.key.code == sf::Keyboard::Up)
				vel.y = -90.f;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			window.close();
		}

		else if (event.type == sf::Event::KeyReleased && (Is_grounded == false) &&
			(m_body->GetPosition().y > 425.f) &&
			(m_body->GetPosition().y < 430.f) &&
			(m_body->GetPosition().x > -0.5f) &&
			(m_body->GetPosition().x < 200.f))
		{
			Is_grounded = true;
		}

		else if (event.type == sf::Event::KeyReleased && (Is_grounded == false) &&
			(m_body->GetPosition().y > 325.f) &&
			(m_body->GetPosition().y < 330.f) &&
			(m_body->GetPosition().x > 350.f) &&
			(m_body->GetPosition().x < 820.f))
		{
			Is_grounded = true;
		}

		else if (event.type == sf::Event::KeyReleased && (Is_grounded == false) &&
			(m_body->GetPosition().y > 425.f) &&
			(m_body->GetPosition().y < 430.f) &&
			(m_body->GetPosition().x > 850.f) &&
			(m_body->GetPosition().x < 1290.f))
		{
			Is_grounded = true;
		}

		else if (event.type == sf::Event::KeyReleased && (Is_grounded == false) &&
			(m_body->GetPosition().y > 325.f) &&
			(m_body->GetPosition().y < 330.f) &&
			(m_body->GetPosition().x > 1350.f) &&
			(m_body->GetPosition().x < 1600.5f))
		{
			Is_grounded = true;
		}

		if (m_body->GetPosition().y > 600.f)
		{


			text.setFont(font);
			text.setString("You died, try again !\nPress Space to exit !");
			text.setPosition(500.f, 100.f);
			text.setColor(sf::Color::Red);
			text.setCharacterSize(50.f);

		}
		window.clear();
		m_body->SetLinearVelocity(vel);
		draw(window, background, text, sh_character, ground1, ground2, ground3, ground4);
		window.display();
	}

	delete myWorld;

	return EXIT_SUCCESS;

}