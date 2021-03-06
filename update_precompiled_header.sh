#!/bin/bash

cd include

mv PrecompiledHeader.hpp PrecompiledHeader.hpp.old
grep -v "#include\|#endif // !defined(__cplusplus)" PrecompiledHeader.hpp.old > PrecompiledHeader.hpp
rm PrecompiledHeader.hpp.old

# SkinnedGUI seems broken
for h in *.h */*.h ; do
echo "#include \"$h\""; done | \
grep -v "SkinnedGUI" | \
grep -v "CWorld.h" | \
grep -v "UCString.h" | \
grep -v "_generated.h" | \
grep -v "win32memleakdebug.h" >> \
PrecompiledHeader.hpp
cd ../src
for h in */*.h */*.h */*/*.h */*/*/*.h ; do
echo "#include \"$h\""; done | \
grep -v "breakpad/" | \
grep -v "gss-grammar.h" | \
grep -v "omfg_script_parser.h" >> \
../include/PrecompiledHeader.hpp

echo "#endif // !defined(__cplusplus)" >> ../include/PrecompiledHeader.hpp
