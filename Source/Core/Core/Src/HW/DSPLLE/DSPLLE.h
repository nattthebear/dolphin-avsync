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

#ifndef _DSPLLE_H
#define _DSPLLE_H

#include "Thread.h"
#include "SoundStream.h"
#include "DSPLLEGlobals.h" // Local
#include "../../DSPEmulator.h"

class DSPLLE : public DSPEmulator {
public:
	DSPLLE();

	virtual bool Initialize(void *hWnd, bool bWii, bool bDSPThread);
	virtual void Shutdown();
	virtual bool IsLLE() { return true; }

	virtual void DoState(PointerWrap &p);
	virtual void PauseAndLock(bool doLock, bool unpauseOnUnlock=true);

	virtual void DSP_WriteMailBoxHigh(bool _CPUMailbox, unsigned short);
	virtual void DSP_WriteMailBoxLow(bool _CPUMailbox, unsigned short);
	virtual unsigned short DSP_ReadMailBoxHigh(bool _CPUMailbox);
	virtual unsigned short DSP_ReadMailBoxLow(bool _CPUMailbox);
	virtual unsigned short DSP_ReadControlRegister();
	virtual unsigned short DSP_WriteControlRegister(unsigned short);
	virtual void DSP_SendAIBuffer(unsigned int address, unsigned int num_samples);
	virtual const short *DSP_PeekAIBuffer (unsigned int address, unsigned int num_samples);
	virtual void DSP_Update(int cycles);
	virtual void DSP_StopSoundStream();
	virtual void DSP_ClearAudioBuffer(bool mute);

private:
	static void dsp_thread(DSPLLE* lpParameter);
	void InitMixer();

	std::thread m_hDSPThread;
	std::mutex m_csDSPThreadActive;
	bool m_InitMixer;
	void *m_hWnd;
	bool m_bWii;
	bool m_bDSPThread;
	bool m_bIsRunning;
	volatile u32 m_cycle_count;
};

#endif  // _DSPLLE_H
