#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iostream>
#include <cmath>

#include "classifier.h"
#include "EasyBMP.h"
#include "linear.h"
#include "argvparser.h"
#include "matrix.h"
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::make_pair;
using std::cout;
using std::cerr;
using std::endl;

using CommandLineProcessing::ArgvParser;

typedef vector<pair<BMP*, int> > TDataSet;
typedef vector<pair<string, int> > TFileList;
typedef vector<pair<vector<float>, int> > TFeatures;

// Load list of files and its labels from 'data_file' and
// stores it in 'file_list'




Matrix<float> GrayScale(BMP image)
{

        int i,j = 0;
        int height = image.TellHeight();
        int width = image.TellWidth();
        RGBApixel pixel;
        Matrix<float> ansver = Matrix<float>(height, width);

        for(i = 0; i < height; i++)
                for(j = 0; j < width; j++)
                {
                        pixel = image.GetPixel(j,i);
                        ansver(i,j) = 0.299 * pixel.Red + 0.587 * pixel.Green + 0.114 * pixel.Blue;
                }
        return ansver;
}

std::vector<float> Bonus_1_blok(BMP image, Matrix<float> matr, int i, int j)
{
	int height = image.TellHeight();
        int width = image.TellWidth();
        int i_gis = i + height/8;
        int j_gis = j + width/8;

        int summ = 0, norma = 0;
	int p = 0;
        std::vector<float> vector = std::vector<float>(0);
	while(p < 256)
	{
		vector.push_back(0);
		p++;
	}
        for(i = i; i < i_gis; i++)
        {

		if(i == height)
			break;

                for(j = j; j < j_gis; j++)
		{
			if(j == width)
				break;
			if(matr(i+1,j+1) > matr(i,j))
				summ = summ + pow(2,7);
			if(matr(i+1,j+1) > matr(i,j+1))
				summ = summ + pow(2,6);
			if(matr(i+1,j+1) > matr(i,j+2))
				summ = summ + pow(2,5);
			if(matr(i+1,j+1) > matr(i+1,j+2))
				summ = summ + pow(2,4);
			if(matr(i+1,j+1) > matr(i+2,j+2))
				summ = summ + pow(2,3);
			if(matr(i+1,j+1) > matr(i+2,j+1))
				summ = summ + pow(2,2);
			if(matr(i+1,j+1) > matr(i+2,j))
				summ = summ + pow(2,1);
			if(matr(i+1,j+1) > matr(i+1,j))
				summ = summ + pow(2,0);
			vector[summ]++;
			summ = 0;	

		}
	}
	p = 0;
	while(p < 256)
        {
                norma = norma + vector[p] * vector[p];
                p++;
        }
	norma = sqrt(norma);
	p = 0;
	while(p < 256)
        {
               vector[p] = vector[p] / norma;
                p++;
        }
	return vector;

}

std::vector<float> Bonus_1(BMP image, Matrix<float> ansver)
{
	int height = image.TellHeight();
        int width = image.TellWidth();
        int i, j;
        uint  p = 0;
	

        std::vector<float> vector = std::vector<float>(0);
        std::vector<float> concat = std::vector<float>(0);

        for(i = 0; i < height; i = i + height/8)
                for(j = 0; j < width; j = j + width/8)
                {
                        vector = Bonus_1_blok(image, ansver, i, j);

                        while(p < vector.size())
                        {
                                concat.push_back(vector[p]);
                                p++;
                        }
                        p = 0;

                }
        return concat;

}

std::vector<float> Bonus_blok(BMP image, int i, int j)
{
        int height = image.TellHeight();
        int width = image.TellWidth();

	int i_gis = i + height/8;
        int j_gis = j + width/8;

	int count = 0;
        float r = 0.0, g = 0.0, b = 0.0;
        std::vector<float> vector = {0,0,0};
	RGBApixel pixel;

        for(i = i; i < i_gis; i++)
	{	
                for(j = j; j < j_gis; j++)
		{
			pixel = image.GetPixel(j,i);
			r = r + pixel.Red;
			g = g + pixel.Green;
			b = b + pixel.Blue;
			count++;
			if(j == width - 1)
				break;
		}
		
		if(i == height - 1)
			break;
	}
	r = r/count;
	g = g/count;
	b = b/count;

	r = r/255;
	g = g/255;
	b = b/255;
	vector = {r,g,b};
	return vector;
}

