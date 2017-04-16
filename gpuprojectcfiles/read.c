#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;

ofstream file2("/media/siva/New\ Volume/GPUproject/gpuprojectcfiles/out", ios::out);
int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}
void ReadMNIST(int NumberOfImages, int DataOfAnImage,vector<vector<double> > &arr)
{   ifstream file;
    
    arr.resize(NumberOfImages,vector<double>(DataOfAnImage));
    file.open("/media/siva/New\ Volume/GPUproject/gpuprojectcfiles/train",ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        printf("rows%d:",n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        printf("cols%d:",n_cols);
        for(int i=0;i<number_of_images;++i)
        {
             for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    if ((double)temp != 0)
                    arr[i][(n_rows*r)+c]= 1;
                    else
                    arr[i][(n_rows*r)+c]= 0;
                  
                    //printf("element:%f\n",arr[i][(n_rows*r)+c]);
                }
              }
	
	
                 for (int a = 0; a < n_rows; ++a) 
                 {
                    for (int b = 0; b < n_cols; ++b)
                    {
			file2 << arr[i][(n_rows*a)+b] << " ";
		     }
                  
		file2 << endl;


                 }
                file2<<"next image\n";
        }
        }
  }

int main()
{
  vector<vector<double> > ar;
  ReadMNIST(10000,784,ar);
 
  return 0;
}
