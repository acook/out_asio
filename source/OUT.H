#ifndef NULLSOFT_OUTH
#define NULLSOFT_OUTH
#include <windows.h>
#include <stddef.h>
// ids:
// waveout: 32
// gapless: 64
// xfade: 63
// disk: 33
// dsound: 38
// NULL: 65
// mm2: 69

#define OUT_VER 0x10

typedef struct 
{
	int version;				// module version (OUT_VER)
	char *description;			// description of module, with version string
	intptr_t id;						// module id. each input module gets its own. non-nullsoft modules should
								// be >= 65536. 

	HWND hMainWindow;			// winamp's main window (filled in by winamp)
	HINSTANCE hDllInstance;		// DLL instance handle (filled in by winamp)

	void (__cdecl *Config)(HWND hwndParent); // configuration dialog 
	void (__cdecl *About)(HWND hwndParent);  // about dialog

	void (__cdecl *Init)();				// called when loaded
	void (__cdecl *Quit)();				// called when unloaded

	int (__cdecl *Open)(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms); 
					// returns >=0 on success, <0 on failure

					// NOTENOTENOTE: bufferlenms and prebufferms are ignored in most if not all output plug-ins. 
					//    ... so don't expect the max latency returned to be what you asked for.
					// returns max latency in ms (0 for diskwriters, etc)
					// bufferlenms and prebufferms must be in ms. 0 to use defaults. 
					// prebufferms must be <= bufferlenms
					// pass bufferlenms==-666 to tell the output plugin that it's clock is going to be used to sync video
					//   out_ds turns off silence-eating when -666 is passed

	void (__cdecl *Close)();	// close the ol' output device.

	int (__cdecl *Write)(char *buf, int len);	
					// 0 on success. Len == bytes to write (<= 8192 always). buf is straight audio data. 
					// 1 returns not able to write (yet). Non-blocking, always.

	int (__cdecl *CanWrite)();	// returns number of bytes possible to write at a given time. 
						// Never will decrease unless you call Write (or Close, heh)

	int (__cdecl *IsPlaying)(); // non0 if output is still going or if data in buffers waiting to be
						// written (i.e. closing while IsPlaying() returns 1 would truncate the song

	int (__cdecl *Pause)(int pause); // returns previous pause state

	void (__cdecl *SetVolume)(int volume); // volume is 0-255
	void (__cdecl *SetPan)(int pan); // pan is -128 to 128

	void (__cdecl *Flush)(int t);	// flushes buffers and restarts output at time t (in ms) 
							// (used for seeking)

	int (__cdecl *GetOutputTime)(); // returns played time in MS
	int (__cdecl *GetWrittenTime)(); // returns time written in MS (used for synching up vis stuff)

} Out_Module;


#endif