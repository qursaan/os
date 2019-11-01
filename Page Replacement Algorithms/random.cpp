#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "helper.h"
using namespace std;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << "  <-i FILENAME> [-o FILENAME | -p NUMBER | -a | -s]\n"
              << "Required: \n"
              << "\t-i,--input FILENAME\tthe name of input file\n"
              << "Options: \n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-o,--output FILENAME\tthe name of output file (default output.csv)\n"
              << "\t-p,--pagesize NUMBER\tthe max of page generated (default 10)\n"
              << "\t-a,--analysis\t\tBrute-force all page sizes\n"
              << "\t-s,--show\t\tPrint steps\n"
              << std::endl;
}

int main(int argc,char**argv)
{
    if(argc<3)
    {
        show_usage(argv[0]);
        return 0;
    }
    string  input_filename = "input.txt";
    string output_filename = "output.csv";
    int  max_pagesize = 10;
    bool print        = false;
    bool analysis     = false;
    srand(time(0)); // RANDOMIZATION
    /*
        0. READ ARGUEMENTS
    */
    try
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];

            if ((arg == "-h") || (arg == "--help"))
            {
                show_usage(argv[0]);
                return 0;
            }
            else if ((arg == "-i") || (arg == "--input"))
            {
                if (i + 1 < argc)
                {
                    input_filename = argv[++i];
                }
                else
                {
                    std::cerr << "--input option requires one argument." << std::endl;
                    return 1;
                }
            }
            else if ((arg == "-o") || (arg == "--output"))
            {
                if (i + 1 < argc)
                {
                    output_filename = argv[++i];
                }
                else
                {
                    std::cerr << "--output option requires one argument." << std::endl;
                    return 1;
                }
            }
            if ((arg == "-p") || (arg == "--pagesize"))
            {
                if (i + 1 < argc)
                {
                    max_pagesize = stoi(argv[++i]);
                }
                else
                {
                    std::cerr << "--pagesize option requires one argument." << std::endl;
                    return 1;
                }
            }
            if ((arg == "-s") || (arg == "--show"))
            {
                print = true;
            }
            if ((arg == "-a") || (arg == "--analysis"))
            {
                analysis = true;
            }
        }
    }
    catch(std::exception& e)
    {
        show_usage(argv[0]);
    }

    ofstream writer;
    ifstream reader(input_filename.c_str());

    if(!reader.good()){
        cerr<< "Input File not found!\n";
        return 1;
    }

    writer.open(output_filename);
    writer << "Page Size,Fault Rate\n";
    cout << "Page Size" <<"\tFault Rate(%)"<< endl;

    /* BRUTE-FORCE ALL PAGE SIZE */
    for(int pagesize = 1; pagesize <= max_pagesize; pagesize++)
    {
        if(!analysis)
        {
            pagesize = max_pagesize;
        }
        /* START READING */
        reader.open(input_filename);
        reader.clear();
        reader.seekg(0, ios::beg);
        /*
            1. CREATE MEMORY ARRAY
        */
        int memory_size = pagesize;
        int *memory = new int[memory_size];
        memset(memory,-1,memory_size*sizeof(memory));

        /*
            2. PAGING
        */
        int counter = 0;   /* Count Data   */
        int fault   = 0;   /* Count Faults */
        int idx     = -1;  /* Hold Random  */
        int key;           /* Element      */

        /*  2.1 READ REQUESTS  */
        while(reader>>key)
        {
            /*  2.2 LOOKUP IN MEMORY  */
            int result = sequenialSearch(memory,memory_size,key);

            /*  2.3 NOT FOUND - PAGE IT RANDOMLY */
            if(result == -1)
            {
                fault++;
                idx= rand()%memory_size;
                memory[idx] = key;
            }//IF

            if(print)
            {
                printArray(memory,memory_size);
            }

            ++counter; // READING STEP
        }//FOR
        if(counter==0){
            cerr << "Input file is empty!";
            return 1;
        }

        float fault_rate = (fault*100.0)/counter;
        /*
            3. WRITE RESULTS
        */
        writer << pagesize <<","<<fault_rate<< "%\n";
        cout   <<"\t" <<pagesize <<"\t"<<fault_rate <<" %"<< endl;


        /* FREE UP MEMORY */
        delete memory;
        reader.close();
    }
    writer.close();
    cout   << "Saved Output in " << output_filename << "\n";
    return 0;

}//MAIN
