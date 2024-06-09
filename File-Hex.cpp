#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>

void toFile(const std::string &inputFilePath, const std::string &outputFilePath)
{
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
    std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);

    if (!inputFile.is_open())
    {
        std::cout << "Error opening input file!" << std::endl;
        return;
    }

    if (!outputFile.is_open())
    {
        std::cout << "Error opening output file!" << std::endl;
        return;
    }

    std::string hexData;
    inputFile >> std::noskipws >> hexData;

    // Process the hex data and convert it to binary
    for (std::size_t i = 0; i < hexData.length(); i += 2)
    {
        unsigned int byte;
        std::stringstream ss;
        ss << std::hex << hexData.substr(i, 2);
        ss >> byte;
        outputFile.put(static_cast<char>(byte));
    }

    inputFile.close();
    outputFile.close();
}

void toHex(const std::string &inputFilePath, const std::string &outputFilePath)
{
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
    std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);

    if (!inputFile.is_open())
    {
        printf("Error opening input file!\n");
        return;
    }

    if (!outputFile.is_open())
    {
        printf("Error opening output file!\n");
        return;
    }

    char byte;
    while (inputFile.get(byte))
    {
        outputFile << std::hex << std::setw(2) << std::setfill('0') << (0xff & (int)byte);
    }

    inputFile.close();
    outputFile.close();
}

std::string getExtension(std::string fileName)
{
    std::string result;

    return result;
}

int main(int argc, char *argv[])
{
    std::cout << "                                                  | |                \n";
    std::cout << "       ___    ___    _ __   __   __   ___   _ __  | |_    ___   _ __ \n";
    std::cout << "      / __|  / _ \\  | '_ \\  \\ \\ / /  / _ \\ | '__| | __|  / _ \\ | '__|\n";
    std::cout << "  _  | (__  | (_) | | | | |  \\ V /  |  __/ | |    | |_  |  __/ | |   \n";
    std::cout << " (_)  \\___|  \\___/  |_| |_|   \\_/    \\___| |_|     \\__|  \\___| |_|   \n";
    std::cout << "                                                                      \n";

    switch (argc)
    {
    case 5:
    {
        if (strcmp(argv[1], "-a") == 0)
        {
            std::string dirPath(argv[3]);
            printf("\nInput dir:\t%s", dirPath.c_str());
            std::filesystem::create_directory(argv[4]);
            printf("\nOutput dir:\t%s\n", argv[4]);
            std::string outDir(argv[4]);
            if (strcmp(argv[2], "-h") == 0)
            {
                for (const auto &file : std::filesystem::directory_iterator(dirPath))
                {
                    if (strcmp(file.path().string().c_str(), outDir.c_str()) == 0)
                    {
                        continue;
                    }
                    printf("[hexing file]\t%s\n", file.path().string().c_str());
                    toHex(file.path().string(), outDir + "\\" + file.path().stem().string() + file.path().extension().string() + ".bin");
                }
            }
            else if (strcmp(argv[2], "-f") == 0)
            {
                for (const auto &file : std::filesystem::directory_iterator(dirPath))
                {
                    if (strcmp(file.path().string().c_str(), outDir.c_str()) == 0)
                    {
                        continue;
                    }
                    printf("[converting file]\t%s\n", file.path().string().c_str());
                    toFile(file.path().string(), outDir + "\\" + file.path().stem().string());
                }
            }
        }
    }
    break;
    case 4:
    {
        // a specific conversion was given
        std::string inputFilePath = argv[2];
        std::string outputFilePath = argv[3];

        if (strcmp(argv[1], "-f") == 0)
        {
            toFile(inputFilePath, outputFilePath);
        }
        else if (strcmp(argv[1], "-h") == 0)
        {
            toHex(inputFilePath, outputFilePath);
        }
    }
    break;
    default:
    {
        printf("\n\nUsage %s ", argv[0]);
        printf("\n\t<-h>\tfor file to hex\n\t<-f>\tfor hex to file (provide file type at the end eg file.jpg)");
        printf("\n\t<-a> <path to input dir> <path to output dir>\tfor all the files in the dir to be converted\n");
        printf("\n\t<input file>\tthe file you want as input\n\t<output file> the file that will be generated\n");
    }
    }
    return 0;
}