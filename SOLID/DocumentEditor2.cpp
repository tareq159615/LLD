#include <bits/stdc++.h>
using namespace std;

// Abstraction for document elements
class DocumentElement
{
public:
    virtual string render() = 0;
};

// Concrete implementation for text elements
class TextElement : public DocumentElement
{
private:
    string text;

public:
    TextElement(string text)
    {
        this->text = text;
    }

    string render() override
    {
        return text;
    }
};

// Concrete implementation for Image elements
class ImageElement : public DocumentElement
{
private:
    string imgPath;

public:
    ImageElement(string imgPath)
    {
        this->imgPath = imgPath;
    }

    string render() override
    {
        return "[Image: " + imgPath + "]";
    }
};

// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement
{
public:
    string render() override
    {
        return "\n";
    }
};

// TabSpaceElement represents a tab spaced in the document.
class TabSpaceElement : public DocumentElement
{
public:
    string render() override
    {
        return "\t";
    }
};

// document class responsible for holding a collection of elements
class Document
{
private:
    vector<DocumentElement *> documentElements;

public:
    void addElement(DocumentElement *element)
    {
        documentElements.push_back(element);
    }
    // Renders the document by concateanating the render output of all elements.
    string render()
    {
        string result = "";
        for (auto element : documentElements)
        {
            result += element->render();
        }
        return result;
    }
};

// Persistence Interface
class Persistence
{
public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of persistence
class FileStorage : public Persistence
{
    void save(string data) override
    {
        ofstream outFile("document.txt");
        if (outFile)
        {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistence
{
    void save(string data) override
    {
        cout << "save to DB" << endl;
    }
};

// DocumentEditor class managing client interactions
class DocumentEditor
{
private:
    Document *document;
    Persistence *storage;
    string renderedDocument;

public:
    DocumentEditor(Document *document, Persistence *storage)
    {
        this->document = document;
        this->storage = storage;
    }
    // add text
    void addText(string text)
    {
        document->addElement(new TextElement(text));
    }
    // add img
    void addImage(string imgPath)
    {
        document->addElement(new ImageElement(imgPath));
    }
    // add a new line
    void addNewLine()
    {
        document->addElement(new NewLineElement());
    }
    // add tab space
    void addTabSpace()
    {
        document->addElement(new TabSpaceElement());
    }

    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument()
    {
        storage->save(renderDocument());
    }
};

int main()
{
    Document *document = new Document();
    Persistence *persistence = new FileStorage();

    DocumentEditor *editor = new DocumentEditor(document, persistence);

    // Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and display the final document.
    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}