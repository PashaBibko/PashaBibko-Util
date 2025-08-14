# PashaBibko-Util

PashaBibko-Util is a C++ util library that I developed for use in my projects.
It is cross platform and supports both Windows and Linux based systems.
Some of the main features include coloured text in the console, logging/better console printing
and lightweight implementations of STD classes for easier use and faster builds. The documentation
for the library can be found [here](https://pashabibko.github.io/PashaBibko-Util/index.html).

### Adding to your project

##### CMake

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

##### Pre-built binaries

If you would like to use a pre-built binary of the project and link manually
to your project you can find them [here](https://github.com/PashaBibko/PashaBibko-Util/releases).
Prebuilt binaries are only available for windows.

To add to your project you will need to add the PB-UTIL.lib to your linker
dependencies. In VS-22 you can find this in [Linker->Input->Additional Dependencies].
You will also need to add the root of the project to the include paths as
all paths are relative to it. In VS-22 you can find this in
[C/C++->General->Additional Include Directories].

##### Build manually

If you would like to link to your project but still build the project you can
run the build.bat file located within the scripts folder. This will require you
to have CMake, Ninja and a C++ compiler available on your machine.

### Getting started

To use any of the functions/classes within your project you can find them under the
"PashaBibko::Util" namespace. As the namespace is quite long shorthands are provided:
- PBU for PashaBibko::Util
- PB for PashaBibko

Example uses of some of the classes and functions can be found within the examples/ subdir
or can be seen [here](https://github.com/PashaBibko/PashaBibko-Util/blob/main/example/ExampleUse.cpp)
on the Github repository.
