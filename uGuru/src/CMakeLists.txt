#-----------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------
include_directories (
    ${UGURU_SOURCE_DIR}/include
    ${UGURU_SOURCE_DIR}/tinyxml
    ${UGURU_SOURCE_DIR}/winhttp
)

link_directories (${UGURU_BINARY_DIR}/lib ${UGURU_SOURCE_DIR}/winhttp) 

#-----------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------
SET (MONGOOSE_SRCS mongoose.c main.c)
SET (UGURU_SRCS  global.cpp solver.cpp taskman.cpp node.cpp request.cpp
    download.c config.cpp sysinfo.cpp base64.cpp log.cpp datetime.cpp)

#-----------------------------------------------------------------------------
#
#-----------------------------------------------------------------------------
# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(UGURU_SRCS ${UGURU_SRCS} ${UGURU_SOURCE_DIR}/res/res.rc)
endif(WIN32)    

#-----------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------    
set(CMAKE_CXX_FLAGS "-DDEBUG -DHAVE_STDINT")
set(CMAKE_C_FLAGS "-DDEBUG -DHAVE_STDINT")

#-----------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------
add_executable (uGuru ${UGURU_SRCS} ${MONGOOSE_SRCS})

target_link_libraries (uGuru tinyxml winhttp ws2_32) 

