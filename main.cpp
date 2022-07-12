#include "Detect.h"
#include <vector>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {
    Detect_target("video","../1920_1.avi",20);
    destroyAllWindows();
    return 0;
}