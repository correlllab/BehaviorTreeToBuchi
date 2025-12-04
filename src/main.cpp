#include <iostream>
#include "BTtoBuchiConverter.h"
#include "BuchiNode.h"
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/control_node.h> // for SequenceNode

int main() {
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleAction("BAR1", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("AAB1", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("RB1", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("BAR2", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("AAB2", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("RB2", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("BAR3", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("AAB3", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("RB3", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });


    auto tree = factory.createTreeFromText(R"(
        <root main_tree_to_execute="MainTree" BTCPP_format="4">
            <BehaviorTree ID="MainTree">
                <Sequence name="root_sequence">
                    <Fallback name="fallback1">
                        <BAR1/>
                        <Sequence name="sq1">
                            <AAB1/>
                            <RB1/>
                        </Sequence>
                    </Fallback>
                    <Fallback name="fallback2">
                        <BAR2/>
                        <Sequence name="sq2">
                            <AAB2/>
                            <RB2/>
                        </Sequence>
                    </Fallback>
                    <Fallback name="fallback3">
                        <BAR3/>
                        <Sequence name="sq3">
                            <AAB3/>
                            <RB3/>
                        </Sequence>
                    </Fallback>
                </Sequence>
            </BehaviorTree>
        </root>
    )");

    BTtoBuchiConverter converter;
    //Initialize in Bolt Already Removed 1 (BAR1)
    auto node = converter.toBuchi(tree.rootNode());
    std::cout << node->name_ << std::endl;
    // Failure -> Arm At Bolt 1 (AAB1)
    node = node->transition(AP::FAILURE);
    std::cout << node->name_ << std::endl;
    // Success -> Remove Bolt 1
    node = node->transition(AP::SUCCESS);
    std::cout << node->name_ << std::endl;
    // Failure -> Go To Screw (GTSC)
    node = node->transition(AP::FAILURE);
    std::cout << node->name_ << std::endl;
    // Failure -> Back to Initial state (AU)
    node = node->transition(AP::FAILURE);
    std::cout << node->name_ << std::endl;



    return 0;
}
