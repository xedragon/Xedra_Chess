@echo off

for %%f in (protocols\*.proto) do (
	call protoc.exe --proto_path=protocols --cpp_out=.\cpp  --java_out=.\java  %%f

	protogen -i:%%f -o:csharp/%%~nf.cs

	echo %%f
)


pause