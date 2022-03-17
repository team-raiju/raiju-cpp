bash scripts/cube.sh

mkdir -p /workspaces/Raiju/build
/usr/sbin/cmake --build /workspaces/Raiju/build --config Debug --target all -j 8
