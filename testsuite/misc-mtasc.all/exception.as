// exception.as - MTASC testcase for try/catch 
//
//   Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//
// Original author: Asger Ottar Alstrup <asger@area9.dk>
//

#include "check.as"

// This movie tests exceptions

class Test 
{

	// constructor
	function Test()
	{
		note("Test constructor called");
	}

	function test_all()
	{
		var res;
		try {
			throw(1);
			res = 0;
		} catch (e) {
			res = e;
		}

		xcheck_equals(res, 1);
	}

	static function main(mc)
	{
		var myTest = new Test;
		myTest.test_all();

                Dejagnu.done();
	}

}
