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

#include "sfml.hpp"

namespace solui
{

// TYPES //

template<typename T>
struct Rect
{
	Rect():
		x(0), y(0),
		w(0), h(0) {}

	Rect(const T x, const T y, const T w, const T h):
		x(x), y(y),
		w(w), h(h) {}

	T x, y;
	T w, h;
};

using Recti = Rect<int>;
using Rectf = Rect<float>;

// GLOBAL VARIABLES //

/**
 * @brief The sf::RenderWindow solui will use to display UI
 */
inline sf::RenderWindow* window = nullptr;

/**
 * @brief The sf::Font solui will use to display text
 */
inline sf::Font font = sf::Font();

// FUNCTIONS //

/**
 * @brief Initialize solui
 * @param window The sf::RenderWindow solui will use
 * @param font The sf::Font solui will use
 */
bool init(sf::RenderWindow* window, const sf::Font font);

/**
 * @brief Draw a button on the screen and check if it has been pressed
 * @param text The text on the button
 * @param rect The solui::Rectf to use
 * @param color The font color
 * @param font_size The font size
 * @return True if the button was pressed, false if not
 */
bool button(const std::string text, const Rectf rect, const unsigned int font_size = 12);

}