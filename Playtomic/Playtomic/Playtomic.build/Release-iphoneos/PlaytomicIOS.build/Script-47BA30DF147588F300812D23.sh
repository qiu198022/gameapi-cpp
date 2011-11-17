#!/bin/sh
# name and build location
FRAMEWORK_NAME=${PROJECT_NAME}
FRAMEWORK_BUILD_PATH="${PROJECT_DIR}/build/Framework"

# these never change
FRAMEWORK_VERSION=A
FRAMEWORK_CURRENT_VERSION=1
FRAMEWORK_COMPATIBILITY_VERSION=1

# Clean any existing framework that might be there
if [ -d "$FRAMEWORK_BUILD_PATH" ]
then
echo "Framework: Cleaning framework..."
rm -rf "$FRAMEWORK_BUILD_PATH"
fi

# Build the canonical Framework bundle directory structure
echo "Framework: Setting up directories..."
FRAMEWORK_DIR=$FRAMEWORK_BUILD_PATH/$FRAMEWORK_NAME.framework
mkdir -p $FRAMEWORK_DIR
mkdir -p $FRAMEWORK_DIR/Versions
mkdir -p $FRAMEWORK_DIR/Versions/$FRAMEWORK_VERSION
mkdir -p $FRAMEWORK_DIR/Versions/$FRAMEWORK_VERSION/Resources
mkdir -p $FRAMEWORK_DIR/Versions/$FRAMEWORK_VERSION/Headers

echo "Framework: Creating symlinks..."
ln -s $FRAMEWORK_VERSION $FRAMEWORK_DIR/Versions/Current
ln -s Versions/Current/Headers $FRAMEWORK_DIR/Headers
ln -s Versions/Current/Resources $FRAMEWORK_DIR/Resources
ln -s Versions/Current/$FRAMEWORK_NAME $FRAMEWORK_DIR/$FRAMEWORK_NAME

CURRENTCONFIG_DEVICE_DIR=${SYMROOT}/${CONFIGURATION}-iphoneos
CURRENTCONFIG_SIMULATOR_DIR=${SYMROOT}/${CONFIGURATION}-iphonesimulator

# combine lib files for various platforms into one
echo "Framework: Creating library..."
lipo -create "${CURRENTCONFIG_DEVICE_DIR}/${EXECUTABLE_NAME}" "${CURRENTCONFIG_SIMULATOR_DIR}/${EXECUTABLE_NAME}" -o "$FRAMEWORK_DIR/Versions/Current/$FRAMEWORK_NAME"

echo "Framework: Copying assets into current version..."
cp ${SRCROOT}/Playtomic/*.h $FRAMEWORK_DIR/Headers/
cp ${SRCROOT}/Tools/*.h $FRAMEWORK_DIR/Headers/
cp ${SRCROOT}/CurlWrap/*.h $FRAMEWORK_DIR/Headers/
cp ${SRCROOT}/json/include/*.h $FRAMEWORK_DIR/Headers/
