# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we

* use `xxd` Unix utility to convert `box.osgt` model (a binary resource) into C header file
* use generated C header file across all platforms to load the model with OpenSceneGraph

**Note**: the example assumes you have already passed [OpenSceneGraph cross-platform guide][osgcpg].

# Generate C header file from a binary resource

Apart from `xxd`'s numerous uses, `xxd` can represent any binary file as `unsigned char[]`, an
array that you can use as is in C/C++ applications.

To generate `box.osgt.h` C header from `box.osgt` model, run the following command:

`xxd -i box.osgt > box.osgt.h`

Here's what generated C header file (`box.osgt.h`) looks like:

```
unsigned char box_osgt[] = {
  0x23, 0x41, 0x73, 0x63, 0x69, 0x69, 0x20, 0x53, 0x63, 0x65, 0x6e, 0x65,
  0x0a, 0x23, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x39, 0x32,
  0x0a, 0x23, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x74, 0x6f, 0x72, 0x20,
  0x6f, 0x73, 0x67, 0x65, 0x78, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x30, 0x2e,
  0x31, 0x33, 0x2e, 0x30, 0x0a, 0x0a, 0x6f, 0x73, 0x67, 0x3a, 0x3a, 0x47,
  - - - -
  0x20, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x2e,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x20, 0x31, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a,
  0x20, 0x20, 0x7d, 0x0a, 0x7d, 0x0a
};
unsigned int box_osgt_len = 32058;

```

As you noticed, `xxd` created two variables:
* `unsigned char box_osgt[]`, an array of raw bites
* `unsigned int box_osgt_len`, size of the array

Please, note that both variables start with `box_osgt`, this is derived from the original
file name given to `xxd` when we passed `box.osgt` model. The dot was replaced with an underscore.

# Reference `box.osgt.h` during building

The generated `box.osgt.h` file is located at `data/box.osgt.h`.
We should reference `data` directory in CMakeLists.txt with `INCLUDE_DIRECTORIES` command.

# Read `box.osgt.h` at run-time


[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide

