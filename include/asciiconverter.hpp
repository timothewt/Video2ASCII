#pragma once

#include <opencv2/opencv.hpp>
#include <string>

/**< The mapping of a pixel brightness into the corresponding ASCII character. */
constexpr char GRAY_MAPPING[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"     ";
/**< The scaling to get the correct index in the pixel to character mapping. */
constexpr float GRAY_MAPPING_SCALING = 69.0 / 255.0;
/**< The aspect ratio of the console character, used to determine the output height. */
constexpr float CHAR_ASPECT_RATIO = 0.55;

/**
 * Converter of image to ASCII string frame.
 */
class ASCIIConverter {
public:
    /**
     * @brief Class constructor from the video to render.
     *
     * @param width Width of the printed video in the unit of the number of characters.
     * @param height Height of the printed video in number of terminal lines.
     */
    ASCIIConverter(int width, int height);
    /**
     * @brief Converts a frame of grayscale pixels into a 2d array of ASCII characters.
     *
     * @param frame The frame to convert to ASCII.
     * @return The frame as a string.
     */
    std::string frame_to_ascii(cv::Mat frame);

private:
    const int width; /**< Width, in characters number, of the printed video. */
    const int height; /**< Width, in terminal lines number, of the printed video. */
    cv::Mat gray_frame_buffer {}; /**< Used to keep the cv::Mat instance of the grayscale frame buffer. */
    cv::Mat resized_frame_buffer {}; /**< Used to keep the cv::Mat instance of the resized frame buffer. */
    /**
     * @brief Gets the ASCII character equivalent of a grayscale pixel.
     *
     * @param pixel Pixel to convert to a character.
     * @return The equivalent character depending on the pixel's brightness.
     */
    char pixel_to_char(uchar pixel);
};
