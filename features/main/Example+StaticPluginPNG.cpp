FEATURE main.h/Impl
// Reference (statically) plugins to read `png` file.
// Apple platforms use ImageIO. All others use libpng.

#ifdef __APPLE__
    USE_OSGPLUGIN(imageio)
#else
    USE_OSGPLUGIN(png)
#endif
