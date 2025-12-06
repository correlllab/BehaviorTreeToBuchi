#include <iostream>
#include "BTtoBuchiConverter.h"
#include "BuchiNode.h"
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/control_node.h> // for SequenceNode

int main() {
    BT::BehaviorTreeFactory factory;

    // Humanoid Bolt Removal BT Nodes
    // factory.registerSimpleAction("Bolt_Already_Removed", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("Arm_Not_at_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("Remove_the_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    
    // Humanoid Bolt Removal BT
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

    // UR16E Robotic Arm Bolt Removal BT Nodes
    // factory.registerSimpleAction("Already_Unscrewed_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("Humanoid_Not_Removing_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("At_Bolt_Location", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("Go_To_Bolt_Location", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    // factory.registerSimpleAction("Unscrew_Bolt", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });

    // UR16E Robotic Arm Bolt Removal BT
    // auto tree = factory.createTreeFromText
    //     (R"(
    //     <root
    //     main_tree_to_execute="MainTree"
    //     BTCPP_format="4">
    //     <BehaviorTree ID="MainTree">
    //         <Fallback
    //         name="root_fallback">
    //         <Already_Unscrewed_Bolt/>
    //         <Sequence name="sq1">
    //             <Humanoid_Not_Removing_Bolt/>
    //             <Fallback name="fb">
    //                 <Go_To_Bolt_Location/>
    //                 <Unscrew_Bolt/>
    //             </Fallback>
    //             <Unscrew_Bolt/>
    //         </Sequence>
    //         </Fallback>
    //     </BehaviorTree>
    //     </root>
    //     )");


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
