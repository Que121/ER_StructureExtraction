#include "main.hpp"

cv::Mat src = imread(TEST_PATH, IMREAD_COLOR);
cv::Mat grey_dst = Mat ::zeros(src.size(), src.type());
cv::Mat morphologyEx_dst = Mat ::zeros(src.size(), src.type());
cv::Mat threshold_dst = Mat ::zeros(src.size(), src.type());
cv::Mat erode_dst1 = Mat ::zeros(src.size(), src.type());
cv::Mat erode_dst2 = Mat ::zeros(src.size(), src.type());
cv::Mat dilate_dst1 = Mat ::zeros(src.size(), src.type());
cv::Mat dilate_dst2 = Mat ::zeros(src.size(), src.type());

float alpha = 2.5;                // 对比度
float beta = 170;                 // 亮度
float g_nStructElementSize1 = 30; //结构元素(内核矩阵)的尺寸
float g_nStructElementSize2 = 7.5;
float g_nStructElementSize3 = 6;
float g_nStructElementSize4 = 3;
float g_nStructElementSize5 = 6;

int g_nStructElementSize = 10;
int thresholds = 150;

cv::Mat element1 = getStructuringElement(MORPH_ELLIPSE,
                                         Size(g_nStructElementSize1,
                                              g_nStructElementSize1)); // 膨胀腐蚀内核
cv::Mat element2 = getStructuringElement(MORPH_RECT,
                                         Size(g_nStructElementSize2,
                                              g_nStructElementSize2));
cv::Mat element3 = getStructuringElement(MORPH_ELLIPSE,
                                         Size(g_nStructElementSize3,
                                              g_nStructElementSize3));
cv::Mat element4 = getStructuringElement(MORPH_RECT,
                                         Size(g_nStructElementSize4,
                                              g_nStructElementSize4));

// threshold阈值滑动条回调函数
void threshold_track(int typeValue, void *)
{
  cv::threshold(grey_dst, threshold_dst, thresholds, 255, THRESH_TOZERO);
  imshow("threshold_dst", threshold_dst);
}

// morphologyEx滑动条回调函数
void morphologyEx_track(int typeValue, void *)
{
  cv::Mat element = getStructuringElement(MORPH_ELLIPSE,
                                          Size(g_nStructElementSize,
                                               g_nStructElementSize));
  morphologyEx(threshold_dst, morphologyEx_dst, MORPH_CLOSE, element);
  imshow("morphologyEx_dst", morphologyEx_dst);
}

int main()
{
  cvtColor(src, grey_dst, COLOR_BGR2GRAY); // 灰度化

  // 灰度图调整对比度和亮度
  if (grey_dst.channels() == 1)
  {
    for (int row = 0; row < grey_dst.rows; row++)
    {
      for (int col = 0; col < grey_dst.cols; col++)
      {
        float v = grey_dst.at<uchar>(row, col);
        grey_dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);
        grey_dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha);
        // grey_dst.at<uchar>(row, col) = 255 - grey_dst.at<uchar>(row, col); // 反色
      }
    }
    // namedWindow("grey_dst", WINDOW_AUTOSIZE);
    // imshow("grey_dst", grey_dst);
    // imwrite(GREY_SAVE_PATH, grey_dst);
  }

  namedWindow("threshold_dst", WINDOW_AUTOSIZE);
  cv::createTrackbar("threshold阈值:", "threshold_dst", &thresholds, 255, threshold_track); // 创建threshold阈值滑动条 70
  threshold_track(0, 0);
  waitKey(0);

#if IS_CLOSED
  // 闭运算
  // morphologyEx(threshold_dst, morphologyEx_dst, MORPH_CLOSE, element1);
  // imshow("morphologyEx_dst", morphologyEx_dst);
  namedWindow("morphologyEx_dst", WINDOW_AUTOSIZE);
  cv::createTrackbar("morphologyEx阈值:","morphologyEx_dst", &g_nStructElementSize,50,morphologyEx_track); // 创建morphologyEx滑动条 14
  morphologyEx_track(0, 0);

#else
  // 腐蚀_1
  cv::erode(grey_dst, erode_dst1, element1);
  namedWindow("erode_dst1", WINDOW_AUTOSIZE);
  imshow("erode_dst1", erode_dst1);
  imwrite(ERODE_SAVE_PATH, erode_dst1);

  // 膨胀_1
  cv::dilate(erode_dst1, dilate_dst1, element2);
  namedWindow("dilate_dst", WINDOW_AUTOSIZE);
  imshow("dilate_dst", dilate_dst1);
  imwrite(DILATE_SAVE_PATH, dilate_dst1);

  // 腐蚀_2
  cv::erode(dilate_dst1, erode_dst2, element3);
  namedWindow("erode_dst2", WINDOW_AUTOSIZE);
  imshow("erode_dst2", erode_dst2);

  // 膨胀_2
  cv::dilate(erode_dst2, dilate_dst2, element4);
  namedWindow("dilate_dst2", WINDOW_AUTOSIZE);
  imshow("dilate_dst2", dilate_dst2);

  // imwrite(ERODE_SAVE_PATH, erode_dst2);

#endif

  namedWindow("Test window", WINDOW_AUTOSIZE);
  imshow("Test window", grey_dst);
  // imwrite(SAVE_PATH, grey_dst);
  waitKey(0);

  return 0;
}