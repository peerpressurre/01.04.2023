#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::istream; 
using std::ostream; 
using std::fstream; 
using std::ios_base;
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
    bool Save(string text, bool append = false) {
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
    string isEmptyStringFormatResponse()
    {
        string buf;
        if (Load(buf))
        {
            return (buf.empty()) ? "File empty!" : "File not empty!";
        }
        else {
            return "File not found!";
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
    string text1, text2, line1, line2;
    File* file1 = new File();
    File* file2 = new File();
    cout << "Enter text for 1st file: ";
    getline(cin, text1);
    cout << "Enter text for 2nd file: ";
    getline(cin, text2);
    cout << file1->Save(text1) << endl;
    cout << file2->Save(text1) << endl;
    int lineNum = 1;
    while (getline(file1, line1) && getline(file2, line2))
    {
        if (text1 != text2) {
            cout << "Рядок " << lineNum << " не збігається:" << endl;
            cout << "file1.txt: " << line1 << endl;
            cout << "file2.txt: " << line2 << endl;
        }
        lineNum++;
    }
    return 0;
}