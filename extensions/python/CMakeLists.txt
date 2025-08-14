# Makes sure Python is available on the machine and adds it to the project #
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

target_include_directories(PashaBibko-UTIL PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(PashaBibko-UTIL PRIVATE ${Python3_LIBRARIES})

# Adds the extension source files to the .lib #
target_sources(PashaBibko-UTIL PRIVATE
	"CTPython.cpp"
)
