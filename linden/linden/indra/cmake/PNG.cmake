# -*- cmake -*-
include(Prebuilt)

set(PNG_FIND_QUIETLY ON)
set(PNG_FIND_REQUIRED ON)

if (STANDALONE)
  include(FindPNG)
else (STANDALONE)
  use_prebuilt_binary(libpng)
  if( DARWIN )
    set(PNG_LIBRARIES png12.0)
  else( DARWIN )
    set(PNG_LIBRARIES png12)
  endif (DARWIN)
  set(PNG_INCLUDE_DIRS ${LIBS_PREBUILT_DIR}/include ${LIBS_PREBUILT_DIR}/${LL_ARCH_DIR}/include)
endif (STANDALONE)
