// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef _AVIDUMP_H
#define _AVIDUMP_H

#ifdef _WIN32
#include <windows.h>
#else
#include <stdint.h>
#endif

class AVIDump
{
	private:
		static bool CreateFile();
		static void CloseFile();
		static void SetBitmapFormat();
		static bool SetCompressionOptions();
		static bool SetVideoFormat();

		static void AddSoundInternal (const short *data, int nsamp);

		static void StoreFrame (const void *data);
		static void *GetFrame (void);

	public:
#ifdef _WIN32
		static bool Start(HWND hWnd, int w, int h);
		static void AddFrame(char *data);
		static void AddSound(const short *data, int nsamp, int rate);
		static void AddSoundBE(const short *data, int nsamp, int rate);
#else
		static bool Start(int w, int h);
		static void AddFrame(uint8_t *data, int width, int height);
#endif
		static void Stop();
};

#endif // _AVIDUMP_H
