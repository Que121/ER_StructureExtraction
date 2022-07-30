#include "main.hpp"

int main()
{
  cv::Mat src = imread(TEST_PATH, IMREAD_COLOR);
  cv::Mat grey_dst = Mat ::zeros(src.size(), src.type());
  cv::Mat morphologyEx_dst = Mat ::zeros(src.size(), src.type());
  cv::Mat threshold_dst = Mat ::zeros(src.size(), src.type());
  cv::Mat erode_dst1 = Mat ::zeros(src.size(), src.type());
  cv::Mat erode_dst2 = Mat ::zeros(src.size(), src.type());
  cv::Mat dilate_dst1 = Mat ::zeros(src.size(), src.type());
  cv::Mat dilate_dst2 = Mat ::zeros(src.size(), src.type());

  float alpha = 2.5;                       // 对比度
  float beta = 170;                        // 亮度
  cvtColor(src, grey_dst, COLOR_BGR2GRAY); // 灰度化
  float g_nStructElementSize1 = 4;         //结构元素(内核矩阵)的尺寸
  float g_nStructElementSize2 = 7.5;
  float g_nStructElementSize3 = 6;
  float g_nStructElementSize4 = 3;
  float g_nStructElementSize5 = 6;
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
  cv::Mat element5 = getStructuringElement(MORPH_ELLIPSE,
                                           Size(g_nStructElementSize5,
                                                g_nStructElementSize5));

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

  cv::threshold(grey_dst, threshold_dst, 150, 255, THRESH_BINARY);
  imshow("threshold_dst", threshold_dst);

#if IS_CLOSED
  // 闭运算
  morphologyEx(grey_dst, morphologyEx_dst, MORPH_CLOSE, element1);
  imshow("morphologyEx_dst", morphologyEx_dst);
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

  // namedWindow("Test window", WINDOW_AUTOSIZE);
  // imshow("Test window", grey_dst);
  // imwrite(SAVE_PATH, grey_dst);
  waitKey(0);

  return 0;
}  