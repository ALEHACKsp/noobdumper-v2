#pragma once
#include <Windows.h>
#include <time.h>


#include <MinHook.h>
#pragma comment (lib, "minhook")

#include <stdio.h>


typedef BOOL( WINAPI* tWriteProcessMemory )
( HANDLE  hProcess,
  LPVOID  lpBaseAddress,
  LPVOID  lpBuffer,
  DWORD   nSize,
  LPDWORD lpNumberOfBytesWritten );

typedef LPVOID(
    WINAPI*
    tVirtualAllocEx )(
    _In_ HANDLE hProcess,
    _In_opt_ LPVOID lpAddress,
    _In_ SIZE_T dwSize,
    _In_ DWORD flAllocationType,
    _In_ DWORD flProtect
    );



BOOL
WINAPI
hkWriteProcessMemory( HANDLE, LPVOID, LPVOID, DWORD, LPDWORD );

LPVOID
WINAPI
hkVirtualAllocEx(
    _In_ HANDLE hProcess,
    _In_opt_ LPVOID lpAddress,
    _In_ SIZE_T dwSize,
    _In_ DWORD flAllocationType,
    _In_ DWORD flProtect
);


extern tWriteProcessMemory oWriteProcessMemory;
extern tVirtualAllocEx oVirtualAllocEx;


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"