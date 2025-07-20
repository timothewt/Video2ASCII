#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void clear_console()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

char pixel_to_char(uchar pixel)
{
    pixel = 255 - pixel;
    int idx = static_cast<int>(pixel * GRAY_MAPPING_SCALING);
    idx = std::min(idx, 68);
    return GRAY_MAPPING[idx];
}

cv::Mat resize_frame(const cv::Mat& frame, int new_width)
{
    double aspect_ratio = static_cast<double>(frame.rows) / frame.cols;
    int new_height = static_cast<int>(aspect_ratio * new_width * 0.55);

    cv::Mat resized_frame;
    cv::resize(frame, resized_frame, { new_width, new_height });
    return resized_frame;
}

std::vector<std::vector<char>> frame_to_ascii(const cv::Mat& frame)
{
    std::vector<std::vector<char>> result {};
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

    result.resize(gray_frame.rows);
    for (int i = 0; i < gray_frame.rows; ++i) {
        result[i].resize(gray_frame.cols);
        for (int j = 0; j < gray_frame.cols; ++j) {
            result[i][j] = pixel_to_char(gray_frame.at<uchar>(i, j));
        }
    }

    return result;
}

void print_ascii_frame(const std::vector<std::vector<char>>& frame)
{
    std::string output {};
    for (auto row : frame) {
        for (auto ascii_pixel : row)
            output += ascii_pixel;
        output += '\n';
    }
    std::cout << output << std::endl;
}
