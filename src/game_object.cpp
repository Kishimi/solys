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

#include "game_object.hpp"

unsigned int GameObject::id = 0;

GameObject::GameObject(const Type type):
	type(type)
{
	set_name(std::to_string(id));
	id++;
}

GameObject::~GameObject()
{
	id--;
}

sf::Vector2f GameObject::get_pos() const
{
	return pos;
}

sf::Vector2f GameObject::get_vel() const
{
	return vel;
}

void GameObject::set_pos(const sf::Vector2f pos)
{
	this->pos = pos;
}

void GameObject::set_pos(const float p_x, const float p_y)
{
	set_pos(sf::Vector2f(p_x, p_y));
}

void GameObject::set_vel(const sf::Vector2f vel)
{
	this->vel = vel;
}

void GameObject::set_vel(const float v_x, const float v_y)
{
	set_vel(sf::Vector2f(v_x, v_y));
}

float GameObject::get_mass() const
{
	return mass;
}

float GameObject::calc_magnitude(const sf::Vector2f vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

void GameObject::accelerate(const sf::Vector2<float> a)
{
	vel += a;
}

void GameObject::accelerate(const float a_x, const float a_y)
{
	accelerate(sf::Vector2f(a_x, a_y));
}

float GameObject::calc_acceleration(const float F)
{
	return F / mass;
}

float GameObject::calc_orbital_velocity(const float G, const GameObject* const obj)
{
	return std::sqrt((G * obj->get_mass()) / calc_distance(obj));
}

float GameObject::calc_orbital_velocity(const float G, const std::vector<GameObject*> objs)
{
	// add all masses
	float mass = 0.0f;
	for (const auto& obj: objs)
	{
		mass += obj->get_mass();
	}

	return std::sqrt((G * mass) / calc_distance(objs[0]));
}

float GameObject::calc_distance(const GameObject* const obj) const
{
	const sf::Vector2f dist = pos - obj->get_pos();
	return std::sqrt(dist.x * dist.x + dist.y * dist.y);
}

float GameObject::calc_distance_sq(const GameObject* const obj) const
{
	const sf::Vector2f dist = pos - obj->get_pos();
	return dist.x * dist.x + dist.y * dist.y;
}

float GameObject::calc_gravitation(const float G, const GameObject* const obj) const
{
	return (G * mass * obj->get_mass()) / calc_distance_sq(obj);
}

float GameObject::calc_angle(const GameObject* const obj) const
{
	const sf::Vector2f dist = pos - obj->get_pos();

	float angle = std::atan2(dist.y, dist.x) * 180.0f / float(M_PI);

	if (angle < 0.0f)
	{
		angle += 360.0f;
	}

	return angle - 90.0f;
}

sf::Vector2f GameObject::calc_angle_to_vec(const float angle)
{
	sf::Vector2f vec;
	vec.x = std::sin(angle / 180.0f * (float)M_PI);
	vec.y = -std::cos(angle / 180.0f * (float)M_PI);
	return vec;
}

bool GameObject::compare(const GameObject* const obj) const
{
	return
	(
		pos		== obj->pos		&&
		vel		== obj->vel		&&
		mass	== obj->mass
	);
}

void GameObject::set_name(const std::string name)
{
	this->name = name;
}

std::string GameObject::get_name() const
{
	return name;
}