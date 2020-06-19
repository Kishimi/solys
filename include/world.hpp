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

#include <string>
#include <vector>

#include "sfml.hpp"
#include "game_object.hpp"
#include "celestial_body.hpp"

class World
{
public: /* PUBLIC FUNCS */
	World(const float G);
	~World();

	/**
	 * @brief Update the World
	 * @param clock the game timer
	 */
	void update(const sf::Clock& clock);

	/**
	 * @brief Draw the Worl to an sf::RenderWindow
	 * @param window The sf::RenderWindow to draw to
	 */
	void draw(sf::RenderWindow& window);

	/**
	 * @brief "Spawn" a new GameObject in the world
	 * @param obj The GameObject to be spawned
	 */
	void spawn(GameObject* obj);

	/**
	 * @brief Get a copy of all game_objects
	 * @return Copy of all game_objects
	 */
	std::vector<GameObject*> get_objs() const;

private: /* PRIVATE FUNCS */

	// GAME OBJECT
	//
	/**
	 * @brief Update a GameObject
	 * @param clock The game timer
	 * @param obj A reference to the GameObject
	 */
	void update(const sf::Clock& clock, GameObject* obj) const;

	// CELESTIAL BODY
	//
	/**
	 * @brief Update a CelestialBody
	 * @param clock the game timer
	 * @param obj The CelestialBody to update
	 */
	void update(const sf::Clock& clock, CelestialBody* obj) const;

private: /* PRIVATE VARS */
	std::vector<GameObject*> objects;
	float G;
};