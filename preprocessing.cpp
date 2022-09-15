// #include "preprocessing.hpp"

// cv::Mat src;
// cv::Mat dst;

// float alpha = 2.5;                // 对比度
// float beta = 170;                 // 亮度
// float g_nStructElementSize1 = 30; //结构元素(内核矩阵)的尺寸
// float g_nStructElementSize2 = 7.5;
// float g_nStructElementSize3 = 6;
// float g_nStructElementSize4 = 3;
// float g_nStructElementSize5 = 6;

// int g_nStructElementSize = 17;
// int g_nStructElementSize_Debug = 0;
// int thresholds = 70;
// int thresholds_Debug = 0;
// int selectContoursMin = 100;
// int selectContoursMin_Debug = 0;

// vector<vector<Point>> contours;
// vector<Vec4i> hierarchy;

// // 反色
// void invertColor(cv::Mat &dst)
// {
//   if (dst.channels() == 1)
//   {
//     for (int row = 0; row < dst.rows; row++)
//     {
//       for (int col = 0; col < dst.cols; col++)
//       {
//         float v = dst.at<uchar>(row, col);
//         dst.at<uchar>(row, col) = 255 - dst.at<uchar>(row, col); // 反色
//       }
//     }
//   }
// }

// // 灰度化与提亮
// void greyAndBrightness(cv::Mat &src, cv::Mat &dst)
// {
//   cvtColor(src, dst, COLOR_BGR2GRAY); // 灰度化
//   if (dst.channels() == 1)
//   {
//     for (int row = 0; row < dst.rows; row++)
//     {
//       for (int col = 0; col < dst.cols; col++)
//       {
//         float v = dst.at<uchar>(row, col);
//         dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);
//         dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha);
//       }
//     }
//     // namedWindow("grey_dst", WINDOW_AUTOSIZE);
//     // imshow("grey_dst", grey_dst);
//     // imwrite(GREY_SAVE_PATH, grey_dst);
//   }
// }

// // threshold阈值滑动条回调函数
// void threshold_track(int typeValue, void *)
// {
//   cv::threshold(dst, dst, thresholds_Debug, 255, THRESH_TOZERO);
//   cv::imshow("threshold_dst", dst);
// }

// // thresholds二值化处理
// void thresholdsProcessing(cv::Mat &dst)
// {
// #if IS_DEBUG_THRESHOLD
//   namedWindow("threshold_dst", WINDOW_AUTOSIZE);
//   cv::createTrackbar("threshold阈值:", "threshold_dst", &thresholds_Debug, 255, threshold_track); // 创建threshold阈值滑动条 70
//   threshold_track(0, 0);
// #else
//   cv::threshold(dst, dst, thresholds, 255, THRESH_TOZERO);
// #endif
// }

// // morphologyEx滑动条回调函数
// void morphologyEx_track(int typeValue, void *)
// {
//   cv::Mat element = getStructuringElement(MORPH_ELLIPSE,
//                                           Size(g_nStructElementSize_Debug,
//                                                g_nStructElementSize_Debug));
//   morphologyEx(dst, dst, MORPH_CLOSE, element);
//   imshow("morphologyEx_dst", dst);
// }

// // 闭运算
// void closedoPerations(cv::Mat &dst)
// {
// #if IS_DEBUG_MORPHOLOGYEX
//   namedWindow("morphologyEx_dst", WINDOW_AUTOSIZE);
//   cv::createTrackbar("morphologyEx阈值:", "morphologyEx_dst", &g_nStructElementSize, 50, morphologyEx_track); // 创建morphologyEx滑动条 14
//   morphologyEx_track(0, 0);
// #else
//   morphologyEx(dst, dst, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(g_nStructElementSize, g_nStructElementSize)));
//   cv::imshow("morphologyEx_dst", dst);
// #endif
// }

// // 绘制轮廓
// void drawContours(cv::Mat &dst)
// {
//   findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
//   Mat imageContours = Mat::zeros(dst.size(), CV_8UC1);
//   Mat Contours = Mat::zeros(dst.size(), CV_8UC1); //绘制
//   for (int i = 0; i < contours.size(); i++)
//   {
//     // contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数
//     for (int j = 0; j < contours[i].size(); j++)
//     {
//       //绘制出contours向量内所有的像素点
//       Point P = Point(contours[i][j].x, contours[i][j].y);
//       Contours.at<uchar>(P) = 255;
//     }

// #if IS_DEBUG_HIERARCHY
//     //输出hierarchy向量内容
//     char ch[256];
//     sprintf(ch, "%d", i);
//     string str = ch;
//     cout << "向量hierarchy的第" << str << " 个元素内容为：" << endl
//          << hierarchy[i] << endl
//          << endl;
// #endif

//     //绘制轮廓
//     drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
//   }
//   invertColor(imageContours);
//   imshow("Contours Image", imageContours); //轮廓
//   imshow("Point of Contours", Contours);   //向量contours内保存的所有轮廓点集
// }

// // contours面积筛选回调函数
// void selectContours_track(int typeValue, void *)
// {
//   vector<vector<Point>>::iterator iter = contours.begin();
//   for (; iter != contours.end();)
//   {
//     double g_dConArea = contourArea(*iter);
//     if (g_dConArea < selectContoursMin_Debug)
//     {
//       iter = contours.erase(iter);
//     }
//     else
//     {
//       ++iter;
//     }
//   }
//   cout << "【筛选后总共轮廓个数为：" << (int)contours.size() << endl;
//   Mat result(dst.size(), CV_8U, Scalar(0));
//   drawContours(result, contours, -1, Scalar(255), -1); // -1 表示所有轮廓
//   namedWindow("selectContours_dst");
//   cv::imshow("selectContours_dst", result);
// }

// // 轮廓过滤
// void contoursFilter(cv::Mat &dst)
// {
//   cout << "【筛选前总共轮廓个数为】：" << (int)contours.size() << endl;
//   for (int i = 0; i < (int)contours.size(); i++)
//   {
//     double g_dConArea = contourArea(contours[i], true);
//     // cout << "【用轮廓面积计算函数计算出来的第" << i << "个轮廓的面积为：】" << g_dConArea << endl;
//   }
// #if IS_DEBUG_SELECTCONTOURS
//   namedWindow("selectContours_dst", WINDOW_AUTOSIZE);
//   cv::createTrackbar("selectContours最大值:", "selectContours_dst", &selectContoursMin_Debug, 1000, selectContours_track);
//   selectContours_track(0, 0);
// #else
//   //筛选剔除掉面积小于100的轮廓
//   vector<vector<Point>>::iterator iter = contours.begin();
//   for (; iter != contours.end();)
//   {
//     double g_dConArea = contourArea(*iter);
//     if (g_dConArea < selectContoursMin)
//     {
//       iter = contours.erase(iter);
//     }
//     else
//     {
//       ++iter;
//     }
//   }
//   cout << "【筛选后总共轮廓个数为：" << (int)contours.size() << endl;
//   Mat result(dst.size(), CV_8U, Scalar(0));
//   drawContours(result, contours, -1, Scalar(255), -1); // -1 表示所有轮廓
//   namedWindow("result");
//   imshow("result", result);
// #endif
// }
