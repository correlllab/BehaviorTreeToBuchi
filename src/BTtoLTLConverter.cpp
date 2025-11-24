#include "BTtoLTLConverter.h"
#include <behaviortree_cpp/control_node.h>

std::string BTtoLTLConverter::toLTL(BT::TreeNode* node) {
    if (!node) return "";

    // Sequence node
    if (auto seq = dynamic_cast<BT::SequenceNode*>(node)) {
        return sequenceLTL(seq->children());
    }

    return node->name();
}

std::string BTtoLTLConverter::sequenceLTL(const std::vector<BT::TreeNode*>& children) {
    if (children.empty()) return "";

    // Start from the last child
    std::string ltl = toLTL(children.back());

    for (int i = static_cast<int>(children.size()) - 2; i >= 0; --i) {
        std::string childLTL = toLTL(children[i]);
        ltl = childLTL + " -> X (" + ltl + ")";
    }

    return "G (" + ltl + ")";
}
