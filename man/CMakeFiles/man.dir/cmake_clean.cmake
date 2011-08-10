FILE(REMOVE_RECURSE
  "man1"
  "man3"
  "CMakeFiles/man"
  "man1/stdair-config.1"
  "man3/stdair-library.3"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/man.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
