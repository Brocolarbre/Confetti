# This script installs vcpkg and premake, an optional path for an existing installation of vcpkg can be specified
# The external dependencies described in the manifest files are installed using vcpkg
# The workspace is generated using premake

#!/bin/bash

vcpkg_path="./external/vcpkg"
if [ "$1" = "--vcpkg-path" ] && [ -n "$2" ]; then
	vcpkg_path="$2"
fi

bash ./scripts/linux/install_vcpkg.sh --path "$vcpkg_path"
if [ $? -ne 0 ]; then
	exit 1
fi

mkdir ./external/premake
bash ./scripts/linux/install_premake.sh --path ./external/premake
if [ $? -ne 0 ]; then
	exit 1
fi

"$vcpkg_path/vcpkg" install --clean-buildtrees-after-build --x-install-root=./external/vcpkg_installed --x-manifest-root=./external/vcpkg_manifests/x64-linux --triplet x64-linux
"$vcpkg_path/vcpkg" install --clean-buildtrees-after-build --x-install-root=./external/vcpkg_installed --x-manifest-root=./external/vcpkg_manifests/x64-linux-release --triplet x64-linux-release

bash ./scripts/linux/set_workspace.sh
if [ $? -ne 0 ]; then
	exit 1
fi

echo "Environment set."