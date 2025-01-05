# overlayappbase-patch

Aroma plugin that patches the Wii U and HOME Menu to load the internal OverlayAppBase image layout rather than the default OverlayAppBase_EU layout for some versions

## building

This project requires:
- [devkitPro](https://devkitpro.org)
- [wut](https://github.com/devkitPro/wut)
- [WUPS](https://github.com/wiiu-env/WiiUPluginSystem)
- [WUMS](https://github.com/wiiu-env/WiiUModuleSystem)
- [libkernel](https://github.com/wiiu-env/libkernel)

Make sure to clone the project recursively since the [libwupsxx](https://github.com/dkosmari/libwupsxx) submodule is used:

``git clone --recursive https://github.com/primaviera/overlayappbase-patch``

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
