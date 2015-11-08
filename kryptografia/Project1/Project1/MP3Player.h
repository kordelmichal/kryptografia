#pragma once
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <mmreg.h>
#include <msacm.h>
#include <wmsdk.h>
#include <wincrypt.h>

#pragma comment(lib, "msacm32.lib") 
#pragma comment(lib, "wmvcore.lib") 
#pragma comment(lib, "winmm.lib") 
#pragma intrinsic(memset,memcpy,memcmp)

#ifdef _DEBUG
#define mp3Assert(function) assert((function) == 0)
#else
//#define mp3Assert(function) if ( (function) != 0 ) { MessageBoxA(NULL,"Error in [ " #function "]", "Error",MB_OK); ExitProcess(0); }
#define mp3Assert(function) (function)
#endif


class MP3Player {
private:
	HWAVEOUT hWaveOut;
	DWORD bufferLength;
	double durationInSecond;
	BYTE* soundBuffer;
public:
	HRESULT OpenFromFile(TCHAR* inputFileName);
	HRESULT OpenFromMemory(BYTE* mp3InputBuffer, DWORD mp3InputBufferSize);
	void Play();
	void __inline Close();
	double __inline GetDuration();
	double GetPosition();
};