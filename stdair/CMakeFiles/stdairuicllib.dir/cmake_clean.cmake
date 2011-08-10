FILE(REMOVE_RECURSE
  "libstdairuicl.pdb"
  "libstdairuicl.so"
  "libstdairuicl.so.99.99.99"
  "libstdairuicl.so.99.99"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/stdairuicllib.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
