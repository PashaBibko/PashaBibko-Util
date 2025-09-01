# For v1.1 release

### Documentaion

- Write documentation for:
    PBTest extension
    Extensions

- ReturnVal.h
    Update documentation to work with the new version

- Log.h
    Update documentation to include custom log iterators and new LogStr function versions

### Tests

- Write tests for:
    Log.h/.cpp
    ReturnVal.h/.cpp (after update)
    FileManagment.h/.cpp

### Code (linux-only)

- Misc.cpp TriggerBreakpoint (Can be in later release)
    Figure out how to detect debuggers on Linux
    Make sure that breakpoints are actually triggered

- FileManagment.cpp TempFilePath
    Write implementation for Linux

# Future releases

### Code (general)

- PBTest extension
    Add more EXPECT_X macros with relevant errors
    Add error checking to some of the macros to stop missuse

- Interpreter extension (new)
    Add support for lua interpreter
    Add support for python interpreter

- ReturnVal
    Allow multiple warnings via a linked list

### Code ideas

- InternalVal extension (new)
    Reaserch into if it is possible
    If so look into how to avoid triggering VirusDetection

- Perfect(Hash)Map class (new)
    Reaserch into how to do it
    Create it within the library

- Mac/IOS support (when I get one)
