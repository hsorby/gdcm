# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv
# gdcmanon


IF(WIN32 AND NOT CYGWIN)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/getopt"
  )
ENDIF(WIN32 AND NOT CYGWIN)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

IF(WIN32)
  IF (BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DGETOPT_DLL)
  ENDIF (BUILD_SHARED_LIBS)
ENDIF(WIN32)

SET(GDCM_EXECUTABLE_NAME
  gdcmdump
  gdcmraw
  gdcmscanner
  gdcmanon
  gdcmgendir
  #gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcmtar
  gdcminfo
  )
IF(GDCM_USE_SYSTEM_POPPLER)
  INCLUDE(CheckCXXSourceCompiles)
  SET(CMAKE_REQUIRED_INCLUDES ${POPPLER_INCLUDE_DIRS})
  SET(CMAKE_REQUIRED_LIBRARIES ${POPPLER_LIBRARIES})
  CHECK_CXX_SOURCE_COMPILES(
    "\#include <poppler/GlobalParams.h>\nint main() { globalParams = new GlobalParams(0); return 0;}"
    LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  IF(LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
    SET_SOURCE_FILES_PROPERTIES(
      ${CMAKE_CURRENT_SOURCE_DIR}/gdcmpdf.cxx
      PROPERTIES COMPILE_FLAGS -DLIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  ENDIF(LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  INCLUDE_DIRECTORIES(${POPPLER_INCLUDE_DIRS})
  SET(GDCM_EXECUTABLE_NAME
  ${GDCM_EXECUTABLE_NAME}
  gdcmpdf
)
ENDIF(GDCM_USE_SYSTEM_POPPLER)

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  IF(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx puff.c)
  ELSE(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx)
  ENDIF(${exename} STREQUAL "gdcminfo")
  TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  IF(${exename} STREQUAL "gdcmpdf")
    TARGET_LINK_LIBRARIES(${exename} ${POPPLER_LIBRARIES})
  ENDIF(${exename} STREQUAL "gdcmpdf")
  IF(GDCM_EXECUTABLE_PROPERTIES)
  SET_TARGET_PROPERTIES(${exename} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  ENDIF(GDCM_EXECUTABLE_PROPERTIES)
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
  IF(NOT GDCM_INSTALL_NO_RUNTIME)
    INSTALL(TARGETS ${exename}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
  ENDIF(NOT GDCM_INSTALL_NO_RUNTIME)
ENDFOREACH(exename)

#IF(GDCM_USE_PVRG)
#  ADD_EXECUTABLE(gdcmpvrg gdcmpvrg.cxx)
#  TARGET_LINK_LIBRARIES(gdcmpvrg pvrg)
#ENDIF(GDCM_USE_PVRG)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

