# About

Some Realtek GPON ONT/ONU based on RTL960x SoC provides support to Huawei vendor-specific OMCI MEs but they are not enabled by default. This small and dumb lib replies implements the feature code (0x14) for this, enabling them. As simple as it gets.

Since no other code is used besides checking if the feature is on or off (registered or not), the feature's handler function is stubbed out.

A device with Huawei support should list the following *.so* in it's MIB library, usually located in **/lib/omci** devices's rootfs:

```
mib_Me350.so
mib_Me370.so
mib_Me373.so
```

If your device don't have these files, there is no support for HWTC specific stuff, so this lib is of **no use**. Maybe a 'Frankenstein' firmware can be made on these devices by copying the files over, but that hasn't been and won't be tested.

Also, *.so* for other vendor specific stuff are included in some devices, like "*mib_fh65\*.so*" for FiberHome stuff, as seen on D-Link DPN-101G. If they're working on not, unknown.

Information on unpacking and repacking firmware images are out of scope, hence not provided and should be sourced from somewhere else.

This lib has been tested and working successfully on ODI DFP-34X-2C2 (more info on [ODI DFP-34X-2C2](https://www.tripleoxygen.net/wiki/ont/odi/dfp-34x-2c2)). Additionally, the same type of modification has been done on V-SOL V2802RH, but as direct binary patches as it's a non-Linux device ([V-SOL V2802RH](https://www.tripleoxygen.net/wiki/ont/vsol/v2802rh)).

# Use

* Update your uClibc MIPS/Lexra GCC toolchain prefix in *Makefile*, if needed.
  * Tweaks on linked libraries or some GCC args may be needed too, this has been tested with a old GCC 5.4.0 toolchain only.
* Compile *.so* with
```
make
```
* Copy produced *.so* lib to your device's features folder, usually at **/lib/features**
```
cp libohwtc.so <rootfs>/lib/features/
```
* Repack your rootfs, firmware and flash to device.

Check if the Huawei entities was activated by running the following commands inside your device shell:
```
omcicli mib get 350
omcicli mib get 370
omcicli mib get 373
```
If any meaningful output is generated, they are active. Or, by running:
```
omcicli get tables
```
.. and you see entries with "ME{350,350,373}".

Sorry, no additional support for this code and/or its use is provided.