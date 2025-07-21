# Video2ASCII 

CLI tool that converts a video into ASCII characters.

## How to use

1. Clone the repository
```
git clone https://github.com/timothewt/Video2ASCII.git
cd Video2ASCII
```

2. 
```
mkdir build
cd build
cmake ..
make
```

3. Start the program with by specifying a video file path
```
./video2ascii /path/to/video.mp4
```

## Dependencies

- OpenCV 

## To Do

- Restructure class (split rendering from logic)
- Save the ASCII video (GIF ?)
- Keyboard control (play/pause)

## License

Apache License 2.0

