# CMakeLists.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required(VERSION 3.26)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("ZubenokGame")

# Включите подпроекты.
add_subdirectory("ZubenokGame")

# Keep a root-level compile_commands.json for clangd / Cursor IntelliSense.
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
	execute_process(
		COMMAND
			"${CMAKE_COMMAND}" -E copy_if_different
			"${CMAKE_BINARY_DIR}/compile_commands.json"
			"${CMAKE_SOURCE_DIR}/compile_commands.json"
	)
endif()
