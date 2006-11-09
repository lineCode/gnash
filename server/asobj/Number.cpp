// 
//   Copyright (C) 2005, 2006 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

// 
//
//

/* $Id: Number.cpp,v 1.6 2006/11/09 21:15:42 strk Exp $ */

// Implementation of ActionScript Number class.

#include "tu_config.h"
#include "Number.h"
#include "smart_ptr.h"
#include "fn_call.h"
#include "as_object.h" // for inheritance
#include "builtin_function.h" // need builtin_function

#include <sstream>

namespace gnash {

// Forward declarations
//static void number_to_string(const fn_call& fn);

static void
attachNumberInterface(as_object& /*o*/)
{
	// FIXME: add Number interface here:
	// Number.MAX_VALUE
	// Number.MIN_VALUE
	// Number.NaN
	// Number.NEGATIVE_INFINITY
	// Number.POSITIVE_INFINITY
	// Number.toString()
	// Number.valueOf()
}

static as_object*
getNumberInterface()
{
	static smart_ptr<as_object> o=NULL;
	if ( o == NULL )
	{
		o = new as_object();
		attachNumberInterface(*o);
	}
	return o.get_ptr();
}

// FIXME: add some useful methods :)
class number_as_object : public as_object
{
	// the number value
	double _val;

	// string representation of the above number
	mutable char _str[256];

public:

	number_as_object(double val=0.0)
		:
		as_object(getNumberInterface()),
		_val(val)
	{
		sprintf(_str, "%g", _val);
	}

	// override from as_object
	const char* get_text_value() const
	{
		return _str;
	}

	// override from as_object
	double get_numeric_value() const
	{
		return _val;
	}

};


static void
number_ctor(const fn_call& fn)
{
	double val = 0;
	if (fn.nargs > 0)
	{
		val = fn.arg(0).to_number();
	}

	number_as_object* obj = new number_as_object(val);
	
	fn.result->set_as_object(obj); // will keep alive
}

// extern (used by Global.cpp)
void number_class_init(as_object& global)
{
	// This is going to be the global Number "class"/"function"
	static smart_ptr<builtin_function> cl=NULL;

	if ( cl == NULL )
	{
		cl=new builtin_function(&number_ctor, getNumberInterface());
		// replicate all interface to class, to be able to access
		// all methods as static functions
		attachNumberInterface(*cl);
		     
	}

	// Register _global.Number
	global.set_member("Number", cl.get_ptr());

}

std::auto_ptr<as_object>
init_number_instance(double val)
{
	return std::auto_ptr<as_object>(new number_as_object(val));
}
  
} // namespace gnash
