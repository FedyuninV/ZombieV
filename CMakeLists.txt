cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME ZombieV)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
find_package(OpenGL)

file(GLOB source_files
	"src/*.cpp"
	"src/Blur/*.cpp"
	"src/LightEngine/*.cpp"
	"src/Props/*.cpp"
	"src/System/*.cpp"
	"src/UnitedEngine/*.cpp"
	"src/Weapons/*.cpp"
)

set(SOURCES ${source_files})
set(CMAKE_CXX_STANDARD 11)

# Download SFML and build it from source
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

# Copy data dir to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
   foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   endforeach()
endif(MSVC)

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY "data" DESTINATION ${CMAKE_INSTALL_BINDIR})
