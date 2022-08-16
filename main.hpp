#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

// ================== 记得更改为自己的路径 ================== //
#define TEST_PATH "/home/quinton/Desktop/ER_StructureExtraction/test3.png"               // 测试路径
#define SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/test_processed2.png"     // 保存路径
#define SAVE_PATH_RESULT "/home/quinton/Desktop/ER_StructureExtraction/test3_result.png" // 保存路径
#define GREY_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/grey_dst.png"       // 灰度图保存路径
#define ERODE_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/erode_dst.png"     // 灰度图保存路径
#define DILATE_SAVE_PATH "/home/quinton/Desktop/ER_StructureExtraction/dilate_dst.png"   // 灰度图保存路径
// ================== 记得更改为自己的路径 ================== //

#define IS_CLOSED 1 // 是否闭运算
#define IS_DEBUG 1  // 是否进入调试
// #define IS_DEBUG_THRESHOLD 1 // 调试threshold
// #define IS_DEBUG_MORPHOLOGYEX 1 // 调试morphologyex
// #define IS_DEBUG_HIERARCHY 1 //
#define IS_DEBUG_SELECTCONTOURS 1 // 

class Macrocontrol
{
private:
  string test_path = TEST_PATH;
  string save_path = SAVE_PATH;

public:
  Macrocontrol(/* args */);
  ~Macrocontrol();
};

Macrocontrol::Macrocontrol(/* args */)
{
}

Macrocontrol::~Macrocontrol()
{
}

// 预处理
class Pretreatment
{
private:
public:
  Pretreatment(/* args */);
  ~Pretreatment();
};

Pretreatment::Pretreatment(/* args */)
{
}

Pretreatment::~Pretreatment()
{
}

// 细化
class Refinement
{
private:
  /* data */
public:
  Refinement(/* args */);
  ~Refinement();
};

Refinement::Refinement(/* args */)
{
}

Refinement::~Refinement()
{
}

// 节点检测
class NodeDetection
{
private:
  /* data */
public:
  NodeDetection(/* args */);
  ~NodeDetection();
};

NodeDetection::NodeDetection(/* args */)
{
}

NodeDetection::~NodeDetection()
{
}
