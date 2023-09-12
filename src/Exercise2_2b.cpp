#include <opencv2/opencv.hpp>

int main() {
  cv::Mat noisy_image = cv::imread("./res/barn_noisy.jpg");
  cv::Mat denoised_image;

  cv::fastNlMeansDenoisingColored(noisy_image, denoised_image, 5, 10, 7, 21);

  cv::imshow("Noisy", noisy_image);
  cv::imshow("Denoised", denoised_image);

  cv::waitKey(0);
  cv::destroyAllWindows();
}
