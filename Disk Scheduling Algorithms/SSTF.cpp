#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include "helper.h"

using namespace std;

void print_ruler_empty(int to){
    for(int i=0;i<to+2;i++){
         cout<<"|";
    }
    cout<<endl;
}

void print_ruler(int to)
{
    int y = to;
    //int x;
    int powers = 1;
    int nlines = 1;
    while(y>10)
    {
        y/=10;
        powers*=10;
        nlines++;
    }
    int cPow  = 1;
    print_ruler_empty(to);

    while(nlines>0)
    {
        cPow*=10;
        int counter = 0;
        //cout << "Power " <<powers << " lines " << nlines << endl;
        cout<<"|";
        for(int k=0; k<cPow && counter<to; k++)
        {
            for(int i=0; i<10 && counter<to; i++)
            {
                for(int j=0; j<powers && counter<to; j++)
                {
                    cout<<i;
                    counter++;
                }
            }
        }
        cout<<"|"<<endl;
        nlines--;
        powers/=10;
    }
    print_ruler_empty(to);
}

void print_movement(int from, int to, int length)
{
    int x,y;
    if(from<=to)
    {
        x = from;
        y = to ;
    }
    else
    {
        x = to;
        y = from;
    }
    cout<<"|";
    for(int i=0; i<x; i++)
        cout<<' ';
    cout<< (from<=to ?"|":"X") ;
    for(int k=x+1; k < y; k++)
    {
        cout<< (from<=to ?">":"<") ;
    }
    cout<< (from<=to ? (from==to?"\bX":"X"):"|") ;

    for(int l=y+1; l < length; l++)
        cout<<' ';
    cout<<"|" << endl;
}

int find_next_minimum(int *arr, bool *done,int headPos, int arr_size )
{
    int i = 0;
    //look for first non done request.
    while(done[i]==1)
    {
        i++;
    }
    int minimum = i;

    for(int k=i+1; k<arr_size ; k++)
    {
        if(abs(headPos-arr[k])<abs(headPos-arr[minimum]) && done[k]==0)
            minimum=k;
    }

    return minimum;
}

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << "  [<-p HEADPOSITION> -l NUMBER -i | FILENAME | -r NUMBER | -s]\n"
              << "Options: \n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-p,--head NUMBER\tthe head position in less than track length (random)\n"
              << "\t-i,--input FILENAME\tthe name of input file contains data\n"
              << "\t-l,--length NUMBER\tthe track length (default 200)\n"
              << "\t-r,--random\t\tRandom NUMBER of seeking (default 10 numbers)\n"
              << "\t-s,--show\t\tPrint steps\n"
              << std::endl;
}

int main(int argc,char**argv)
{
    if(argc<1)
    {
        show_usage(argv[0]);
        return 0;
    }
    string  input_filename = "";
    int  track_length  = 200;
    bool print         = false;
    int head_position  = -1;
    int n_requests     = 10;
    int total_distance = 0;
    int *requests;
    bool*requests_done;
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
            else if ((arg == "-l") || (arg == "--length"))
            {
                if (i + 1 < argc)
                {
                    track_length = stoi(argv[++i]);
                }
                else
                {
                    std::cerr << "--length option requires one argument." << std::endl;
                    return 1;
                }
            }
            else if ((arg == "-p") || (arg == "--head"))
            {
                if (i + 1 < argc)
                {
                    head_position = stoi(argv[++i]);
                }
                else
                {
                    std::cerr << "--head option requires one argument." << std::endl;
                    return 1;
                }
            }
            else if ((arg == "-s") || (arg == "--show"))
            {
                print = true;
            }
            else if ((arg == "-r") || (arg == "--random"))
            {
                if (i + 1 < argc)
                {
                    n_requests = stoi(argv[++i]);
                }
                else
                {
                    std::cerr << "--head option requires one argument." << std::endl;
                    return 1;
                }
            }
        }
    }
    catch(std::exception& e)
    {
        show_usage(argv[0]);
    }

    ifstream reader(input_filename.c_str());


    /**
        1. CREATE REQUEST ARRAY
    **/
    if(strlen(input_filename.c_str())>0)
    {
        if(!reader.good())
        {
            cerr<< "Input File not found!\n";
            return 1;
        }
        int req; // read flag
        n_requests = 0;
        /** Count request from file **/
        while(reader>>req)
        {
            n_requests++;
        }
        /** Create array of requests **/
        requests = new int[n_requests];

        /** Fill data **/
        reader.open(input_filename);
        for(int i =0; i<n_requests; i++)
        {
            reader>>req;
            requests[i]=req;
        }
        reader.close();

    }
    else
    {
        /** Create random requests **/
        requests = new int[n_requests];
        for(int i =0; i<n_requests; i++)
        {
            int next_rand =rand()%track_length;
            while(sequenialSearch(requests,i,next_rand )!=-1)
            {
                //looking for random not exist
                next_rand++;
            }
            requests[i] = next_rand;
        }
    }


    /** reset done requests **/
    requests_done = new bool[n_requests];
    memset(requests_done,0,n_requests*sizeof(requests_done));


    /** reset head **/
    if(head_position==-1)
        head_position= rand()%track_length;

    /** print requests **/
    printArray(requests, n_requests);
    cout<< "Start Head @ " << head_position <<endl;

    print_ruler(track_length);
    /** ALL REQUESTS **/
    for(int k = 0; k < n_requests; k++)
    {

        /**
            2. FIND NEXT Shortest Seek Time
        **/
        int idx = find_next_minimum(requests, requests_done, head_position, n_requests );
        // Mark as done
        requests_done[idx] = true;
        // Add distance
        total_distance += abs(requests[idx]-head_position);

        if(print)
        {
            print_movement(head_position,requests[idx],track_length);
        }

        // Move head to new
        head_position = requests[idx];

    }

    print_ruler_empty(track_length);
    cout<< "Total Distance = " << total_distance << endl;
    delete requests;
    delete requests_done;
    return 0;

}//MAIN
