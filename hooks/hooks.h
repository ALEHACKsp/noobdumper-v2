#pragma once
#include <Windows.h>
#include <time.h>

#include <tlhelp32.h>

#include <MinHook.h>
#pragma comment (lib, "minhook")

#include <stdio.h>


//Type definitions
//////////////////
typedef NTSTATUS( NTAPI* tNtWriteVirtualMemory )
( 
  HANDLE hProcess,
  PVOID pBaseAddress,
  PVOID pBuffer,
  ULONG uNumberOfBytesToWrite,
  PULONG puNumberOfBytesWritten
);

//typedef BOOL( WINAPI* tWriteProcessMemory )
//( 
//  HANDLE  hProcess,
//  LPVOID  lpBaseAddress,
//  LPVOID  lpBuffer,
//  DWORD   nSize,
//  LPDWORD lpNumberOfBytesWritten 
//);

typedef LPVOID( WINAPI* tVirtualAllocEx )
( 
  _In_ HANDLE hProcess,
  _In_opt_ LPVOID lpAddress,
  _In_ SIZE_T dwSize,
  _In_ DWORD flAllocationType,
  _In_ DWORD flProtect
);



//Functions
///////////

NTSTATUS
NTAPI
hkNtWriteVirtualMemory
(
	HANDLE hProcess,
	PVOID pBaseAddress,
	PVOID pBuffer,
	ULONG uNumberOfBytesToWrite,
	PULONG puNumberOfBytesWritten
);

//BOOL
//WINAPI
//hkWriteProcessMemory
//( 
//  HANDLE,
//  LPVOID,
//  LPVOID,
//  DWORD,
//  LPDWORD
//);

LPVOID
WINAPI
hkVirtualAllocEx
(
  _In_ HANDLE hProcess,
  _In_opt_ LPVOID lpAddress,
  _In_ SIZE_T dwSize,
  _In_ DWORD flAllocationType,
  _In_ DWORD flProtect
);



//extern definitions
////////////////////
// 
//extern tWriteProcessMemory oWriteProcessMemory;
extern tVirtualAllocEx oVirtualAllocEx;

extern tNtWriteVirtualMemory oNtWriteVirtualMemory;
