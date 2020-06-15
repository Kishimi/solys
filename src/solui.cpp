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

#include "solui.hpp"

namespace solui
{

bool init(sf::RenderWindow* window, const sf::Font font)
{
	solui::window = window;
	solui::font = font;

	if (window == nullptr)
	{
		return false;
	}

	return true;
}

bool button(const std::string text, const Rectf rect, const unsigned int font_size)
{
	// set up the rect
	sf::RectangleShape r;
	r.setPosition(rect.x, rect.y);
	r.setSize(sf::Vector2f(rect.w, rect.h));

	// draw the text
	sf::Text t;
	t.setString(text);
	t.setFont(font);
	t.setCharacterSize(font_size);
	t.setOrigin(t.getGlobalBounds().width / 2.0f, t.getGlobalBounds().height / 2.0f);
	t.setPosition(rect.x + (rect.w / 2.0f), rect.y + (rect.h / 2.0f));
	t.setFillColor(sf::Color::White);

	// check if the mouse pointer is inside the rect
	const sf::Vector2i mpos = sf::Mouse::getPosition(*window);

	if (mpos.x >= (int)rect.x &&
		mpos.x <= (int)(rect.x + rect.w) &&
		mpos.y >= (int)rect.y &&
		mpos.y <= (int)(rect.y + rect.h))
	// mouse pointer is inside rect
	{
		r.setFillColor(sf::Color(40, 153, 130));
		window->draw(r);
		window->draw(t);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		// the button is being pressed
		{
			return true;
		}
	}
	// draw rect differently when mouse doesn't hover
	else
	{
		
		r.setFillColor(sf::Color(55, 196, 168));
		window->draw(r);
		window->draw(t);
	}

	return false;
}

}