#include <iostream>
#include "BTtoLTLConverter.h"
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/control_node.h> // for SequenceNode

int main() {
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleAction("A", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("B", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("C", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("D", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });

    auto tree = factory.createTreeFromText(R"(
        <root main_tree_to_execute="MainTree">
            <BehaviorTree ID="MainTree">
                <Sequence name="root_sequence">
                    <Sequence name="first_sequence">
                        <A/>
                        <B/>
                    </Sequence>
                    <Sequence name="second_sequence">
                        <C/>
                        <D/>
                    </Sequence>
                </Sequence>
            </BehaviorTree>
        </root>
    )");


    BTtoLTLConverter converter;
    std::string ltl = converter.toLTL(tree.rootNode());

    std::cout << "LTL formula for the sequence: " << ltl << std::endl;

    return 0;
}
