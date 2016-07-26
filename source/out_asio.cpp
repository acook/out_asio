
/*
** out_asio - ASIO output for WINAMP5
**
** 2006/10/4 Written by Otachan
** http://otachan.com/
*/

#define	STRICT

#include <windows.h>
#include <process.h>

#include "out_asio.h"
#include "Config.h"
#include "pcmasio.h"

extern HINSTANCE	WSLhInstance;

extern AsioDrivers*	asioDrivers;

Out_Module	mod =
{
	OUT_VER,
	NAME,
	0x7e4ede2f,
	NULL,
	NULL,
	Config,
	About,
	Init,
	Quit,
	Open,
	Close,
	Write,
	CanWrite,
	IsPlaying,
	Pause,
	SetVolume,
	SetPan,
	Flush,
	GetOutputTime,
	GetWrittenTime,
};

PARAM_GLOBAL	ParamGlobal;

PcmAsio*	pPcmAsio;

HHOOK	hHook;

HANDLE	hThread;
HANDLE	EventReadyThread;
HANDLE	EventDestroyThread;

bool	PlayEOF;

extern "C"
{
	__declspec(dllexport) Out_Module* __cdecl
	winampGetOutModule(void)
	{
		return &mod;
	}
}

LRESULT CALLBACK
HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode == HC_ACTION) {
		const PMSG	pMsg = reinterpret_cast<PMSG>(lParam);

		if((pMsg->hwnd == mod.hMainWindow) && (pMsg->message == WM_WA_MPEG_EOF)) PlayEOF = true;
	}

	return ::CallNextHookEx(NULL, nCode, wParam, lParam);
}

unsigned int __stdcall
ThreadProc(void* /*Param*/)
{
	MSG		Msg;

	::PeekMessage(&Msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	asioDrivers = new AsioDrivers;
	pPcmAsio = new PcmAsio;

	::SetEvent(EventReadyThread);

	while(_WaitForSingleObjectEx(EventDestroyThread) != WAIT_OBJECT_0);

	delete pPcmAsio;
	delete asioDrivers;

	_endthreadex(0);

	return 0;
}

void CALLBACK
ApcProc(ULONG_PTR dwParam)
{
	ParamMsg* const	Param = reinterpret_cast<ParamMsg*>(dwParam);

	switch(Param->Msg) {
	case MSG_OPEN:
		Param->RetMsg = pPcmAsio->MsgOpen(Param->Param1, Param->Param2, Param->Param3);
		break;
	case MSG_CLOSE:
		pPcmAsio->MsgClose();
		break;
	case MSG_WRITE:
		Param->RetMsg = pPcmAsio->MsgWrite(Param->Param1, Param->Buff);
		break;
	case MSG_CAN_WRITE:
		Param->RetMsg = pPcmAsio->MsgCanWrite();
		break;
	case MSG_IS_PLAYING:
		Param->RetMsg = pPcmAsio->MsgIsPlaying();
		break;
	case MSG_PAUSE:
		Param->RetMsg = pPcmAsio->MsgPause(Param->Param1);
		break;
	case MSG_FLUSH:
		pPcmAsio->MsgFlush(Param->Param1);
		break;
//	case MSG_GET_OUTPUTTIME:
//		Param->RetMsg = pPcmAsio->MsgGetOutputTime();
//		break;
//	case MSG_GET_WRITTENTIME:
//		Param->RetMsg = pPcmAsio->MsgGetWrittenTime();
//		break;
	}

	Param->UnPause();
}

ParamMsg::ParamMsg(const int _Msg)
{
	Msg = _Msg;
}

ParamMsg::ParamMsg(const int _Msg, const int _Param1)
{
	Msg = _Msg;
	Param1 = _Param1;
}

ParamMsg::ParamMsg(const int _Msg, const int _Param1, const int _Param2, const int _Param3)
{
	Msg = _Msg;
	Param1 = _Param1;
	Param2 = _Param2;
	Param3 = _Param3;
}

ParamMsg::ParamMsg(const int _Msg, const int _Param1, unsigned char* _Buff)
{
	Msg = _Msg;
	Param1 = _Param1;
	Buff = _Buff;
}

ParamMsg::~ParamMsg(void)
{
}

int
ParamMsg::Call(void)
{
	EventWaitThread = ::CreateEvent(NULL, false, false, NULL);

	::QueueUserAPC(&ApcProc, hThread, reinterpret_cast<ULONG_PTR>(this));
	::WaitForSingleObject(EventWaitThread, INFINITE);

	::CloseHandle(EventWaitThread);

	return RetMsg;
}

void
ParamMsg::UnPause(void)
{
	::SetEvent(EventWaitThread);
}

void
ReadProfile(void)
{
	char	FileName[MAX_PATHLEN];

	::GetModuleFileName(mod.hDllInstance, FileName, sizeof FileName);
	CutPathFileName(FileName, ParamGlobal.IniFileName, sizeof ParamGlobal.IniFileName);
	strcat_s(ParamGlobal.IniFileName, sizeof ParamGlobal.IniFileName, "plugin.ini");

	ParamGlobal.Device =
		::GetPrivateProfileInt(INI_NAME, "Device", 0, ParamGlobal.IniFileName);
	ParamGlobal.ThreadPriority =
		::GetPrivateProfileInt(INI_NAME, "ThreadPriority", 3, ParamGlobal.IniFileName);
	ParamGlobal.BufferSize =
		::GetPrivateProfileInt(INI_NAME, "BufferSize", 7, ParamGlobal.IniFileName);
	ParamGlobal.ShiftChannels =
		::GetPrivateProfileInt(INI_NAME, "ShiftChannels", 0, ParamGlobal.IniFileName);
	ParamGlobal.GaplessMode =
		::GetPrivateProfileInt(INI_NAME, "GaplessMode", 0, ParamGlobal.IniFileName) != 0;
	ParamGlobal.Convert1chTo2ch =
		::GetPrivateProfileInt(INI_NAME, "Convert1chTo2ch", 1, ParamGlobal.IniFileName) != 0;
	ParamGlobal.DirectInputMonitor =
		::GetPrivateProfileInt(INI_NAME, "DirectInputMonitor", 0, ParamGlobal.IniFileName) != 0;
	ParamGlobal.Resampling_Enable =
		::GetPrivateProfileInt(INI_NAME, "Resampling_Enable", 0, ParamGlobal.IniFileName) != 0;
	ParamGlobal.Resampling_ThreadPriority =
		::GetPrivateProfileInt(INI_NAME, "Resampling_ThreadPriority", 2, ParamGlobal.IniFileName);
	ParamGlobal.Resampling_SampleRate =
		::GetPrivateProfileInt(INI_NAME, "Resampling_SampleRate", 88200, ParamGlobal.IniFileName);
	ParamGlobal.Resampling_Quality =
		::GetPrivateProfileInt(INI_NAME, "Resampling_Quality", 3, ParamGlobal.IniFileName);
}

void
WriteProfile(void)
{
	char str[32];

	_itoa_s(ParamGlobal.Device, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Device", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.ThreadPriority, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "ThreadPriority", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.BufferSize, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "BufferSize", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.ShiftChannels, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "ShiftChannels", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.GaplessMode, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "GaplessMode", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.Convert1chTo2ch, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Convert1chTo2ch", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.DirectInputMonitor, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "DirectInputMonitor", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.Resampling_Enable, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Resampling_Enable", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.Resampling_ThreadPriority, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Resampling_ThreadPriority", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.Resampling_SampleRate, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Resampling_SampleRate", str, ParamGlobal.IniFileName);

	_itoa_s(ParamGlobal.Resampling_Quality, str, sizeof str, 10);
	WritePrivateProfileString(INI_NAME, "Resampling_Quality", str, ParamGlobal.IniFileName);
}

void __cdecl
Config(HWND hwndParent)
{
	DialogOption(hwndParent).Execute();
}

void __cdecl
About(HWND hwndParent)
{
	::MessageBox(
			hwndParent,
			NAME "\n\n"
			"Copyright (C) 2002-2006 Otachan\n"
			"http://otachan.com/\n\n"
			"ASIO Technology by Steinberg.",
			"About",
			MB_ICONINFORMATION);
}

void __cdecl
Init(void)
{
	WSLhInstance = mod.hDllInstance;

	hHook = NULL;

	EventDestroyThread = ::CreateEvent(NULL, false, false, NULL);
	EventReadyThread = ::CreateEvent(NULL, false, false, NULL);

	unsigned int	dwThread;

	hThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, ThreadProc, NULL, 0, &dwThread));

	::WaitForSingleObject(EventReadyThread, INFINITE);

	::CloseHandle(EventReadyThread);

	ReadProfile();
}

