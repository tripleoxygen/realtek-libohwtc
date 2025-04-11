# About

Some Realtek GPON ONT/ONU based on RTL960x SoC provides support to Huawei vendor-specific OMCI MEs but they are not enabled by default. The lack of these MEs may prevent the ONT/ONU to work with Huawei OLTs (provided the configuration is valid, it should still authenticate and reach O5 status, however). This small and dumb lib implements the needed feature code (0x14) for enabling them. As simple as it gets.

Since no other code is used besides checking if the feature is on or off (registered or not), the feature's handler function is stubbed out.

A device firmware with Huawei support - enabled or not - should list the following *.so* in it's MIB library, usually located in **/lib/omci** within device's rootfs:

```
mib_Me350.so
mib_Me370.so
mib_Me373.so
```

If these files are not available, there is no support for HWTC specific stuff, so this lib is of **no use**. Maybe a 'Frankenstein' firmware can be made on these by copying the files over from another image containing them, but that hasn't and won't be tested. Refer to [Wiki / GPON - OMCI MIB](https://www.tripleoxygen.net/wiki/misc/gpon/omci-mib#privados) for more information on these and other vendor-specific MEs.

Also, in some devices, libraries (*.so*) for other vendor-specific MEs seems to be included, like "*mib_fh65\*.so*" for FiberHome (fh) stuff (seen on D-Link DPN-101G). If they're working/enabled or not, unknown.

Tools and information on unpacking and repacking firmware images to include this lib are out of scope, hence should be sourced from somewhere else.

This lib has been tested and working successfully on ODI DFP-34X-2C2 (more info on [ODI DFP-34X-2C2](https://www.tripleoxygen.net/wiki/ont/odi/dfp-34x-2c2)). Additionally, the same type of modification was done successfully on older versions of V-SOL V2802RH's firmware, but as direct binary patches on it's OS since it's not a Linux device ([V-SOL V2802RH](https://www.tripleoxygen.net/wiki/ont/vsol/v2802rh)). They were enabled by the manufacturer on the latest version.

# Use

* Update your uClibc MIPS/Lexra GCC toolchain prefix in *Makefile* if needed.
  * Tweaks on linked libraries or some GCC args may be needed. This has been tested with an old GCC 5.4.0 toolchain only.
* Compile *.so* with:
```
make
```
* With an unpacked rootfs copy of your device's firmware, copy the produced *libohwtc.so* file to features folder, usually at **/lib/features**
```
cp libohwtc.so <rootfs-path>/lib/features/
```
* Repack your rootfs, rebuild the firmware and flash to the device.

Check if the Huawei entities were activated by running the following commands inside your device's shell:
```
omcicli mib get 350
omcicli mib get 370
omcicli mib get 373
```
If any seemly meaningful output is generated, they have been activated. Or, by running:
```
omcicli get tables
```
.. and you see entries with "ME{350,350,373}".
* Now your device should be able to work with Huawei OLTs.

# Notes

* Having these MEs enabled shouldn't interfere when using the device on GPON links handled by non-Huawei OLTs.
* Supposedly, the *emulated/faked* ONT/ONU should also be an Huawei one.
* This was a quick hack so no support for this code or it's use is provided.
* All linked Wiki pages are in brazilian portuguese only. Please use a translator if needed.
