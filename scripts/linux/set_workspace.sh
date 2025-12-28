# This script generates the workspace using the premake scripts, the arguments are forwarded to the premake scripts

#!/bin/bash

target="gmake"
if [ "$1" = "--target" ] && [ -n "$2" ]; then
	target="$2"
fi

if [ ! -f "./external/premake/premake5" ]; then
	echo "Premake not found, run the setup_environment script first."
	exit 1
fi

./external/premake/premake5 "$target"
echo "Workspace set."