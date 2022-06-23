#include "ptrie.hpp"
#include "ptrie_edge.hpp"
#include "ptrie_node.hpp"
#include <iostream>

int main() {

    PTrie pt;   
        pt.insert("AFF");
    pt.insert("ASDASD");    

 pt.insert("ASD");

    // pt.remove("AFF");    


    // pt.remove("ASDASD");

    // pt.remove("ASD");

    // std::cout << "num: " << pt.root->getEdges().begin()->second->getPrefix() << std::endl;
    // pt.root = pt.root->getEdges().begin()->second->getNode();
    // if(!pt.root->hasEdges()) std::cout << "maika ti da eba" << std::endl;

    std::cout << pt.search("ASDASD") << std::endl;
    // pt.remove("ASDASD");
    // std::cout << "is there " << pt.search("ASD") << std::endl;

    return 0;
}