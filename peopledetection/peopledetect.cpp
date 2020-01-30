#include <iostream>
#include <opencv2/opencv.hpp>
#include "videoio_c.h"
#include "highgui/highgui_c.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;
int counter;

int main (int argc, const char * argv[])
{
    VideoCapture cap(CV_CAP_ANY);		//capture live video from camera
    cap.set(CV_CAP_PROP_FPS, 30);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);   
    //cap.set(CV_CAP_PROP_CONVERT_RGB , false); 
    if (!cap.isOpened())
        return -1;
 
    Mat img;
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
 
    namedWindow("video capture", CV_WINDOW_AUTOSIZE);
    while (true)
    {
        cap >> img;
        if (!img.data)
            continue;
 
        vector<Rect> found, found_filtered;
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(16,16), 1.05, 2);
 
        size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            counter = found.size();		//function to determine if person or not.
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                found_filtered.push_back(r);
        }
        for (i=0; i<found_filtered.size(); i++)
        {
        Rect r = found_filtered[i];			//draw rectangle when person is found
            r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.06);
        r.height = cvRound(r.height*0.9);
        rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
        }
        {
            ostringstream buf;				//print person count on live feed
            buf << "People: " << counter;
            putText(img, buf.str(), Point(10, 30), FONT_HERSHEY_PLAIN, 1.5, Scalar(0, 0, 255), 2, LINE_AA);
        }
        imshow("video capture", img);
        if (waitKey(20) >= 0)
            break;
        //cout << counter << endl;	//print person count in terminal
        counter = 0;
    }
    return 0;
}