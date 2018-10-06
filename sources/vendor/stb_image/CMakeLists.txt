add_library (stb_image stb_image.cpp)

install (TARGETS stb_image DESTINATION bin)
install (FILES stb_iamge.h DESTINATION include)