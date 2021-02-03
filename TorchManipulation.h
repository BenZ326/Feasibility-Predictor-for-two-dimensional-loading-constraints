#pragma once
#include <list>
#include <torch/script.h>

class Rectangle;
namespace ml
{
	torch::Tensor TransItemsTensor(const std::list<const Rectangle*>& t_rectanlges);
	torch::Tensor ExtractFeatures(const std::list<const Rectangle*>& t_rectangles);
	class MLModelsContainer
	{
	public:
		static torch::jit::script::Module FC;
	};
};