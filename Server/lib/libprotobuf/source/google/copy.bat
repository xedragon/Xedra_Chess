@echo off

Set sourcedir=D:\CppWorkSpace\ProtocolBuffer\protobuf\src\google\


for %%f in (protobuf\compiler\*) do (
	rem echo %sourcedir%%%f
	copy %sourcedir%%%f %%f
	echo %%f
)
for %%f in (protobuf\io\*) do (
	rem echo %sourcedir%%%f
	copy %sourcedir%%%f %%f
	echo %%f
)
for %%f in (protobuf\stubs\*) do (
	rem echo %sourcedir%%%f
	copy %sourcedir%%%f %%f
	echo %%f
)
for %%f in (protobuf\*) do (
	rem echo %sourcedir%%%f
	copy %sourcedir%%%f %%f
	echo %%f
)

pause