std::vector<float> Bonus_2(BMP image)
{
        int height = image.TellHeight();
        int width = image.TellWidth();
        int i, j, c = 0;
        uint  p = 0;

        std::vector<float> vector = std::vector<float>(0);
        std::vector<float> concat = std::vector<float>(0);

        for(i = 0; i < height; i = i + height/8)
                for(j = 0; j < width; j = j + width/8)
                {
			c++;
                        vector = Bonus_blok(image, i, j);

                        while(p < vector.size())
                        {
                                concat.push_back(vector[p]);
                                p++;
                        }
                        p = 0;

                }
        return concat;
}

Matrix<float> Sobel_y(BMP image)
{
	Matrix<float> ansver = GrayScale(image);
	Matrix<float> buffer = ansver.extra_borders(1,1);
	int height = image.TellHeight();
	int width = image.TellWidth();
	Matrix<float> m_sobel = {{-1,-2,-1}, {0,0,0}, {1,2,1}};
	
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			ansver(i,j) = m_sobel(0,0) * buffer(i,j) + m_sobel(0,1) * buffer(i,j+1) + m_sobel(0,2) * buffer(i,j+2) +
				m_sobel(1,0) * buffer(i+1,j) + m_sobel(1,1) * buffer(i+1,j+1) + m_sobel(1,2) * buffer(i+1,j+2) +
				m_sobel(2,0) * buffer(i+2,j) + m_sobel(2,1) * buffer(i+2,j+1) + m_sobel(2,2) * buffer(i+2,j+2); 
		}

	return ansver;
}

Matrix<float> Sobel_x(BMP image)
{
        Matrix<float> ansver = GrayScale(image);
        Matrix<float> buffer = ansver.extra_borders(1,1);
        int height = image.TellHeight();
        int width = image.TellWidth();
        Matrix<float> m_sobel = {{-1,0,1}, {-2,0,2}, {-1,0,1}};

        for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                {
                        ansver(i,j) = m_sobel(0,0) * buffer(i,j) + m_sobel(0,1) * buffer(i,j+1) + m_sobel(0,2) * buffer(i,j+2) +
                                m_sobel(1,0) * buffer(i+1,j) + m_sobel(1,1) * buffer(i+1,j+1) + m_sobel(1,2) * buffer(i+1,j+2) +
                                m_sobel(2,0) * buffer(i+2,j) + m_sobel(2,1) * buffer(i+2,j+1) + m_sobel(2,2) * buffer(i+2,j+2);
                }

        return ansver;
}

				/* WITH SSE

Matrix<float> Sobel_y(BMP image)
{
        Matrix<float> ansver = GrayScale(image);
        Matrix<float> buffer = ansver.extra_borders(1,1);
        int height = image.TellHeight();
        int width = image.TellWidth();
        Matrix<float> m_sobel = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

        __m128 m1, m2, m3, m4;
	float summ[4];

	m1 = _mm_setr_ps(m_sobel(0,0), m_sobel(0,1), m_sobel(0,2), m_sobel(2,0));
        m2 = _mm_setr_ps(m_sobel(2,1), m_sobel(2,2), 0, 0);

        for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                {
			m3 = _mm_setr_ps(buffer(i,j), buffer(i,j+1), buffer(i,j+2), buffer(i+2,j));
                        m4 = _mm_setr_ps(buffer(i+2,j+1), buffer(i+2,j+2), 0, 0);

                        m3 = _mm_mul_ps(m3, m1);
                        m4 = _mm_mul_ps(m4, m2);
                        m4 = _mm_add_ps(m3,m4);
			_mm_store_ps(summ, m4);
                        ansver(i,j) = summ[0] + summ[1] + summ[2] + summ[3];
                }

        return ansver;
}

Matrix<float> Sobel_x(BMP image)
{
        Matrix<float> ansver = GrayScale(image);
        Matrix<float> buffer = ansver.extra_borders(1,1);
        int height = image.TellHeight();
        int width = image.TellWidth();
        Matrix<float> m_sobel = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
	__m128 m1, m2, m3, m4;
	float summ[4];
	m1 = _mm_setr_ps(m_sobel(0,0), m_sobel(0,2), m_sobel(1,0), m_sobel(1,2));
        m2 = _mm_setr_ps(m_sobel(2,0), m_sobel(2,2), 0, 0);
	

        for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                {
			m3 = _mm_setr_ps(buffer(i,j), buffer(i,j+2), buffer(i+1,j), buffer(i+1,j+2));
			m4 = _mm_setr_ps(buffer(i+2,j), buffer(i+2,j+2), 0, 0);
			
			m3 = _mm_mul_ps(m3, m1);
			m4 = _mm_mul_ps(m4, m2);
                        m4 = _mm_add_ps(m3,m4);
			_mm_store_ps(summ, m4);
			ansver(i,j) = summ[0] + summ[1] + summ[2] + summ[3];
                }

        return ansver;
}

Matrix<float> ModulGrad(BMP image)
{
        Matrix<float> sobel_x = Sobel_x(image);
        Matrix<float> sobel_y = Sobel_y(image);
        
        int height = image.TellHeight();
        int width = image.TellWidth();
       
        Matrix<float> ansver = Matrix<float>(height, width);
	__m128 m1, m2;
	float summ[4];
        for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                {
			m1 = _mm_setr_ps(sobel_x(i,j), sobel_y(i,j), 0, 0);
			m2 = _mm_mul_ps(m1,m1);
			_mm_store_ps(summ, m2);
                        ansver(i,j) = sqrt(summ[0] + summ[1]);
                }

        return ansver;
}

 					WITH SSE */
