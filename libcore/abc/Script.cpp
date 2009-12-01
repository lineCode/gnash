// 
//   Copyright (C) 2007, 2008, 2009 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "Script.h"
#include "as_object.h"
#include "ClassHierarchy.h"
#include "VM.h"
#include "namedStrings.h"
#include "as_value.h"
#include "Namespace.h"
#include "Global_as.h"
#include "as_class.h"

#ifdef ENABLE_AVM2
#include "Method.h"
#include "abc_function.h"
#endif

namespace gnash {
namespace abc {

#ifdef ENABLE_AVM2    
bool
Script::addValue(string_table::key name, Namespace *ns,
        boost::uint32_t slotId, Script *type, as_value& val, bool isconst,
        bool isstatic)
{
    Global_as* g = VM::get().getGlobal();

    if (val.is_object()) {
		val.to_object(*g)->set_member(NSV::INTERNAL_TYPE, 
			std::size_t(type->getName()));
    }

	string_table::key nsname = ns ? ns->getURI() : string_table::key(0);

	int flags = PropFlags::dontDelete;
	if (isconst)
		flags |= PropFlags::readOnly;
	if (isstatic)
		flags |= PropFlags::staticProp;

	if(slotId == 0){
		_prototype->init_member(name, val, flags, nsname);
	}
	else{
		_prototype->init_member(name, val, flags, nsname, slotId);
	}
	return true;
}

void
Script::initPrototype()
{
    Global_as& gl = *VM::get().getGlobal();
    _prototype = new as_class(gl);
}

bool
Script::addMemberScript(string_table::key name, Namespace *ns,
	boost::uint32_t slotId, Script *type, bool isstatic)
{
	return addSlot(name, ns, slotId, type, isstatic);
}

bool
Script::addSlotFunction(string_table::key name, Namespace *ns,
	boost::uint32_t slotId, Method *method, bool isstatic)
{
	Script a;
	a.setName(NSV::CLASS_FUNCTION);
	as_value b(method->getPrototype());
	return addValue(name, ns, slotId, &a, b, false, isstatic);
}

bool
Script::addSlot(string_table::key name, Namespace* ns,
        boost::uint32_t slotId, Script* /*type*/, bool /*isstatic*/)
{
	string_table::key nsname = ns ? ns->getURI() : 0;

	//TODO: Set flags.
	if (slotId == 0) {
		_prototype->init_member(name, as_value(), 0, nsname);
	}
	else {
		_prototype->reserveSlot(ObjectURI(name, nsname), slotId);
	}
	return true;
}

    bool
Script::addMethod(string_table::key name, Namespace* /*ns*/,
        Method* method, bool /*isstatic*/)
{
	as_value val = new abc::abc_function(method,
            getVM(*_prototype).getMachine());
	_prototype->init_member(name, val);
	return true;
}


bool
Script::addGetter(string_table::key name, Namespace *ns, Method *method,
	bool isstatic)
{
	string_table::key nsname = ns ? ns->getURI() : string_table::key(0);

	Property *getset = _prototype->getOwnProperty(name, nsname);

	if (getset)
		getset->setGetter(method->getPrototype());
	else
	{
		int flags = PropFlags::dontDelete | PropFlags::dontEnum;
		if (isstatic)
			flags |= PropFlags::staticProp;
		_prototype->init_property(name, *method->getPrototype(), 
			*method->getPrototype(), flags, nsname);
	}
	return true;
}

bool
Script::addSetter(string_table::key name, Namespace *ns, Method *method,
	bool isstatic)
{
	string_table::key nsname = ns ? ns->getURI() : string_table::key(0);

	Property *getset = _prototype->getOwnProperty(name, nsname);

	if (getset)
		getset->setSetter(method->getPrototype());
	else
	{
		int flags = PropFlags::dontDelete | PropFlags::dontEnum;
		if (isstatic)
			flags |= PropFlags::staticProp;
		_prototype->init_property(name, *method->getPrototype(), 
			*method->getPrototype(), flags, nsname);
	}
	return true;
}

#if 0 // TODO
void
Script::buildFromPrototype(as_object *o, string_table::key name,
	ClassHierarchy *pCH)
{
	setName(name);
	PropertyList *pList = &o->_members;
	PropertyList::iterator i = pList->begin();

	for ( ; i != pList->end(); ++i)
	{
		Property *pProp = i->second;
		fprintf(stderr, "Evaluating property %s.\n", STV(i->first));
		if (pProp->isDestructive())
		{
			fprintf(stderr, "%s is destructive.\n", STV(i->first));
		}
		if (pProp->isGetterSetter())
		{
			fprintf(stderr, "%s is a getset.\n", STV(i->first));
		}
		if (pProp->isReadOnly())
		{
			fprintf(stderr, "%s is read only.\n", STV(i->first));
		}
	}
}

bool
Script::addValue(string_table::key name, Namespace *ns, boost::uint32_t slotId,
	Script *type, as_value& val, bool isconst, bool isstatic,
	ClassHierarchy *CH)
{
	asBoundValue *bv = CH->newBoundValue();
	bv->setType(type);
	bv->setValue(val);
	if (!isstatic)
		return addBinding(name, asBinding(ns, bv, slotId, isconst, isstatic));
	return addStaticBinding(name, asBinding(ns, bv, slotId, isconst, isstatic));
}

bool
Script::addSlot(string_table::key name, Namespace *ns, boost::uint32_t slotId,
	Script *type, bool isstatic, ClassHierarchy *CH)
{
	asBoundValue *bv = CH->newBoundValue();
	bv->setType(type);
	if (!isstatic)
		return addBinding(name, asBinding(ns, bv, slotId, isstatic));
	return addStaticBinding(name, asBinding(ns, bv, slotId, isstatic));
}

bool
Script::addMethod(string_table::key name, Namespace *ns, Method *method,
	bool isstatic)
{
	if (!isstatic)
		return addBinding(name, asBinding(ns, method, isstatic));
	else
		return addStaticBinding(name, asBinding(ns, method, isstatic));
}

bool
Script::addMemberScript(string_table::key name, Namespace *ns,
	boost::uint32_t slotId, Script *type, bool isstatic)
{
	if (!isstatic)
		return addBinding(name, asBinding(ns, type, slotId, isstatic));
	return addStaticBinding(name, asBinding(ns, type, slotId, isstatic));
}

// TODO: Figure out how this differs from addMethod
bool
Script::addSlotFunction(string_table::key name, Namespace *ns,
	boost::uint32_t slotId, Method *method, bool isstatic)
{
	if (!isstatic)
		return addBinding(name, asBinding(ns, method, slotId, isstatic));
	return addStaticBinding(name, asBinding(ns, method, slotId, isstatic));
}
#endif 

#endif

} // namespace abc 
} // namespace gnash 