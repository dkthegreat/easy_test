OUTPUT_DIR=build_android_aarch64
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}

cd ${OUTPUT_DIR}
cmake \
        -DCMAKE_TOOLCHAIN_FILE=/data/android-sdk/ndk-bundle/build/cmake/android.toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DMNN_DEBUG=false \
        -DANDROID_ABI="arm64-v8a" \
        -DANDROID_STL=c++_static \
        -DANDROID_NATIVE_API_LEVEL=android-21  \
        -DMNN_DEBUG=false \
        -DMNN_BUILD_FOR_ANDROID_COMMAND=true \
        -DMNN_FORBID_MULTI_THREAD="ON" \
        -DMNN_OPENMP="OFF" \
        -DMNN_USE_THREAD_POOL="OFF" \
    ..
make -j8