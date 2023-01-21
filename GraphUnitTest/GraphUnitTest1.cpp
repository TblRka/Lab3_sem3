#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\User\source\repos\TblRka\Lab3_sem3_test\DirectedGraph.h"
#include "C:\Users\User\source\repos\TblRka\Lab3_sem3_test\UndirectedGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphUnitTest
{
	TEST_CLASS(UndirectedGraphTest)
	{
	public:

		TEST_METHOD(get)
		{
			UndirectedGraph<int, int>* test_graph = new UndirectedGraph<int, int>();
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, 0);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, 0);
				}
			}

			Assert::IsTrue((test_graph->get_vertex_count()) == 150, L"Get vertex get test");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2, L"Get edge get test");

			delete test_graph;
		}

		TEST_METHOD(is_weight)
		{
			UndirectedGraph<int, int>* test_graph = new UndirectedGraph<int, int>();
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, 0);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, 0);
				}
			}

			Assert::IsTrue((test_graph->is_weighed()) == false, L"Is weighed");

			delete test_graph;
		}
			
		TEST_METHOD(erase)
		{
			UndirectedGraph<int, int>* test_graph = new UndirectedGraph<int, int>();
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, 0);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, 0);
				}
			}

			test_graph->erase_vertex(5);

			Assert::IsTrue((test_graph->get_vertex_count()) == 149, L"Get vertex erase test");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2 - 149, L"Get edge erase test");

			delete test_graph;
		}

		TEST_METHOD(min_path_weight)
		{
			UndirectedGraph<int, int>* test_graph = new UndirectedGraph<int, int>();
			for (int i = 1; i < 7; ++i)
			{
				test_graph->add_vertex(i);
			}

			test_graph->add_edge(1, 2, 12);
			test_graph->add_edge(2, 3, 1);
			test_graph->add_edge(1, 4, 5);
			test_graph->add_edge(4, 3, 10);
			test_graph->add_edge(6, 5, 2);
			test_graph->add_edge(5, 2, 1);
			test_graph->add_edge(1, 6, 7);

			Graph<int, int>::Path path;
			path.push_back(1, 6, 7);
			path.push_back(6, 5, 2);
			path.push_back(5, 2, 1);
			path.push_back(2, 3, 1);

			Assert::IsTrue((test_graph->min_path(1, 3)) == path, L"Dijkstra");

			delete test_graph;
		}

		TEST_METHOD(min_path_unweight)
		{
			UndirectedGraph<int, int>* test_graph = new UndirectedGraph<int, int>();
			for (int i = 1; i < 6; ++i)
			{
				test_graph->add_vertex(i);
			}

			test_graph->add_edge(1, 2);
			test_graph->add_edge(1, 3);
			test_graph->add_edge(2, 5);
			test_graph->add_edge(3, 4);
			test_graph->add_edge(4, 5);


			Graph<int, int>::Path path1;
			path1.push_back(1, 2);
			path1.push_back(2, 5);

			Graph<int, int>::Path res = test_graph->min_path(1, 5);
			Assert::IsTrue(path1 == res, L"DFS");

			delete test_graph;
		}
		
	};

	TEST_CLASS(DirectedGraphTest)
	{
	public:
		TEST_METHOD(get)
		{
			DirectedGraph<int, int>* test_graph = new DirectedGraph<int, int>();
			srand(time(NULL));
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, rand() % 100);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, rand() % 100);
				}
			}

			Assert::IsTrue((test_graph->get_vertex_count()) == 150, L"Get vertex 1");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2, L"Get edge 1");

			delete test_graph;
		}

		TEST_METHOD(is_weight)
		{
			DirectedGraph<int, int>* test_graph = new DirectedGraph<int, int>();
			srand(time(NULL));
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, rand() % 100);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, rand() % 100);
				}
			}

			Assert::IsTrue((test_graph->is_weighed()) == true, L"Is weighed");

			delete test_graph;
		}

		TEST_METHOD(erase)
		{
			DirectedGraph<int, int>* test_graph = new DirectedGraph<int, int>();

			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, 0);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, 0);
				}
			}

			test_graph->erase_vertex(5);

			Assert::IsTrue((test_graph->get_vertex_count()) == 149, L"Get vertex erase test");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2 - 149, L"Get edge erase test");

			delete test_graph;
		}

		TEST_METHOD(min_path_weight1)
		{
			DirectedGraph<int, int>* test_graph = new DirectedGraph<int, int>();
			for (int i = 1; i < 7; ++i)
			{
				test_graph->add_vertex(i);
			}

			test_graph->add_edge(1, 2, 12);
			test_graph->add_edge(2, 3, 1);
			test_graph->add_edge(1, 4, 5);
			test_graph->add_edge(4, 3, 10);
			test_graph->add_edge(6, 5, 2);
			test_graph->add_edge(2, 5, 1);
			test_graph->add_edge(1, 6, 7);

			Graph<int, int>::Path path;
			path.push_back(1, 2, 12);
			path.push_back(2, 3, 1);

			Assert::IsTrue((test_graph->min_path(1, 3)) == path, L"Dijkstra");

			delete test_graph;
		}
		TEST_METHOD(min_path_unweight1)
		{
			DirectedGraph<int, int>* test_graph = new DirectedGraph<int, int>();

			test_graph->add_edge(1, 2);
			test_graph->add_edge(1, 3);
			test_graph->add_edge(5, 2);
			test_graph->add_edge(3, 4);
			test_graph->add_edge(4, 5);


			Graph<int, int>::Path path1;
			path1.push_back(1, 3);
			path1.push_back(3, 4);
			path1.push_back(4, 5);

			Assert::IsTrue((test_graph->min_path(1, 5)) == path1, L"DFS");
			delete test_graph;
		}

	};
}