Matrix<float> ModulGrad(BMP image)
{
	Matrix<float> sobel_x = Sobel_x(image);
	Matrix<float> sobel_y = Sobel_y(image);
	
	int height = image.TellHeight();
        int width = image.TellWidth();
       
	Matrix<float> ansver = Matrix<float>(height, width);

	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			ansver(i,j) = sqrt(sobel_x(i,j) * sobel_x(i,j) + sobel_y(i,j) * sobel_y(i,j));
		}

	return ansver;
}

Matrix<float> DirectionGrad(BMP image)
{
        Matrix<float> sobel_x = Sobel_x(image);
        Matrix<float> sobel_y = Sobel_y(image);

        int height = image.TellHeight();
        int width = image.TellWidth();

        Matrix<float> ansver = Matrix<float>(height, width);

        for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                {
                        ansver(i,j) = atan2(sobel_y(i,j), sobel_x(i,j));
                }

        return ansver;
}

std::vector<float> Gistogramma(BMP image, int i, int j, Matrix<float> modul , Matrix<float> direction)
{
	int height = image.TellHeight();
        int width = image.TellWidth();

	int i_gis = i + 8;
	int j_gis = j + 8;
	float summ_vect = 0.0, sq = 0.0;
	std::vector<float> vector = {0,0,0,0,0,0,0,0};
	
	for(i = i; i < i_gis; i++)
	{
		for(j = j; j < j_gis; j++)
		{
			if(j == width)
				break;
			if(direction(i,j) >= -M_PI && direction(i,j) < -3*(M_PI_4))
			{
				vector[0] = vector[0] + modul(i,j);
			 	continue;
			}
			if(direction(i,j) >= -3*(M_PI_4) && direction(i,j) < -M_PI_2)
                        {
                                vector[1] = vector[1] + modul(i,j);
                        	continue;
			}
			if(direction(i,j) >= -M_PI_2 && direction(i,j) < -M_PI_4)
                        {
                                vector[2] = vector[2] + modul(i,j);
                        	continue;
			}
			if(direction(i,j) >= -M_PI_4 && direction(i,j) < 0)
                        {
                                vector[3] = vector[3] + modul(i,j);
                        	continue;
			}
 			if(direction(i,j) >= 0 && direction(i,j) < M_PI_4)
                        {
                                vector[4] = vector[4] + modul(i,j);
                        	continue;
			}
 			if(direction(i,j) >= M_PI_4 && direction(i,j) < 3*(M_PI_4))
                        {
                                vector[5] = vector[5] + modul(i,j);
				continue;

                        }
 			if(direction(i,j) >= 3*(M_PI_4) && direction(i,j) < M_PI_2)
                        {
                                vector[6] = vector[6] + modul(i,j);
				continue;
                        }
			if(direction(i,j) >= M_PI_2 && direction(i,j) <= M_PI)
                        {
                                vector[7] = vector[7] + modul(i,j);
                        }
			
		}
		if(i == height - 1)
			break;
	}
	for(i = 0; i < 8; i++)
	{
		sq = vector[i] * vector[i];
		summ_vect = summ_vect + sq;
	}
		
	summ_vect = sqrt(summ_vect);
		
	for(i = 0; i < 8; i++)
	{
		vector[i] = vector[i] / summ_vect;
		if(std::isnan(vector[i]))
			vector[i] = 0;
	}

	return vector;
}

