#!/bin/sh
set -e;

build_dir=$(dirname $0);
module_dir=$build_dir/bin/tawkto;

if [ -d "$module_dir" ]; then
	echo "Removing existing module folder";
	rm -r $module_dir;
fi

echo "Creating module folder";
mkdir -p $module_dir;

echo "Copying files to module folder";
cp $build_dir/../tawk_to.* $module_dir
cp -r $build_dir/../views $module_dir

echo "Done building module folder";

echo "Building docker image"
docker-compose build
