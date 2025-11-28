#pragma once

#include "BuchiNode.h"
#include <behaviortree_cpp/bt_factory.h>
#include <string>
#include <vector>
#include <memory>

class BTtoBuchiConverter {
public:
    BTtoBuchiConverter();
    std::shared_ptr<BuchiNode> toBuchi(BT::TreeNode* node);
    std::shared_ptr<BuchiNode> getGlobalSuccessNode();

private:
    void patch(std::shared_ptr<BuchiNode> node, std::shared_ptr<BuchiNode> pch);
    std::shared_ptr<BuchiNode> recursiveToBuchi(BT::TreeNode* node, std::shared_ptr<BuchiNode> success, std::shared_ptr<BuchiNode> failure);
    std::shared_ptr<BuchiNode> startNode_;
    std::string startNodeName_;
    std::shared_ptr<BuchiNode> globalSuccess_;
    std::shared_ptr<BuchiNode> createGlobalSuccessNode();
};
