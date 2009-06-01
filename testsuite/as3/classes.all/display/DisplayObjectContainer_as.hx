// DisplayObjectContainer_as.hx:  ActionScript 3 "DisplayObjectContainer" class, for Gnash.
//
// Generated by gen-as3.sh on: 20090514 by "rob". Remove this
// after any hand editing loosing changes.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
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

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.display.DisplayObjectContainer;
import flash.display.Sprite;
import flash.geom.Point;
import flash.text.TextSnapshot;
import flash.display.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class DisplayObjectContainer_as {
    static function main() {
#if flash9
        var x1:DisplayObjectContainer = new Sprite();

        // Make sure we actually get a valid class        
        if (Std.is(x1, DisplayObjectContainer)) {
            DejaGnu.pass("DisplayObjectContainer class exists");
        } else {
            DejaGnu.fail("DisplayObjectContainer lass doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (Std.is(x1.mouseChildren, Bool)) {
	    DejaGnu.pass("DisplayObjectContainer::mouseChildren property exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::mouseChildren property doesn't exist");
	}
	if (Std.is(x1.numChildren, Int)) {
	    DejaGnu.pass("DisplayObjectContainer::numChildren property exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::numChildren property doesn't exist");
	}
	if (Std.is(x1.tabChildren, Bool)) {
	    DejaGnu.pass("DisplayObjectContainer::tabChildren property exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::tabChildren property doesn't exist");
	}
 	if (Std.is(x1.textSnapshot, TextSnapshot)) {
 	    DejaGnu.pass("DisplayObjectContainer::textSnapshot property exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::textSnapshot property doesn't exist");
 	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
 	if (Type.typeof(x1.addChild) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::addChild() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::addChild() method doesn't exist");
 	}
 	if (Type.typeof(x1.addChildAt) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::addChildAt() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::addChildAt() method doesn't exist");
 	}
// FIXME: this needs to be a point
 	if (Type.typeof(x1.areInaccessibleObjectsUnderPoint) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::areInaccessibleObjectsUnderPoint() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::areInaccessibleObjectsUnderPoint() method doesn't exist");
 	}
 	if (Type.typeof(x1.contains) == ValueType.TFunction) {
 	 	DejaGnu.pass("DisplayObjectContainer::contains() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::contains() method doesn't exist");
 	}
 	if (Type.typeof(x1.getChildAt) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::getChildAt() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::getChildAt() method doesn't exist");
 	}
 	if (Type.typeof(x1.getChildByName) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::getChildByName() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::getChildByName() method doesn't exist");
 	}
 	if (Type.typeof(x1.getChildIndex) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::getChildIndex() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::getChildIndex() method doesn't exist");
 	}
 	if (Type.typeof(x1.getObjectsUnderPoint) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::getObjectsUnderPoint() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::getObjectsUnderPoint() method doesn't exist");
 	}
  	if (Type.typeof(x1.removeChild) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::removeChild() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::removeChild() method doesn't exist");
 	}
 	if (Type.typeof(x1.removeChildAt) == ValueType.TFunction) {
 	    DejaGnu.pass("DisplayObjectContainer::removeChildAt() method exists");
 	} else {
 	    DejaGnu.fail("DisplayObjectContainer::removeChildAt() method doesn't exist");
 	}
	if (Type.typeof(x1.setChildIndex) == ValueType.TFunction) {
	    DejaGnu.pass("DisplayObjectContainer::setChildIndex() method exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::setChildIndex() method doesn't exist");
	}
	if (Type.typeof(x1.swapChildren) == ValueType.TFunction) {
	    DejaGnu.pass("DisplayObjectContainer::swapChildren() method exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::swapChildren() method doesn't exist");
	}
	if (Type.typeof(x1.swapChildrenAt) == ValueType.TFunction) {
	    DejaGnu.pass("DisplayObjectContainer::swapChildrenAt() method exists");
	} else {
	    DejaGnu.fail("DisplayObjectContainer::swapChildrenAt() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
#else
	DejaGnu.note("This class (DisplayObjectContainer) is only available in flash9");
#end
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

