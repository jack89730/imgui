SET(MOMOIMG_SRC_LIST
  generaloption.cpp
  imgfiledlg.cpp
  imgfilemodel.cpp
  loadformats.cpp
  main.cpp
  mainwindow.cpp
  resizegrp.cpp
  readerror.cpp
  convert.cpp
  ../resource/myapp.rc
  
  )

SET(MOMOIMG_MOC_HEADER
  imgfiledlg.h
  imgfilemodel.h
  mainwindow.h
  resizegrp.h
  readerror.h
  convert.h
  )

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

FIND_PACKAGE(Magick REQUIRED)
INCLUDE_DIRECTORIES (${MAGICK++_INCLUDE_DIR} ${MAGICK_INCLUDE_DIR} ${CMAKE_BINARY_DIR} src/ )

QT4_WRAP_CPP(fuckingimg_MOC_SRCS ${MOMOIMG_MOC_HEADER})


SET(fuckingimg_RESOURCES  
   ../resource/resources.qrc
)
QT4_ADD_RESOURCES(fuckingimg_RESOURCES ${fuckingimg_RESOURCES})

SET(fuckingimg_LANG
  ../language/zh_CN.ts
)
QT4_ADD_TRANSLATION(fuckingimg_RESOURCES ${fuckingimg_LANG})


IF(WIN32)
  ADD_DEFINITIONS(-D_AFXDLL)
  SET(CMAKE_MFC_FLAG 2) 
  SET(GUI_TYPE WIN32)
ENDIF(WIN32)
# Set some Apple MacOS Specific settings
IF (APPLE)
SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

ADD_EXECUTABLE(ImgBatch ${GUI_TYPE}
  ${MOMOIMG_SRC_LIST}
  ${fuckingimg_MOC_SRCS} 
  ${fuckingimg_RESOURCES}
  )

IF(WIN32)
  set_target_properties(ImgBatch PROPERTIES
    COMPILE_DEFINITIONS _AFXDLL,_UNICODE,UNICODE,_BIND_TO_CURRENT_CRT_VERSION,_BIND_TO_CURRENT_MFC_VERSION
    LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(ImgBatch
  ${QT_LIBRARIES}
  ${MAGICK_LIBRARIES}
  ${MAGICK++_LIBRARIES}
)


