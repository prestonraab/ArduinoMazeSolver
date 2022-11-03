#include "Campus.h"

#define DOWN [0]+1
#define UP [0]-1
#define LEFT [1]-1
#define RIGHT [1]+1
#define VERT [0]
#define HORIZ [1]

vector<vector<bool>> Campus::readBMP(const std::string& file)
{
	static constexpr size_t HEADER_SIZE = 54;
	
	uint32_t fileSize;
	uint32_t dataOffset;
	int32_t width;
	int32_t height;
	uint32_t depth;
	long dataSize;
	
	
	ifstream bmp = readIntoImg1(file, fileSize, dataOffset, width, height, depth);
	
	std::vector<char> img(dataOffset - HEADER_SIZE);
	
	readIntoImg2(img, bmp, file, dataSize, height, width, depth);
	
	bmp.close();

	std::cout << "fileSize: " << fileSize << std::endl;
	std::cout << "dataOffset: " << dataOffset << std::endl;
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "depth: " << depth << "-bit" << std::endl;

	int bytesPerPixel = depth / 8;
	int extraBit = (4 - (width * bytesPerPixel) % 4) % 4;


	char temp = 0;

	vector<vector<unsigned char>> greyscaleMap(height, vector<unsigned char>(width, 0));

	
	cout << "Reading image into map" << endl;
	int i = 0;
	int j = width - 1;
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
    
    int bluestValue = -100;
    int greenestValue = -100;

	int f = 0;
	double imageAverage = 0;
	long numPixelsLookedAt = 0;
	
    //Find the start and end points
    
	for (signed long x = dataSize - bytesPerPixel; x >= 0; x -= bytesPerPixel)
	{
		// + extraBit
		temp = img[x];
		img[x] = img[x + 2];
		img[x + 2] = temp;

		red = (unsigned char)(img[x] & 0xff);
		green = (unsigned char)(img[x + 1] & 0xff);
		blue = (unsigned char)(img[x + 2] & 0xff);

        int greenValue = (int)green - int(blue) - int(red) + 512;
        int blueValue =  (int)blue - int(green) - int(red) + 512;
		if (greenValue > greenestValue) { //Green == start
            greenestValue = greenValue;
			start[0] = i;
			start[1] = j;
            cout << " Change start: " << greenValue / 7.3 << "% green match" << endl;
		}
		if (blueValue > bluestValue) { //Blue == end
            bluestValue = blueValue;
			end[0] = i;
			end[1] = j;
            cout << " Change end: " << blueValue / 7.3 << "% blue match" << endl;
		}
		
		greyscaleMap[i][j] = (unsigned char)(red * 0.299 + green * 0.587 + blue * 0.114);
		numPixelsLookedAt += 1;
		imageAverage += (greyscaleMap[i][j] - imageAverage) / numPixelsLookedAt;
		//cout << imageAverage << " ";
		
		j--;

		if (j == -1 ) {
			j = width - 1;
            x -= extraBit;
			i++;
		}
	}
	
    
    //Use the greymap, and our image average alpha value to create a black and white image

	vector<vector<bool>> map(height + extraBit, vector<bool>(width + extraBit, 1));
	
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			map[row][col] = (greyscaleMap[row][col] < imageAverage*5/6);
		}
	}
    
    
    //Ensure our start and end points are not trapped
    while(map[start[0]][start[1]]){
        int randHStep = (rand() % 3) - 1;
        int randVStep = (rand() % 3) - 1;
        
        if(start HORIZ + randHStep >= 0 &&
           start HORIZ + randHStep < width){
            start[0] += randHStep;
        }
        
        if(start VERT + randVStep >= 0 &&
           start VERT + randVStep < height){
            start[1] += randVStep;
        }
    }
    
    while(map[end[0]][end[1]]){
        int randHStep = (rand() % 3) - 1;
        int randVStep = (rand() % 3) - 1;
        
        if(end HORIZ + randHStep >= 0 &&
           end HORIZ + randHStep < width){
            end[0] += randHStep;
        }
        
        if(end VERT + randVStep >= 0 &&
           end VERT + randVStep < height){
            end[1] += randVStep;
        }
    }
    
//    int n = 0;
//    while((start DOWN  >= height || map[start DOWN][start HORIZ]) &&
//          (start UP    < 0       || map[start UP]  [start HORIZ]) &&
//          (start RIGHT >= width  || map[start VERT][start RIGHT]) &&
//          (start LEFT  < 0       || map[start VERT][start LEFT])){
//
//        if(start DOWN  < height) map[start DOWN][start HORIZ] = false;
//        if(start UP    >= 0    ) map[start UP]  [start HORIZ] = false;
//        if(start RIGHT < width ) map[start VERT][start RIGHT] = false;
//        if(start LEFT  >= 0    ) map[start VERT][start LEFT]  = false;
//        cout << "HI ";
//        n += 1;
//    }
//
//    n = 0;
//    while((end DOWN  >= height || map[end DOWN][end HORIZ]) &&
//          (end UP    < 0       || map[end UP]  [end HORIZ]) &&
//          (end RIGHT >= width  || map[end VERT][end RIGHT]) &&
//          (end LEFT  < 0       || map[end VERT][end LEFT])){
//        cout << " BYE";
//        if(end DOWN  < height) map[end DOWN][end HORIZ] = false;
//        if(end UP    >= 0    ) map[end UP]  [end HORIZ] = false;
//        if(end RIGHT < width ) map[end VERT][end RIGHT] = false;
//        if(end LEFT  >= 0    ) map[end VERT][end LEFT]  = false;
//
//        n += 1;
//    }
	
	map[start[0]][start[1]] = false;
	map[end[0]][end[1]] = false;
	
	found = f;
	greyMap = greyscaleMap;
	return map;
}

ifstream Campus::readIntoImg1(const std::string& file, uint32_t &fileSize, uint32_t &dataOffset, int32_t &width, int32_t &height, uint32_t &depth)
{
	static constexpr size_t HEADER_SIZE = 54;
	
	ifstream bmp(file, std::ios::binary);

	std::array<char, HEADER_SIZE> header;
	bmp.read(header.data(), header.size());
	
	
	fileSize = *reinterpret_cast<uint32_t*>(&header[2]);
	dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
	width = *reinterpret_cast<int32_t*>(&header[18]);
	height = *reinterpret_cast<int32_t*>(&header[22]);
	height = abs(height);
	depth = *reinterpret_cast<uint16_t*>(&header[28]);
	
	return bmp;
}

void Campus::readIntoImg2(std::vector<char> &img, ifstream &bmp, const std::string& file, long &dataSize, int32_t height, int32_t width, uint32_t depth)
{
	bmp.read(img.data(), img.size());

	dataSize = ((width * (depth/8) + 3) & (~3)) * height;
	img.resize(dataSize);
	bmp.read(img.data(), img.size());
	
}
