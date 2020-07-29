#include "categorizer.hpp"

using namespace std;

unsigned int histogram[256];
int alphabet[256];

int main(int argc, char **args)
{
    fstream file;
    char PGM_hdr1[2];
    int width;
    int height;
    width = 0;
    height = 0;

    if (argc == 1)
    {
        cerr << "Please specify file(s)" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        file.open(args[i], ios::binary|ios::in);
        if (!file.is_open())
        {
            cerr << "File " << args[i] << " is not accesseble" << endl;
            continue;
        }
        cout << "File " << args[i] << " opened" << endl;

        file.read(PGM_hdr1, 2);

        if ((PGM_hdr1[0] != 0x50) || (PGM_hdr1[1] != 0x32))
            continue;

        cout << "PGM file detected" << endl;

        file.seekg(static_cast<unsigned int>(file.tellg()) + 1);
        unsigned int digit_b = static_cast<unsigned int>(file.tellg());
        char sym;
        do 
        {
            file.read(&sym, 1);
        } while(sym != 0x20);
        unsigned int digit_e = static_cast<unsigned int>(file.tellg()) - 2;
        int j = 0; 
        for (int d = '0'; d <= '9'; d++, j++) alphabet[d] = j;
        int c = 1;
        for (j = digit_e; j >= digit_b; j--, c *= 10)
        {
            file.seekg(j);
            file.read(&sym, 1);
            width += alphabet[sym] * c;
        }

        cout << "Width: " << width << endl;

        digit_b = digit_e + 2;

        do 
        {
            file.read(&sym, 1);
        } while(sym != 0x0A);

        digit_e = static_cast<unsigned int>(file.tellg()) - 2;

        c = 1;
        for (j = digit_e; j >= digit_b; j--, c *= 10)
        {
            file.seekg(j);
            file.read(&sym, 1);
            height += alphabet[sym] * c;
        }

        cout << "Height: " << height << endl;

        file.close();
    }

    return 0;
}