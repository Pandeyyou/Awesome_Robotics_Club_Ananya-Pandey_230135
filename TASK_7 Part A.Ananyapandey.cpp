#include <iostream>
#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    cv::Mat image;

    ImageProcessor(const std::string& filename) {
        image = cv::imread(filename);
        if (image.empty()) {
            std::cerr << "Error: Unable to read image file." << std::endl;
            return;
        }
    }

    void removeNoise() {
        cv::Mat grayImage, blurredImage, thresholdedImage;
        
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0);
        cv::threshold(blurredImage, thresholdedImage, 200, 255, cv::THRESH_BINARY);
        
        cv::imshow("Processed Image", thresholdedImage);
        cv::waitKey(0);
    }
};

int main() {
    ImageProcessor processor("grid_image.png");
    processor.removeNoise();

    return 0;
}
