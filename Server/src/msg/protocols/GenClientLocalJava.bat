chcp 65001
@echo off

if "%1"=="" (
for %%f in (protocols_client\*.proto) do	call protoc.exe --proto_path=protocols_client --java_out=..\..\app_sandbox\project_android\app_sandbox\src\main\java %%f) else (
call protoc.exe --proto_path=protocols_client --java_out=..\..\app_sandbox\project_android\app_sandbox\src\main\java %1
)

@echo "finish build......"
pause
