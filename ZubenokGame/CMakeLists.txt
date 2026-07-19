cmake_minimum_required(VERSION 3.28)

project(
	ZubrenokGame
	Version 0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchConent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SML/SML.git 
	GIT_TAG 3.1.0
	GIT_SHALLOW ON 
	EXCLUDE_FROM_ALL
	SYSTEM 
)

set(SQLITECPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SQLLITECPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SQLLITECPP_INCLUDE_SCRIPT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_INTERNAL_SQLITE ON CACHE BOOL "" FORCE)

FetchConent_Declare(
	SQLiteCpp 
	GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git 
	GIT_TAG 3.3.3
	GIT_SHALLOW ON 
	EXCLUDE_FROM_ALL
)

FetchConent_MakeAvilable(SFML SQLiteCpp)

add_executable(
	ZubrenokGame
	src/main.cpp 
	src/app/Application.cpp 
	src/persistence/Database.cpp 
)

target_include_directories(
	ZubrenokGame
	PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(
	ZubrenokGame
	PRIVATE 
	SFML::Graphics
	SFML::Audio
	SQLiteCpp
)

if(MSVC)
	target_compile_options(
		ZubrenokGame
		PRIVATE 
		/W4
		/permissive-
		/utf-8
	)
else()
	target_compile_options(
		ZubrenokGame
		PRIVATE 
		-Wall
		-Wextra
		-Wpedantic
	)
endif()

add_custom_command(
	TARGET ZubrenokGame
	POST_BUILD
	COMMAND 
		${CMAKE_COMMAND}
		-E 
		copy_directory 
		"${CMAKE_CURRENT_SOURCE_DIR}/assets"
		"$<TARGET_FILE_DIR:ZubrenokGame>/assets"
)

set_property(
	DIRECTORY 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	PROPERTY
	VS_STARTUP_PROJECT ZubrenokGame
)

set_property(
	TARGET ZubrenokGame
	PROPERTY
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ZubrenokGame>"
)

