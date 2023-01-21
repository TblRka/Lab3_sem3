#include "Graph.h"

template <class TV, class TE>
class UndirectedGraph : public Graph<TV, TE> {
private:
	using Path = typename Graph<TV, TE>::Path;

	Path bfs(size_t from, size_t to) 
	{
		Path path;
		std::queue<size_t> q;
		std::unordered_map<size_t, bool> checked(Graph<TV, TE>::vertex_count);
		std::unordered_map<size_t, size_t> parents(Graph<TV, TE>::vertex_count);
		q.push(from);
		parents[from] = 0;
		checked[from] = true;
		while (!q.empty()) 
		{
			size_t vert = q.front();
			if (vert == to) 
			{
				break;
			}
			q.pop();
			for (auto it = Graph<TV, TE>::incidence_list[vert].begin(); it != Graph<TV, TE>::incidence_list[vert].end(); it++) 
			{
				if (checked.find(it->id_from) == checked.end()) 
				{
					checked[it->id_from] = true;
					q.push(it->id_from);
					parents[it->id_from] = vert;
				}
				else if (checked.find(it->id_to) == checked.end()) 
				{
					checked[it->id_to] = true;
					q.push(it->id_to);
					parents[it->id_to] = vert;
				}
			}
		}
		if (checked.find(to) == checked.end()) 
		{
			return path;
		}
		size_t child = to;
		size_t cur_parent = parents[child];
		while (cur_parent != 0) {
			for (auto it = Graph<TV, TE>::incidence_list[child].begin(); it != Graph<TV, TE>::incidence_list[child].end(); it++) 
			{
				if (cur_parent == it->id_from || cur_parent == it->id_to) 
				{
					path.push_front(*it);
					break;
				}
			}
			child = cur_parent;
			cur_parent = parents[cur_parent];
		}
		return path;
	}

	Path dijkstra(size_t from, size_t to) 
	{
		Path res;
		sup<TE> inf;
		std::unordered_map<size_t, bool> checked;
		std::unordered_map<size_t, TE> dist;
		std::unordered_map<size_t, size_t> parents;
		std::unordered_map<Pair<size_t, size_t>, TE, pair_hash<size_t>, pair_unord_equal<size_t>> edges;
		checked.reserve(Graph<TV, TE>::vertex_count);
		dist.reserve(Graph<TV, TE>::vertex_count);
		parents.reserve(Graph<TV, TE>::vertex_count);
		edges.reserve(Graph<TV, TE>::edge_count);
		for (auto el = Graph<TV, TE>::vertexes.begin(); el != Graph<TV, TE>::vertexes.end(); el++) 
		{
			checked[el->second.id] = false;
			dist[el->second.id] = inf();
			parents[el->second.id] = 0;
		}
		dist[from] = TE();
		parents[from] = from;
		for (size_t i = 0; i < Graph<TV, TE>::vertex_count; ++i) 
		{
			size_t v = 0;
			for (auto it = Graph<TV, TE>::vertexes.cbegin(); it != Graph<TV, TE>::vertexes.cend(); it++) 
			{
				if (!checked[it->second.id] && (v == 0 || dist[it->second.id] < dist[v])) 
				{
					v = it->second.id;
				}
			}
			if (dist[v] == inf()) 
			{
				break;
			}
			checked[v] = true;
			for (auto it = Graph<TV, TE>::incidence_list[v].cbegin(); it != Graph<TV, TE>::incidence_list[v].cend(); it++) 
			{
				size_t v1 = 0;
				if (v == it->id_from) 
				{
					v1 = it->id_to;
				}
				else 
				{
					v1 = it->id_from;
				}
				TE len = it->value;
				if (dist[v] + len < dist[v1])
				{
					dist[v1] = dist[v] + len;
					parents[v1] = v;
				}
				edges[Pair<size_t, size_t>{v, v1}] = len;
			}
		}
		if (dist[to] == inf()) 
		{
			return res;
		}
		size_t i = to;
		size_t p = parents[i];
		while (p != from) 
		{
			res.push_front(p, i, edges[Pair<size_t, size_t>{p, i}]);
			i = p;
			p = parents[i];
		}
		res.push_front(p, i, edges[Pair<size_t, size_t>{p, i}]);
		return res;
	}
public:
	void erase_edge(size_t from, size_t to, TE _value = TE());

	Path min_path(size_t from, size_t to) 
	{
		if (Graph<TV, TE>::weighed) 
		{
			return dijkstra(from, to);
		}
		return bfs(from, to);
	}
};



template <class TV, class TE>
void UndirectedGraph<TV, TE>::erase_edge(size_t from, size_t to, TE _value) 
{
	if (Graph<TV, TE>::vertexes.find(from) == Graph<TV, TE>::vertexes.end()) 
	{
		return;
	}
	if (Graph<TV, TE>::vertexes.find(to) == Graph<TV, TE>::vertexes.end()) 
	{
		return;
	}
	for (auto it = Graph<TV, TE>::incidence_list[from].begin(); it != Graph<TV, TE>::incidence_list[from].end(); ) 
	{
		if (((it->id_from == from && it->id_to == to) || (it->id_from == to && it->id_to == from)) && it->value == _value) 
		{
			it = Graph<TV, TE>::incidence_list[from].erase(it);
			Graph<TV, TE>::edge_count--;
		}
		else 
		{
			it++;
		}
	}
	for (auto it = Graph<TV, TE>::incidence_list[to].begin(); it != Graph<TV, TE>::incidence_list[to].end(); ) 
	{
		if (((it->id_from == from && it->id_to == to) || (it->id_from == to && it->id_to == from)) && it->value == _value) 
		{
			it = Graph<TV, TE>::incidence_list[to].erase(it);
		}
		else 
		{
			it++;
		}
	}
}