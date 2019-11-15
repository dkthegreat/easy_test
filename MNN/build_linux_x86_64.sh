OUTPUT_DIR=build_linux_x86_64
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}

cd ${OUTPUT_DIR}
cmake .. \
        -DCMAKE_PREFIX_PATH="/data/opensource_code/protobuf-3.1.0/install_linux_x86_64" \
        -DMNN_FORBID_MULTI_THREAD="ON" \
        -DMNN_OPENMP="OFF" \
        -DMNN_USE_THREAD_POOL="OFF" \
        -DMNN_BUILD_CONVERTER="ON" \

        #-DCMAKE_BUILD_TYPE="Debug" \
        #-DMNN_CONVERT_DEBUG="ON" \
make -j8