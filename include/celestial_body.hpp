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
#include "game_object.hpp"

class CelestialBody : public GameObject
{
public: /* PUBLIC FUNCS */

	/**
	 * @brief Constructor to create a celestial body with density and radius, and a color.
	 * @param density The density of the celestial in kg / m^3
	 * @param radius The radius of the celestial in m
	 * @param color The color of the celestial, default = sf::Color::White
	 */
	CelestialBody(const float density, const float radius,
		const sf::Color color = sf::Color::White);
	
	virtual ~CelestialBody() {};

	/**
	 * @brief Update a celestial relative to time
	 * @param clock The delta time
	 */
	void update(const float time) override;

	/**
	 * @brief Draw a celestial
	 * @param window The sf::RenderWindow to draw to
	 */
	void draw(sf::RenderWindow& window) override;

	/**
	 * @brief Set the origin by radius
	 * @param radius The radius of the celestial in m
	 */
	void set_origin(const float radius);

	/**
	 * @brief Set the radius of the CelestialBody, automatically set's origin to (radius, radius)
	 * @param radius The radius
	 */
	void set_radius(const float radius);

	/**
	 * @brief Set the color of the shape
	 * @param color The sf::Color
	 */
	void set_color(const sf::Color color);

	/**
	 * @brief Calculate mass from volume and density; m = d * V;
	 * @param density The density in kg / m^3
	 * @param volume The volume in m^3
	 * @return The mass in kg
	 */
	static float calc_mass(const float density, const float volume);

	/**
	 * @brief Calculate volume from radius; V = (4/3) * pi * r^3
	 * @param radius The radius in m
	 * @return The volume in m^3
	 */
	static float calc_volume(const float radius);

	/**
	 * @brief Get the radius of the CelestialBody
	 * @return The radius in m
	 */
	float get_radius() const;

	/**
	 * @brief Get the desnity of the CelestialBody
	 * @return The density in kg / m^3
	 */
	float get_density() const;

	/**
	 * @brief Set the density of the CelestialBody
	 * @param density The density in kg / m^3
	 */
	void set_density(const float density);

private: /* PRIVATE VARS */
	float	density,
			radius,
			volume;

	sf::CircleShape shape;
};