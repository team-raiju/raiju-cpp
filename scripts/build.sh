bash scripts/cube.sh

mkdir -p build
/usr/sbin/cmake --build build --config Debug --target all -j 8
