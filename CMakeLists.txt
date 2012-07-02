CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(FUCKINGIMG)

ADD_DEFINITIONS( ${OPTIMIZATION_FLAGS} )

SET(CMAKE_BUILD_TYPE debug)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" "${CMAKE_SOURCE_DIR}")


SET(SRC_LIST
  src/generaloption.h
  src/imgfiledlg.h
  src/imgfilemodel.h
  src/loadformats.h
  src/mainwindow.h
  src/resizegrp.h
  src/generaloption.cpp
  src/imgfiledlg.cpp
  src/imgfilemodel.cpp
  src/loadformats.cpp
  src/main.cpp
  src/mainwindow.cpp
  src/resizegrp.cpp
  )

SET(MOC_HDLIST
  src/generaloption.h
  src/imgfiledlg.h
  src/imgfilemodel.h
  src/mainwindow.h
  src/resizegrp.h
  )

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})
QT4_WRAP_CPP(fuckingimg_MOC_SRCS ${MOC_HDLIST})

FIND_PACKAGE(Magick REQUIRED)
INCLUDE_DIRECTORIES (${MAGICK++_INCLUDE_DIR} ${MAGICK_INCLUDE_DIR} . src/ src/include)

ADD_EXECUTABLE(fuckImgBatch
  ${SRC_LIST}
  )
TARGET_LINK_LIBRARIES(fuckImgBatch
  ${QT_LIBRARIES}
  ${MAGICK_LIBRARIES}
  ${MAGICK++_LIBRARIES}
)

