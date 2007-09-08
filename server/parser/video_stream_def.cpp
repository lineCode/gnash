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
// $Id: video_stream_def.cpp,v 1.14 2007/09/08 11:19:50 strk Exp $

#include "video_stream_def.h"
#include "video_stream_instance.h"
#include "render.h"

#ifdef USE_FFMPEG
#include "embedVideoDecoderFfmpeg.h"
#elif defined(SOUND_GST)
#include "embedVideoDecoderGst.h"
#endif

namespace gnash {

video_stream_definition::video_stream_definition(uint16_t char_id)
	:
	m_char_id(char_id)
{
}


video_stream_definition::~video_stream_definition()
{
	for (int32_t size = m_video_frames.size()-1; size >= 0; size--) {
		delete m_video_frames[size];
	}
	m_video_frames.clear();
}


void
video_stream_definition::read(stream* in, SWF::tag_type tag, movie_definition* m)
{

	// Character ID has been read already, and was loaded in the constructor

	assert(tag == SWF::DEFINEVIDEOSTREAM ||	tag == SWF::VIDEOFRAME);

	if (tag == SWF::DEFINEVIDEOSTREAM)
	{
		m_start_frame = m->get_loading_frame();

		m_num_frames = in->read_u16();

		uint16_t width = in->read_u16();
		uint16_t height = in->read_u16();
		m_bound.enclose_point(0, 0);
		m_bound.expand_to_point(PIXELS_TO_TWIPS(width), PIXELS_TO_TWIPS(height));

		m_reserved_flags = in->read_uint(5);
		m_deblocking_flags = in->read_uint(2);
		m_smoothing_flags = in->read_bit(); 

		m_codec_id = in->read_u8();

	}
	else if (tag == SWF::VIDEOFRAME)
	{
		// TODO: do *not* skip the frame number !
		//       The SWF may not contain a video frame for
		//       each SWF frame, in which case we make a mess
		//
		in->skip_bytes(2); //int frameNum = in->read_u16();

		// We need to make the buffer a bit bigger than the data
		// to avoid libavcodec (ffmpeg) making illegal reads.
		// The reason is a bit sketchy, but it seems that the h263
		// decoder (perhaps other decoders as well) assumes that the
		// buffer with the data is bigger than the data it contains.
		// We make the buffer 4 bytes bigger than the data, and set
		// them to 0.

		// The data size is 4 bytes smaller than this, but because of 
		// what is mentioned above we don't subtract the 4 bytes.
		int size = in->get_tag_length();
		uint8_t* data = new uint8_t[size];
		memset(data, 0, size);
		for (int i = 0; i < size-4; i++) // The size-variable 4 bytes bigger than the data
		{
			data[i] = in->read_u8();
		}
		m_video_frames.push_back(data);
		m_video_frames_size.push_back(size);

	}

}


character*
video_stream_definition::create_character_instance(character* parent, int id)
{
	character* ch = new video_stream_instance(this, parent, id);
	return ch;
}

std::auto_ptr<embedVideoDecoder>
video_stream_definition::get_decoder()
{

	std::auto_ptr<embedVideoDecoder> decoder;

	if (m_num_frames == 0) return decoder;


#ifdef USE_FFMPEG
	decoder.reset( new embedVideoDecoderFfmpeg() );
#elif defined(SOUND_GST)
	decoder.reset( new embedVideoDecoderGst() );
#else
	decoder.reset( new embedVideoDecoder() );
#endif

	decoder->createDecoder(
				static_cast<int>(TWIPS_TO_PIXELS(m_bound.width())),// m_width,
				static_cast<int>(TWIPS_TO_PIXELS(m_bound.height())), // m_height,
				m_deblocking_flags,
				m_smoothing_flags,
				m_codec_id,
				gnash::render::videoFrameFormat());
	return decoder;

}

void 
video_stream_definition::get_frame_data(int frameNum, uint8_t** data, int* size)
{
	int cur_frame = frameNum - m_start_frame;
	if ( cur_frame < 0 || cur_frame >= m_video_frames.size() )
	{
		log_error(_("No video data available for frame %d."), frameNum);
		*data = 0;
		*size = 0;
		return;
	}

	assert( cur_frame < m_video_frames_size.size() );
	*size = m_video_frames_size[cur_frame];
	*data = m_video_frames[cur_frame];
}

} // namespace gnash

