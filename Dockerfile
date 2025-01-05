FROM ghcr.io/wiiu-env/devkitppc:20240704

COPY --from=ghcr.io/wiiu-env/wiiupluginsystem:20240505 /artifacts $DEVKITPRO
COPY --from=ghcr.io/wiiu-env/wiiumodulesystem:20240424/ /artifacts $DEVKITPRO
COPY --from=ghcr.io/wiiu-env/libkernel:20230621 /artifacts $DEVKITPRO

WORKDIR project
