#include "BuchiNode.h"
#include <memory>

// Constructor
BuchiNode::BuchiNode(std::string name) 
    : name_(name), successNode(nullptr), failureNode(nullptr) {}

// Setters
void BuchiNode::setSuccessNode(std::shared_ptr<BuchiNode> node) {
    successNode = node;
}

void BuchiNode::setFailureNode(std::shared_ptr<BuchiNode> node) {
    failureNode = node;
}

// Transition function
std::shared_ptr<BuchiNode> BuchiNode::transition(AP prep) {
    if (prep == AP::FAILURE) {
        return failureNode ? failureNode : shared_from_this();
    } 
    else if (prep == AP::SUCCESS) {
        return successNode ? successNode : shared_from_this();
    } 
    else {
        return shared_from_this(); // RUNNING
    }
}
