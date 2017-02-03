// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MONOLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MONOLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MONOLIB_EXPORTS
#define MONOLIB_API __declspec(dllexport)
#else
#define MONOLIB_API __declspec(dllimport)
#endif

// This class is exported from the MonoLib.dll
class MONOLIB_API CMonoLib {
public:
	CMonoLib(void);
	// TODO: add your methods here.
};

extern MONOLIB_API int nMonoLib;

MONOLIB_API int fnMonoLib(void);
