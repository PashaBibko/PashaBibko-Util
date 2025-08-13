# PashaBibko-Util

PashaBibko-Util is a C++ util library that I developed for use in my projects.
It is cross platform and supports both Windows and Linux based systems.
Some of the main features include coloured text in the console, logging/better console printing
and lightweight implementations of STD classes for easier use and faster builds.

NOTE: This project is not fully documented. All of the functions and classes within the latest release
will be documentated but if you are using the latest push from Github some sections may be undocumented.
The documentation for the language can be found [here](https://pashabibko.github.io/PashaBibko-Util/).

### Adding to your project

The library is built with CMake and is designed to be used as a git submodule.
If you are unfamilar with git-submodules is recommended to learn about them
before intergrating them with your project which can be done [here](https://github.blog/open-source/git/working-with-submodules/). 

To add the project to your project run this in the powershell of the root directory:
```powershell
cd path/to/your/project/root
mkdir external
mkdir external/pb-util
git submodule add "https://github.com/PashaBibko/PashaBibko-Util.git" external/pb-util
```

Then to add it to your build process of your CMakeLists.txt file add:
```CMake
target_link_libraries(PROJECT PUBLIC PashaBibko-UTIL)
target_include_directories(PROJECT ${CMAKE_ROOT}/external/pb-util)
```

Finally you should be able to use Util library within your project by adding
(it is recommended to do this within a precompiled header): `#include <Util.h>`

### Getting started

To use any of the functions/classes within your project you can find them under the
"PashaBibko::Util" namespace. As the namespace is quite long shorthands are provided:
- PBU for PashaBibko::Util
- PB for PashaBibko

Example uses of some of the classes and functions can be found within the examples/ subdir
or can be seen [here](https://github.com/PashaBibko/PashaBibko-Util/blob/main/example/ExampleUse.cpp)
on the Github repository.
