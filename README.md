# overlayappbase-patch

## building

This project requires these toolchains and libraries installed:
- [devkitPro](https://devkitpro.org)
- [wut](https://github.com/devkitPro/wut)
- [WUPS](https://github.com/wiiu-env/WiiUPluginSystem)
- [WUMS](https://github.com/wiiu-env/WiiUModuleSystem)
- [libkernel](https://github.com/wiiu-env/libkernel)

After that, you can just use ``make``

## building with docker

Run this command to build the docker image:

```
docker build . -t overlayappbase-docker
```

And then run this command to compile the plugin:

```
docker run -it --rm -v ${PWD}:/project overlayappbase-docker make
```
