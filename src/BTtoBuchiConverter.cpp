#include "BTtoBuchiConverter.h"
#include <behaviortree_cpp/control_node.h>


BTtoBuchiConverter::BTtoBuchiConverter() {
    globalSuccess_ = createGlobalSuccessNode();
}

std::shared_ptr<BuchiNode> BTtoBuchiConverter::toBuchi(BT::TreeNode* node) {
    auto startNode_= recursiveToBuchi(node, globalSuccess_, nullptr);
    //post process all nullptr to be startNode_
    patch(startNode_, startNode_);
    return startNode_;
}


void BTtoBuchiConverter::patch(std::shared_ptr<BuchiNode> node, std::shared_ptr<BuchiNode> pch){
    if(node->successNode == nullptr){
        node->setSuccessNode(pch);
    }
    else if(node->successNode != node){
        patch(node->successNode, pch);
    }
    if(node->failureNode == nullptr){
        node->setFailureNode(pch);
    }
    else if(node->failureNode != node){
        patch(node->failureNode, pch);
    }
    return;
}


std::shared_ptr<BuchiNode> BTtoBuchiConverter::recursiveToBuchi(
    BT::TreeNode* node,
    std::shared_ptr<BuchiNode> successNode,
    std::shared_ptr<BuchiNode> failureNode)
{
    if (!node) return successNode;

    // --- Simple Action ---
    if (auto action = dynamic_cast<BT::SyncActionNode*>(node)) {
        auto bNode = std::make_shared<BuchiNode>(action->name());
        bNode->setSuccessNode(successNode);
        bNode->setFailureNode(failureNode);   // may be nullptr for now
        return bNode;
    }

    // --- Sequence Node ---
    else if (auto seq = dynamic_cast<BT::SequenceNode*>(node)) {
        auto& children = seq->children();

        std::shared_ptr<BuchiNode> first = nullptr;
        std::shared_ptr<BuchiNode> prev  = nullptr;

        for (size_t i = 0; i < children.size(); ++i) {
            auto child = children[i];

            auto childSuccess =
                (i + 1 < children.size()) ? nullptr : successNode;

            auto childBuchi =
                recursiveToBuchi(child, childSuccess, failureNode);

            if (!first) first = childBuchi;
            if (prev)
                prev->setSuccessNode(childBuchi);

            prev = childBuchi;
        }

        return first;
    }

    // --- Fallback Node ---
    else if (auto fb = dynamic_cast<BT::FallbackNode*>(node)) {
        auto& children = fb->children();

        std::shared_ptr<BuchiNode> first = nullptr;
        std::shared_ptr<BuchiNode> prev  = nullptr;

        for (size_t i = 0; i < children.size(); ++i) {
            auto child = children[i];

            auto childSuccess = successNode;
            auto childFailure =
                (i + 1 < children.size()) ? nullptr : failureNode;

            auto childBuchi =
                recursiveToBuchi(child, childSuccess, childFailure);

            if (!first) first = childBuchi;
            if (prev)
                prev->setFailureNode(childBuchi);

            prev = childBuchi;
        }

        return first;
    }

    return successNode;
}

std::shared_ptr<BuchiNode> BTtoBuchiConverter::createGlobalSuccessNode(){
    auto node = std::make_shared<BuchiNode>("GlobalSuccess");
    node->setSuccessNode(node);  // loops to itself
    node->setFailureNode(node);  // loops to itself
    return node;
}