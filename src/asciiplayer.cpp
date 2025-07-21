
#include "asciiplayer.hpp"
#include "asciiconverter.hpp"
#include <chrono>
#include <iostream>
#include <thread>

ASCIIPlayer::ASCIIPlayer(std::string filename, int width)
    : video(open_video_file(filename))
    , width(width)
    , height(compute_height())
    , ascii_converter(width, height)
    , frame_duration(compute_frame_duration())
{
}

void ASCIIPlayer::play()
{
    bool first_frame = true;

    while (true) {
        auto start = std::chrono::steady_clock::now();
        cv::Mat frame;
        bool ret = video.read(frame);
        if (!ret)
            break;

        std::string ascii_frame = ascii_converter.frame_to_ascii(frame);
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

cv::VideoCapture ASCIIPlayer::open_video_file(std::string& filename)
{
    cv::VideoCapture video { filename };
    if (!video.isOpened()) {
        throw std::runtime_error("[Error] Could not open video file " + filename);
    }
    return video;
}

const int ASCIIPlayer::compute_height()
{

    float video_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    float video_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    double aspect_ratio = video_width / video_height;
    return static_cast<int>(width / aspect_ratio * CHAR_ASPECT_RATIO);
}

const std::chrono::milliseconds ASCIIPlayer::compute_frame_duration()
{
    double fps = video.get(cv::CAP_PROP_FPS);
    return std::chrono::milliseconds(static_cast<int>(1000.0 / fps));
}

void ASCIIPlayer::move_cursor_up_left(int i, int j)
{
    std::cout << "\033[" << i << "A"
              << "\033[" << j << "D"
              << std::flush;
}
