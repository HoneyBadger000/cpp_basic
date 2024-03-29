// Dependency inversion principle
// Both high level and low level modules must depend on interfaces/abstractions but not on each others implementations
// Abstractions shouldnot depend on details, details should depend on abstractions

// Abstractions are interfaces or base classes

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person{
    string name;
};

struct RelationshipBrowser{
    virtual vector<Person> find_all_children_of(const string& name) =0;

};

struct Relationships : RelationshipBrowser // low level module
{
    vector<tuple<Person, Relationship , Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child){
        relations.push_back({parent, Relationship::parent , child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string& name) override{
        vector<Person> result;

        for(auto&& [first, rel, second] : relations)
        {
            if(first.name == name && rel == Relationship::parent)
                result.push_back(second);
        }

        return result;
    }
};

struct Research // High level module
{
    // this is directly accessing low level module!this is bad!!

    Research(RelationshipBrowser& browser){
        for(auto& child : browser.find_all_children_of("John"))
            cout << "John has a child called " << child.name << endl;
    }
    
    // Research(Relationships& relationships){
    //     auto& relations = relationships.relations;
    //     for(auto& [first, rel, second] : relations){
    //         if(first.name == "John" && rel == Relationship::parent)
    //             cout << "John has a child called " << second.name << endl;
    //     }

    // }
};






int main(){
    Person parent{"John"};
    Person child1{"Chirs"}, child2{"Matt"};

    Relationships relationships;

    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent,child2);

    Research research(relationships);

    return 0;
}