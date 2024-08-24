
set ROOT_DIR=%~dp0
set ROOT_DIR=%ROOT_DIR:~0,-1%

set UE_ROOT_DIR=C:\UE_5.4
set UBT_EXE=%UE_ROOT_DIR%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe
set ProjectPath=%ROOT_DIR%\ReignOfConquest.uproject

"%UBT_EXE%" -projectfiles -progress -project="%ProjectPath%"