// morphology.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int max_kernel_size = 21;

const char* window_name = "Morphology Transformations Demo";

void Morphology_Operations(int, void*);

int main(int argc,char** argv)
{
	CommandLineParser parser(argc, argv, "{@input |H:\\opencv\\sources\\samples\\data\\baboon.jpg| input image}");
	src = imread(parser.get<String>("@input"), IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage:" << argv[0] << "<Input image>" << endl;
		return -1;
	}
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar("Operator:\n 0:Opening - 1:Closing \n 2:Gradient -3:Top Hat\n 4:Black Hat", 
		window_name, &morph_operator, max_operator, Morphology_Operations);
	createTrackbar("Element:\n 0:Rect -1:Cross -2:Ellipse", window_name, &morph_elem, max_elem, Morphology_Operations);
	createTrackbar("Kernel size:\n 2n+1", window_name, &morph_size, max_kernel_size, Morphology_Operations);
	Morphology_Operations(0, 0);
	waitKey(0);
	return 0;
}
void Morphology_Operations(int, void*)
{
	int operation = morph_operator + 2;
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, dst, operation, element);
	imshow(window_name, dst);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
