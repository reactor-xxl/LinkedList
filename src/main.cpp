/*****************************************************************************
							   MIT License

Copyright (c) 2020	Jonathon Rogers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <iostream>
#include <iomanip>
#include "LinkedList_t.hpp"
#include <map>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;


int main()
{

	char c = 1;
	int i = 1;

	char *pc = &c;
	int *pi = &i;
	void *pv = &i;

	if ( pi == pv )
	{
		cout << "pointer comparisons between different types are meaningless." << endl;
	}

	LinkedList_t<int> ll;

	cout << ll.debug_dump_internals() << endl;

	for ( auto i = 0; i < 10; ++i )
		ll.push_back( i );

	cout << ll.debug_dump_values() << endl;
	cout << ll.debug_dump_internals() << endl;

	auto it = ll.find( 5 );
	ll.remove( it );

	it = ll.find( 3 );
	auto it2{ it };

	*it2 = -15;

	if ( it != it2 )
	{
		cout << "uh oh" << endl;
	}

	ll.insert_after( it2, 55 );
	ll.insert_after( it2, 66 );
	ll.insert_after( it2, 77 );
	ll.insert_after( ll.begin(), -100 );

	auto it_end = ll.end();

	try
	{
		*it_end = 57;
	}
	catch ( std::exception & e )
	{
		cout << e.what() << endl;
	}

	--it_end;

	cout << "it_end == " << *it_end << endl;


	cout << ll.debug_dump_values() << endl;
	cout << ll.debug_dump_internals() << endl;

	ll.pop_back();
	ll.pop_back();
	ll.pop_back();

	cout << ll.debug_dump_values() << endl;
	cout << ll.debug_dump_internals() << endl;

	cin.get();
	return 0;
}
