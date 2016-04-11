# Get revision number
REV_NUM=`svn info | grep Редакция: | awk -F ': ' '{print $2}'`

# Get build number
BUILD_NUM_STR=`cat build_data/build_number`
BUILD_NUM=$(($BUILD_NUM_STR + 1))

# Get version number
VER_NUM=`cat build_data/version_number`

# Create version.hpp
echo "// This file was generated automatically" > version.hpp
echo "#define REVISION \"$REV_NUM\"" >> version.hpp
echo "#define BUILD \"$BUILD_NUM\"" >> version.hpp
echo "#define VERSION \"$VER_NUM\"" >> version.hpp

# Save new number of build
echo $BUILD_NUM > build_data/build_number
