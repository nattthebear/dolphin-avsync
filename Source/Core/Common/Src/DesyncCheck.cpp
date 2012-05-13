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

#include "DesyncCheck.h"
#include "Common.h"
#include <memory>
#include <cstdio>

namespace DesyncCheck
{
	const char* const g_tmp_file_name = "desynccheck.bin";

	bool g_enable = false;
	bool g_is_write;
	File::IOFile g_file;
	
	bool IsEnable () { return g_enable; }
	bool IsWrite () { return g_is_write; }

	void StateSaveLoadCheck (bool is_save)
	{
		static bool first_load_flag = true;
		if (first_load_flag)
			first_load_flag = false;
		else
			Start(is_save);
	}

	void Start (bool is_write)
	{
		if (g_enable)
			End();
		g_is_write = is_write;
		if (is_write)
		{
			g_file.Open(g_tmp_file_name, "wb");
		}
		else
		{
			g_file.Open(g_tmp_file_name, "rb");
		}
		g_enable = true;
	}

	void End ()
	{
		g_enable = false;
		g_file.Close();
	}
	
#if _MSC_VER
	__declspec(noinline)
#endif
	void Error()
	{
		NOTICE_LOG(COMMON, "DesyncCheck: Error (tell: 0x%x)", g_file.Tell());
		End();
	}

#if _MSC_VER
	__declspec(noinline)
#endif
	void Ok()
	{
		NOTICE_LOG(COMMON, "DesyncCheck: Ok");
		End();
	}

#ifdef _MSC_VER
	__declspec(noinline)
#endif
	void CheckVoid (const void* const p, size_t size)
	{
		if (g_enable)
		{
			if (g_is_write)
			{
				g_file.WriteBytes(p, size);
			}
			else
			{
				u8* tmp = new u8[size];
				if (g_file.ReadBytes(tmp, size))
				{
					if (std::memcmp(p, tmp, size) != 0)
					{
						Error();
					}
					delete[] tmp;
				}
				else
				{
					if (std::feof(g_file.GetHandle()))
					{
						Ok();
					}
					else
					{
						PanicAlert("DesyncCheck: File Error");
					}
				}
			}
		}
	}

};	//namespace
