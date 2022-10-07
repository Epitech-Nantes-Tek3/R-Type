mkdir build
cd build

echo "Build Folder created"

conan install .. --build=missing  -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cd ..
cmake -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build -j

echo "Compilation Done"

copy .\Debug\r-type_client.exe .
copy .\Debug\r-type_server.exe .

echo "Executables created"