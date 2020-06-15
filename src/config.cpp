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

#include "config.hpp"

#include <iostream>

bool Config::load(const std::string filename)
{
	std::ifstream file(filename);
	std::string data, line;

	if (!file.is_open())
	{
		// TODO: Error handling
		return false;
	}

	while (std::getline(file, line))
	{
		data += line + "\n";
	}

	sections = parse(data);

	if (sections.size() == 0)
	{
		return false;
	}

	return true;
}

template<>
std::string Config::get_value<std::string>(const std::string sname, const std::string vname) const
{
	bool found = false;
	Section sec;

	// find the section
	for (const auto& section : sections)
	{
		if (section.name == sname)
		{
			found = true;
			sec = section;
		}
	}

	if (!found)
	{
		return "null";
	}

	// find the variable
	for (const auto& var : sec.vars)
	{
		if (var.name == vname)
		{
			return var.value;
		}
	}

	return "null";
}

template<>
unsigned int Config::get_value<unsigned int>(const std::string sname, const std::string vname) const
{
	const std::string val = get_value<std::string>(sname, vname);

	try
	{
		return (unsigned int)std::stoi(val);
	}
	catch (...)
	{
		return 0;
	}
}

template<>
float Config::get_value<float>(const std::string sname, const std::string vname) const
{
	const std::string val = get_value<std::string>(sname, vname);

	try
	{
		return std::stof(val);
	}
	catch (...)
	{
		return 0.0f;
	}
}

template<>
bool Config::get_value<bool>(const std::string sname, const std::string vname) const
{
	const std::string val = get_value<std::string>(sname, vname);

	try
	{
		return (bool)std::stoi(val);
	}
	catch (...)
	{
		return 0;
	}
}

std::vector<std::string> Config::splitstr(const std::string str, const char delim)
{
	std::stringstream strstream(str);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(strstream, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

std::vector<Config::Section> Config::parse(const std::string data)
{
	std::string line;
	Section section;
	std::vector<Section> sections;

	// try to read one section per iteration
	for (std::size_t i = 0; i < data.size(); i++)
	{
		if (data[i] == '[')
		// new section begins
		{
			i++;
			while (data[i] != ']' && i < data.size())
			{
				section.name += data[i++];
			}

			while (data[i] != '\n')
			{
				i++;
			}

			// read the section variables
			while (data[i] != '-' && data[i + 1] != '-' && data[i + 2] != '-' && i < data.size())
			{
				line.clear();

				// read line by line
				while (data[i++] != ';')
				{
					line += data[i];
				}

				// check if the line ends with a '\n',
				// and if not return
				if (*(line.end() - 1) != ';')
				{
					return std::vector<Section>();
				}
				line.pop_back();

				// remove spaces, tabs and other whitespace characters
				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

				// split the variable into lvalue and rvalue
				std::vector<std::string> tokens = splitstr(line, '=');

				Var var;
				var.name = tokens[0]; // lvalue
				var.value = tokens[1]; // rvalue

				section.vars.push_back(var);
			}

			sections.push_back(section);

			// clean up
			section.name.clear();
			section.vars.clear();
		}
	}

	return sections;
}