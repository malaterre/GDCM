IF(WIN32)
  FIND_PACKAGE(DotNETFrameworkSDK)
ELSE(WIN32)
  #TODO handle CSharp_FIND_QUIETLY
  #TODO handle CSharp_FIND_REQUIRED
  FIND_PACKAGE(MONO)
ENDIF(WIN32)

# http://public.kitware.com/Bug/view.php?id=7757
#MESSAGE("DEBUG:${CMAKE_CURRENT_LIST_FILE}")
GET_FILENAME_COMPONENT(current_list_path ${CMAKE_CURRENT_LIST_FILE} PATH)
#MESSAGE("DEBUG:${current_list_path}")
SET(CSharp_USE_FILE ${current_list_path}/UseCSharp.cmake)

