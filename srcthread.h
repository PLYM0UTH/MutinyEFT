#pragma once
#include <basetsd.h>
#include <functional>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <string>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <functional>
#include <thread>
#include "srrcThread.h"
#include "pgCollection.h"
#pragma comment(lib, "Psapi")
typedef enum {
	DummyThread = 0x1,
	SpawnThread = 0x2,
	InitScriptThread = 0x3,
	FishThread = 0x4,
	TestScriptThread = 0x5,
} ScriptThread;

extern int AddScript(std::function<void(ScriptThread)>);
extern void DeleteScript(int);
extern void HookScripts();
void AttachScripthook();