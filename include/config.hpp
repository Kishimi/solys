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

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class Config
{
public: /* PUBLIC FUNCS */
	/**
	 * @brief Load a config file
	 * @param filename The filename of the file
	 * @return Returns false if there was an error, true if all went ok
	 */
	bool load(const std::string filename);

	/**
	 * @brief Read variables from sections of the config file
	 * @tparam T the return type
	 * @param sname The section name
	 * @param vname The variable name of the variable in the section
	 * @return The value of the variable or "null" if the variable doesn't exist
	 */
	template<typename T>
	T get_value(const std::string sname, const std::string vname) const;

private: /* PRIVATE TYPES */
	/**
	 * @brief aka Attribute, variable;
	 * 		Has an variable name and a value
	 */
	struct Var
	{
		std::string name;
		std::string value;
	};

	/**
	 * @brief A "section" has a name and stores a bunch of Config::Var
	 */
	struct Section
	{
		std::string name;
		std::vector<Var> vars;
	};

private: /* PRIVATE FUNCS */
	/**
	 * @brief Split a string at a delimiter into a std::vector of std:string
	 * @param str The string to be splitted
	 * @param delim The delimiter, aka where to split the str
	 * @return std::vector of std::string
	 */
	static std::vector<std::string> splitstr(const std::string str, const char delim);

	/**
	 * @brief Parse config file data into Sections and vars
	 * @param data The file content as string
	 * @return std::vector<Section>
	 */
	static std::vector<Section> parse(const std::string data);

private: /* PRIVATE VARS */
	std::vector<Section> sections;
};

template<typename T>
T Config::get_value(const std::string sname, const std::string vname) const
{
	throw "Unknown type!" + sname + ", " + vname;
	return T();
}