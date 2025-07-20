#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

/**< The mapping of a pixel brightness into the corresponding ASCII character. */
constexpr char GRAY_MAPPING[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"     ";
/**< The scaling to get the correct index in the pixel to character mapping. */
constexpr float GRAY_MAPPING_SCALING = 69.0 / 255.0;

/**
 * @brief Clears the console to print the next frame properly.
 */
void clear_console();
/**
 * @brief Gets the ASCII character equivalent of a grayscale pixel.
 *
 * @param pixel Pixel to convert to a character.
 * @return The equivalent character depending on the pixel's brightness.
 */
char pixel_to_char(uchar pixel);
/**
 * @brief Resizes the frame to the correct width and height for printing in to the console, using the desired width.
 *
 * @param frame The frame to resize.
 * @param new_width The desired frame width in number of characters.
 * @return The resized frame.
 */
cv::Mat resize_frame(const cv::Mat& frame, int new_width);
/**
 * @brief Converts a frame of grayscale pixels into a 2d array of ASCII characters.
 *
 * @param frame The frame to convert to ASCII.
 * @return The 2d array of characters depicting the frame in ASCII characters.
 */
std::vector<std::vector<char>> frame_to_ascii(const cv::Mat& frame);
/**
 * @brief Prints a frame of ASCII character stored in a 2d array. The console should be cleared beforehand.
 *
 * @param frame The frame to print to the console.
 */
void print_ascii_frame(const std::vector<std::vector<char>>& frame);
