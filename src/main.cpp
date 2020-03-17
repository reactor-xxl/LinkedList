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
#include "LinkedList_t.hpp"

using std::cout;
using std::cin;
using std::endl;


int main()
{

	LinkedList<int> ll;

	ll.push_front( 5 );
	ll.push_back( 5 );

	ll.front();
	ll.back();

	ll.pop_front();
	ll.pop_back();

	ll.sort( &cmp );


	auto it = ll.find( 17 );

	*it = 19;

	int value = -18;

	ll.insert_before( it, value );
	ll.insert_after( it, value );

	ll.remove( it );


	cin.get();
	return 0;
}

