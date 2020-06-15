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

#include "celestial_body.hpp"

CelestialBody::CelestialBody(const float density, const float radius, const sf::Color color):
	GameObject(Type::celestial_body),
	density(density),
	radius(radius)
{
	set_radius(radius);
	set_color(color);
	volume = calc_volume(radius);
	mass = calc_mass(density, volume);

	pos = sf::Vector2f(0.0f, 0.0f);
	vel = sf::Vector2f(0.0f, 0.0f);
}

void CelestialBody::update(const sf::Clock& clock)
{
	pos += vel * (float)clock.getElapsedTime().asSeconds();
	shape.setPosition((float)pos.x, (float)pos.y);
}

void CelestialBody::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void CelestialBody::set_origin(const float radius)
{
	shape.setOrigin(float(radius), float(radius));
}

void CelestialBody::set_radius(const float radius)
{
	shape.setRadius(radius);
	set_origin(radius);
}

void CelestialBody::set_color(const sf::Color color)
{
	shape.setFillColor(color);
}

float CelestialBody::calc_mass(const float density, const float volume)
{
	return density * volume;
}

float CelestialBody::calc_volume(const float radius)
{
	return (4.0f / 3.0f) * (float)M_PI * radius * radius * radius;
}