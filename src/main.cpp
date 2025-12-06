#include <iostream>
#include "BTtoBuchiConverter.h"
#include "BuchiNode.h"
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/control_node.h> // for SequenceNode

int main() {
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleAction("Already_Unscrewed_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("Humanoid_Not_Removing_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("At_Bolt_Location", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("Go_To_Bolt_Location", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("Unscrew_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });

    // auto tree = factory.createTreeFromText
    // (R"(
    // <root
    // main_tree_to_execute="MainTree"
    // BTCPP_format="4">
    // <BehaviorTree ID="MainTree">
    //     <Sequence
    //     name="root_sequence">
    //         <Fallback name="Remove_Bolt_1">
    //             <Bolt_Already_Removed/>
    //             <Sequence name="Do_Remove_Bolt_1">
    //                 <Arm_Not_at_Bolt/>
    //                 <Remove_the_Bolt/>
    //             </Sequence>
    //         </Fallback>
    //         <Fallback name="Remove_Bolt_2">
    //             <Bolt_Already_Removed/>
    //             <Sequence name="Do_Remove_Bolt_2">
    //                 <Arm_Not_at_Bolt/>
    //                 <Remove_the_Bolt/>
    //             </Sequence>
    //         </Fallback>
    //         <Fallback name="Remove_Bolt_3">
    //             <Bolt_Already_Removed/>
    //             <Sequence name="Do_Remove_Bolt_3">
    //                 <Arm_Not_at_Bolt/>
    //                 <Remove_the_Bolt/>
    //             </Sequence>
    //         </Fallback>
    //     </Sequence>
    // </BehaviorTree>
    // </root>
    // )");

    auto tree = factory.createTreeFromText
        (R"(
        <root
        main_tree_to_execute="MainTree"
        BTCPP_format="4">
        <BehaviorTree ID="MainTree">
            <Fallback
            name="root_fallback">
            <Already_Unscrewed_Bolt/>
            <Sequence name="sq1">
                <Humanoid_Not_Removing_Bolt/>
                <Fallback name="fb">
                    <Go_To_Bolt_Location/>
                    <Unscrew_Bolt/>
                </Fallback>
                <Unscrew_Bolt/>
            </Sequence>
            </Fallback>
        </BehaviorTree>
        </root>
        )");

    BTtoBuchiConverter converter;
    auto start = converter.toBuchi(tree.rootNode());
    std::cout << start->name_ << std::endl;
    auto next = start->transition(AP::FAILURE);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::SUCCESS);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::FAILURE);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::FAILURE);
    std::cout << next->name_ << std::endl;
    return 0;
}
