chcp 65001
@echo off

if "%1"=="" (
for %%f in (protocols_client\*.proto) do	call protoc.exe --proto_path=protocols_client --cpp_out=..\source\msg %%f) else (
call protoc.exe --proto_path=protocols_client --cpp_out=..\source\msg %1
)

@echo "finish build......"
pause
