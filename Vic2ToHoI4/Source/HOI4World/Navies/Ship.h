/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#ifndef SHIP_H_
#define SHIP_H_


#include <ostream>
#include <string>



namespace HoI4
{

class Ship
{
	public:
		Ship(
			const std::string& _name,
			const std::string& _type,
			const std::string& _equipment,
			const std::string& _owner
		);
		Ship() = delete;
		virtual ~Ship() = default;
		Ship(const Ship&) = default;
		Ship(Ship&&) = default;
		Ship& operator=(const Ship&) = default;
		Ship& operator=(Ship&&) = default;

	protected:
		std::string name;
		std::string type;
		std::string equipment;
		std::string owner;
};

}



#endif // SHIP_H_