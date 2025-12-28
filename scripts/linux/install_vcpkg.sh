# This script installs vcpkg at the provided path (--path) or in the current working directory if no path is provided
# If vcpkg is already installed, it is updated without overriding

#!/bin/bash

vcpkg_path="."
if [ "$1" = "--path" ] && [ -n "$2" ]; then
	vcpkg_path="$2"
fi

if [ ! -d "$vcpkg_path" ]; then
	echo "Cloning vcpkg..."
	mkdir -p "$vcpkg_path"
	git clone https://github.com/microsoft/vcpkg.git "$vcpkg_path"
	echo "Initializing vcpkg..."
	"$vcpkg_path/bootstrap-vcpkg.sh" -disableMetrics
else
	echo "Updating vcpkg..."
	pushd "$vcpkg_path" >/dev/null
	git pull
	popd >/dev/null
fi