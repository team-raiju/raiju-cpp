bash scripts/cube.sh

mkdir -p build
/usr/sbin/cmake --no-warn-unused-cli                           \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE                  \
    -DCMAKE_BUILD_TYPE:STRING=Debug                            \
    -DCMAKE_C_COMPILER:FILEPATH=/bin/arm-none-eabi-gcc-11.2.0  \
    -S ${PWD}                                                  \
    -B ${PWD}/build                                            \
    -G Ninja

/usr/sbin/cmake --build build --config Debug --target all -j 8
