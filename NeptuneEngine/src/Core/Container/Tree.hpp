/**
* @file Tree.hpp.
* @brief The Tree Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <memory>
#include <queue>

namespace Neptune {

    /**
    * @brief simple tree.
    * 
    * @tparam T specific stored type.
    */
    template<typename T>
    class Tree
    {
    private:

        /**
        * @brief Children node.
        */
        std::vector<std::unique_ptr<Tree>> m_Child {};

        /**
        * @brief This node stored data.
        */
        T m_Data;

        /**
        * @brief Mutex.
        */
        std::mutex m_Mutex {};

    public:

        /**
        * @brief Constructor Function.
        */
        Tree()
            : m_Data{}
        {}
        
        /**
        * @brief Constructor Function.
        *
        * @param[in] args T construct params.
        */
        template<typename ...Args>
        Tree(Args&&... args)
            : m_Data{ std::forward<Args>(args)... }
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Tree() = default;

        /**
        * @brief Add a child to this tree.
        * 
        * @param[in] args T construct params.
        * 
        * @return Returns child.
        */
        template<typename ...Args>
        Tree* AddChild(Args&&... args)
        {
            std::unique_lock lock(m_Mutex);
            
            m_Child.push_back(std::make_unique<Tree>(std::forward<Args>(args)...));

            return m_Child.back().get();
        }

        /**
        * @breif Visit this data.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void View(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::forward<Args>(args)...);
            
            std::invoke(visitor, m_Data);
        }

        /**
        * @breif Visit this data.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void View(F&& fn, Args&&...  args)
        {
            std::unique_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::forward<Args>(args)...);
            
            std::invoke(visitor, m_Data);
        }
        
        /**
        * @breif Visit child with DSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewDSF(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::placeholders::_2, std::forward<Args>(args)...);
            
            ViewDSFImpl(visitor, 0);
        }

        /**
        * @breif Visit child with DSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewDSF(F&& fn, Args&&...  args)
        {
            std::unique_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::placeholders::_2, std::forward<Args>(args)...);
            
            ViewDSFImpl(visitor, 0);
        }

        /**
        * @breif Visit child with WSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewWSF(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::placeholders::_2, std::forward<Args>(args)...);
            
            ViewWSFImpl(visitor);
        }

        /**
        * @breif Visit child with WSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewWSF(F&& fn, Args&&...  args)
        {
            std::unique_lock lock(m_Mutex);
            
            auto visitor = std::bind(std::forward<F>(fn), std::placeholders::_1, std::placeholders::_2, std::forward<Args>(args)...);
            
            ViewWSFImpl(visitor);
        }

        /**
        * @breif Set this node data.
        * 
        * @param[in] data The data.
        */
        void SetData(const T& data)
        {
            std::unique_lock lock(m_Mutex);
            
            m_Data = data;
        }

        /**
        * @breif Get this node data.
        *
        * @return Returns this node data.
        */
        [[nodiscard]] const T& GetData() const { return m_Data; }

    private:

        /**
        * @breif Visit child with DSF Implementation.
        *
        * @param[in] fn Visitor.
        * @param[in] depth Visitor depth.
        *
        * @return Returns true if needs to continue.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewDSFImpl(F&& fn, uint32_t depth);

        /**
        * @breif Visit child with WSF Implementation.
        *
        * @param[in] fn Visitor.
        *
        * @return Returns true if needs to continue.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewWSFImpl(F&& fn);
        
    };

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewDSFImpl(F&& fn, uint32_t depth)
    {
        if (!std::invoke(std::forward<F>(fn), m_Data, depth))
        {
            return false;
        }
        
        for (auto& child : m_Child)
        {
            if (!child->ViewDSFImpl(std::forward<F>(fn), depth + 1))
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewWSFImpl(F&& fn)
    {
        std::queue<std::pair<Tree*, uint32_t>> queue;

        queue.push({ this, 0 });

        while (!queue.empty())
        {
            auto [ node, depth ] = queue.front();
            queue.pop();      
            
            if (!std::invoke(std::forward<F>(fn), node->m_Data, depth))
            {
                return false;
            }
            
            for (auto& child : node->m_Child)
            {
                queue.push({ child.get(), depth + 1 });
            }
        }
        
        return true;
    }
}
