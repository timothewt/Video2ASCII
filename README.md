# Video2ASCII

CLI tool that converts a video into ASCII characters. This allows you to play any video in the console, either for fun or for convenience, e.g., when you're connected to a remote via SSH.

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

## Demonstration

| Input | Result |
|-------|--------|
|![Input](./assets/input.gif)|![Result](./assets/result.gif)|

## Dependencies

- OpenCV 

## To Do

- Save the ASCII video (GIF ?)
- Keyboard control (play/pause)

## License

Apache License 2.0

