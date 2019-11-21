./build_linux_x86_64.sh

OUTPUT_DIR=easy_test_console_linux_x86_64
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}

cp MNN/libs/linux_x86_64/libMNN.so ${OUTPUT_DIR}/
cp build_linux_x86_64/easy_test ${OUTPUT_DIR}/
cp models/mnn/squeezenet_v1.1.mnn ${OUTPUT_DIR}/
cp ./6016x4512_nv12.yuv ${OUTPUT_DIR}/

cd ${OUTPUT_DIR}/
echo "export LD_LIBRARY_PATH=./" > run.sh
chmod +x run.sh
echo "./easy_test" >> run.sh