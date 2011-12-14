NDK_SDK=/Users/mcalegaris/Downloads/android-ndk-r6-crystax-2

echo "set out dir ${SRCROOT}" 
OUT_DIR=./prebuilt/android
echo "OUT_DIR = $OUT_DIR"

# Clean any existing framework that might be there
if [ -d "$OUT_DIR" ]
then
echo "Framework: Cleaning framework..."
rm -rf "$OUT_DIR"
fi

# Build the canonical Framework bundle directory structure
echo "Framework: Setting up directories..."

mkdir -p $OUT_DIR
mkdir -p $OUT_DIR/Playtomic
mkdir -p $OUT_DIR/json
mkdir -p $OUT_DIR/json/include
mkdir -p $OUT_DIR/CurlWrap
mkdir -p $OUT_DIR/Tools
echo "Start Universal Playtomic Generation"

$NDK_SDK/ndk-build NDK_APPLICATION_MK=./Application.mk

echo "copy files"

cp ./Playtomic/*.h $OUT_DIR/Playtomic/
cp ./json/include/*.h $OUT_DIR/json/include/
cp ./CurlWrap/*.h $OUT_DIR/CurlWrap/
cp ./Tools/*.h $OUT_DIR/Tools/
cp -r ./libs/ $OUT_DIR/libs/

$NDK_SDK/ndk-build NDK_APPLICATION_MK=./Application.mk clean