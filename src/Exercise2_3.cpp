#include <opencv2/opencv.hpp>

// Stolen from @VinnieTheProgrammer
std::vector<std::vector<cv::Point>> calculateCorners(std::vector<std::vector<cv::Point>> contours) {
    std::vector<std::vector<cv::Point> > corners (contours.size());
    for(size_t i = 0; i< contours.size(); i++ ) {
        cv::approxPolyDP(contours[i], corners[i], arcLength(contours[i], true) * 0.02, true);
    }
    return corners;
}

std::vector<cv::Point> findLicensePlate(cv::Mat image){
  cv::Mat blackMask;

  // Remove red colors  
  cv::Mat removedRed = image.clone();
  cv::inRange(image, cv::Scalar(0, 0, 0), cv::Scalar(100, 100, 255), blackMask);
  removedRed.setTo(cv::Scalar(0, 0, 0), blackMask);

  // Find blobs
  cv::Mat gray;
  cv::cvtColor(removedRed, gray, cv::COLOR_BGR2GRAY);
  cv::Mat binary;
  cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

  // Find contours
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

  // Find biggest contour
  int biggestContourIndex = 0;
  double biggestContourArea = 0;

  for (int i = 0; i < contours.size(); i++) {
    double area = cv::contourArea(contours[i]);
    if (area > biggestContourArea) {
      biggestContourArea = area;
      biggestContourIndex = i;
    }
  }

  return contours[biggestContourIndex];
}

cv::Mat transformLicencePlate(cv::Mat image, std::vector<cv::Point> licensePlateContour){
  // Get corners
  std::vector<std::vector<cv::Point>> contoursArray = {licensePlateContour};
  std::vector<std::vector<cv::Point>> corners = calculateCorners(contoursArray);

  int width = cv::norm(corners[0][0] - corners[0][1]);
  int height = cv::norm(corners[0][1] - corners[0][2]);

  // Original corners
  std::vector<cv::Point2f> originalCorners = {corners[0][0], corners[0][1], corners[0][2], corners[0][3]};
  std::vector<cv::Point2f> wantedCorners = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(width, height), cv::Point2f(0, height)};

  // Transform
  cv::Mat transform = cv::getPerspectiveTransform(originalCorners, wantedCorners);
  cv::Mat transformedImage;
  cv::warpPerspective(image, transformedImage, transform, cv::Size(width, height));

  cv::flip(transformedImage, transformedImage, 1);

  return transformedImage;
}

int main() {
  cv::Mat image = cv::imread("./res/LicensePlate1.jpg");

  cv::imshow("Original", image);
 
  std::vector<cv::Point> licensePlateContour = findLicensePlate(image);
  cv::Mat transformedImage = transformLicencePlate(image, licensePlateContour);

  cv::imshow("Transformed", transformedImage);

  // Wait for any key press
  cv::waitKey(0);
  cv::destroyAllWindows();
}