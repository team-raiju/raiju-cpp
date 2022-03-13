FROM archlinux

RUN pacman -Syu --noconfirm && pacman -S --noconfirm \
    arm-none-eabi-binutils \
    arm-none-eabi-newlib \
    arm-none-eabi-gcc \
    ninja \
    cmake \
    zip \
    unzip \
    git \
    libsm \
    libxrender \
    libxfixes \
    libxtst \
    libxcursor \
    fontconfig \
    ttf-dejavu \
    xorg-server-xvfb \
    libxrandr \
    jdk11-openjdk \
    && pacman -Scc --noconfirm

WORKDIR /usr/share

RUN git clone https://github.com/STMicroelectronics/STM32CubeF1

WORKDIR /tmp

RUN mkdir st && cd st && \
    curl -O https://sw-center.st.com/packs/resource/library/stm32cube_mx_v650-lin.zip && \
    unzip stm32cube_mx_v650-lin.zip && \
    mv MX /opt/stm32cubemx && cd .. && rm -rf st
