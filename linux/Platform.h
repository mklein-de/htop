/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Platform
#define HEADER_Platform
/*
htop - linux/Platform.h
(C) 2014 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Action.h"
#include "MainPanel.h"
#include "BatteryMeter.h"
#include "LinuxProcess.h"
#include "SignalsPanel.h"

#ifndef CLAMP
#define CLAMP(x,low,high) (((x)>(high))?(high):(((x)<(low))?(low):(x)))
#endif

extern ProcessField Platform_defaultFields[];

extern int Platform_numberOfFields;

extern const SignalItem Platform_signals[];

extern const unsigned int Platform_numberOfSignals;

void Platform_setBindings(Htop_Action* keys);

extern MeterClass* Platform_meterTypes[];

int Platform_getUptime();

void Platform_getLoadAverage(double* one, double* five, double* fifteen);

int Platform_getMaxPid();

double Platform_setCPUValues(Meter* this, int cpu);

void Platform_setMemoryValues(Meter* this);

void Platform_setSwapValues(Meter* this);

char* readProcFile(const char* procname);

char* Platform_getProcessEnv(pid_t pid);

char* Platform_getProcessArgs(pid_t pid);

#endif
