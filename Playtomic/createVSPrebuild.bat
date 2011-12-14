CLS
set vstudio="Microsoft Visual Studio 10.0"
set programFiles="Program Files (x86)"
set DEVENV_DIR=C:\%programFiles%\%vstudio%\Common7\IDE

set SOLUTION_DIR=Z:\Documents\gameapi-cpp\Playtomic
echo start build

rmdir /s /q prebuilt\vstudio


%DEVENV_DIR%\devenv.exe %SOLUTION_DIR%\Playtomic.sln /Build LibDebug /project "%SOLUTION_DIR%\Playtomic\Playtomic.vcxproj" /ProjectConfig Debug
%DEVENV_DIR%\devenv.exe %SOLUTION_DIR%\Playtomic.sln /Build LibRelease /project "%SOLUTION_DIR%\Playtomic\Playtomic.vcxproj" /ProjectConfig Release
%DEVENV_DIR%\devenv.exe %SOLUTION_DIR%\Playtomic.sln /Build DLLlDebug /project "%SOLUTION_DIR%\Playtomic\Playtomic.vcxproj" /ProjectConfig DllDebug
%DEVENV_DIR%\devenv.exe %SOLUTION_DIR%\Playtomic.sln /Build DLLRelease /project "%SOLUTION_DIR%\Playtomic\Playtomic.vcxproj" /ProjectConfig DLLRelease

md prebuilt\vstudio\include\CurlWrap
md prebuilt\vstudio\include\json\include
md prebuilt\vstudio\include\Playtomic
md prebuilt\vstudio\include\Tools
md prebuilt\vstudio\Lib\Debug
md prebuilt\vstudio\Lib\DebugDll
md prebuilt\vstudio\Lib\Release
md prebuilt\vstudio\Lib\ReleaseDll

copy Playtomic\*.h prebuilt\vstudio\include\Playtomic\
copy json\include\*.h prebuilt\vstudio\include\json\include
copy CurlWrap\*.h prebuilt\vstudio\include\CurlWrap
copy Tools\*.h prebuilt\vstudio\include\Tools

copy Debug\Playtomic.lib prebuilt\vstudio\Lib\Debug
copy DllDebug\Playtomic.lib prebuilt\vstudio\Lib\DebugDll
copy DllDebug\Playtomic.dll prebuilt\vstudio\Lib\DebugDll
copy DLLRelease\Playtomic.lib prebuilt\vstudio\Lib\ReleaseDll
copy DLLRelease\Playtomic.dll prebuilt\vstudio\Lib\ReleaseDll
copy Release\Playtomic.lib prebuilt\vstudio\Lib\Release



