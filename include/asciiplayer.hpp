#pragma once

#include "asciiconverter.hpp"
#include <chrono>
#include <opencv2/opencv.hpp>
#include <string>

/**
 * ASCII video player, to read a video in the console.
 */
class ASCIIPlayer {
public:
    /**
     * @brief Class constructor.
     *
     * @param filename Path of the video file to play.
     * @param width Width, in characters number, of the video output.
     */
    ASCIIPlayer(std::string filename, int width);
    /**
     * @brief Plays the given video in the console, with the specified parameters.
     */
    void play();

private:
    cv::VideoCapture video; /**< Original video to play in the console. */
    int width; /**< Width, in characters number, of the video output. */
    int height; /**< Height, in terminal lines number, of the video output. */
    ASCIIConverter ascii_converter; /**< Instance of the image to ASCII converter for a fixed width / height. */
    std::chrono::milliseconds frame_duration; /**< Duration of a single video frame. */

    /**
     * @brief Opens the video file.
     *
     * @param filename Name and path of the video file.
     * @return Returns the video file as a cv::VideoCapture instance.
     */
    cv::VideoCapture open_video_file(std::string& filename);
    /**
     * @brief Computes the height of the video render.
     *
     * @return The height depending on the video apsect ratio and desired width.
     */
    const int compute_height();
    /**
     * @brief Computes the duration of a single frame to stay in sync during render.
     *
     * @return The duration of a single video frame in ms.
     */
    const std::chrono::milliseconds compute_frame_duration();
    /**
     * @brief Moves the cursor up and left to re-write upon the previous frame.
     */
    void move_cursor_up_left(int i, int j);
};
