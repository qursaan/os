#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << "<-n NUMBER | -r NUMBER | -f FILENAME>\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-n,--numbers NUMBER\tthe no of number generated (default 1000)\n"
              << "\t-r,--range NUMBER\tthe range of number generated from 0 (default 10)\n"
              << "\t-f,--filename FILENAME\tthe name of output file (default bigfile.txt)"
              << std::endl;
}

int main(int argc , char** argv){
    // default values
	int numbers  = 1000;
	int range    = 10;
	string fname = "bigfile.txt";

	// READ ARGUMENTS
	try{
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            if ((arg == "-h") || (arg == "--help")) {
                show_usage(argv[0]);
                return 0;
            } else if ((arg == "-n") || (arg == "--numbers")) {
                if (i + 1 < argc) {
                    numbers = stoi(argv[++i]);
                } else {
                    std::cerr << "--numbers option requires one argument." << std::endl;
                    return 1;
                }
            } else if ((arg == "-r") || (arg == "--range")) {
                if (i + 1 < argc) {
                    range = stoi(argv[++i]);
                } else {
                    std::cerr << "--range option requires one argument." << std::endl;
                    return 1;
                }
            }if ((arg == "-f") || (arg == "--filename")) {
                if (i + 1 < argc) {
                    fname = argv[++i];
                } else {
                    std::cerr << "--filename option requires one argument." << std::endl;
                    return 1;
                }
            }
        }
	} catch(std::exception& e) {
        show_usage(argv[0]);
    }
    cout << "Start generate using N(" << numbers << ") and Range (0-" << range-1 << ") \n";
	srand( time(0) ); // generate random based on time

	ofstream outputFile;
	outputFile.open(fname);
	int rn;

	for(int i=0; i<numbers; i++)
	{
		rn = rand()% range + 1;
		outputFile << rn  << ' ';
		if(i%32==0) cout << "\b\b"<< std::flush <<": ";
    else if(i%32==8) cout << "\b\b"<< std::flush <<"..";
    else if(i%32==16) cout << "\b\b"<< std::flush <<" :";
    else if(i%32==24) cout << "\b\b"<< std::flush <<"::";
	}
	outputFile.close();
    cout << "\b\bSaved in " << fname << endl;
	return 0;
}
