#include "Setting.hpp"

using namespace cv;
using namespace std;

// 反色
void invertColor(cv::Mat &dst);

// 灰度化与提亮
void greyAndBrightness(cv::Mat &src, cv::Mat &dst);

// threshold阈值滑动条回调函数
void threshold_track(int typeValue, void *);

// thresholds二值化处理
void thresholdsProcessing(cv::Mat &dst);

// morphologyEx滑动条回调函数
void morphologyEx_track(int typeValue, void *);

// 闭运算
void closedoPerations(cv::Mat &dst);

// 绘制轮廓
void drawContours(cv::Mat &dst);

// contours面积筛选回调函数
void selectContours_track(int typeValue, void *);

// contours面积筛选回调函数
void selectContours_track(int typeValue, void *);

// 轮廓过滤
void contoursFilter(cv::Mat &dst);