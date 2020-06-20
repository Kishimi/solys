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

#pragma once

#include "sfml.hpp"
#include "world.hpp"
#include "game_object.hpp"
#include "celestial_body.hpp"
#include "config.hpp"
#include "version.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

class Game
{
public: /* PUBLIC TYPES */

	/**
	 * @brief The state of the game
	 */
	enum class State
	{
		playing,
		paused
	};

public: /* PUBLIC FUNCS */

	/**
	 * @brief Just clean up
	 */
	~Game();

	/**
	 * @brief Initialize the game and create a SFML2 RenderWindow with videomode
	 * @param window An sf::RenderWindow with set settings
	 * @param videomode The sf::VideoMode to use
	 * @return True if the window has been successfully created, false if not
	 */
	bool init(const Config& config);

	/**
	 * @brief Start the main loop of the game
	 */
	void run();

private: /* PRIVATE FUNCS */

	/**
	 * @brief Draw game world
	 */
	void draw_game_world();

	/**
	 * @brief Draw ui
	 */
	void draw_ui();

	/**
	 * @brief Handle all queued sf::Events
	 */
	void handle_events();

	/**
	 * @brief Handle input for the camera
	 */
	void handle_camera_input();

private: /* PRIVATE VARS */
	sf::RenderWindow window;
	sf::View camera;
	float camera_speed, fast_camera_speed;
	unsigned int framerate_limit;

	sf::Clock clock;
	World world = World(0.081f);
	State state;

	GameObject* selected_obj;
};