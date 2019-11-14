#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct HtmlElement{
    string name, text;
    vector <HtmlElement> elements;

    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(const string& name, const string& text) : name(name) , text(text) {}

    string str(int indent = 0) const{
        ostringstream oss;
        string i(indent_size* indent, '');
        oss << i << "<" << name << ">" << endl;

        if(text.size() > 0)
            oss << string(indent_size*(indent + 1), '') << text << endl;

        for(const auto& e : elements)
            oss
    }
};

int main(){

    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";

    cout << output << endl;

    string words[] = {"hello", "world"};
    ostringstream oss;

    oss << "<ul>";

    for(auto w:words){
        oss << "  <li>" << w << "</li>";
    }

    oss << "/ul";
    cout << oss.str() << endl;

    return 0;

}