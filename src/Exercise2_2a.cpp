#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  std::cout << "Press any key to capture an image" << std::endl;
  cv::Mat capture;
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }

  cap.read(capture);
  cv::imshow("Original", capture);

  // Gaussian noise
  cv::Mat noise(capture.size(),capture.type());
  float m = (10,12,34);
  float sigma = (1,5,50);
  cv::randn(noise, m, sigma); //mean and variance
  
  cv::Mat noisy_image = capture + noise;
  cv::imshow("Noisy", noisy_image);

  // Salt and pepper noise
  cv::Mat saltpepper_noise = cv::Mat::zeros(capture.size(), capture.type());
  cv::randu(saltpepper_noise, 0, 255);
  cv::Mat black = saltpepper_noise < 10;
  cv::Mat white = saltpepper_noise > 245;
  cv::Mat saltpepper_image = capture.clone();
  saltpepper_image.setTo(255, white);
  saltpepper_image.setTo(0, black);
  cv::imshow("Salt and pepper", saltpepper_image);

  cv::waitKey(0);
  cv::destroyAllWindows();
}
