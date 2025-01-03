# GPUFUCKER

### About

This project manipulates DirectX calls because I thought it would be funny. Yes, I know, hilarious.

**IMPORTANT:** Please be extremely careful. I have no idea if this will break your system in any way.

**DO NOT** replace any system DLLs (like those in System32) with these files. I have not tested them, and doing so **may brick your Windows installation**.

Okay, now go have fun!

(Only 32 bit is supported atm, this is due to the original DirectX Wrappers repo not supporting it. I may add support soon...)

### Progress

- DirectX 1-7, DirectDraw, and Direct3D (ddraw.dll) --------- **NOT STARTED**
- DirectX 8, Direct3D (d3d8.dll) ------------------------------- **NOT STARTED**
- DirectX 9, Direct3D (d3d9.dll) ------------------------------- **STARTED** (Visible effects)

d3d9.dll has been tested on hl2 and gmod!!!

##### oh yeah this is a *MODIFIED* version of the repository "DirectX Wrappers" go check that out <3
##### its recommended to build for release as debug is VERY VERY slow....

Code in this project is taken from:
- [Jari Komppa's dxwrapper](https://github.com/jarikomppa/dxwrapper)
- [d3d8to9](https://github.com/crosire/d3d8to9)
- [Direct3D9 Wrapper DLL](https://gist.github.com/shaunlebron/3854bf4eec5bec297907)
- [DirectSoundControl](https://github.com/nRaecheR/DirectSoundControl)
- [XWA hooks](https://github.com/JeremyAnsel/xwa_hooks/tree/master/DInputLogger)

# How to build
Open the solution with visual studio 2022.
If it needs extra components, install them.
Then switch to release and right click on the solution and build.
TODO: make this more indepth
