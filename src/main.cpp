#include <behaviortree_cpp/bt_factory.h>
#include <iostream>
#include <spot/tl/parse.hh>
#include <spot/tl/formula.hh>
#include <thread>
#include <chrono>

int main() {
    // -------------------------
    // BehaviorTree.CPP test
    // -------------------------
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleAction("HelloWorld",
        [](BT::TreeNode&) -> BT::NodeStatus {
            std::cout << "Hello from BehaviorTree node!" << std::endl;
            return BT::NodeStatus::SUCCESS;
        });

    auto tree = factory.createTreeFromText(R"(
        <root main_tree_to_execute="MainTree">
            <BehaviorTree ID="MainTree">
                <HelloWorld/>
            </BehaviorTree>
        </root>
    )");

    // Tick the tree
    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    while (status == BT::NodeStatus::RUNNING) {
        status = tree.rootNode()->executeTick();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << "BehaviorTree status: " << static_cast<int>(status) << std::endl;

    // -------------------------
    // LTL formula for the behavior
    // -------------------------
    // Map HelloWorld node to atomic proposition "hello"
    std::string ltl_formula = "G hello"; // HelloWorld always succeeds

    spot::parsed_formula pf = spot::parse_infix_psl(ltl_formula);

    if (!pf.errors.empty()) {
        std::cerr << "Spot parse errors:\n";
        for (const auto& err : pf.errors) {
            const auto& loc = err.first;
            const auto& msg = err.second;
            std::cerr << "  at " << loc << ": " << msg << "\n";
        }
        return 1;
    }

    spot::formula f = pf.f;

    std::cout << "Parsed LTL formula with Spot: " << f << std::endl;

    return 0;
}


// #include <behaviortree_cpp/bt_factory.h>
// #include <iostream>
// #include <spot/tl/parse.hh>
// #include <spot/tl/formula.hh>
// #include <thread>
// #include <chrono>

// int main() {
//     // -------------------------
//     // BehaviorTree.CPP test
//     // -------------------------
//     BT::BehaviorTreeFactory factory;

//     factory.registerSimpleAction("HelloWorld",
//         [](BT::TreeNode&) -> BT::NodeStatus {
//             std::cout << "Hello from BehaviorTree node!" << std::endl;
//             return BT::NodeStatus::SUCCESS;
//         });

//     auto tree = factory.createTreeFromText(R"(
//         <root main_tree_to_execute="MainTree">
//             <BehaviorTree ID="MainTree">
//                 <HelloWorld/>
//             </BehaviorTree>
//         </root>
//     )");

//     // Tick the tree
//     BT::NodeStatus status = BT::NodeStatus::RUNNING;
//     while (status == BT::NodeStatus::RUNNING) {
//         status = tree.rootNode()->executeTick();
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//     }

//     std::cout << "BehaviorTree status: " << static_cast<int>(status) << std::endl;

//     // -------------------------
//     // Spot test
//     // -------------------------
//     std::string ltl_formula = "G !a";

//     spot::parsed_formula pf = spot::parse_infix_psl(ltl_formula);

//     // Print errors properly
//     if (!pf.errors.empty()) {
//         std::cerr << "Spot parse errors:\n";
//         for (const auto& err : pf.errors) {
//             const auto& loc = err.first;
//             const auto& msg = err.second;
//             std::cerr << "  at " << loc << ": " << msg << "\n";
//         }
//         return 1;
//     }

//     spot::formula f = pf.f;

//     std::cout << "Parsed LTL formula with Spot: " << f << std::endl;

//     return 0;
// }
