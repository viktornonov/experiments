#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char **argv) {
    namedWindow("Jonkata", WINDOW_AUTOSIZE);
    VideoCapture cap;
    cap.open(argv[1]);
    Mat frame;
    while(true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        imshow("jonkataFrame", frame); //display the newly fetched frame
        if(waitKey(33) >= 0) { //waitKey waits for 33ms and if key is pressed returns value >= 0. It's 33 because 33ms * 30 fps = 990ms (1 second)
            break;
        }
    }
    return 0;
}
