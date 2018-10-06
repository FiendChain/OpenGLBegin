file (GLOB SRC_FILES *.cpp)
file (GLOB HEADER_FILES *.h)

add_library (imgui ${SRC_FILES})

install (TARGETS imgui DESTINATION bin)
install (FILES ${HEADER_FILES} DESTINATION include)