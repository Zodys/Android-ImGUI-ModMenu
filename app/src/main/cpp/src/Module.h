#pragma once
#include <string>
using namespace std;
class Module
{
public:
    Module(const std::string& name) : m_name(name){};

    virtual void draw() = 0; //for drawlist shit
    virtual void drawUI() = 0;

    std::string get_name() { return m_name; }
private:
    std::string m_name;
};
