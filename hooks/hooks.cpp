#include "hooks.h"
#include <string>

tWriteProcessMemory oWriteProcessMemory = NULL;
tVirtualAllocEx oVirtualAllocEx = NULL;

static INT g_imgCount = 0;
static INT g_vAllocSuffix = 0;

LPVOID
WINAPI
hkVirtualAllocEx(
    _In_ HANDLE hProcess,
    _In_opt_ LPVOID lpAddress,
    _In_ SIZE_T dwSize,
    _In_ DWORD flAllocationType,
    _In_ DWORD flProtect
)
{
    g_vAllocSuffix++;
    printf( "\r\nVirtualAllocEx ( 0x%p, 0x%p, 0x%i, 0x%i, 0x%i )\r\n\r\n", hProcess, ( PVOID ) &lpAddress, dwSize, flAllocationType, flProtect);

    return oVirtualAllocEx( hProcess, lpAddress, dwSize, flAllocationType, flProtect );
}

BOOL
WINAPI
hkWriteProcessMemory( HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesWritten )
{
    char const *mzString;

    if ( ( ( char* ) lpBuffer )[ 0 ] == 0x4D && ( ( char* ) lpBuffer )[ 1 ] == 0x5A )
  //if ( ( ( DWORD* ) lpBuffer )[ 0 ] == 0x4D5A )
        mzString = "<- MZ Sig Found";
    else
        mzString = "None";

    printf( "WriteProcessMemory ( 0x%p, 0x%p, 0x%p, 0x%d, 0x%p ) %s \r\n", hProcess, ( PVOID ) &lpBaseAddress, ( PVOID ) &lpBuffer, nSize, ( PVOID ) &lpNumberOfBytesWritten, mzString );

    g_imgCount++;

    char buf[ 512 ];
    HANDLE hFile;
    DWORD dwBytes;

    sprintf_s( buf, "Dumps\\fileDumped-%i-[VirtualAllocEx]_%i.bin", g_imgCount, g_vAllocSuffix );
    hFile = CreateFileA( buf, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, 0, 0 );
    

    if ( hFile == INVALID_HANDLE_VALUE )
        printf("\n\r[NoobDumper] ERROR:\r\n CreateFileA: %i ( %d )\r\n\r\n", 0, GetLastError( ) );


    BOOL bSuccess = WriteFile( hFile, lpBuffer, nSize, &dwBytes, 0 );
    if ( !bSuccess )
        printf("\r\n[NoobDumper] ERROR:\r\n WriteFile: %i ( %d )\r\n\r\n", bSuccess, GetLastError( ) );

    CloseHandle( hFile );

    
    printf( "[NoobDumper] File dump saved to %s\r\n", buf );


	return oWriteProcessMemory( hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten );
}