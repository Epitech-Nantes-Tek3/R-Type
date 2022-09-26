git submodule init
git submodule update
vcpkg/bootstrap-vcpkg.bat -disableMetrics && vcpkg/vcpkg install SFML && cmake -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build build