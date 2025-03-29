#include <opencv2/opencv.hpp>
#include <vector>

int main(int argc, char** argv) {
    // Video source: usa webcam se non dai un path
    cv::VideoCapture cap;
    if (argc > 1)
        cap.open(argv[1]);  // video path
    else
        cap.open(0);        // webcam

    if (!cap.isOpened()) {
        std::cerr << "Errore: impossibile aprire il video." << std::endl;
        return -1;
    }

    cv::Mat frame, gray, blurred, thresh, morph;
    cv::namedWindow("Tracking", cv::WINDOW_NORMAL);

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Blur per ridurre il rumore
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

        // Threshold inverso perché lo sfondo è bianco
        cv::threshold(blurred, thresh, 200, 255, cv::THRESH_BINARY_INV);

        // Operazioni morfologiche per pulire
        cv::morphologyEx(thresh, morph, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, {3,3}));

        // Trova contorni (ogni formica è un contorno)
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(morph, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            if (area < 50 || area > 5000) continue; // filtra piccoli/rumorosi o troppo grandi

            // Bounding box
            cv::Rect bbox = cv::boundingRect(contour);
            cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2);

            // Disegna contorno preciso
            cv::drawContours(frame, std::vector<std::vector<cv::Point>>{contour}, -1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Tracking", frame);
        if (cv::waitKey(30) == 27) break; // ESC per uscire
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
