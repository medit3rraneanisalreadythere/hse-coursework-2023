#include "Model.hpp"

bool Model::insert(const int x)
{
    if (!presence[x])
    {
        presence[x]++;
        tree.insert(x);
        data = tree.getTree();
        return true;
    }

    return false;
}

bool Model::remove(const int x)
{
    if (presence[x])
    {
        presence[x]--;
        tree.remove(x);
        data = tree.getTree();
        return true;
    }
    
    return false;
}

void Model::clear()
{
    presence.clear();
    tree.clear();
    data = tree.getTree();
}

void Model::print()
{
    tree.printTree();
}

void Model::close()
{
    presence.clear();
    tree.clear();
}