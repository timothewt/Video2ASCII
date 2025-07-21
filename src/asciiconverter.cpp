#include "asciiconverter.hpp"
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <span>
#include <string>

ASCIIConverter::ASCIIConverter(int width, int height)
    : width(width)
    , height(height)
{
}

char ASCIIConverter::pixel_to_char(uchar pixel)
{
    pixel = 255 - pixel; // for dark theme console
    int idx = static_cast<int>(pixel * GRAY_MAPPING_SCALING);
    idx = std::min(idx, 68);
    return GRAY_MAPPING[idx];
}

std::string ASCIIConverter::frame_to_ascii(cv::Mat frame)
{
    cv::cvtColor(frame, gray_frame_buffer, cv::COLOR_BGR2GRAY);
    cv::resize(gray_frame_buffer, resized_frame_buffer, { width, height });

    std::string ascii_frame;
    ascii_frame.reserve((width + 1) * height);
    std::span<const uchar> pixels { resized_frame_buffer.data, static_cast<size_t>(height * width) };
    for (int i = 0; i < height; ++i) {
        int row_offset = i * width;
        for (int j = 0; j < width; ++j)
            ascii_frame.push_back(pixel_to_char(pixels[row_offset + j]));
        ascii_frame.push_back('\n');
    }

    return ascii_frame;
}
