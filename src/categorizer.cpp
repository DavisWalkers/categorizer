#include "categorizer.hpp"

using namespace std;

unsigned int histogram[256];

int main(int argc, char **args)
{
    fstream file;
    char PGM_hdr1[2];

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

        if ((PGM_hdr1[0] != 0x50) || (PGM_hdr1[1] != 0x35))
            continue;

        cout << "PGM file detected" << endl;

        file.seekg(file.tellg() + 1);

        file.close();
    }

    return 0;
}