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

#include <vector>
#include <cmath>

#include "sfml.hpp"

/**
 * @brief Interface class for GameObject's.
 * 		Every GameObject should inherit from this class.
 */
class GameObject
{
public:
	/* "SUB"-TYPES */
	enum class Type
	{
		celestial_body,
		unknown
	};

public: /* PUBLIC FUNCS */
	/**
	 * @brief Constructor to initialize a GameObject with a type
	 * @param type The type of the GameObject
	 */
	GameObject(const Type type);
	virtual ~GameObject() {};

	/* PUBLIC FUNCS */
	/**
	 * @brief Update the GameObject relative to time
	 * @param clock Sfml clock with delta time
	 */
	virtual void update(const sf::Clock& clock) = 0;

	/**
	 * @brief Draw GameObject to sf::RenderWindow
	 * @param window The sf::RenderWindow
	 */
	virtual void draw(sf::RenderWindow& window) = 0;

	/**
	 * @brief Get the GameObject's position
	 * @return The position
	 */
	sf::Vector2f get_pos() const;

	/**
	 * @brief Get the GameObject's velocity
	 * @return The velocity
	 */
	sf::Vector2f get_vel() const;

	/**
	 * @brief Set the GameObject's position
	 * @param pos The position
	 */
	void set_pos(const sf::Vector2f pos);

	/**
	 * @brief Set the GameObject's position
	 * @param p_x Position on x axis
	 * @param p_y Position on y axis
	 */
	void set_pos(const float p_x, const float p_y);

	/**
	 * @brief Set the GameObject's velocity
	 * @param pos The velocity
	 */
	void set_vel(const sf::Vector2f vel);

	/**
	 * @brief Set the GameObject's velocity
	 * @param v_x Velocity on x axis
	 * @param v_y Velocity on y axis
	 */
	void set_vel(const float v_x, const float v_y);

	/**
	 * @brief Get the GameObject's mass
	 * @return The mass in kg
	 */
	float get_mass() const;

	/**
	 * @brief Calculate the magnitude of a vector.
	 * 		||vec|| = sqrt(x * x + y * y);
	 * 
	 * @return the magnitude of the vector
	 */
	static float calc_magnitude(const sf::Vector2f vec);

	/**
	 * @brief Accelerate the GameObject; v = m * a
	 * @param a The acceleration to accelerate with in m/s^2
	 */
	void accelerate(const sf::Vector2f a);

	/**
	 * @brief Accelerate the GameObject; v = m * a
	 * @param a_x The acceleration on the x axis to accelerate with in m/s^2
	 * @param a_y The acceleration on the y axis to accelerate with in m/s^2
	 */
	void accelerate(const float a_x, const float a_y);

	/**
	 * @brief Calculate the acceleration from a force; a = F / m
	 * @param F the force in N
	 * @return Acceleration in m/s^2
	 */
	float calc_acceleration(const float F);

	/**
	 * @brief Calculate the perfect orbital velocity; v = sqrt((G * M) / r)
	 * @param G the gravitational constant in m^3 / (kg * s^2)
	 * @param obj The other planet
	 * @return The orbit velocity, in m/s
	 */
	float calc_orbital_velocity(const float G, const GameObject* const obj);

	/**
	 * @brief Calculate the perfect orbital velocity for infinite GameObject's; v = sqrt((G * (M_1 + M_2 + ... + M_n)) / r);
	 * 		The GameObject's should be in order, r will be the distance from objs[0] to this GameObject, else the result is wrong.
	 * @param G the gravitational constant in m^3 / (kg * s^2)
	 * @param objs All GameObject's the GameObject is orbiting
	 * @return The orbit velocity, in m/s
	 */
	float calc_orbital_velocity(const float G, const std::vector<GameObject*> objs);

	/**
	 * @brief Calculate the distance between two GameObject's, relative to this GameObject.
	 * 		s = sqrt(x * x - y * y);
	 * @param obj The other GameObject to calculate the distance to
	 * @return The distance to obj in m
	 */
	float calc_distance(const GameObject* const obj) const;

	/**
	 * @brief Calculate the squared distance between two GameObject's, relative to this GameObject.
	 * 		s = x * x - y * y;
	 * @param obj The other GameObject to calculate the distance to
	 * @return The distance to obj squared in m
	 */
	float calc_distance_sq(const GameObject* const obj) const;

	/**
	 * @brief Calculate the gravitation of two GameObject's; F = (G * M * m) / r^2
	 * @param G the gravitational constant in m^3 / (kg * s^2)
	 * @param obj the other GameObject 
	 * @return the gravitional force in N
	 */
	float calc_gravitation(const float G, const GameObject* const obj) const;

	/**
	 * @brief Calculate the angle between two GameObject's, relative to this GameObject.
	 * 		a = atan2(y, x) * 180 / pi
	 * @param obj The other GameObject
	 * @return the angle in deg
	 */
	float calc_angle(const GameObject* const obj) const;

	/**
	 * @brief Transform and angle to a vector
	 * @param angle The angle to be transformed
	 * @return An converted sf::Vector2f
	 */
	static sf::Vector2f calc_angle_to_vec(const float angle);

	/**
	 * @brief Compare this GameObject with another GameObject
	 * @param obj The other GameObject
	 * @return True if they are the same, false if not
	 */
	bool compare(const GameObject* const obj) const;

	/**
	 * @brief This is the GameObject type.
	 * 		It is used to cast a GameObject to a derived class of Base GameObject.
	 */
	const Type type;

protected: /* PROTECTED VARS */
	sf::Vector2f pos, vel;
	float mass;
};