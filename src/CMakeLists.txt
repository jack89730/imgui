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

ADD_EXECUTABLE(ImgBatch
  ${MOMOIMG_SRC_LIST}
  ${fuckingimg_MOC_SRCS} 
  ${fuckingimg_RESOURCES}
  )

TARGET_LINK_LIBRARIES(ImgBatch
  ${QT_LIBRARIES}
  ${MAGICK_LIBRARIES}
  ${MAGICK++_LIBRARIES}
)


