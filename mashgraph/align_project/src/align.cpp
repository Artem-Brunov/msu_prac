#include "align.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

double metrik_kor(Image im_1, Image im_2)
{
        int cols = im_1.n_cols;
        int rows = im_1.n_rows;
        int i = 0, j = 0, raznost = 0, summa = 0;
        double metrika;
        for(i = 1; i < rows - 1; i ++)
                for(j = 1; j < cols - 1; j++)
                {       
                        raznost = static_cast<int>(std::get<0>(im_1(i,j))) * static_cast<int>(std::get<0>(im_2(i,j)));
                        summa = summa + raznost;
                }
        metrika = summa;
        return metrika;
}

double metrikas(Image im_1, Image im_2)
{
	int cols = im_1.n_cols;
        int rows = im_1.n_rows;
	int i = 0, j = 0, raznost = 0, summa = 0;
	double metrika;
	for(i = 1; i < rows - 1; i ++)
		for(j = 1; j < cols - 1; j++)
		{
			raznost = static_cast<int>(std::get<0>(im_1(i,j))) - static_cast<int>(std::get<0>(im_2(i,j)));
			raznost = raznost * raznost;
			summa = summa + raznost;
		}	
	metrika = summa / (rows * cols);
	return metrika;
}

void best_shift(Image im_1, Image im_2, int* best_1, int* best_2, int* best_3, int* best_4)
{	
	int i, j, n = 15, m = 15, p = 15, q = 15, w = 0, e = 0;
	int cols = im_1.n_cols;
        int rows = im_1.n_rows;


	Image im_3, im_4;
	double  metrika, min = 99999; 
	for(i = 30; i > -1; i--)
	{
		q = 15;
		m = 15;
		e = 0;
		cout << "i"<< i<<endl; 
		for(j = 30; j > -1; j--)
		{
			im_3 = im_1.submatrix(p, q, rows - n, cols - m);
			im_4 = im_2.submatrix(w, e, rows - n, cols - m);
			metrika = metrikas(im_3, im_4);
			if(metrika < min)
			{
				*best_1 = p;
				*best_2 = q;
				*best_3 = w;
				*best_4 = e;
				min = metrika;
			}
			if(j > 15)
			{
				e = 0;
				m--;
				q--;
			}
			else
			{
				m++;
				q = 0;
				e++;
			}	
		}
		if(i > 15)
                {
			w = 0;
			p--;
                	n--;
                }
                else
                {
                        n++;
			p = 0;
			w++;
                }
	}
}

Image combine(Image im_1, Image im_2, int* best_1, int* best_2, int* best_3, int* best_4, int flag)
{
		int cols = im_1.n_cols;
        	int rows = im_1.n_rows;
		int i = 0, j = 0, r = 0, m = 0, n = 0, q = 0, w = 0, g = 0, b = 0, max_1, max_2;
		if(*best_1 > *best_3)
			max_1 = *best_1;
		else
			max_1 = *best_3;

		if(*best_2 > *best_4)
			max_2 = *best_2;
		else
			max_2 = *best_4;
		for(m = *best_1, n = *best_3, i = 0; i < rows - max_1; m++, n++, i++)
		{
               		for(q = *best_2, w = *best_4, j = 0; j < cols - max_2; q++, w++, j++)
                	{
				if(flag == 1)
				{
                        		r = std::get<0>(im_1(m, q));
                        		g = std::get<1>(im_2(n, w));
                        		b = std::get<2>(im_1(i,j));
                        		im_1(i,j) = std::make_tuple(r, g, b);
				}
				else
				{
					r = std::get<0>(im_1(m, q));
                                        g = std::get<1>(im_1(m, q));
					b = std::get<2>(im_2(n,w));			                                im_1(i,j) = std::make_tuple(r, g, b);

				}
	                        cout << "flag"<<flag<<endl;
                	}	
        	}
		return im_1;	
}

Image align(Image srcImage, bool isPostprocessing, std::string postprocessingType, double fraction, bool isMirror, bool isInterp, bool isSubpixel, double subScale)
{		
	int cols = srcImage.n_cols;
	int rows = srcImage.n_rows;

	int best_1 = 0, best_2 = 0, best_3 = 0, best_4 = 0, flag = 1;
 	
	Image im_B = srcImage.submatrix(0, 0, rows/3, cols);
	Image im_G = srcImage.submatrix(rows/3, 0, rows/3, cols);
	Image im_R = srcImage.submatrix(2*rows/3, 0, rows/3, cols);
	cout << "qq" << endl; 	
	best_shift(im_R, im_G, &best_1, &best_2, &best_3, &best_4);
	im_R = combine(im_R, im_G, &best_1, &best_2, &best_3, &best_4, flag);
	     best_shift(im_R, im_B, &best_1, &best_2, &best_3, &best_4);
	flag = 0;
        im_R = combine(im_R, im_B, &best_1, &best_2, &best_3, &best_4, flag);

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
