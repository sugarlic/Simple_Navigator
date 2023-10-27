set(LIB_NAME s21_graph_algorithms)
AUX_SOURCE_DIRECTORY(./src ${LIB_NAME}_SRCS)
file(GLOB_RECURSE ${LIB_NAME}_HEADERS
    includes/*.h
)
add_library(${LIB_NAME} STATIC
    ${${LIB_NAME}_SRCS}
    ${${LIB_NAME}_HEADERS}
)
target_link_libraries(${LIB_NAME} PUBLIC containers s21_graph)
target_include_directories(${LIB_NAME} PUBLIC includes)