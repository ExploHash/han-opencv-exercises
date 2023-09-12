#include <opencv2/opencv.hpp>

int main() {
  // Read image
  cv::Mat image = cv::imread("./res/dark_flower.bmp");

  // To hsv
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Split channels
  std::vector<cv::Mat> channels;
  cv::split(hsv, channels);

  // Show channels
  cv::imshow("Hue", channels[0]);
  cv::imshow("Saturation", channels[1]);
  cv::imshow("Value", channels[2]);

  // Wait for any key press
  cv::waitKey(0);
  cv::destroyAllWindows();
}
