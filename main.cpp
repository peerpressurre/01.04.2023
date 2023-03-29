#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::cout;
using std::istream; 
using std::ostream; 
using std::fstream; 
using std::ios_base;
#define next_line { cout << endl; }

int mystrlen(string str)
{
    int i = 0;
    int counter = 0;
    while (str[i] != '\0')
    {
        counter++;
        i++;
    }
    return counter;
}

bool isVowel(char c) 
{
    c = toupper(c); 
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

bool isConsonant(char c) {
    c = toupper(c); 
    return (c == 'B' || c == 'C' || c == 'D' || c == 'F' || c == 'G' || c == 'H' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'V' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z')? true : false;
}


struct File
{
private:
    string path;
    fstream file;
    ios_base::open_mode open_mode;
public:
    //Setters & Getters
    void setPath(string path)
    {
        this->path = path;
    }

    void setOpenMode(ios_base::open_mode open_mode)
    {
        this->open_mode = open_mode;
    }

    ios_base::open_mode getOpenMode()
    {
        return open_mode;
    }

    string getPath()
    {
        return path;
    }


    //Constructors & Destructor 
    File()
    {
        setPath("text.txt");
        setOpenMode(ios::out);
    }
    File(string path) : File()
    {
        setPath(path);
    }
    File(string path, ios_base::open_mode open_mode) : File(path)
    {
        setOpenMode(open_mode);
    }
    ~File()
    {
        path.clear();
        file.close();
        open_mode = 0;
    }
    //Actions 
    bool Write(string text, bool append = false) {
        if (open_mode != ios::out && append == false)
        {
            open_mode = ios::out;
        }
        else if (open_mode != ios::app && append == true)
        {
            open_mode = ios::app;
        }
        file.open(path, open_mode);
        if (file.is_open())
        {
            file << text << endl;
            this->CloseFile();
            return true;
        }
        else {
            return false;
        }
    }

    void WriteChar(char c)
    {
        if (file)
        {

        }
        file.open(path, open_mode);
        if (file.is_open())
        {
            file << text << endl;
            this->CloseFile();
            return true;
        }
    }
    bool isEmpty()
    {
        string buf;
        if (Load(buf))
        {
            return (buf.empty()) ? true : false;
        }
        else {
            return true;
        }
    }
    bool Load(string& text) {
        string buf;
        if (open_mode != ios::in)
        {
            open_mode = ios::in;
        }
        file.open(path, open_mode);
        if (file.is_open())
        {
            while (getline(file, buf))
            {
                text += buf;
                text += "\n";
            }
            this->CloseFile();
            return true;
        }
        else {
            return false;
        }
    }
    bool CreateFile() {
        if (open_mode != ios::out)
        {
            open_mode = ios::out;
        }
        file.open(path, open_mode);
        return (file.is_open()) ? true : false;
    }
    void CloseFile() {
        this->file.close();
    }
    void New_line()  
    {
        open_mode = ios::out;
        file.open(path, open_mode);
        if (file.is_open())
        {
            file << endl;
            this->CloseFile();
        }
    }
};

int main()
{
    string in_text, out_text;
    int digits = 0, symbols = 0, lines = 0, vowels = 0, consonants = 0;
  
    File* file1 = new File();  //create original file
    File* file2 = new File();  //create copy file

    cout << "Enter text for 1st file (for new line type \"/n\"): ";
    getline(cin, in_text);
    for (size_t i = 0; i < mystrlen(in_text); i++)
    {
        if (in_text[i] == '/')
        {
            if (in_text[i+1] == 'n')
            {
                file1->New_line();
            }
        }
        else
        {
            file1->Write(in_text[i]); //fill first file
        }
    }

    file1->Load(out_text); //load file out

    for (size_t i = 0; i < mystrlen(out_text); i++)
    {
        if (isdigit(out_text[i]))
        {
            digits++;
        }
        if (isdigit(out_text[i]) || isVowel(out_text[i]) || isConsonant(out_text[i]) || ((out_text[i]) >= 33 && out_text[i] <= 47) || ((out_text[i]) >= 58 && out_text[i] <= 64) || ((out_text[i]) >= 91 && out_text[i] <= 96) || ((out_text[i]) >= 123 && out_text[i] <= 126))
        {
            symbols++;
        }
        if (out_text[i] == '\n')
        {
            lines++;
        }
        if (isVowel(out_text[i]))
        {
            vowels++;
        } 
        if (isConsonant(out_text[i]))
        {
            consonants++;
        }
    }
    system("pause");
    system("cls");
    cout << out_text << endl;
    cout << "Symbols: " << symbols << endl;
    cout << "Lines: " << lines << endl;
    cout << "Vowels: " << vowels << endl;
    cout << "Consonants: " << consonants << endl;
    cout << "Digits: " << digits << endl;

    return 0;
}