std::vector<float> Concatination(BMP image)
{
	Matrix<float> modul = ModulGrad(image);
        Matrix<float> direction = DirectionGrad(image);


	int height = image.TellHeight();
        int width = image.TellWidth();
	int i, j;
	uint  p = 0;
	std::vector<float> vector = std::vector<float>(0);
	std::vector<float> concat = std::vector<float>(0);
        std::vector<float> bonus_concat = std::vector<float>(0);
	std::vector<float> bonus_1_concat = std::vector<float>(0);

        Matrix<float> buff = GrayScale(image);
        Matrix<float> ansver = buff.extra_borders(1,1);

	for(i = 0; i < height; i = i + 8)
		for(j = 0; j < width; j = j + 8)
		{
			vector = Gistogramma(image, i, j, modul, direction);
			
			while(p < vector.size())
			{
				concat.push_back(vector[p]);
				p++;
			}
			p = 0;
		}
	
	bonus_concat = Bonus_2(image);
	bonus_1_concat = Bonus_1(image, ansver);
	
	p = 0;
        while(p < bonus_concat.size())
        {
                concat.push_back(bonus_concat[p]);
                p++;
        }
	p = 0;
        while(p < bonus_1_concat.size())
        {
                concat.push_back(bonus_1_concat[p]);
                p++;
        }

	return concat;
}
void LoadFileList(const string& data_file, TFileList* file_list) {
    ifstream stream(data_file.c_str());

    string filename;
    int label;
    
    int char_idx = data_file.size() - 1;
    for (; char_idx >= 0; --char_idx)
        if (data_file[char_idx] == '/' || data_file[char_idx] == '\\')
            break;
    string data_path = data_file.substr(0,char_idx+1);
    
    while(!stream.eof() && !stream.fail()) {
        stream >> filename >> label;
        if (filename.size())
            file_list->push_back(make_pair(data_path + filename, label));
    }

    stream.close();
}

// Load images by list of files 'file_list' and store them in 'data_set'
void LoadImages(const TFileList& file_list, TDataSet* data_set) {
    for (size_t img_idx = 0; img_idx < file_list.size(); ++img_idx) {
            // Create image
        BMP* image = new BMP();
            // Read image from file
        image->ReadFromFile(file_list[img_idx].first.c_str());
            // Add image and it's label to dataset
        data_set->push_back(make_pair(image, file_list[img_idx].second));
    }
}

// Save result of prediction to file
void SavePredictions(const TFileList& file_list,
                     const TLabels& labels, 
                     const string& prediction_file) {
        // Check that list of files and list of labels has equal size 
    assert(file_list.size() == labels.size());
        // Open 'prediction_file' for writing
    ofstream stream(prediction_file.c_str());

        // Write file names and labels to stream
    for (size_t image_idx = 0; image_idx < file_list.size(); ++image_idx)
        stream << file_list[image_idx].first << " " << labels[image_idx] << endl;
    stream.close();
}

// Exatract features from dataset.
// You should implement this function by yourself =)
void ExtractFeatures(const TDataSet& data_set, TFeatures* features) {
    for (size_t image_idx = 0; image_idx < data_set.size(); ++image_idx) {
        
        // PLACE YOUR CODE HERE
        // Remove this sample code and place your feature extraction code here

        vector<float> one_image_features = Concatination(*std::get<0>(data_set[image_idx]));
        features->push_back(make_pair(one_image_features, std::get<1>(data_set[image_idx])));
        // End of sample code

    }
}

