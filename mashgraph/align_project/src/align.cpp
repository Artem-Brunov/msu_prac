#include "align.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

double metrikas(Image im_1, Image im_2)
{
	int cols = im_1.n_cols;
        int rows = im_1.n_rows;
	int i = 0, j = 0, raznost = 0, summa = 0;
	double metrika;
	cout << "Hello";
	for(i = 0; i < rows - 1; i ++)
		for(j = 0; j < cols - 1; j++)
		{
			raznost = static_cast<int>(std::get<0>(im_1(i,j))) - static_cast<int>(std::get<0>(im_2(i,j)));
			raznost = raznost * raznost;
			summa = summa + raznost;
		}	
	cout << "Hi";
	metrika = summa / (rows * cols);
	cout << metrika << endl;; 
	return metrika;
}

void best_shift(Image im_1, Image im_2, int* best_1, int* best_2, int* best_3, int* best_4)
{
	int i = 0, j = 0, shift_1 = 15, n = 15, m = 15, shift_2 = 15, shift_3 = 0, shift_4 = 0;
	int cols = im_1.n_cols;
        int rows = im_1.n_rows;
	Image im_3, im_4;
	double metrika_2 = 0, metrika = 999999;
	for(i = shift_1; i > -15; i--)
	{
		for(j = shift_2; j > -15; j --)
		{
			cout << "m" << m << "n" << n;
			cout << "i"<< i << "j" << j << "cols"<< cols-i << "rows" << rows -j<< endl ;
			if(j < 1)
				m = 0;
			if(i < 1)
				n = 0;
			cout << "1" << endl;

			im_3 = im_1.submatrix(n, m, rows - j, cols - i);
			cout << "1" << endl; 
			if(i < 1)
				shift_3++;
			if(j < 1)
				shift_4++;
			im_4 = im_2.submatrix(shift_3, shift_4, rows - j, cols - i);
			cout << "2"<< endl;
			metrika_2 = metrikas(im_3, im_4);

			if(metrika_2 < metrika)
			{
				*best_1 = n;
				*best_2 = m;
				*best_3 = shift_3;
				*best_4 = shift_4;
				metrika = metrika_2;
			}
			m--;
		}
	n--;
	}
}

Image combine(Image im_1, Image im_2, int* best_1, int* best_2, int* best_3, int* best_4)
{
		int cols = im_1.n_cols;
        	int rows = im_1.n_rows;

		int i = 0, j = 0, r = 0, m = 0, n = 0, q = 0, w = 0, g = 0, b = 0;

		for(m = *best_1, n = *best_3, i = 0; i < rows ; m++, n++, i++)
		{
               		for(q = *best_2, w = *best_4, j = 0; j < cols; q++, w++, j++)
                	{
                        	r = std::get<0>(im_1(m, q));
                        	g = std::get<1>(im_2(n, w));
                        	b = std::get<2>(im_1(i,j));
                        	im_1(i,j) = std::make_tuple(r, g, b);
                	}	
        	}
		return im_1;	
}

Image align(Image srcImage, bool isPostprocessing, std::string postprocessingType, double fraction, bool isMirror, bool isInterp, bool isSubpixel, double subScale)
{		
	int cols = srcImage.n_cols;
	int rows = (srcImage.n_rows / 3);

	cout << cols << endl<< rows << endl;	
	int best_1 = 0, best_2 = 0, best_3 = 0, best_4 = 0;
 	
	Image im_B = srcImage.submatrix(0, 0, rows, cols);
	Image im_G = srcImage.submatrix(rows/3, 0, rows, cols);
	Image im_R = srcImage.submatrix(2*rows/3, 0, rows, cols);
	
	best_shift(im_R, im_G, &best_1, &best_2, &best_3, &best_4);
	im_R = combine(im_R, im_G, &best_1, &best_2, &best_3, &best_4);

	srcImage = im_R;
//	printf("%d \n%d \n%p \n%p \n%p \n%p \n %d\n",shift_1, shift_2, best_1, best_2, best_3, best_4, metrika);

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
