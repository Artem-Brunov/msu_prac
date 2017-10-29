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
                	}	
        	}
		return im_1;	
}

Image align(Image srcImage)
{		
	int cols = srcImage.n_cols;
	int rows = srcImage.n_rows;
	int best_1 = 0, best_2 = 0, best_3 = 0, best_4 = 0, flag = 1;
	
	Image im_B = srcImage.submatrix(0, 0, rows/3, cols);
	Image im_G = srcImage.submatrix(rows/3, 0, rows/3, cols);
	Image im_R = srcImage.submatrix(2*rows/3, 0, rows/3, cols);
	
	best_shift(im_R, im_G, &best_1, &best_2, &best_3, &best_4);
	im_R = combine(im_R, im_G, &best_1, &best_2, &best_3, &best_4, flag);
	
	best_shift(im_R, im_B, &best_1, &best_2, &best_3, &best_4);
	flag = 0;
        im_R = combine(im_R, im_B, &best_1, &best_2, &best_3, &best_4, flag);

	srcImage = im_R;
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
    	
	Matrix<double> growing = { {-(1/6.0), -(2/3.0), -(1/6.0)},
                             	 {-(2/3.0), (13/3.0), -(2/3.0)},
				 {-(1/6.0), -(2/3.0), -(1/6.0)}};
	int cols = src_image.n_cols;
        int rows = src_image.n_rows;
	
	cout << growing(0,0);
	int size = 2;
	double r, g, b, sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
	Image image = src_image.submatrix(1, 1, rows - 1, cols - 1);

	for(int i = 1; i < rows - 1; i++)
		for(int j = 1; j < cols - 1; j++)
		{
			for(int p = -1; p < size; p++)
			{
				for(int q = -1; q < size; q++)
				{
					r = std::get<0>(src_image(i + p, j + q));
                        		g = std::get<1>(src_image(i + p, j + q));
                        		b = std::get<2>(src_image(i + p, j + q));
		
					sum_r = sum_r + r * growing(p + 1, q + 1);
					sum_g = sum_g + g * growing(p + 1, q + 1);
					sum_b = sum_b + b * growing(p + 1, q + 1);
	
				}
			}	
			if(sum_r > 255)
                        	sum_r = 255;
                        if(sum_g > 255)
                        	sum_g = 255;
                        if(sum_b > 255)
                              	sum_b = 255;

                        if(sum_r < 0)
                               	sum_r = 0;
                        if(sum_g < 0)
                               	sum_g = 0;
                        if(sum_b < 0)
                               	sum_b = 0;
			image((i-1),(j-1)) = std::make_tuple(sum_r, sum_g, sum_b);
			sum_r = 0.0;
			sum_b = 0.0;
			sum_g = 0.0;
		}
		
	return image;
}

Image gray_world(Image src_image) {
	
	int cols = src_image.n_cols;
        int rows = src_image.n_rows;
	
	int r = 0, g = 0, b = 0;
	double i = 0, j = 0, sum = 0, sum_r = 0, sum_g = 0, sum_b = 0;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
			r = std::get<0>(src_image(i, j));
			g = std::get<1>(src_image(i, j));
        		b = std::get<2>(src_image(i, j));
			
			sum_r = sum_r + r;
			sum_g = sum_g + g;
			sum_b = sum_b + b;
		}
	sum_r = sum_r/(rows * cols);
	sum_b = sum_b/(rows * cols);
	sum_g = sum_g/(rows * cols);
	
	sum = (sum_r + sum_g + sum_b) / 3;
	
	sum_r = sum / sum_r;
	sum_g = sum / sum_g;
	sum_b = sum / sum_b;

	for(i = 0; i < rows; i++)
                for(j = 0; j < cols; j++)
                {       
                        r = std::get<0>(src_image(i, j));
                        g = std::get<1>(src_image(i, j));
                        b = std::get<2>(src_image(i, j)); 

			r = r * sum_r;
			g = g * sum_g;
			b = b * sum_b;
			
			if(r > 255)
				r = 255;
			if(g > 255)
				g = 255;
			if(b > 255)
				b = 255;
			src_image(i,j) = std::make_tuple(r, g, b);

                }

    	return src_image;
}