void __cdecl
Quit(void)
{
	if(hHook) ::UnhookWindowsHookEx(hHook);

	WriteProfile();

	::SetEvent(EventDestroyThread);

	if(::WaitForSingleObject(hThread, 5000) != WAIT_OBJECT_0) {
		if(::TerminateThread(hThread, 0)) {
			::WaitForSingleObject(hThread, 3000);
		}
	}

	::CloseHandle(hThread);
	::CloseHandle(EventDestroyThread);
}

int __cdecl
Open(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms)
{
	PlayEOF = false;

	if(hHook == NULL) hHook = ::SetWindowsHookEx(WH_GETMESSAGE, HookProc, NULL, ::GetCurrentThreadId());

	return ParamMsg(MSG_OPEN, samplerate, bitspersamp, numchannels).Call();
}

void __cdecl
Close(void)
{
	ParamMsg(MSG_CLOSE).Call();
}

int __cdecl
Write(char *buf, int len)
{
	return ParamMsg(MSG_WRITE, len, reinterpret_cast<unsigned char*>(buf)).Call();
}

int __cdecl
CanWrite(void)
{
	return ParamMsg(MSG_CAN_WRITE).Call();
}

int __cdecl
IsPlaying(void)
{
	return ParamMsg(MSG_IS_PLAYING).Call();
}

int __cdecl
Pause(int pause)
{
	return ParamMsg(MSG_PAUSE, pause).Call();
}

void __cdecl
SetVolume(int volume)
{
}

void __cdecl
SetPan(int pan)
{
}

void __cdecl
Flush(int t)
{
	ParamMsg(MSG_FLUSH, t).Call();
}

int __cdecl
GetOutputTime(void)
{
	return pPcmAsio->MsgGetOutputTime();
}

int __cdecl
GetWrittenTime(void)
{
	return pPcmAsio->MsgGetWrittenTime();
}

