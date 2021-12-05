#include "hooks.h"


DWORD
WINAPI
Initialization( LPVOID )
{
    
    HMODULE krnl32;
    PCHAR pcAddress;
    PCHAR pcAddress2;

    HMODULE ntdll;
    PCHAR krnlAddress;

    krnl32 = GetModuleHandleA( "kernel32" );
    ntdll = GetModuleHandleA( "ntdll.dll" );

    if ( krnl32 && ntdll )
    {
        krnlAddress = ( PCHAR ) GetProcAddress( ntdll, "NtWriteVirtualMemory" );

        pcAddress = ( PCHAR ) GetProcAddress( krnl32, "WriteProcessMemory" );
        pcAddress2 = ( PCHAR ) GetProcAddress( krnl32, "VirtualAllocEx" );
    }  
    else
    {
        MessageBoxA( 0, "Couldn't get kernel32 or ntdll module handle!", "Error", 0 );
        //if you actually wanna see which one is missing
        //fucking debug, I won't just add more junk than that
        return FALSE;
    }
        

    if ( !pcAddress )
    {
        MessageBoxA( 0, "Couldn't get WriteProcessMemory address!", "Error", 0 );
        return FALSE;
    }
    if ( !pcAddress2 )
    {
        MessageBoxA( 0, "Couldn't get VirtualAllocEx address!", "Error", 0 );
        return FALSE;
    }

    if ( MH_Initialize( ) != MH_OK )
    {
        MessageBoxA( 0, "Something went wrong while initializating minhook.", "Error", 0 );
        return FALSE;
    }

    /*if ( MH_CreateHook( pcAddress, &hkWriteProcessMemory, ( LPVOID* ) &oWriteProcessMemory ) != MH_OK )
    {
        MessageBoxA( 0, "Something went wrong while creating the hook!", "Error", 0 );
        return FALSE;
    }*/

    if ( MH_CreateHook( krnlAddress, &hkNtWriteVirtualMemory, ( LPVOID* ) &oNtWriteVirtualMemory ) != MH_OK )
    {
        MessageBoxA( 0, "Something went wrong while creating the hook x3!", "Error", 0 );
        return FALSE;
    }

    if ( MH_CreateHook( pcAddress2, &hkVirtualAllocEx, ( LPVOID* ) &oVirtualAllocEx ) != MH_OK )
    {
        MessageBoxA( 0, "Something went wrong while creating the hook x2!", "Error", 0 );
        return FALSE;
    }
    


    if ( MH_EnableHook( MH_ALL_HOOKS ) != MH_OK )
    {
        MessageBoxA( 0, "Something went wrong while enabling the hook!", "Error", 0 );
        return FALSE;
    }

    printf( "\n\r[NoobDumper] Dumper has been initialized, next time it finds a process write, it will start dumping.\r\n");

    CreateDirectoryA( "Dumps", 0 );

    while ( 1 ) Sleep(0xFFFFFF);
    return TRUE;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    BOOL bConsole = TRUE; //your choice
    BOOL bLogConsole = FALSE; //enabling will disable the console output.

    if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        if ( bConsole )
        {
            FILE* fTemp;
            AllocConsole( );

            if ( bLogConsole )
                freopen_s( &fTemp, "logs.log", "w", stdout );
            else
                freopen_s( &fTemp, "CONOUT$", "w", stdout );

        }

        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) Initialization, 0, 0, 0 );
    }
    return TRUE;
}

