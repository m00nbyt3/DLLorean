# DLLorean
A tool for automatizing the DLL Proxying. Just specify the original DLL and your payload, and you are done.

## How-to-use
1. Compile it using GCC (or use precompiled binary "DLLorean"): 
```
gcc main.c
```
2. Enjoy :))
```
Usage: ./DLLorean [options ...]

SUPPORT INSTRUCTIONS:
-h,   --help                            Shows this help text
-gp,  --get-payload                     Generates a .c file containing basic payload info

PROXYING INSTRUCTIONS: (all of them must be passed)
-d <DLL file name (.dll)>               Specifies the original DLL file name
-p <Payload file name (.c)>             Specifies the payload file name

EXAMPLE OF USAGE:
./DLLorean -d my_dll_file.dll -p my_payload_file.c

ATTENTION:
Its important that the DLL file is located IN THE SAME DIRECTORY as the binary ("DLLorean" file)
```

## Video POC
[![IMAGE ALT TEXT](http://img.youtube.com/vi/2EM6zr990QQ/0.jpg)](https://www.youtube.com/watch?v=2EM6zr990QQ "DLLorean, a DLL Proxying tool (POC)")
