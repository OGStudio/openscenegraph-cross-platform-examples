
Table of contents =================

* [Overview](#overview)
* [Steps](#steps)
    * [1.1. Generate C header file from a binary resource](#generate)
    * [1.2. Reference the generated C header file](#reference)
    * [1.3. Load a node from the resource](#?)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we embed `box.osgt` model (a binary resource) into application.
Embedding binary resources unifies data loading for platforms with different file
system requirements and constraints like desktop, Android, iOS, and web.

<a name="steps"/>

# Steps

<a name="generate"/>

## 1.1. Generate C header file from a binary resource

`xxd` can represent any binary file as `unsigned char[]`, a C array that you
can use as is in C/C++ applications.

Generate `box.osgt.h` C header from `box.osgt` model by running the following command:

`xxd -i box.osgt > box.osgt.h`

Generated [`box.osgt.h`][box.osgt.h] file looks like this:

```
unsigned char box_osgt[] = {
  0x23, 0x41, 0x73, 0x63, 0x69, 0x69, 0x20, 0x53, 0x63, 0x65, 0x6e, 0x65,
  0x0a, 0x23, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x39, 0x32,
  0x0a, 0x23, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x74, 0x6f, 0x72, 0x20,
  0x6f, 0x73, 0x67, 0x65, 0x78, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x30, 0x2e,
  0x31, 0x33, 0x2e, 0x30, 0x0a, 0x0a, 0x6f, 0x73, 0x67, 0x3a, 0x3a, 0x47,
  - - - - trimmed for brevity - - - -
  0x20, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x2e,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x20, 0x31, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a,
  0x20, 0x20, 0x7d, 0x0a, 0x7d, 0x0a
};
unsigned int box_osgt_len = 32058;

```

As you can see, `xxd` created two variables:

* `unsigned char box_osgt[]`, an array of raw bites
* `unsigned int box_osgt_len`, size of the array

Both variables start with `box_osgt`, which is derived from `box.osgt` filename.

<a name="reference"/>

# 1.2. Reference `box.osgt.h`

* Reference `box.osgt.h` by simply including it in the sources:
    ```
    #include "box.osgt.h"
    ```
    [Here's how desktop version does it][ref_res_src]
* Make sure CMakeLists.txt includes the directory with `box.osgt.h`:
    ```
    INCLUDE_DIRECTORIES(/path/to/the/directory)
    ```
    [Here's how desktop version does it][ref_res_cmake]


[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[box.osgt.h]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/data/box.osgt.h
[ref_res_src]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/01.EmbedResource/desktop/src/Example.h#L31
[ref_res_cmake]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/01.EmbedResource/desktop/CMakeLists.txt#L16

