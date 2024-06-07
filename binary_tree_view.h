#include<stack>
namespace Yc{
template<class value_type, class tree_node_type>
class binary_tree_view
{
	tree_node_type* root;
	class pre_order_view :std::ranges::view_interface<pre_order_view>
	{
		tree_node_type* root;
		class iterator
		{
			std::stack<tree_node_type*>st;
			//enum current_t:class unsigned char
			//{
			//	left, right;
			//}current;
		public:
			iterator(tree_node_type* root) /*current{left}*/
			{
				st.push(root);
			}
			iterator(const iterator&) = default;
			iterator(iterator&&) = default;
			value_type& operator*()const
			{
				return st.top()->val;
			}
			iterator& operator++()
			{
				if (st.top()->left != nullptr)
				{
					st.push(st.top()->left);
				}
				else
					if (st.top()->right != nullptr)
					{
						st.push(st.top()->right);
					}
					else
					{
						do
						{
							tree_node_type* tmp1 = st.top();
							st.pop();
							if (st.empty())
							{
								break;
							}
							if (st.top()->left == tmp1)
							{
								if (st.top()->right != nullptr)
								{
									st.push(st.top()->right);
									break;
								}
							}
						} while (true);
					}
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			bool operator==(std::default_sentinel_t)
			{
				return st.empty();
			}
		};
	public:
		pre_order_view(tree_node_type* root) :root{ root }
		{
		}
		iterator begin()const
		{
			return { root };
		}
		std::default_sentinel_t end()const
		{
			return {};
		}
	};
	class in_order_view :std::ranges::view_interface<in_order_view>
	{
		tree_node_type* root;
		class iterator
		{
			std::stack<tree_node_type*>st;
			//enum current_t:class unsigned char
			//{
			//	left, right;
			//}current;
		public:
			iterator(tree_node_type* root) /*current{left}*/
			{
				while (root->left!=nullptr)
				{
					st.push(root);
					root = root->left;
				}
				st.push(root);
			}
			iterator(const iterator&) = default;
			iterator(iterator&&) = default;
			value_type& operator*()const
			{
				return st.top()->val;
			}
			iterator& operator++()
			{
				if (st.top()->right != nullptr)
				{
					st.push(st.top()->right);
					while (st.top()->left!=nullptr)
					{
						st.push(st.top()->left);
					}
				}
				else
				{
					loop:
					tree_node_type* tmp = st.top();
					st.pop();
					if (!st.empty())
					{
						if (st.top()->right == tmp)goto loop;
					}
				}
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			bool operator==(std::default_sentinel_t)
			{
				return st.empty();
			}
		};
	public:
		in_order_view(tree_node_type* root) :root{ root }
		{
		}
		iterator begin()const
		{
			return { root };
		}
		std::default_sentinel_t end()const
		{
			return {};
		}
	};
	class post_order_view :std::ranges::view_interface<post_order_view>
	{
		tree_node_type* root;
		class iterator
		{
			std::stack<tree_node_type*>st;
		public:

			bool operator==(const iterator&)const = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&)noexcept = default;
			iterator():st {}
			{}
			iterator(tree_node_type* root) /*current{left}*/
			{
				loop:
				while (root->left != nullptr)
				{
					st.push(root);
					root = root->left;
				}
				st.push(root);
				if (root->right != nullptr)
				{
					/*st.push(root->right);*/
					root = root->right;
					goto loop;
				}
			}
			iterator(const iterator&) = default;
			iterator(iterator&&)noexcept = default;
			value_type& operator*()const
			{
				return st.top()->val;
			}
			value_type* operator->()const
			{
				return &(st.top()->val);
			}
			iterator& operator++()
			{
				tree_node_type* tmp = st.top();
				st.pop();
				if (!st.empty())
				{
					if (tmp == st.top()->left)
					{
						if (st.top()->right != nullptr)
						{
							auto root = st.top()->right;
						loop:
							while (root->left != nullptr)
							{
								st.push(root);
								root = root->left;
							}
							st.push(root);
							if (root->right != nullptr)
							{
								root = root->right;
								goto loop;
							}
						}
					}
				}
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			bool operator==(std::default_sentinel_t)
			{
				return st.empty();
			}
		};
	public:
		post_order_view(tree_node_type* root) :root{ root }
		{
		}
		iterator begin()const
		{
			return { root };
		}
		std::default_sentinel_t end()const
		{
			return {};
		}
	};
public:
	binary_tree_view(tree_node_type* root) :root{ root }
	{
	}
	pre_order_view pre_order()const
	{
		return { root };
	}
	in_order_view in_order()const
	{
		return { root };
	}
	post_order_view post_order()const
	{
		return { root };
	}
};
}
