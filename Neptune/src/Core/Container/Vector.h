/**
* @file Vector.h.
* @brief The Vector Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

namespace Neptune::Container {

	/**
	* @brief This Class is similar to std::vector
	* The difference between that is this one allocates memory by malloc rather than new.
	* This is important is ObjectPool.
	*/
	template<typename T>
	class Vector
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Vector();

		/**
		* @brief Destructor Function.
		*/
		virtual ~Vector();

		/**
		* @brief Get vector Begin Pointer.
		* 
		* @return Return vector Begin Pointer.
		*/
		T* Begin() const { return m_Begin; }

		/**
		* @brief Get vector End Pointer.
		* 
		* @return Return vector End Pointer.
		*/
		T* End() const { return m_End; }

		/**
		* @brief Get vector size.
		* 
		* @return Returns vector size.
		*/
		size_t Size() const { return m_UseCount; }

		/**
		* @brief Determine if vector is empty.
		* 
		* @retrun Returns true if empty.
		*/
		bool Empty() const { return m_UseCount == 0; }

		/**
		* @brief Push an element in the end of vector.
		* 
		* @param[in] element .
		*/
		void PushBack(const T& element);

		/**
		* @brief Get element by index.
		* 
		* @param[in] index .
		* 
		* @return Returns element.
		*/
		T& Get(size_t index);

	private:
		
		T* m_Begin;              // @brief Vector Begin Pointer.
		T* m_End;                // @brief Vector End Pointer.
		size_t m_UseCount;       // @brief vector used size.
		size_t m_SpareCount;     // @brief vector spare count.
		size_t m_ExpandRate;     // @brief Vector expand rate.
	};

	template<typename T>
	inline Vector<T>::Vector()
		: m_Begin(nullptr)
		, m_End(nullptr)
		, m_UseCount(0)
		, m_SpareCount(0)
		, m_ExpandRate(2)
	{}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		if (m_UseCount == 0) return;
		
		free(m_Begin);
	}

	template<typename T>
	inline void Vector<T>::PushBack(const T& element)
	{
		if (m_SpareCount != 0)
		{
			*m_End = element;

			++m_UseCount;
			--m_SpareCount;
			++m_End;
		}
		else
		{
			if (m_UseCount == 0)
			{
				const size_t bytes = sizeof(T) * m_ExpandRate;

				m_UseCount   = 1;
				m_SpareCount = m_ExpandRate - 1;

				m_Begin      = static_cast<T*>(malloc(bytes));
						     
				m_End        = m_Begin;
				*m_End       = element;
				++m_End;
			}
			else
			{
				T*    om           = m_Begin;
				const size_t ob    = sizeof(T) * m_UseCount;
				const size_t nb    = sizeof(T) * m_UseCount * m_ExpandRate;
				m_SpareCount       = (nb - ob) / sizeof(T);
      
				m_Begin            = static_cast<T*>(malloc(nb));
				memset(m_Begin, 0, nb);
				memcpy(m_Begin, om, ob);

				m_End              = reinterpret_cast<T*>(reinterpret_cast<char*>(m_Begin) + ob);
				*m_End             = std::move(element);

				++m_UseCount;
				--m_SpareCount;
				++m_End;

				free(om);
			}
		}
	}

	template<typename T>
	inline T& Vector<T>::Get(size_t index)
	{
		assert(index < m_UseCount);

		return *(reinterpret_cast<T*>(reinterpret_cast<char*>(m_Begin) + sizeof(T) * index));
	}
}