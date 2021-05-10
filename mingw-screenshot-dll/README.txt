### 1: 生成Screencapture.dll
## cmake -B build

```
cl /c /D _WIN32 /I ../include/  ../src/win/*.cpp ../src/*.cpp ../test/*.cpp 
link *.obj /machine:x64 /SUBSYSTEM:console /ENTRY:WinMainCRTStartup /OUT:screen.exe "kernel32.lib" "user32.lib" "shell32.lib"


//cl /nologo /Z7  /Zi /MT /W3 /GX /O2 /D /DEBUG   /I ../include/  ../src/win/*.cpp ../src/*.cpp ../test/*.cpp /SUBSYSTEM:console /ENTRY:WinMainCRTStartup /OUT:screen.exe "kernel32.lib" "user32.lib" "shell32.lib"
//link *.obj /DEBUG:NONE  /machine:x64 /SUBSYSTEM:console /ENTRY:WinMainCRTStartup /OUT:screen.exe "kernel32.lib" "user32.lib" "shell32.lib"


cl /c /D _WIN32 /I ../include/  ../src/win/*.cpp ../src/*.cpp ../interface/*.cpp 
```