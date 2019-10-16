# Page Replacement Algorithms

## How to use

- **fifo**: Paging using FIFO Algorithm
```
Usage: .\fifo.exe <-i FILENAME> [-o FILENAME | -p NUMBER | -a | -s]
Required:
        -i,--input FILENAME     the name of input file
Options:
        -h,--help               Show this help message
        -o,--output FILENAME    the name of output file (default output.csv)
        -p,--pagesize NUMBER    the max of page generated (default 10)
        -a,--analysis           Brute-force all page sizes
        -s,--show               Print steps
```

- **random**: Paging using RANDOM Algorithm
```
Usage: .\random.exe <-i FILENAME> [-o FILENAME | -p NUMBER | -a | -s]
Required:
        -i,--input FILENAME     the name of input file
Options:
        -h,--help               Show this help message
        -o,--output FILENAME    the name of output file (default output.csv)
        -p,--pagesize NUMBER    the max of page generated (default 10)
        -a,--analysis           Brute-force all page sizes
        -s,--show               Print steps
```

- **secondchance**: Paging using Second-Chance Algorithm
```
Usage: .\random.exe <-i FILENAME> [-o FILENAME | -p NUMBER | -a | -s]
Required:
        -i,--input FILENAME     the name of input file
Options:
        -h,--help               Show this help message
        -o,--output FILENAME    the name of output file (default output.csv)
        -p,--pagesize NUMBER    the max of page generated (default 10)
        -a,--analysis           Brute-force all page sizes
        -s,--show               Print steps
```
