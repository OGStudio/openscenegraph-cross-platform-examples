
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [6.1. Get to know Reporter](#reporter)
    * [6.2. Introduce Sequence](#sequence)
    * [6.3. Create a sequence of operations](#operations-sequence)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we create an asynchronous command sequence to combine
animations with other operations.

**Note**: this example requires [05.NodeSelection example][ex05] knowledge.

<a name="steps"/>

# Steps

<a name="reporter"/>

## 6.1. Get to know Reporter

Previous examples used `Reporter` class, which was not explained before.
`Reporter` is at the core of asynchronous operations. `Reporter` is a simple
implementation of powerful [publish-subscribe pattern][pattern].

### 6.1.1. Theory

To make a class be able to report changes to any number of
listeners, the class has to have an instance of `Reporter`. Whenever the class
wants to report changes, the class should call `Reporter`'s `report()`
function.

The listening parties should subscribe to the instance
of `Reporter` with its `addCallback()` function.

### 6.1.2. Practice

Here's how we subscribe to be notified of each frame event
([source code][reporter-subscription]):

```
this->app->frameReporter.addCallback(
    [&] {
        this->rotateBox();
    },
    this->boxRotationCallbackName
);
```

And here's how the "main loop" drives `frameReporter` instance of `Reporter`
([source code][reporter-reporting]):

```
void frame()
{
    this->viewer->frame();
    this->frameReporter.report();
}
```

<a name="sequence"/>

## 6.2. Introduce Sequence

In order to have a sequence of asynchronous operations, we need
to combine asynchronous functions.

### 6.2.1. Asynchronous functions

From the point of view of `Sequence`, an asynchronous function is a function
that returns pointer to `Reporter` instance ([source code][async-func]):

```
core::Reporter *waitForBoxSelection()
{
    return &this->boxSelected;
}
```

### 6.2.2. Instant asynchronous functions

If you need to have a normal function call as part of `Sequence`, you should
use instant asynchronous functions, i.e., functions that return zero
`Reporter` instance ([source code][async-func-instant]):

```
core::Reporter *setBoxSelectionEnabled(bool state)
{
	- - - -
    return 0;
}
```

<a name="operations-sequence"/>

## 6.3. Create a sequence of operations

Let's perform the following upon the box selection:

* disable selection
* dim background
* rotate the box
* restore background
* enable selection

Here's how it translates into code ([source code][sequence-sample]):

```
this->sequence.setActions({
    CORE_SEQUENCE_ACTION(
        "enableBoxSelection",
        this->setBoxSelectionEnabled(true)
    ),
    CORE_SEQUENCE_ACTION(
        "waitForBoxSelection",
        this->waitForBoxSelection()
    ),
    CORE_SEQUENCE_ACTION(
        "disableBoxSelection",
        this->setBoxSelectionEnabled(false)
    ),
    CORE_SEQUENCE_ACTION(
        "dimBackground",
        this->changeBackground(true)
    ),
    CORE_SEQUENCE_ACTION(
        "startBoxRotation",
        this->setBoxRotationEnabled(true)
    ),
    CORE_SEQUENCE_ACTION(
        "simulateLoading",
        this->simulateLoading()
    ),
    CORE_SEQUENCE_ACTION(
        "stopBoxRotation",
        this->setBoxRotationEnabled(false)
    ),
    CORE_SEQUENCE_ACTION(
        "lightBackground",
        this->changeBackground(false)
    ),
});

// Enable sequence.
this->sequence.isRepeatable = true;
this->sequence.setEnabled(true);
```

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[ex05]: ../05.NodeSelection
[pattern]: https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern
[reporter-subscription]: desktop/src/main.h#L471
[reporter-reporting]: desktop/src/main.h#L153
[async-func]: desktop/src/main.h#L454
[async-func-instant]: desktop/src/main.h#L441
[sequence-sample]: desktop/src/main.h#L388

[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/06/ex06-command-sequence.html
