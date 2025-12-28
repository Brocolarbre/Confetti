# This script installs premake at the provided path (--path) or in the current working directory if no path is provided

#!/bin/bash

premake_path="."
if [ "$1" = "--path" ] && [ -n "$2" ]; then
	premake_path="$2"
fi

if [ ! -f "$premake_path/premake5" ]; then
	echo "Downloading Premake..."
	curl -L -o premake.zip "https://github.com/premake/premake-core/releases/download/v5.0.0-beta7/premake-5.0.0-beta7-linux.tar.gz"
	mkdir -p "$premake_path"
	tar -xf premake.zip -C "$premake_path"
	rm -f "premake.zip"
fi