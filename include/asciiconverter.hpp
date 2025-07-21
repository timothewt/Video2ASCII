#pragma once

#include <chrono>
#include <opencv2/opencv.hpp>
#include <string>

/**< The mapping of a pixel brightness into the corresponding ASCII character. */
constexpr char GRAY_MAPPING[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"     ";
/**< The scaling to get the correct index in the pixel to character mapping. */
constexpr float GRAY_MAPPING_SCALING = 69.0 / 255.0;
/**< The aspect ratio of the console character, used to determine the output height. */
constexpr float CHAR_ASPECT_RATIO = 0.55;

class ASCIIConverter {
public:
    /**
     * @brief Class constructor from the video to render.
     *
     * @param video Video to render in ASCII.
     * @param width Value of the printed video width in the unit of the number of characters.
     */
    ASCIIConverter(std::string filename, int width);
    /**
     * @brief Runs the program to print the video to the console.
     */
    void run();

private:
    cv::VideoCapture video;
    double fps;
    std::chrono::milliseconds frame_duration;
    const int width;
    const int height;
    cv::Mat frame_buffer {};
    cv::Mat gray_frame_buffer {};
    cv::Mat resized_frame_buffer {};
    std::string ascii_frame {};
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
     * @brief Moves the cursor up and left to re-write upon the previous frame.
     */
    void move_cursor_up_left(int i, int j);
    /**
     * @brief Gets the ASCII character equivalent of a grayscale pixel.
     *
     * @param pixel Pixel to convert to a character.
     * @return The equivalent character depending on the pixel's brightness.
     */
    char pixel_to_char(uchar pixel);
    /**
     * @brief Converts a frame of grayscale pixels into a 2d array of ASCII characters.
     */
    void frame_to_ascii();
};
