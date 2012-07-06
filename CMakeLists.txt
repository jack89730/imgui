CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET( CMAKE_COLOR_MAKEFILE ON )
SET( CMAKE_VERBOSE_MAKEFILE ON )
# enable warnings
IF(CMAKE_COMPILER_IS_GNUCXX )
  ADD_DEFINITIONS( -g -Wall )
ENDIF(CMAKE_COMPILER_IS_GNUCXX )


PROJECT(IMGBATCHER)
ADD_DEFINITIONS( ${OPTIMIZATION_FLAGS} )

# SET(CMAKE_BUILD_TYPE Release)   
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Module")


SET(SRC_LIST
  src/generaloption.cpp
  src/imgfiledlg.cpp
  src/imgfilemodel.cpp
  src/loadformats.cpp
  src/main.cpp
  src/mainwindow.cpp
  src/resizegrp.cpp
  src/readerror.cpp
  src/convert.cpp
  )

SET(MOC_HDLIST
  src/imgfiledlg.h
  src/imgfilemodel.h
  src/mainwindow.h
  src/resizegrp.h
  src/readerror.h
  src/convert.h
  )

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

FIND_PACKAGE(Magick REQUIRED)
INCLUDE_DIRECTORIES (${MAGICK++_INCLUDE_DIR} ${MAGICK_INCLUDE_DIR} ${CMAKE_BINARY_DIR} src/ )

SET(fuckingimg_RESOURCES  
   resource/resources.qrc
)

# NO NEED NOW
SET(fuckingimg_LANG
  language/zh_CN.ts
)

QT4_WRAP_CPP(fuckingimg_MOC_SRCS ${MOC_HDLIST})
QT4_ADD_RESOURCES(fuckingimg_RESOURCES ${fuckingimg_RESOURCES})
QT4_ADD_TRANSLATION(fuckingimg_RESOURCES ${fuckingimg_LANG})

# NO NEED NOW
# QT4_ADD_TRANSLATION(fuckingimg_RESOURCES ${fuckingimg_LANG}) 

ADD_EXECUTABLE(ImgBatch
  ${SRC_LIST}
  ${fuckingimg_MOC_SRCS} 
  ${fuckingimg_RESOURCES}
  )

TARGET_LINK_LIBRARIES(ImgBatch
  ${QT_LIBRARIES}
  ${MAGICK_LIBRARIES}
  ${MAGICK++_LIBRARIES}
)

