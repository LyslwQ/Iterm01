FILE(REMOVE_RECURSE
  "echo.pb.cc"
  "echo.pb.h"
  "CMakeFiles/echo_proto.dir/echo.pb.cc.o"
  "../../../lib/libecho_proto.pdb"
  "../../../lib/libecho_proto.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/echo_proto.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
