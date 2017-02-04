#include <SFML/Graphics.hpp>
#include "GameObject.hh"
#include "Scene.hh"
#include <iostream>
#include <chrono>
#include "Gravity.hh"
#include "ClassTest.h"

#include <Windows.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Test Physical Engine -> Gravity");


	Scene& scene = Scene::getInstance();


	std::vector<sf::RectangleShape>		shapes;
	std::vector<GameObject *>			gos;

	// Bottom
	shapes.push_back(sf::RectangleShape(sf::Vector2f(900, 100)));
	shapes.back().setFillColor(sf::Color::Green);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(0, 900), "Bottom")->addCollider(900, 100)->addRigidBody(0, 0.f));
	gos.back()->addEffect(new EnvironmentalEffect::Gravity(-0.05f));
	// Top
	shapes.push_back(sf::RectangleShape(sf::Vector2f(900, 100)));
	shapes.back().setFillColor(sf::Color::Green);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(100, 0), "Top")->addCollider(900, 100)->addRigidBody(0, 0.f));
	// gos.back()->addEffect(new EnvironmentalEffect::Gravity(0.05f));
	// Left
	shapes.push_back(sf::RectangleShape(sf::Vector2f(100, 900)));
	shapes.back().setFillColor(sf::Color::White);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(0, 0), "Left")->addCollider(100, 900)->addRigidBody(0, 0.f));
	// gos.back()->addEffect(new EnvironmentalEffect::Gravity(0.05f));
	// Right
	shapes.push_back(sf::RectangleShape(sf::Vector2f(100, 900)));
	shapes.back().setFillColor(sf::Color::White);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(900, 100), "Right")->addCollider(100, 900)->addRigidBody(0, 0.f));
	// gos.back()->addEffect(new EnvironmentalEffect::Gravity(0.05f));


	// Stuff
/**/	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Magenta);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(390, 390), "Tiny 1")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, 0));

	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Red);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(390, 570), "Tiny 2")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, -1));

	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Magenta);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(570, 390), "Tiny 3")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, 0));

	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Red);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(570, 570), "Tiny 4")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, -1));


	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Red);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(390, 200), "Tiny 5")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, 0));

	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Red);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(570, 200), "Tiny 6")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(0, 0));

	shapes.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
	shapes.back().setFillColor(sf::Color::Yellow);
	gos.push_back(scene.addGameObject<ClassTest>(Vector::Vector2<float>(200, 700), "Tiny 7")->addCollider(50, 50)->addRigidBody(1, 1.f));
	gos.back()->getRigidBody()->applyForce(Vector::Vector2<float>(3, -3));


	/*sf::RectangleShape shape1(sf::Vector2f(1000, 100));
	shape1.setFillColor(sf::Color::Green);
	GameObject* go1 = scene.addGameObject<ClassTest>(Vector::Vector2<float>(0, -900), "toto")->addCollider(1000, 100)->addRigidBody(0, 0.f);
	go1->addEffect(new EnvironmentalEffect::Gravity(0.05f));*/

	/*
	sf::RectangleShape shape2(sf::Vector2f(100, 200));
	shape2.setFillColor(sf::Color::Blue);
	GameObject* go2 = scene.addGameObject<ClassTest>(Vector::Vector2<float>(800, -320), "titi")->addCollider(100, 200)->addRigidBody(1, .5f);
	go2->getRigidBody()->applyForce(Vector::Vector2<float>(-0.1, 0.8));


	sf::RectangleShape shape3(sf::Vector2f(50, 60));
	shape3.setFillColor(sf::Color::Red);
	GameObject* go3 = scene.addGameObject<ClassTest>(Vector::Vector2<float>(800, -180), "tutu")->addCollider(50, 60)->addRigidBody(1, 1.f);
	go3->getRigidBody()->applyForce(Vector::Vector2<float>(-0.1, -0.1));*/

	//go2->getLayer().addLayer(Layer::LayerTypes::GHOST);
	//go2->getLayer().removeLayer(Layer::LayerTypes::DEFAULT);
	//go1->getLayer().addLayer(Layer::LayerTypes::GHOST);
	//reinterpret_cast<ClassTest*>(go1)->setVerboseMode(false);

	/*scene.addGameObject(go2);
	scene.addGameObject(go3);
	scene.addGameObject(go4);*/
	//scene.addGameObject(go5);

	//go2->getRigidBody().applyForce(Vector::Vector2<float>(0.16, 0));
	//go3->getRigidBody().applyForce(Vector::Vector2<float>(-0.5, 0));
	//go4->getRigidBody().applyForce(Vector::Vector2<float>(-2, 0));

	//sf::RectangleShape shape4(sf::Vector2f(100, 100));
	//shape4.setFillColor(sf::Color::Yellow);

	//sf::RectangleShape shape5(sf::Vector2f(200, 10));
	//shape5.setFillColor(sf::Color::Magenta);

	std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point currentTime;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (auto shape : shapes)
			window.draw(shape);

		//window.draw(shape1);
		//window.draw(shape2);
		//window.draw(shape3);
		//window.draw(shape4);
		//window.draw(shape5);
		window.display();

		currentTime = std::chrono::system_clock::now();

		for (int i = 0; i < shapes.size(); i++) {
			//if (i == 4)
			//	std::cout << "Shape " << i << " On (" << gos[i]->getPosition().x() << ", " << gos[i]->getPosition().y() << ") / ";
			shapes[i].setPosition(sf::Vector2f(gos[i]->getPosition().x(), gos[i]->getPosition().y()));
		}
		std::cout << std::endl;

		//shape1.setPosition(sf::Vector2f(go1->getPosition().x(), -go1->getPosition().y()));
		//shape2.setPosition(sf::Vector2f(go2->getPosition().x(), -go2->getPosition().y()));
		//shape3.setPosition(sf::Vector2f(go3->getPosition().x(), -go3->getPosition().y()));
		//shape4.setPosition(sf::Vector2f(go4->getPosition().x(), -go4->getPosition().y()));
		//shape5.setPosition(sf::Vector2f(go5->getPosition().x(), -go5->getPosition().y()));
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 10.f << std::endl;

		scene.update(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 10.f);
		//scene.update(5/10.f);

		startTime = currentTime;
		//Sleep(1000);

		std::string lol;
		//std::getline(std::cin, lol);
	}
	return 0;
}