IF(WIN32)
cmake_minimum_required(VERSION 2.6)
ELSE(WIN32)
cmake_minimum_required(VERSION 2.4)
ENDIF(WIN32)
if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

PROJECT(crawlPlanner)

FIND_PACKAGE(ICUB)
FIND_PACKAGE(YARP)

INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ICUB_INCLUDE_DIRS})
    
LINK_LIBRARIES(
	${YARP_LIBRARIES} 
	${ICUB_LIBRARIES} 
)

FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h )
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

ADD_EXECUTABLE(crawlPlanner ${folder_source} ${folder_header})
TARGET_LINK_LIBRARIES(crawlPlanner ${YARP_LIBRARIES} ${ICUB_LIBRARIES})
INSTALL(TARGETS crawlPlanner DESTINATION ${ICUB_DIR}/bin)
