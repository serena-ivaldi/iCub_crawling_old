SET(PROJECTNAME velImpControl)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(ICUB QUIET)
IF (NOT ICUB_FOUND)
   MESSAGE (STATUS "ICUB repository not found; assuming distributed build.")
   MESSAGE (STATUS "If this is not what you want, set ICUB_DIR variable.")
ENDIF (NOT ICUB_FOUND)

INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ICUB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
    
LINK_LIBRARIES(${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${OpenCV_LIBRARIES})

FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h)

# Declare groups of source and header files -- makes things pretty in MSVC.
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


# Create everything needed to build our executable.
ADD_EXECUTABLE(${PROJECTNAME} ${folder_source} ${folder_header})
TARGET_LINK_LIBRARIES(${PROJECTNAME} ${YARP_LIBRARIES} ${ICUB_LIBRARIES})
INSTALL(TARGETS ${PROJECTNAME} DESTINATION ${ICUB_DIR}/bin)
