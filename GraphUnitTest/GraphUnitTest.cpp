#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\User\source\repos\TblRka\Lab3_sem3_test\DirectedGraph.h"
#include "C:\Users\User\source\repos\TblRka\Lab3_sem3_test\UndirectedGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphUnitTest
{
	TEST_CLASS(GraphUnitTest)
	{
	public:
		
		TEST_METHOD(UnderectedGraphTest)
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

			Assert::IsTrue((test_graph->get_vertex_count()) == 150, L"Get vertex 1");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2, L"Get edge 1");

			test_graph->erase_vertex(5);

			Assert::IsTrue((test_graph->get_vertex_count()) == 149, L"Get vertex 2");
			Assert::IsTrue((test_graph->get_edge_count()) == 150 * (150 - 1) / 2 - 149, L"Get edge 2");

			Assert::IsTrue((test_graph->is_weighed()) == false, L"Is weighed");


		}

		TEST_METHOD(DirectedGraphTest)
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
		}
	};
}
