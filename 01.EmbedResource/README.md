
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [1.1. Generate C header file from a binary resource](#generate)
    * [1.2. Reference `box.osgt.h`](#reference)
    * [1.3. Provide `box_osgt` as `std::istream`](#stream)
    * [1.4. Load the model from `std::istream`](#load)
* [Result](#result)

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

Generated [`box.osgt.h`][model-header] file looks like this:

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

* `unsigned char box_osgt[]`, an array of raw bytes
* `unsigned int box_osgt_len`, size of the array

Both variables start with `box_osgt`, which is derived from `box.osgt` filename.

<a name="reference"/>

## 1.2. Reference `box.osgt.h`

First, reference `box.osgt.h`([source code][model-reference]):
```
#include "box.osgt.h"
```

Second, make sure `CMakeLists.txt` includes the directory with `box.osgt.h` ([source code][data-cmake]):
```
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/data)
```

<a name="stream"/>

## 1.3. Provide `box_osgt` as `std::istream`

In order to let OpenSceneGraph access the data from a C array, we have to
represent it as `std::istream`.

To simplify resource management in code, we introduce two classes:

* [Resource][Resource] to hold generated contents
* [ResourceStreamBuffer][ResourceStreamBuffer] to provide C array contents as `std::streambuf`, which can be converted to `std::istream`

**Note**: `ResourceStreamBuffer::seekoff()` implementation is crucial for
OpenSceneGraph plugins to correctly load resources.

<a name="load"/>

## 1.4. Load the model from `std::istream`

First, create `Resource` instance to work with ([source code][model-resource]):
```
resource::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
```

Second, load the model. To load the model from `std::istream`, we:

* find a reader that is capable of reading the model (such a reader can be located by providing file extension)
* let the reader create a node with the model

Here's how the crucial part of the implementation looks like ([source code][node-resource]):

```
- - - -
auto reader = osgDB::Registry::instance()->getReaderWriterForExtension(extension);
if (reader)
{
    ResourceStreamBuffer buf(box);
    std::istream in(&buf);
    auto result = reader->readNode(in, 0);
    if (result.success())
    {
        node = result.getNode();
    }
- - - -
```

Third, reference plugin capable of loading `.osgt` ([source code][plugin-reference]):

```
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
```

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[model-header]: ../data/box.osgt.h
[model-reference]: desktop/src/main.h#L43
[data-cmake]: CMakeLists.txt#L19
[Resource]: desktop/src/resource.h#L55
[ResourceStreamBuffer]: desktop/src/resource.h#L77
[model-resource]: desktop/src/main.h#L232
[node-resource]: desktop/src/resource.h#L123
[plugin-reference]: desktop/src/main.h#L66
[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/01/ex01-embed-resource.html
