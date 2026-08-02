@echo off
setlocal
call "D:\vsstudio\VC\Auxiliary\Build\vcvars64.bat" || ( echo [ERROR] vcvars64.bat failed & exit /b 1 )
cmake -S "D:\furthre\qt\bookkeepings" -B "D:\furthre\qt\bookkeepings\cmake-build-release-visual-studio" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="D:\CLion 2026.1.4\bin\ninja\win\x64\ninja.exe" -DCMAKE_CXX_COMPILER="D:\vsstudio\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe" -DCMAKE_PREFIX_PATH=D:/qt/5.9.6/msvc2017_64 || ( echo [ERROR] CMake configure failed & exit /b 1 )
cmake --build "D:\furthre\qt\bookkeepings\cmake-build-release-visual-studio" || ( echo [ERROR] Build failed & exit /b 1 )
echo [OK] Build succeeded
