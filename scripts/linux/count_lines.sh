# This script counts source files, directories and lines in the project

#!/bin/bash

root="."
if [[ "$1" == "--root" && -n "$2" ]]; then
    root="$2"
fi

cppCount=0
hppCount=0
cCount=0
hCount=0
totalLines=0
folderCount=0

while IFS= read -r -d '' dir; do
    ((folderCount++))
done < <(find "$root" -path "*/external" -prune -o -type d -print0)

while IFS= read -r -d '' file; do
    ext="${file##*.}"
    ext="${ext,,}"

    case "$ext" in
        cpp) ((cppCount++)) ;;
        hpp) ((hppCount++)) ;;
        c)   ((cCount++)) ;;
        h)   ((hCount++)) ;;
    esac

    lines=$(wc -l < "$file")
    ((totalLines += lines))

done < <(find "$root" -path "*/external" -prune -o -type f \( -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.c" -o -iname "*.h" \) -print0)

echo "-----------------------------"
echo "Folders: $folderCount"
echo "-----------------------------"
echo "Files:"
echo "  .cpp: $cppCount"
echo "  .hpp: $hppCount"
echo "  .c:   $cCount"
echo "  .h:   $hCount"
echo "-----------------------------"
echo "Lines: $totalLines"
echo "-----------------------------"