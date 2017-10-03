#include "align.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

Image align(Image srcImage, bool isPostprocessing, std::string postprocessingType, double fraction, bool isMirror, bool isInterp, bool isSubpixel, double subScale)
{		
	int cols = srcImage.n_cols;
	int rows = srcImage.n_rows;
	
	int d = 0, s = 0, flag = 0, r = 0, g = 0, b = 0, i = 0, j = 0;

 	Image im_B = srcImage.submatrix(0, 0, rows/3, cols);
	Image im_G = srcImage.submatrix(rows/3, 0, rows/3, cols);
	Image im_R = srcImage.submatrix(2*rows/3, 0, rows/3, cols);
	
	save_image(im_B, "../image1.bmp");
	save_image(im_G, "../image2.bmp");
 	save_image(im_R, "../image3.bmp");
	for(d = -15; d < (rows/3 + 15); d++)
		for(s = -15; s < (rows/3 + 15); s++)
		{
		}
	for(i = 0; i < rows/3; i++)
	{
		for(j = 0; j < cols; j++)
		{
			r = std::get<0>(im_R(i,j));
			g = std::get<1>(im_G(i,j));
		//	b = std::get<2>(im_B(i,j));
			srcImage(i,j) = std::make_tuple(r, g, b);
		}
	}
    	return srcImage;
}

Image sobel_x(Image src_image) {
    Matrix<double> kernel = {{-1, 0, 1},
                             {-2, 0, 2},
                             {-1, 0, 1}};
    return custom(src_image, kernel);
}

Image sobel_y(Image src_image) {
    Matrix<double> kernel = {{ 1,  2,  1},
                             { 0,  0,  0},
                             {-1, -2, -1}};
    return custom(src_image, kernel);
}

Image unsharp(Image src_image) {
    return src_image;
}

Image gray_world(Image src_image) {
    return src_image;
}

Image resize(Image src_image, double scale) {
    return src_image;
}

Image custom(Image src_image, Matrix<double> kernel) {
    // Function custom is useful for making concrete linear filtrations
    // like gaussian or sobel. So, we assume that you implement custom
    // and then implement other filtrations using this function.
    // sobel_x and sobel_y are given as an example.
    return src_image;
}

Image autocontrast(Image src_image, double fraction) {
    return src_image;
}

Image gaussian(Image src_image, double sigma, int radius)  {
    return src_image;
}

Image gaussian_separable(Image src_image, double sigma, int radius) {
    return src_image;
}

Image median(Image src_image, int radius) {
    return src_image;
}

Image median_linear(Image src_image, int radius) {
    return src_image;
}

Image median_const(Image src_image, int radius) {
    return src_image;
}

Image canny(Image src_image, int threshold1, int threshold2) {
    return src_image;
}
