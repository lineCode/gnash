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
// Linking Gnash statically or dynamically with other modules is making
// a combined work based on Gnash. Thus, the terms and conditions of
// the GNU General Public License cover the whole combination.
// 
// In addition, as a special exception, the copyright holders of Gnash give
// you permission to combine Gnash with free software programs or
// libraries that are released under the GNU LGPL and/or with Mozilla, 
// so long as the linking with Mozilla, or any variant of Mozilla, is
// through its standard plug-in interface. You may copy and distribute
// such a system following the terms of the GNU GPL for Gnash and the
// licenses of the other code concerned, provided that you include the
// source code of that other code when and as the GNU GPL requires
// distribution of source code. 
// 
// Note that people who make modified versions of Gnash are not obligated
// to grant this special exception for their modified versions; it is
// their choice whether to do so.  The GNU General Public License gives
// permission to release a modified version without this exception; this
// exception also makes it possible to release a modified version which
// carries forward this exception.
//
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "log.h"

//#include "Object.h"
#include "action.h" // when we've finished, Object.h will stay, action.h away
#include "Function.h"

namespace gnash {

bool
as_object::get_member(const tu_stringi& name, as_value* val)
{
	IF_VERBOSE_ACTION(
		log_msg("  get member: %s (at %p) for object %p\n", name.c_str(), val, this);
	);
	if (name == "__proto__")
	{
		if ( m_prototype == NULL ) log_msg("as_object %p has no prototype\n", this);
		val->set_as_object(m_prototype);
		return true;
	}
	else {
		as_member m;

		if (m_members.get(name, &m) == false)
		{
			IF_VERBOSE_ACTION(log_msg("  not found on first level\n"));
			if (m_prototype == NULL)
			{
				IF_VERBOSE_ACTION(log_msg("  no __proto__ (m_prototype) defined\n"));
				return false;
			}
			else
			{
				IF_VERBOSE_ACTION(log_msg("  checkin in __proto__ (m_prototype) %p\n",m_prototype));
				return m_prototype->get_member(name, val);
			}
		} else {
			IF_VERBOSE_ACTION(log_msg("  found on first level\n"));
			*val=m.get_member_value();
			return true;
		}
	}
	return true;
}

bool
as_object::get_member(const tu_stringi& name, as_member* member) const
{
	//printf("GET MEMBER: %s at %p for object %p\n", name.c_str(), member, this);
	assert(member != NULL);
	return m_members.get(name, member);
}

void
as_object::set_member(const tu_stringi& name, const as_value& val )
{
	//printf("SET MEMBER: %s at %p for object %p\n", name.c_str(), val.to_object(), this);
	if (name == "__proto__") 
	{
		if (m_prototype) m_prototype->drop_ref();
		m_prototype = val.to_object();
		if (m_prototype) m_prototype->add_ref();
	}
	else
	{
		stringi_hash<as_member>::const_iterator it = this->m_members.find(name);
		
		if ( it != this->m_members.end() ) {

			const as_prop_flags flags = (it->second).get_member_flags();

			// is the member read-only ?
			if (!flags.get_read_only()) {
				m_members[name] = as_member(val, flags);
			}

		} else {
			m_members[name] = as_member(val);
		}
	}
}

bool
as_object::set_member_flags(const tu_stringi& name, const int flags)
{
	as_member member;
	if (this->get_member(name, &member)) {
		as_prop_flags f = member.get_member_flags();
		f.set_flags(flags);
		member.set_member_flags(f);

		m_members[name] = member;

		return true;
	}

	return false;
}

void
as_object::clear()
{
	m_members.clear();
	if (m_prototype)
	{
		m_prototype->drop_ref();
		m_prototype = NULL;
	}
}

bool
as_object::instanceOf(function_as_object* ctor)
{
	as_object* proto=m_prototype;
	do {
		if ( proto == ctor->m_properties ) return true;
		proto = ctor->m_properties;
	} while (proto);

	return false;
}

} // end of gnash namespace

