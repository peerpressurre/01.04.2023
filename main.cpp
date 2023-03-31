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
};

int main()
{
    string in_text, out_text, info;
    int digits = 0, symbols = 0, lines = 0, vowels = 0, consonants = 0;
  
    File* file1 = new File("Text");  
    File* file2 = new File("Text Info"); 


    cout << "Enter text (type 'quit' !starting of new line! to exit): " << endl;
    while (getline(cin, in_text) && in_text != "quit")
    {
        if (file1->isEmpty())
        {
            file1->Write(in_text);
        }
        else
        {
            file1->Write(in_text, true);
        }
    }

    file1->Load(out_text); 
    
    for (size_t i = 0; i < mystrlen(out_text); i++)
    {
        if (isdigit(out_text[i]))
        {
            digits++;
        }
        if (((out_text[i]) >= 33 && out_text[i] <= 47) || ((out_text[i]) >= 58 && out_text[i] <= 64) || ((out_text[i]) >= 91 && out_text[i] <= 96) || ((out_text[i]) >= 123 && out_text[i] <= 126))
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
    
    file2->Write("Symbols: ", false);
    file2->Write(to_string(symbols), true);
    file2->Write("Lines: ", true);
    file2->Write(to_string(lines), true);
    file2->Write("Vowels: ", true);
    file2->Write(to_string(vowels), true);
    file2->Write("Consonants: ", true);
    file2->Write(to_string(consonants), true);
    file2->Write("Digits: ", true);
    file2->Write(to_string(digits), true);
    file2->Load(info);
    system("pause");
    system("cls");

    cout << "Text.txt:\n" << out_text << endl;
    cout << "Info:\n" << info << endl;
   
    return 0;
}