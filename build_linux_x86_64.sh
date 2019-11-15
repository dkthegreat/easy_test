OUTPUT_DIR=build_linux_x86_64
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}
cd ${OUTPUT_DIR}
cmake ..
make -j8