#include <iostream>
#include <list>

class BehaviourTree
{
public:
	class Node
	{
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node
	{
	public:
		const std::list<Node*>& getChildren() const
		{
			return m_children;
		}

		void addChild(Node* t_child)
		{
			m_children.emplace_back(t_child);
		}
	private: 
		std::list<Node*> m_children;
	};

	class Selector : public CompositeNode
	{
	public:
		virtual bool run()
		{
			for (Node* child : getChildren())
			{
				if (child->run())
				{
					return true;
				}
			}
			return false;
		}
	};

	class Sequence : public CompositeNode
	{
	public:
		virtual bool run()
		{
			for (Node* child : getChildren())
			{
				if (!child->run())
				{
					return false;
				}
			}
			return true;
		}
	};

	class Root : public Node
	{
	public:
		Node* m_child;
		void setChild(Node* t_newChild)
		{
			m_child = t_newChild;
		}
		virtual bool run()
		{
			return m_child->run();
		}
	};
private:
	Root* m_root;
public:
	BehaviourTree() : m_root(new Root()) {};
	~BehaviourTree() {};
	void setRootChild(Node* rootChild)
	{
		m_root->setChild(rootChild);
	}
	bool run() const
	{
		return m_root->run();
	}
};