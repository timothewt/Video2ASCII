#include "asciiplayer.hpp"
#include <opencv2/opencv.hpp>
#include <stdexcept>

int main(int argc, char** argv)
{
    if (argc < 2)
        throw std::runtime_error("Usage: ./video2ASCII <video_path> [width]");
    int width {};
    if (argc == 3)
        width = std::stoi(argv[2]);
    else
        width = 80;

    ASCIIPlayer ascii_player = ASCIIPlayer(argv[1], width);
    ascii_player.play();

    return 0;
}
