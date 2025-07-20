#include "utils.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

int WIDTH = 80;

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: ./video2ASCII <video_path> [width]" << std::endl;
        return -1;
    }
    if (argc == 3)
        WIDTH = std::stoi(argv[2]);

    cv::VideoCapture video(argv[1]);
    if (!video.isOpened()) {
        std::cout << "[Error] Could not open video file " << argv[1] << "." << std::endl;
        return -1;
    }

    double fps = video.get(cv::CAP_PROP_FPS);
    auto frame_duration = std::chrono::milliseconds(static_cast<int>(1000.0 / fps));

    while (true) {
        auto start = std::chrono::steady_clock::now();
        cv::Mat frame;
        bool ret = video.read(frame);
        if (!ret)
            break;

        auto resized_frame = resize_frame(frame, WIDTH);
        auto ascii_frame = frame_to_ascii(resized_frame);
        clear_console();
        print_ascii_frame(ascii_frame);

        auto elapsed_time = std::chrono::steady_clock::now() - start;
        if (elapsed_time < frame_duration)
            std::this_thread::sleep_for(frame_duration - elapsed_time);
    }

    video.release();
    return 0;
}
