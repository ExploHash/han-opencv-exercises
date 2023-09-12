#include <opencv2/opencv.hpp>

int main() {
  // Read image
  cv::Mat image = cv::imread("./res/dark_flower.bmp");

  // Show image
  cv::imshow("Original", image);

  // Split channels
  std::vector<cv::Mat> channels;
  cv::split(image, channels);

  // Show channels
  cv::imshow("Blue", channels[0]);
  cv::imshow("Green", channels[1]);
  cv::imshow("Red", channels[2]);

  // Wait for any key press
  cv::waitKey(0);
  cv::destroyAllWindows();
}
