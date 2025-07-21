#include "asciiconverter.hpp"
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <span>
#include <stdexcept>
#include <thread>

ASCIIConverter::ASCIIConverter(std::string filename, int width)
    : width(width)
    , video(open_video_file(filename))
    , height(compute_height())
{
    ascii_frame.resize(height * (width + 1));

    fps = video.get(cv::CAP_PROP_FPS);
    frame_duration = std::chrono::milliseconds(static_cast<int>(1000.0 / fps));
}

void ASCIIConverter::run()
{
    bool first_frame = true;

    while (true) {
        auto start = std::chrono::steady_clock::now();
        bool ret = video.read(frame_buffer);
        if (!ret)
            break;

        frame_to_ascii();
        if (first_frame)
            first_frame = false;
        else
            move_cursor_up_left(height, 0);
        std::cout << ascii_frame << std::flush;

        auto elapsed_time = std::chrono::steady_clock::now() - start;
        if (elapsed_time < frame_duration)
            std::this_thread::sleep_for(frame_duration - elapsed_time);
    }
}

cv::VideoCapture ASCIIConverter::open_video_file(std::string& filename)
{
    cv::VideoCapture video { filename };
    if (!video.isOpened()) {
        throw std::runtime_error("[Error] Could not open video file " + filename);
    }
    return video;
}

const int ASCIIConverter::compute_height()
{

    float video_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    float video_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    double aspect_ratio = video_width / video_height;
    return static_cast<int>(width / aspect_ratio * CHAR_ASPECT_RATIO);
}

void ASCIIConverter::move_cursor_up_left(int i, int j)
{
    std::cout << "\033[" << i << "A"
              << "\033[" << j << "D"
              << std::flush;
}

char ASCIIConverter::pixel_to_char(uchar pixel)
{
    pixel = 255 - pixel; // for dark theme console
    int idx = static_cast<int>(pixel * GRAY_MAPPING_SCALING);
    idx = std::min(idx, 68);
    return GRAY_MAPPING[idx];
}

void ASCIIConverter::frame_to_ascii()
{
    cv::cvtColor(frame_buffer, gray_frame_buffer, cv::COLOR_BGR2GRAY);
    cv::resize(gray_frame_buffer, resized_frame_buffer, { width, height });

    std::span<const uchar> pixels { resized_frame_buffer.data, static_cast<size_t>(height * width) };
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ascii_frame[i * (width + 1) + j] = pixel_to_char(pixels[i * width + j]);
        }
        ascii_frame[i * (width + 1) + width] = '\n';
    }
}
