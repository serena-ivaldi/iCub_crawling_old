IF(WIN32)
cmake_minimum_required(VERSION 2.8)
ELSE(WIN32)
cmake_minimum_required(VERSION 2.4)
ENDIF(WIN32)

PROJECT(plannerSupervisor)

FIND_PACKAGE(ICUB)
FIND_PACKAGE(YARP)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_DIR}/conf ${YARP_DIR}/conf)
FIND_PACKAGE(GtkMM REQUIRED)

INCLUDE_DIRECTORIES(${ICUB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GtkMM_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GtkPlus_INCLUDE_DIRS})
    
# LINK_LIBRARIES(${ICUB_LIBRARIES} ${YARP_LIBRARIES} ${GtkMM_LIBRARIES})

FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h )
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

ADD_EXECUTABLE(plannerSupervisor ${folder_source} ${folder_header})
TARGET_LINK_LIBRARIES(plannerSupervisor ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${OpenCV_LIBRARIES} ${GtkMM_LIBRARIES})
INSTALL(TARGETS plannerSupervisor DESTINATION ${ICUB_DIR}/bin)