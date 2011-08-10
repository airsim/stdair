FILE(REMOVE_RECURSE
  "CMakeFiles/devhelpers"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/devhelpers.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
