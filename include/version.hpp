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

/**
 * SOLYS VERSION
 *		- With each update, the version number increases
 *		- Version post-info
 *			b = Bug fix
 *			f = Added a feature
 *			r = Removed a feature
 * 			c = Changed a feature
 *
 *	CHANGELOG
 *		V1.2fr-alpha:
 *			Removed my own gui "library"
 *			Added Dear ImGui library for gui
 *			New main menu bar
 *
 *		V1.1b-alpha:
 *			Fixed setFramerateLimit does not work
 *			Added install.sh script to automatically install solys
 *
 * 		V1.0-alpha:
 * 			The physics work
 * 			You can control the camera
 * 			You have a "menu"
 */ 

#pragma once

#include <string>

#define SOLYS_VERSION (std::string("1.2fr-alpha"))