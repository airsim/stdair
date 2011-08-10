FILE(REMOVE_RECURSE
  "html"
  "latex"
  "CMakeFiles/pdf"
  "latex/refman.pdf"
  "html/index.html"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/pdf.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
