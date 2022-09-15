#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#define TEST_PATH "/home/quinton/Desktop/ER_StructureExtraction/test_processed.png"      // 测试路径
#define SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/test_processed2.png"     // 保存路径
#define SAVE_PATH_RESULT "/home/quinton/Desktop/ER_StructureExtraction/test3_result.png" // 保存路径
#define GREY_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/grey_dst.png"       // 灰度图保存路径
#define ERODE_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/erode_dst.png"     // 灰度图保存路径
#define DILATE_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/dilate_dst.png"   // 灰度图保存路径

// #define IS_DEBUG 1           // 是否进入调试
// #define IS_DEBUG_THRESHOLD 1 // 调试threshold
// #define IS_DEBUG_MORPHOLOGYEX 1 // 调试morphologyex
// #define IS_DEBUG_HIERARCHY 1 // 调试HIERARCHY
#define IS_DEBUG_SELECTCONTOURS 1 // 调试SELECTCONTOURS
