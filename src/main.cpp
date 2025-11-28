#include <iostream>
#include "BTtoBuchiConverter.h"
#include "BuchiNode.h"
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/control_node.h> // for SequenceNode

int main() {
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleAction("A", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("B", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    factory.registerSimpleAction("C", [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });



    // auto tree = factory.createTreeFromText(R"(
    // <root main_tree_to_execute="MainTree" BTCPP_format="4">
    //     <BehaviorTree ID="MainTree">
    //         <A/>
    //     </BehaviorTree>
    // </root>
    // )");
    auto tree = factory.createTreeFromText(R"(
        <root main_tree_to_execute="MainTree" BTCPP_format="4">
            <BehaviorTree ID="MainTree">
                <Sequence name="root_sequence">
                    <A/>
                    <B/>
                </Sequence>
            </BehaviorTree>
        </root>
    )");
//     auto tree = factory.createTreeFromText(R"(
//     <root main_tree_to_execute="MainTree" BTCPP_format="4">
//         <BehaviorTree ID="MainTree">
//             <Fallback name="root_fallback">
//                 <A/>
//                 <B/>
//             </Fallback>
//         </BehaviorTree>
//     </root>
// )");

    BTtoBuchiConverter converter;
    auto start = converter.toBuchi(tree.rootNode());
    std::cout << start->name_ << std::endl;
    auto next = start->transition(AP::FAILURE);
    // next = next->transition(AP::FAILURE);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::SUCCESS);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::FAILURE);
    std::cout << next->name_ << std::endl;
    next = next->transition(AP::SUCCESS);
    next = next->transition(AP::SUCCESS);
    std::cout << next->name_ << std::endl;



    return 0;
}
