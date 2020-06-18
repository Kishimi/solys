/**
 *	MIT LICENSE
 * 
 * 	Copyright (c) 2020 Kishimi
 *		Contact:
 * 			Anton Büttner
 *			anton@green-pr.org
 * 
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include "game.hpp"

bool Game::init(const Config& config)
{
	// Load settings
	//
	sf::VideoMode vmode;

	// Load "graphics" settings
	vmode.width = config.get_value<unsigned int>("graphics", "window-width");
	vmode.height = config.get_value<unsigned int>("graphics", "window-height");
	window.setVerticalSyncEnabled(config.get_value<bool>("graphics", "v-sync"));
	framerate_limit = config.get_value<unsigned int>("graphics", "framerate-limit");

	// Load "advanced" settings
	camera_speed = config.get_value<float>("advanced", "camera-speed");
	fast_camera_speed = config.get_value<float>("advanced", "fast-camera-speed");

	// create window
	window.create(vmode, "Solys " + SOLYS_VERSION);

	// init view
	camera.setCenter(0.0f, 0.0f);
	camera.setSize((float)window.getSize().x, (float)window.getSize().y);
	window.setView(camera);

	// init solui
	sf::Font font;
	font.loadFromFile("data/fonts/DejaVuSans.ttf");
	if (!solui::init(&window, font))
	{
		// TODO: handle error
		return false;
	}

	// init game variables
	state = State::paused;

	// init the game world
	CelestialBody* sun = new CelestialBody(500.0f, 70.0f);
	sun->set_color(sf::Color::Yellow);

	CelestialBody* earth = new CelestialBody(1.5f, 6.0f);
	earth->set_pos(0.0f, -400.0f);
	earth->set_vel(earth->calc_orbital_velocity(0.081f, sun), 0.0f);
	
	world.spawn(sun);
	world.spawn(earth);

	return window.isOpen();
}

void Game::run()
{
	while (window.isOpen())
	{
		handle_events();
		handle_camera_input();

		window.clear();

		switch (state)
		{
			case State::playing:
				draw_game_world();
				break;

			case State::paused:
				draw_main_menu();
				break;
		}

		// window.setTitle("Solys " + SOLYS_VERSION + std::to_string(1.0f / clock.getElapsedTime().asSeconds()));
		window.display();

		clock.restart();

		if (framerate_limit != 0)
		{
			// sleep to hold a framerate
			sf::sleep(sf::milliseconds((1.0f / framerate_limit) * 1000));
		}
	}
}

void Game::draw_game_world()
{
	window.setView(camera);

	world.update(clock);
	world.draw(window);

	// draw gui
	window.setView(window.getDefaultView());

	if (solui::button("<- back to main menu", { 10.0f, 10.0f, 200.0f, 40.0f }))
	{
		state = State::paused;
		sf::sleep(sf::milliseconds(100));
	}
}

void Game::draw_main_menu()
{
	// set back to default view
	window.setView(window.getDefaultView());

	// Play Button
	if (solui::button("Play", { 10.0f, 10.0f, 200.0f, 80.0f }, 50))
	{
		state = State::playing;
		sf::sleep(sf::milliseconds(100));
	}

	if (solui::button("Quit", { 10.0f, 100.0f, 200.0f, 80.0f }, 50))
	{
		window.close();
	}
}

void Game::handle_events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
		}
	}
}

void Game::handle_camera_input()
{
	sf::Vector2f camera_vel = { 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	// move the camera up
	{
		camera_vel.y -= camera_speed * clock.getElapsedTime().asSeconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	// move the camera down
	{
		camera_vel.y += camera_speed * clock.getElapsedTime().asSeconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	// move the camera left
	{
		camera_vel.x -= camera_speed * clock.getElapsedTime().asSeconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	// move the camera right
	{
		camera_vel.x += camera_speed * clock.getElapsedTime().asSeconds();
	}

	// if shift is pressed, then use fast speed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		camera_vel *= (fast_camera_speed / camera_speed);
	}

	// move the camera
	camera.move(camera_vel);
}