set(EXE_NAME ${P_NAME})
AUX_SOURCE_DIRECTORY(./src ${EXE_NAME}_SRCS)
add_executable(${EXE_NAME}
    ${${EXE_NAME}_SRCS}
)
target_link_libraries(${EXE_NAME} 
    ${P_NAME}_Backend
)
