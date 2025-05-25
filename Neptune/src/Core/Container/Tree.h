/**
* @file Tree.h.
* @brief The Tree Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <memory>

namespace Neptune {

    /**
    * @brief simple tree.
    * @tparam T specific stored type.
    */
    template<typename T>
    class Tree
    {
    private:

        /**
        * @brief Children node.
        */
        std::vector<std::unique_ptr<Tree>> m_Child;

        /**
        * @brief This node stored data.
        */
        T m_Data;

    public:

        /**
        * @brief Constructor Function.
        */
        template<typename ...Args>
        Tree(Args&&... args)
                : m_Data{ std::forward<Args>(args)... }
                , m_Childs{}
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Tree() = default;

        /**
        * @brief Add a child to this tree.
        * @param[in] args T construct params.
        */
        template<typename ...Args>
        Tree* AddChild(Args&&... args)
        {
            m_Childs.push_back(std::make_unique<tree>(std::forward<Args>(args)...));

            return m_Childs.back().get();
        }

        /**
        * @brief Get all this node children.
        * @return Returns all this node children.
        */
        const std::vector<std::unique_ptr<Tree>>& GetChild() const { return m_Child; }

        /**
        * @breif Get this node data.
        * @return Returns this node data.
        */
        T& GetData() { return m_Data; }
    };
}