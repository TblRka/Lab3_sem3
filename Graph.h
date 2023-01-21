#ifndef GRAPH_H_LAB3_SEM3
#define GRAPH_H_LAB3_SEM3

#include <limits>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include "Pair.h"
#include "sup.h"

template <class TV, class TE>
class Graph 
{
    //friend class MainWindow;
protected:
	struct Vertex 
	{
		TV value = TV();
		size_t id = 0;

		Vertex() {}

		Vertex(size_t _id, const TV& _value) 
		{
			value = _value;
			id = _id;
		}

		Vertex(const Vertex& another)
		{
			value = another.value;
			id = another.id;
		}

		Vertex& operator=(const Vertex& another) 
		{
			value = another.value;
			id = another.id;
			return *this;
		}

		~Vertex() = default;

		bool operator==(const Vertex& v) 
		{
			if (id == v.id && value == v.value)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Vertex& v) 
		{
			return !(*this == v);
		}
	};

	struct Edge 
	{
		TE value = TE();
		size_t id_from = 0;
		size_t id_to = 0;

		Edge() {}

		Edge(size_t from, size_t to, const TE& _value) 
		{
			value = _value;
			id_from = from;
			id_to = to;
		}

		Edge(const Edge& another) 
		{
			value = another.value;
			id_from = another.id_from;
			id_to = another.id_to;
		}

		Edge& operator=(const Edge& another) 
		{
			value = another.value;
			id_from = another.id_from;
			id_to = another.id_to;
			return *this;
		}

		~Edge() = default;

		bool operator==(const Edge& e) 
		{
			if (value == e.value && id_from == e.id_from && id_to == e.id_to) 
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Edge& e) 
		{
			return !(*this == e);
		}
	};

	std::unordered_map<size_t, std::vector<Edge>> incidence_list;
	std::unordered_map<size_t, Vertex> vertexes;
	//size_t vertex_count = 0;
	size_t edge_count = 0;
	bool weighed = false;

public:

	class Path 
	{
	private:

		std::list<Edge> seq;

	public:
		Path() = default;

		Path(const Path& another) 
		{
			seq = another.seq;
		}

		~Path() = default;

		Path& operator=(const Path& another) 
		{
			seq = another.seq;
			return *this;
		}

		void push_front(const Edge& edge) 
		{
			seq.push_front(edge);
		}

		void push_front(size_t from, size_t to, TE _value = TE()) 
		{
			Edge edge(from, to, _value);
			seq.push_front(edge);
		}

		void push_back(const Edge& edge) 
		{
			seq.push_back(edge);
		}

		void push_back(size_t from, size_t to, TE _value = TE()) 
		{
			Edge edge(from, to, _value);
			seq.push_back(edge);
		}

		void erase(const Edge& edge) 
		{
			for (auto it = seq.begin(); it != seq.end(); ) 
			{
				if ((*it) == edge) 
				{
					it = seq.erase(it);
					break;
				}
				else 
				{
					it++;
				}
			}
		}

        void clear() 
		{
            seq.clear();
        }

        Edge operator[](size_t index) 
		{
            size_t i = 0;
            auto it = seq.cbegin();
            while (i < index) 
			{
                it++;
                i++;
            }
            return *it;
        }

        bool empty() 
		{
			if (seq.size())
			{
				return true;
			}
            return false;
        }

        size_t size() 
		{
            return seq.size();
        }

		bool operator==(const Path& path) 
		{
			if (seq.size() != path.seq.size()) 
			{
				return false;
			}
			auto it2 = path.seq.cbegin();
			for (auto it1 = seq.cbegin(); it1 != seq.cend(); it1++) 
			{
				if (*it1 != *it2) 
				{
					return false;
				}
				it2++;
			}
			return true;
		}

		bool operator!=(const Path& path) 
		{
			return !(*this != path);
		}

		
	};
	Graph() = default;
	~Graph() = default;

	void add_vertex(size_t _id, TV _value = TV());//+
	void add_edge(size_t from, size_t to, TE _value = TE());//+
	void erase_vertex(size_t _id);//+
    void clear();//+

	size_t get_vertex_count() const;//+
	size_t get_edge_count() const;//+

	bool is_weighed() const;//+

};

template <class TV, class TE>
void Graph<TV, TE>::add_vertex(size_t _id, TV _value) 
{
	if (incidence_list.empty()) 
	{
		incidence_list.reserve(10);
		vertexes.reserve(10);
	}
	if (_id <= 0) 
	{
        //throw std::exception("Inappropriate id");
        return;
	}
	if (incidence_list.find(_id) != incidence_list.end()) 
	{
        //throw std::exception("Such vertex exists");
        return;
	}
	Vertex vertex(_id, _value);
	incidence_list[_id] = std::vector<Edge>();
	vertexes[_id] = vertex;
	//vertex_count++;
}

template <class TV, class TE>
void Graph<TV, TE>::add_edge(size_t from, size_t to, TE _value) 
{
	if (incidence_list.empty()) 
	{
		incidence_list.reserve(10);
		vertexes.reserve(10);
	}
	Vertex vf(from, TV());
	Vertex vt(to, TV());
	if (from <= 0) 
	{
        //throw std::exception("Inappropriate id");
	}
	if (to <= 0) 
	{
        //throw std::exception("Inappropriate id");
	}
	if (vertexes.find(from) == vertexes.end()) 
	{
		vertexes[from] = vf;
		//vertex_count++;
 	}
	if (vertexes.find(to) == vertexes.end()) 
	{
		vertexes[to] = vt;
		//vertex_count++;
	}
	incidence_list[from].push_back(Edge(from, to, _value));
	if (from != to) 
	{
		incidence_list[to].push_back(Edge(from, to, _value));
	}
	if (_value != TE() && !weighed) 
	{
		weighed = true;
	}
	edge_count++;
}

template <class TV, class TE>
void Graph<TV, TE>::erase_vertex(size_t _id) 
{
	if (vertexes.find(_id) == vertexes.end()) 
	{
		return;
	}
	edge_count -= incidence_list[_id].size();
	//vertex_count--;
	incidence_list.erase(incidence_list.find(_id));
	vertexes.erase(vertexes.find(_id));

	for (auto elem = incidence_list.begin(); elem != incidence_list.end(); elem++) 
	{
		for (auto itv = elem->second.begin(); itv != elem->second.end(); ) 
		{
			if (itv->id_from == _id || itv->id_to == _id) 
			{
				itv = elem->second.erase(itv);
			}
			else 
			{
				itv++;
			}
		}
	}
}

template <class TV, class TE>
void Graph<TV, TE>::clear() 
{
    for (auto it = incidence_list.begin(); it != incidence_list.end(); it++) 
	{
        it->second.clear();
    }
    incidence_list.clear();
    vertexes.clear();
    //vertex_count = 0;
    edge_count = 0;
    weighed = false;
}

template <class TV, class TE>
size_t Graph<TV, TE>::get_vertex_count() const 
{
	return vertexes.size();
}

template <class TV, class TE>
size_t Graph<TV, TE>::get_edge_count() const 
{
	return edge_count;
}

template <class TV, class TE>
bool Graph<TV, TE>::is_weighed() const 
{
	return weighed;
}

#endif
