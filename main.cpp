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
     bool Clear()
   {
       if (open_mode != ios::out)
       {
           open_mode = ios::out;
       }
       file.open(path, open_mode);
       if (file.is_open())
       {
           file << "" << endl;
           this->CloseFile();
       }
       return (this->isEmpty()) ? true : false;
   }
};

string Cezar(int index, string text)
{
    string text2(text.length(), ' ');
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size = mystrlen(alphabet);
    for (size_t i = 0; i < mystrlen(text); i++)
    {
        if (isalpha(text [i]) || isdigit(text[i]))
        {
            if (islower(text[i]))
            {
                text[i] = toupper(text[i]);
                for (size_t j = 0; j < mystrlen(alphabet); j++)
                {
                    if (text[i] == alphabet[j])
                    {
                        if ((j + index) > size)
                        {
                            text2[i] = (alphabet[(j + index) - size]);
                        }
                        else
                        {
                            text2[i] = (alphabet[j + index]);
                        }
                        text2[i] = tolower(text2[i]);
                    }
                }
            }
            else
            {
                for (size_t j = 0; j < mystrlen(alphabet); j++)
                {
                    if (text[i] == alphabet[j])
                    {
                        if ((j + index) > size)
                        {
                            text2[i] = (alphabet[(j + index) - size]);
                        }
                        else
                        {
                            text2[i] = (alphabet[j + index]);
                        }
                    }
                }
            }
        }
        else
        {
            text2[i] = text[i];
        }
    }
    return text2;
}

int main()
{
    string text1, textC, text2;
    int index;
    File* file1 = new File("Ex3(Orig)");
    File* file2 = new File("Ex3(Cezar)");
    if ((file1->isEmpty()) == false)
    {
        file1->Clear();
    }
    cout << "Enter text (type 'quit' !starting of new line! to exit): " << endl;
    while (getline(cin, text1) && text1 != "quit")
    {
        if (file1->isEmpty())
        {
            file1->Write(text1);
        }
        else
        {
            file1->Write(text1, true);
        }
    }
    file1->Load(text2);
    cout << "Enter index for cipher: ";
    cin >> index;
    textC = Cezar(index, text2);
    system("pause");
    system("cls");
    file2->Write(textC);
    cout << "Original text:\n" << text2 << endl;
    cout << "Cezar cipher by index " << index << ":\n" << textC << endl;
    return 0;
}