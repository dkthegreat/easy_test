NDK_ROOT_DIR=/data/android-sdk/ndk-bundle

OUTPUT_DIR=build_android_aarch64
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}
cd ${OUTPUT_DIR}
cmake .. \
    -DTARGET_PLATFORM=android_aarch64 \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_NDK=${NDK_ROOT_DIR} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=${NDK_ROOT_DIR}/build/cmake/android.toolchain.cmake \
    -DANDROID_PLATFORM=21 \
    -DANDROID_TOOLCHAIN=clang

make -j8