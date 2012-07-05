CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(FUCKINGIMG)

ADD_DEFINITIONS( ${OPTIMIZATION_FLAGS} )

# SET(CMAKE_BUILD_TYPE release)   
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" "${CMAKE_SOURCE_DIR}")


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
INCLUDE_DIRECTORIES (${MAGICK++_INCLUDE_DIR} ${MAGICK_INCLUDE_DIR} . src/ src/include)

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

ADD_EXECUTABLE(fuckImgBatch
  ${SRC_LIST}
  ${fuckingimg_MOC_SRCS} 
  ${fuckingimg_RESOURCES}
  )

TARGET_LINK_LIBRARIES(fuckImgBatch
  ${QT_LIBRARIES}
  ${MAGICK_LIBRARIES}
  ${MAGICK++_LIBRARIES}
)

