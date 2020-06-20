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

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

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

	// init imgui
	ImGui::SFML::Init(window);

	// init game variables
	state = State::paused;

	// init the game world
	selected_obj = nullptr;

	world.spawn(static_cast<GameObject*>(new CelestialBody(10.0f, 25.0f)));

	return window.isOpen();
}

void Game::run()
{
	while (window.isOpen())
	{
		handle_events();
		handle_camera_input();

		window.clear();

		// Update ImGui
		ImGui::SFML::Update(window, clock.getElapsedTime());

		// draw gui
		draw_ui();

		switch (state)
		{	
			case State::playing:
				world.update(clock.getElapsedTime().asSeconds());
				draw_game_world();
				break;

			case State::paused:
				world.update(0.0f);
				draw_game_world();
				break;

			default:
				break;
		}

		// Render ImGui
		ImGui::SFML::Render(window);

		// window.setTitle("Solys " + SOLYS_VERSION + std::to_string(1.0f / clock.getElapsedTime().asSeconds()));
		window.display();

		// reset delta time
		clock.restart();

		// sleep to hold a framerate
		if (framerate_limit != 0)
		{
			sf::sleep(sf::milliseconds((1.0f / framerate_limit) * 1000));
		}
	}
}

void Game::draw_game_world()
{
	window.setView(camera);

	world.draw(window);
}

void Game::draw_ui()
{
	// set back to default view
	window.setView(window.getDefaultView());

	if (ImGui::BeginMainMenuBar())
	{
		// draw the play button depending on the state
		switch (state)
		{
			case State::playing:
				if (ImGui::Button("II"))
				{
					state = State::paused;
				}
				break;

			case State::paused:
				if (ImGui::Button("|>"))
				{
					state = State::playing;
				}
				break;

			default:
				break;
		}

		if (ImGui::Button("Add Planet"))
		{
			CelestialBody* cb = new CelestialBody(50.0f, 10.0f);
			cb->set_pos(camera.getCenter());

			world.spawn(static_cast<GameObject*>(cb));
		}

		if (ImGui::Button("Quit"))
		{
			window.close();
		}
	} ImGui::EndMainMenuBar();

	// Window with planet list
	if (ImGui::Begin("Planets"))
	{
		if (ImGui::Button("None"))
		{
			selected_obj = nullptr;
		}

		for (const auto& obj: world.get_objs())
		{
			if (ImGui::Button(obj->get_name().c_str()))
			{
				selected_obj = obj;
			}
		}

	ImGui::End(); }

	// Window if planet is selected
	if (
		selected_obj != nullptr &&
		ImGui::Begin(selected_obj->get_name().c_str())
	)
	{
		switch (selected_obj->type)
		{
			case GameObject::Type::celestial_body:
			{
				CelestialBody* cb = static_cast<CelestialBody*>(selected_obj);
				float radius = cb->get_radius();
				float density = cb->get_density();
				sf::Vector2f vel = cb->get_vel();

				if (ImGui::SliderFloat("Radius", &radius, 1.0f, 500.0f))
				{
					cb->set_radius(radius);
				}

				if (ImGui::SliderFloat("Density", &density, 1.0f, 1000.0f))
				{
					cb->set_density(density);
				}

				if (ImGui::SliderFloat("X-Vel", &vel.x, -500.0f, 500.0f))
				{
					cb->set_vel(vel);
				}

				if (ImGui::SliderFloat("Y-Vel", &vel.y, -500.0f, 500.0f))
				{
					cb->set_vel(vel);
				}

			}	break;

			default:
				break;
		}
	ImGui::End(); }
}

void Game::handle_events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

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