# Build the GDCM examples

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

FIND_PACKAGE(MAGIC)

SET(EXAMPLES_SRCS
  LargeVRDSExplicit
  #AnonymizeAES
  ClinicalTrialAnnotate
  CheckBigEndianBug
  DuplicatePCDE
  CreateARGBImage
  CreateCMYKImage
  CompressImage
  FixBrokenJ2K
  GenFakeImage
  HelloVizWorld
  HelloWorld
  MergeTwoFiles
  MrProtocol
  PatchFile
  ReadExplicitLengthSQIVR
  SortImage
  csa2img
  rle2img
  uid_unique
  PublicDict
  GenSeqs
  GetJPEGSamplePrecision
)

IF(MAGIC_FOUND)
  INCLUDE_DIRECTORIES(${MAGIC_INCLUDE_DIRS})
  ADD_EXECUTABLE(EncapsulateFileInRawData EncapsulateFileInRawData.cxx)
  TARGET_LINK_LIBRARIES(EncapsulateFileInRawData gdcmMSFF ${MAGIC_LIBRARIES})
ENDIF(MAGIC_FOUND)

IF(GDCM_BUILD_TESTING)
SET(EXAMPLES_SRCS
  ${EXAMPLES_SRCS}
  VolumeSorter
)
ENDIF(GDCM_BUILD_TESTING)

FOREACH(example ${EXAMPLES_SRCS})
  ADD_EXECUTABLE(${example} ${example}.cxx)
  TARGET_LINK_LIBRARIES(${example} gdcmMSFF)
ENDFOREACH(example)

IF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
#../../bin/libgdcmDSED.dll.a(d000469.o)(.text+0x0): multiple definition of `gdcm::VL gdcm::Item::GetLength<gdcm::ImplicitDataElement>() const'
#CMakeFiles/ReadExplicitLengthSQIVR.dir/ReadExplicitLengthSQIVR.obj(.text$_ZNK4gdcm4Item9GetLengthINS_19ImplicitDataElementEEENS_2VLEv[gdcm::VL gdcm::Item::GetLength<gdcm::ImplicitDataElement>() const]+0x0):ReadExplicitLengthSQIVR.cxx: first defined here
#../../bin/libgdcmDSED.dll.a(d000252.o)(.text+0x0): multiple definition of `std::istream& gdcm::DataSet::ReadNested<gdcm::ImplicitDataElement, gdcm::SwapperDoOp>(std::istream&)'
#CMakeFiles/ReadExplicitLengthSQIVR.dir/ReadExplicitLengthSQIVR.obj(.text$_ZN4gdcm7DataSet10ReadNestedINS_19ImplicitDataElementENS_11SwapperDoOpEEERSiS4_[std::basic_istream<char, std::char_traits<char> >& gdcm::DataSet::ReadNested<gdcm::ImplicitDataElement, gdcm::SwapperDoOp>(std::basic_istream<char, std::char_traits<char> >&)]+0x0):ReadExplicitLengthSQIVR.cxx: first defined here
#../../bin/libgdcmDSED.dll.a(d000253.o)(.text+0x0): multiple definition of `std::istream& gdcm::DataSet::ReadNested<gdcm::ImplicitDataElement, gdcm::SwapperNoOp>(std::istream&)'
#CMakeFiles/ReadExplicitLengthSQIVR.dir/ReadExplicitLengthSQIVR.obj(.text$_ZN4gdcm7DataSet10ReadNestedINS_19ImplicitDataElementENS_11SwapperNoOpEEERSiS4_[std::basic_istream<char, std::char_traits<char> >& gdcm::DataSet::ReadNested<gdcm::ImplicitDataElement, gdcm::SwapperNoOp>(std::basic_istream<char, std::char_traits<char> >&)]+0x0):ReadExplicitLengthSQIVR.cxx: first defined here
#../../bin/libgdcmDSED.dll.a(d000271.o)(.text+0x0): multiple definition of `std::istream& gdcm::DataSet::ReadWithLength<gdcm::ImplicitDataElement, gdcm::SwapperDoOp>(std::istream&, gdcm::VL&)'

  SET_TARGET_PROPERTIES( ReadExplicitLengthSQIVR PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition")
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
