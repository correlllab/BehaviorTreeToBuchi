#pragma once
#include <string>
#include <memory>

enum class AP{
    RUNNING,
    SUCCESS,
    FAILURE,
};

class BuchiNode : public std::enable_shared_from_this<BuchiNode> {
    public:
        BuchiNode(std::string name);
        std::shared_ptr<BuchiNode> successNode;
        std::shared_ptr<BuchiNode> failureNode;
        void setSuccessNode(std::shared_ptr<BuchiNode> node);
        void setFailureNode(std::shared_ptr<BuchiNode> node);
        std::shared_ptr<BuchiNode> transition(AP prep);
        std::string name_;

};