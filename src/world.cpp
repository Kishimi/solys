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

#include "world.hpp"

World::World(const float G):
	G(G)
{}

World::~World()
{
	for (std::size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i])
		{
			delete objects[i];
		}
	}

	objects.clear();
}

/* UPDATE FUNCTIONS */

void World::update(const sf::Clock& clock)
{
	for (auto& obj: objects)
	{
		switch (obj->type)
		{
			case GameObject::Type::celestial_body:
				update(clock, static_cast<CelestialBody*>(obj));
				break;

			default:
				update(clock, obj);
				break;
		}
	}
}

void World::update(const sf::Clock& clock, GameObject* obj) const
{
	obj->update(clock);
}

void World::update(const sf::Clock& clock, CelestialBody* obj) const
{
	float F, a, angle;
	sf::Vector2f acceleration;

	for (const auto& other: objects)
	{
		if (!obj->compare(other))
		{
			F = obj->calc_gravitation(G, other);
			a = obj->calc_acceleration(F);
			angle = obj->calc_angle(other);
			acceleration = obj->calc_angle_to_vec(angle) * a;
			obj->accelerate(acceleration * clock.getElapsedTime().asSeconds());
		}
	}

	obj->update(clock);
}

/* DRAW FUNCTIONS */

void World::draw(sf::RenderWindow& window)
{
	for (const auto& obj: objects)
	{
		obj->draw(window);
	}
}

/* OTHER FUNCTIONS */

void World::spawn(GameObject* obj)
{
	objects.push_back(obj);
}

std::vector<GameObject*> World::get_objs() const
{
	return objects;
}