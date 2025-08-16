# Creates the .dll for *CompileTimeGeneration(CTG)                          #
# Whilst it is called CTG it is actually done the first time a build is run #
add_library(PashaBibko-UTIL-PythonCTG SHARED "ct-generator/CTGenerator.c")
target_include_directories(PashaBibko-UTIL-PythonCTG PRIVATE "ct-generator")

# Ensures the DLL is always built #
add_dependencies(PashaBibko-UTIL PashaBibko-UTIL-PythonCTG)

# Makes sure Python is available on the machine and adds it to the CTG-DLL #
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

target_include_directories(PashaBibko-UTIL-PythonCTG PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(PashaBibko-UTIL-PythonCTG PRIVATE ${Python3_LIBRARIES})

# Adds a command to run the main .exe after it is built to generate the PBUtilsPythonCTGValues.cpp #
add_custom_command(
	OUTPUT ${CMAKE_SOURCE_DIR}/.PBUTIL/PBUtilsPythonCTGValues.cpp
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/.PBUTIL/PBUtilsPythonCTGValues.cpp
	COMMAND $<TARGET_FILE:${USES_PYTHON_CTG}>
	DEPENDS $<TARGET_FILE:${USES_PYTHON_CTG}>
	COMMENT "Running [${USES_PYTHON_CTG}] to generate python outputs."
)

# Adds the extension source files to the .lib #
target_sources(PashaBibko-UTIL PRIVATE
	"CTPython.cpp"
)
