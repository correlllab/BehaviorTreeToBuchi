#pragma once

#include <behaviortree_cpp/bt_factory.h>
#include <string>
#include <vector>

class BTtoLTLConverter {
public:
    // Convert a BT node to an LTL formula string
    std::string toLTL(BT::TreeNode* node);

private:
    // Convert a sequence node to LTL
    std::string sequenceLTL(const std::vector<BT::TreeNode*>& children);
};
