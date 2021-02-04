chcp 65001
@echo off

set workingDir=%~dp0

if "%1"=="" (
for %%f in (protocols\*.proto) do	call protoc.exe --proto_path=protocols --cpp_out=..\source\msg %%f) else (
call protoc.exe --proto_path=protocols --cpp_out=..\source\msg %1
)

echo "LF -> CRLF Start Convert ..."
cd ../source/msg
for /R . %%G in (*.cc *.h) do ( 
%workingDir%/../../../../bin/unix2dos.exe %%G
)
echo "LF -> CRLF End Convert ..."

@echo "finish build......"
pause
