#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
//string mygetline(string str, string line, char divider = '\n')
//{
//    char c;
//    for (size_t i = 0, j; i < mystrlen(str); i++)
//    {
//        while (str[i] != divider)
//        {
//            line[i] = str[i];
//           
//        }
//    }
//    return line;
//}

void myGetline(const std::string& str, std::string& line, size_t& pos) {
    size_t start = pos;
    size_t end = str.find('\n', start);
    if (end == std::string::npos) {
        line = str.substr(start);
        pos = str.size();
    }
    else {
        line = str.substr(start, end - start);
        pos = end + 1;
    }
}

int main()
{
    string text1, text2, outtext1, outtext2, line1, line2;
    File* file1 = new File("Ex1(1)");
    File* file2 = new File("Ex1(2)");
    if ((file1->isEmpty()) == false)
    {
        file1->Clear();
    }
    if ((file2->isEmpty()) == false)
    {
        file2->Clear();
    }
    cout << "Enter text 1 (type 'quit' !starting of new line! to exit): " << endl;
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

    cout << "Enter text 2 (type 'quit' !starting of new line! to exit): " << endl;
    while (getline(cin, text2) && text2 != "quit")
    {
        if (file2->isEmpty())
        {
            file2->Write(text2);
        }
        else
        {
            file2->Write(text2, true);
        }
    }   
 
    file1->Load(outtext1); //loading out in case there was already text in that file
    file2->Load(outtext2);

    cout << "Tex1:\n" << outtext1 << endl;
    cout << "Tex2:\n" << outtext2 << endl;
    int line_number = 1;
    while (getline(file1, line1) && getline(file2, line2)) {
        if (line1 != line2)
        {
            cout << "Mismatch on line " << line_number << ":" << endl;
            cout << "File 1: " << line1 << endl;
            cout << "File 2: " << line2 << endl;
            return 0;
        }
        line_number++;
    }
  

    /*while (getline(file1, line1) && getline(file2, line2))
    {
        i++;
        if (line1 == line2)
        {
            cout << line1 << "\t=\t" << line2 << endl;
        }
        else
        {
            cout << line1 << "\t!=\t" << line2 << endl;
        }
    }*/
    
    return 0;
}