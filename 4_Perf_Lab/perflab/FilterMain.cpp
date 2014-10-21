#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);
  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  
  ifstream input(filename.c_str());
  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
      	int value;
      	input >> value;
      	filter -> set(i,j,value);
            }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;

  int width = input->width-5;
  int height = input->height-1;
  int filterSize = filter -> getSize();
  int filterDiv = filter->getDivisor();
  int val0,val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14,val15,val16,val17;
  int filterVal;
  int rowVal, colVal, colVal1, colVal2,colVal3,colVal4;
  int row,col,i,j;
  int filtercount;
  int* filterData = filter->data;

  for(row = 1; row < height; row = row + 1) { 
    for(col = 1; col < width; col = col + 5) {
        val0 = 0;
        val1 = 0;
        val2 = 0;
        val3 = 0;
        val4 = 0;
        val5 = 0;
        val6 = 0;
        val7 = 0;
        val8 = 0;
        val12 = 0;
        val13 = 0;
        val14 = 0;
        val15 = 0;
        val16 = 0;
        val17 = 0;
        filtercount=0;
      	for (i = 0; i < filterSize; i++) {
          rowVal = row+i-1;
          for (j = 0; j < filterSize; j++) {
            filterVal = filterData[filtercount++];
            colVal = col+j-1;
            colVal1 = col+j;
            colVal2 = col+j+1;
            colVal3 = col+j+2;
            colVal4 = col+j+3;
            val0 += input -> color[0][rowVal][colVal]*filterVal;
            val3 += input -> color[0][rowVal][colVal1]*filterVal;
            val6 += input -> color[0][rowVal][colVal2]*filterVal;
            val12 += input -> color[0][rowVal][colVal3]*filterVal;
            val1 += input -> color[1][rowVal][colVal]*filterVal;
            val4 += input -> color[1][rowVal][colVal1]*filterVal;
            val7 += input -> color[1][rowVal][colVal2]*filterVal;
            val13 += input -> color[1][rowVal][colVal3]*filterVal;
            val2 += input -> color[2][rowVal][colVal]*filterVal;
            val5 += input -> color[2][rowVal][colVal1]*filterVal;
            val8 += input -> color[2][rowVal][colVal2]*filterVal;
            val14 += input -> color[2][rowVal][colVal3]*filterVal;
            
            val15 += input -> color[0][rowVal][colVal4]*filterVal;
            val16 += input -> color[1][rowVal][colVal4]*filterVal;
            val17 += input -> color[2][rowVal][colVal4]*filterVal;
      	  }
      	}

        val0 /= filterDiv;
        val1 /= filterDiv;
        val2 /= filterDiv;
        val3 /= filterDiv;
        val4 /= filterDiv;
        val5 /= filterDiv;
        val6 /= filterDiv;
        val7 /= filterDiv;
        val8 /= filterDiv;
        val12 /= filterDiv;
        val13 /= filterDiv;
        val14 /= filterDiv;
        
        val15 /= filterDiv;
        val16 /= filterDiv;
        val17 /= filterDiv;
        
      	val0=(val0<=255 && val0>=0) ? val0 : (val0>255?255:0);
        val1=(val1<=255 && val1>=0) ? val1 : (val1>255?255:0);
        val2=(val2<=255 && val2>=0) ? val2 : (val2>255?255:0);
        val3=(val3<=255 && val3>=0) ? val3 : (val3>255?255:0);
        val4=(val4<=255 && val4>=0) ? val4 : (val4>255?255:0);
        val5=(val5<=255 && val5>=0) ? val5 : (val5>255?255:0);
        val6=(val6<=255 && val6>=0) ? val6 : (val6>255?255:0);
        val7=(val7<=255 && val7>=0) ? val7 : (val7>255?255:0);
        val8=(val8<=255 && val8>=0) ? val8 : (val8>255?255:0);
        val12=(val12<=255 && val12>=0) ? val12 : (val12>255?255:0);
        val13=(val13<=255 && val13>=0) ? val13 : (val13>255?255:0);
        val14=(val14<=255 && val14>=0) ? val14 : (val14>255?255:0);
        
        val15=(val15<=255 && val15>=0) ? val15 : (val15>255?255:0);
        val16=(val16<=255 && val16>=0) ? val16 : (val16>255?255:0);
        val17=(val17<=255 && val17>=0) ? val17 : (val17>255?255:0);
        

      	output -> color[0][row][col] = val0;
        output -> color[0][row][col+1] = val3;
        output -> color[0][row][col+2] = val6;
        output -> color[0][row][col+3] = val12;
        output -> color[1][row][col] = val1;
        output -> color[1][row][col+1] = val4;
        output -> color[1][row][col+2] = val7;
        output -> color[1][row][col+3] = val13;
        output -> color[2][row][col] = val2;
        output -> color[2][row][col+1] = val5;
        output -> color[2][row][col+2] = val8;
        output -> color[2][row][col+3] = val14;
        
        output -> color[0][row][col+4] = val15;
        output -> color[1][row][col+4] = val16;
        output -> color[2][row][col+4] = val17;
        
    }
    for (; col < width+4; col = col +1){
      val9 = 0;
      val10 = 0;
      val11 = 0;
      filtercount=0;
      for (i = 0; i < filterSize; i++) {
         rowVal = row+i-1;
         for (j = 0; j < filterSize; j++) {
         colVal = col+j-1;
         filterVal = filterData[filtercount++];
         
         val9 += input -> color[0][rowVal][colVal]*filterVal;
         val10 += input -> color[1][rowVal][colVal]*filterVal;
         val11 += input -> color[2][rowVal][colVal]*filterVal;
         }
        }

        val9 /= filterDiv;
        val10 /= filterDiv;
        val11 /= filterDiv;

		val9=(val9<=255 && val9>=0) ? val9 : (val9>255?255:0);
        val10=(val10<=255 && val10>=0) ? val10 : (val10>255?255:0);
        val11=(val11<=255 && val11>=0) ? val11 : (val11>255?255:0);
        
        output -> color[0][row][col] = val9;
        output -> color[1][row][col] = val10;
        output -> color[2][row][col] = val11;
	}
  }
  

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
