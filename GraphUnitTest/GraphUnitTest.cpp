#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\User\source\repos\TblRka\Lab3_sem3_test\Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphUnitTest
{
	TEST_CLASS(GraphUnitTest)
	{
	public:
		
		TEST_METHOD(GraphTest)
		{
			Graph<int, int>* test_graph = new Graph<int, int>();
			for (int i = 1; i < 151; i++)
			{
				test_graph->add_vertex(i, 0);
				for (int j = 1; j < i; j++)
				{
					test_graph->add_edge(j, i, 0);
				}
			}

		}
	};
}
