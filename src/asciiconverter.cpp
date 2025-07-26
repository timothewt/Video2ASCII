#include "asciiconverter.hpp"
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <span>
#include <sstream>
#include <string>

ASCIIConverter::ASCIIConverter(int width, int height)
    : width(width)
    , height(height)
{
}

std::string ASCIIConverter::frame_to_ascii(cv::Mat frame)
{
    cv::resize(frame, resized_frame_buffer, { width, height });
    cv::cvtColor(resized_frame_buffer, gray_frame_buffer, cv::COLOR_BGR2GRAY);

    std::string ascii_frame;
    ascii_frame.reserve((width + 1) * height);
    std::span<const uchar> gray_pixels { gray_frame_buffer.data, static_cast<size_t>(height * width) };
    std::span<const cv::Vec3b> rgb_pixels {
        reinterpret_cast<const cv::Vec3b*>(resized_frame_buffer.data),
        static_cast<size_t>(height * width)
    };
    for (int i = 0; i < height; ++i) {
        int row_offset = i * width;
        for (int j = 0; j < width; ++j) {
            char character = pixel_to_char(gray_pixels[row_offset + j]);
            cv::Vec3b rgb = rgb_pixels[row_offset + j];
            ascii_frame.append(get_colored_char(character, rgb));
        }
        ascii_frame.push_back('\n');
    }

    return ascii_frame;
}

char ASCIIConverter::pixel_to_char(uchar pixel)
{
    pixel = 255 - pixel; // for dark theme console
    int idx = static_cast<int>(pixel * GRAY_MAPPING_SCALING);
    idx = std::min(idx, 68);
    return GRAY_MAPPING[idx];
}

std::string ASCIIConverter::get_colored_char(char character, cv::Vec3b pixel)
{
    std::stringstream ss;
    ss << "\033[38;2;"
       << static_cast<int>(pixel[2])
       << ";"
       << static_cast<int>(pixel[1])
       << ";"
       << static_cast<int>(pixel[0])
       << "m"
       << character
       << "\033[0m";
    return ss.str();
}
