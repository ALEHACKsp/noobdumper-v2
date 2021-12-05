# NoobDumper v2
A (mostly dll) dumper for CS:GO cheat loaders that use manual map injection method

# Support server: https://discord.gg/hq2e3xPmEK
# How to use this
##### Inject the dumper into the loader ( x86 ).

1. Let the loader try to inject (manual map) the binary into the target process.
2. Watch how the binary is being exported.

# Changelog
##### 0.2: Switched from userland api (WriteProcessMemory -> NtWriteVirtualMemory) to kernel mode function. (Calling a userland function would automatically call the kernel mode one).

# Configuration
##### Variables ( dllmain.cpp - DllMain ).
1. bool
   - bConsole
     - true  - shows you the debug console
     - false - hides the debug console 
 
   - bLogConsole
     - true  - log the debug output to a file and not to the comnsole
     - false - don't log anything and let everything be as it was

# Tip
#### The second VirtualAllocEx (and the next WriteProcessMemory after it) is/are called just for loader' stub, it/they isn't/aren't useful on its/their own at all.
#### These last 2 files are not part of the binary as they are loader' stub!!!
![image](https://user-images.githubusercontent.com/68382500/144725498-c79a2d9e-da6e-44ba-911f-94105af5d449.png)


# Screenshots

![image](https://user-images.githubusercontent.com/68382500/144724541-0b7221b4-a81f-45d1-b94f-a9cae82d8d89.png)

Dump process:

![image](https://user-images.githubusercontent.com/68382500/144724914-d5e379b3-7196-47a4-8c2a-e95ed38c61f1.png)

File output:

![image](https://user-images.githubusercontent.com/68382500/144724941-ec1111b5-83a8-4fcb-9869-8e0f98fc188a.png)

