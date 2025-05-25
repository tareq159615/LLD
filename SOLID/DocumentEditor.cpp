#include <bits/stdc++.h>
using namespace std;

class DocumentEditor
{
private:
    vector<string> documentElement;
    string rendereDocument;

public:
    // add text
    void addText(string text)
    {
        documentElement.push_back(text);
    }

    // add img
    void addImg(string imgPath)
    {
        documentElement.push_back(imgPath);
    }

    // renders the document by checking the type of each element at runtime
    string renderDocument()
    {

        if (rendereDocument.empty())
        {
            string result;
            for (auto element : documentElement)
            {
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" || element.substr(element.size() - 4) == ".png"))
                {
                    result += "[Image: " + element + "]" + "\n";
                }
                else
                {
                    result += element + "\n";
                }
            }
            rendereDocument = result;
        }
        return rendereDocument;
    }

    // seve To File
    void saveToFile()
    {
        ofstream file("document.txt");
        if (file.is_open())
        {
            file << renderDocument();
            file.close();
            cout << "Document saved to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

int main()
{
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImg("pic.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument()<< endl;

    editor.saveToFile();

    return 0;
}