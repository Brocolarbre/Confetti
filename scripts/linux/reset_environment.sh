# This script removes the external dependencies from their respective folders as well as vcpkg and premake
# The workspace and build are also cleared

#!/bin/bash

for dir in ./external/*/; do
	if [ "$(basename "$dir")" != "vcpkg_manifests" ] && [ "$(basename "$dir")" != "licenses" ]; then
		rm -rf "$dir"
	fi
done

rm -f ./external/* 2>/dev/null

mkdir -p ./external/include
mkdir -p ./external/lib/release
mkdir -p ./external/lib/debug
mkdir -p ./external/bin/release
mkdir -p ./external/bin/debug

touch ./external/include/.gitkeep
touch ./external/lib/release/.gitkeep
touch ./external/lib/debug/.gitkeep
touch ./external/bin/release/.gitkeep
touch ./external/bin/debug/.gitkeep

bash ./scripts/linux/clear_build.sh
bash ./scripts/linux/reset_workspace.sh

echo "Environment reset."