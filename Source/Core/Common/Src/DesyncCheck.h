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

#ifndef _DECYNCCHECK_H_INCLUDED_
#define _DECYNCCHECK_H_INCLUDED_

#include "FileUtil.h"

#define DESYNCCHECK_ENABLE

#ifdef DESYNCCHECK_ENABLE
#	define DESYNCCHECK(x) DesyncCheck::Check((x))
#	define DESYNCCHECK_VOID(x, size) DesyncCheck::CheckVoid((x), (size))
#else
#	define DESYNCCHECK(_x) ((void)0)
#	define DESYNCCHECK_VOID(_x, _y) ((void)0)
#endif

namespace DesyncCheck
{
	extern bool g_enable;
	extern bool g_is_write;
	extern File::IOFile g_file;
	
	bool IsEnable ();
	bool IsWrite ();

	void StateSaveLoadCheck (bool is_save);

	void Start (bool is_write);
	void End ();

	void Error ();
	void Ok ();

	void CheckVoid (const void* const p, size_t size);

	template <typename T>
	void Check(const T& x, size_t size = sizeof T) {
		CheckVoid(&x, size);
	}

};	//namespace 


#endif
