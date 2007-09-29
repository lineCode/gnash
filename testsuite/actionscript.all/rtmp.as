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


rcsid='$Id: rtmp.as,v 1.8 2007/09/29 16:23:00 strk Exp $';

#include "dejagnu.as"
#include "utils.as"

note("Starting...");

client_nc = new NetConnection();
//client_nc.connect("rtmp://localhost/software/gnash/tests/1153948634.flv", "userx");
//client_nc.connect("rtmpt://localhost:8080/software/gnash/tests/1153948634.flv", "userx");
//client_nc.connect("rtmpt://localhost:8080/software/gnash/tests/");

var myStream = new NetStream(client_nc);
myStream.play("1153948634.flv");

var myVideo = new Video();
MyVideo.attachVideo(NewStream);

//client_nc.write("invite");     

note("Done...");
totals();