Image resize(Image src_image, double scale) {

	int cols = src_image.n_cols * scale;
        int rows = src_image.n_rows * scale;
	
	Image image = Image(rows, cols);
	double dx = 0.0, dy = 0.0, r = 0.0, b = 0.0, g = 0.0;
	int i = 0, j = 0, I = 0, J = 0;

	for(i = 0; i < rows  - 2; i++)
		for(j = 0; j < cols - 2 ; j++)
		{
			I = i / scale;
			J = j / scale;
			dx = j / scale - J;
			dy = i / scale - I;
			
			r = (1 - dx) * (1 - dy) * std::get<0>(src_image(I, J))+
				dx * (1 - dy) * std::get<0>(src_image(I, J + 1)) + 
				(1 - dx) * dy * std::get<0>(src_image(I + 1, J)) + 
				dx * dy * std::get<0>(src_image(I + 1, J + 1));
                	g = (1 - dx) * (1 - dy) * std::get<1>(src_image(I, J)) + 
                                dx * (1 - dy) * std::get<1>(src_image(I, J + 1)) + 
                                (1 - dx) * dy * std::get<1>(src_image(I + 1, J)) + 
                                dx * dy * std::get<1>(src_image(I + 1, J + 1));
			b = (1 - dx) * (1 - dy) * std::get<2>(src_image(I, J)) + 
                                dx * (1 - dy) * std::get<2>(src_image(I, J + 1)) + 
                                (1 - dx) * dy * std::get<2>(src_image(I + 1, J)) + 
                                dx * dy * std::get<2>(src_image(I + 1, J + 1));
			
			if(r > 255)
                                r = 255;
                        if(g > 255)
                                g = 255;
                        if(b > 255)
                                b = 255;

                        if(r < 0)
                                r = 0;
                        if(g < 0)
                                g = 0;
                        if(b < 0)
                                b = 0;

 			image(i, j) = std::make_tuple(r, g, b);

		}	

	return image;
}

Image custom(Image src_image, Matrix<double> kernel) {
    // Function custom is useful for making concrete linear filtrations
    // like gaussian or sobel. So, we assume that you implement custom
    // and then implement other filtrations using this function.
    // sobel_x and sobel_y are given as an example.
    return src_image;
}

Image autocontrast(Image src_image, double fraction) {
	double max_I = 0, min_I = 255, I = 0, r, g, b;
	int i = 0, j = 0;

	int cols = src_image.n_cols;
        int rows = src_image.n_rows;

	
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
			r = std::get<0>(src_image(i, j));
                        g = std::get<1>(src_image(i, j));
                        b = std::get<2>(src_image(i, j));
	
			I = 0.2125 * r + 0.7154 * g + 0.0721 * b;
			if(I < min_I)
				min_I = I;
			if(I > max_I)
				max_I = I;
		}
	 for(i = 0; i < rows; i++)
                for(j = 0; j < cols; j++)
                {
                        r = std::get<0>(src_image(i, j));
                        g = std::get<1>(src_image(i, j));
                        b = std::get<2>(src_image(i, j));
			
			r = ((r - min_I) * 255) / (max_I - min_I);	
	                g = ((g - min_I) * 255) / (max_I - min_I);
                        b = ((b - min_I) * 255) / (max_I - min_I);
	
		        if(r > 255)
                                r = 255;
                        if(g > 255)
                                g = 255;
                        if(b > 255)
                                b = 255;
			
                        if(r < 0)
                                r = 0;
                        if(g < 0)
                                g = 0;
                        if(b < 0)
                                b = 0;

			src_image(i,j) = std::make_tuple(r, g, b);
		}
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


