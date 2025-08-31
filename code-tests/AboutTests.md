### About

The tests for this library are written with the Util::Testing extension part of the library.
Code coverage is not 100% as many of the functions and classes within this library cannot easily be
tested via code such as triggering breakpoints or printing to the console in various ways. Tests
for these sections of code would also not be relevant as when issues do arrive it is quite easy to
find and fix.

If you do find an issue with the library (or library tests) feel free to make a PR or create a Github
issue to alert me of the error.

### Building

The tests are included as a seperate project to the main library and require a slightly different build
process. To build the tests from run:

```powershell
cd path/to/pb-util/repository
cd code-tests
mkdir build
cd build
cmake .. -G Ninja
cmake --build .
```

NOTE: Ninja as the generator is not required however it is highly recommended.
