get_filename_component(PLAYER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME "black_jack_solver_${PLAYER_NAME}")

add_library(${TARGET_NAME} SHARED
  black_jack_solver.cpp
  ${CMAKE_SOURCE_DIR}/shared/shim.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/shared
)

set_target_properties(${TARGET_NAME} PROPERTIES
  OUTPUT_NAME ${TARGET_NAME}
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/players
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${CMAKE_BINARY_DIR}/players
)
