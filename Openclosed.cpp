// Open closed principle -- Bad example, every time we need to implement a new filter, 
// A new function needs to be implemented.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium ,large};

struct Product{
    string name;
    Color color;
    Size size;
};

struct ProductFilter_naive{
    vector<Product*> by_color(vector<Product*> items, Color color)
    {
        vector<Product*> result;
        for(auto& i: items){
            if(i->color == color)
            result.push_back(i);        
        }
        return result;
    }

    vector<Product*> by_size(vector<Product *>items, Size size){
        vector<Product *> result;
        for(auto& i : items){
            if(i->size == size)
                result.push_back(i);
        }
        return result;
    }
};

template <typename T> struct Specification
{
    // Pure virtual function which has a boolean function that returns
    virtual bool is_satisfied(T* item) const = 0;

    AndSpecification<T> operator&&(Specification<T>& other){
        
    }
};

template <typename T> struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T> &first,Specification<T> &second) : first(first), second(second){}

    bool is_satisfied(T *item) const override{
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

//Create a better filter, that is deried from the Filter template, and implement the better filter
struct BetterFilter : Filter<Product>
{
    vector<Product *> filter(vector<Product *> items, Specification<Product> & spec) override 
    {
        vector<Product*> result;

        for(auto& p:items)
        {
            if(spec.is_satisfied(p))
                result.push_back(p);
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;
    ColorSpecification(Color color) : color(color){}
    bool is_satisfied(Product* item) const override{
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    // explicit -- prevents the compiler from using this constructor for implicit conversions

    explicit SizeSpecification(Size size) : size(size){}

    bool is_satisfied(Product* item) const override{
        return item->size == size;
    }
};



int main(){

    Product apple{"Apple", Color::green , Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product*> items {&apple, &tree,&house};

    ProductFilter_naive pf;
    BetterFilter bf;

    ColorSpecification green(Color::green);
    SizeSpecification small(Size::small);
    AndSpecification<Product> green_and_small(green, small);

    auto green_things_bf = bf.filter(items, green);

    for(auto& item :green_things_bf)
        cout << item->name << " is green " << endl;

    auto green_small = bf.filter(items, green_and_small);

    for(auto& item:green_small)
        cout << item->name << " is green and small " << endl;

    auto green_things = pf.by_color(items, Color::green);

    for(auto& item :green_things)
        cout << item->name << " is green " << endl;

    auto small_things = pf.by_size(items, Size::small);

    for(auto& item:small_things)
        cout << item->name << " is small " << endl;
    return 0;
}