// Clear dataset structure
void ClearDataset(TDataSet* data_set) {
        // Delete all images from dataset
    for (size_t image_idx = 0; image_idx < data_set->size(); ++image_idx)
        delete (*data_set)[image_idx].first;
        // Clear dataset
    data_set->clear();
}

// Train SVM classifier using data from 'data_file' and save trained model
// to 'model_file'
void TrainClassifier(const string& data_file, const string& model_file) {
        // List of image file names and its labels
    TFileList file_list;
        // Structure of images and its labels
    TDataSet data_set;
        // Structure of features of images and its labels
    TFeatures features;
        // Model which would be trained
    TModel model;
        // Parameters of classifier
    TClassifierParams params;
    
        // Load list of image file names and its labels
    LoadFileList(data_file, &file_list);
        // Load images
    LoadImages(file_list, &data_set);
        // Extract features from images
    ExtractFeatures(data_set, &features);

        // PLACE YOUR CODE HERE
        // You can change parameters of classifier here
    params.C = 0.01;
    TClassifier classifier(params);
        // Train classifier
    classifier.Train(features, &model);
        // Save model to file
    model.Save(model_file);
        // Clear dataset structure
    ClearDataset(&data_set);
}

// Predict data from 'data_file' using model from 'model_file' and
// save predictions to 'prediction_file'
void PredictData(const string& data_file,
                 const string& model_file,
                 const string& prediction_file) {
        // List of image file names and its labels
    TFileList file_list;
        // Structure of images and its labels
    TDataSet data_set;
        // Structure of features of images and its labels
    TFeatures features;
        // List of image labels
    TLabels labels;

        // Load list of image file names and its labels
    LoadFileList(data_file, &file_list);
        // Load images
    LoadImages(file_list, &data_set);
        // Extract features from images
    ExtractFeatures(data_set, &features);

        // Classifier 
    TClassifier classifier = TClassifier(TClassifierParams());
        // Trained model
    TModel model;
        // Load model from file
    model.Load(model_file);
        // Predict images by its features using 'model' and store predictions
        // to 'labels'
    classifier.Predict(features, model, &labels);

        // Save predictions
    SavePredictions(file_list, labels, prediction_file);
        // Clear dataset structure
    ClearDataset(&data_set);
}

int main(int argc, char** argv) {
    // Command line options parser
    ArgvParser cmd;
        // Description of program
    cmd.setIntroductoryDescription("Machine graphics course, task 2. CMC MSU, 2014.");
        // Add help option
    cmd.setHelpOption("h", "help", "Print this help message");
        // Add other options
    cmd.defineOption("data_set", "File with dataset",
        ArgvParser::OptionRequiresValue | ArgvParser::OptionRequired);
    cmd.defineOption("model", "Path to file to save or load model",
        ArgvParser::OptionRequiresValue | ArgvParser::OptionRequired);
    cmd.defineOption("predicted_labels", "Path to file to save prediction results",
        ArgvParser::OptionRequiresValue);
    cmd.defineOption("train", "Train classifier");
    cmd.defineOption("predict", "Predict dataset");
        
        // Add options aliases
    cmd.defineOptionAlternative("data_set", "d");
    cmd.defineOptionAlternative("model", "m");
    cmd.defineOptionAlternative("predicted_labels", "l");
    cmd.defineOptionAlternative("train", "t");
    cmd.defineOptionAlternative("predict", "p");

        // Parse options
    int result = cmd.parse(argc, argv);

        // Check for errors or help option
    if (result) {
        cout << cmd.parseErrorDescription(result) << endl;
        return result;
    }
        // Get values 
    string data_file = cmd.optionValue("data_set");
    string model_file = cmd.optionValue("model");
    bool train = cmd.foundOption("train");
    bool predict = cmd.foundOption("predict");

        // If we need to train classifier
    if (train)
        TrainClassifier(data_file, model_file);
        // If we need to predict data
    if (predict) {
            // You must declare file to save images
        if (!cmd.foundOption("predicted_labels")) {
            cerr << "Error! Option --predicted_labels not found!" << endl;
            return 1;
        }
            // File to save predictions
        string prediction_file = cmd.optionValue("predicted_labels");
            // Predict data
        PredictData(data_file, model_file, prediction_file);
    }
}
